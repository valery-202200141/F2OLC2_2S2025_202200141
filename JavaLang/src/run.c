#include "../include/runtime.h"
#include "../include/ast.h"
#include "../include/gui.h"
#include "../include/semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h> 

#ifndef TYPE_INT
#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_STRING 2
#define TYPE_BOOLEAN 3
#define TYPE_DOUBLE 4
#endif

static ConsolePrintCallback console_callback = NULL;

// Nombre que espera la GUI: guarda el callback
void set_console_print_safe(ConsolePrintCallback callback) {
    console_callback = callback;
}

// Helper que invoca el callback o hace fallback a stdout
static void console_invoke(const char *msg) {
    if (!msg) return;
    if (console_callback) console_callback(msg);
    else printf("%s", msg);
}

// ----------------- Separación OUTPUT vs DEBUG -----------------
static int runtime_debug_enabled = 0; // por defecto apagado
static int runtime_break_flag = 0;
static int runtime_continue_flag = 0;

void set_runtime_debug(int enabled) {
    runtime_debug_enabled = enabled;
}

// Salida del programa (System.out.println) -> se muestra siempre en la consola GUI
void console_print_program(const char *msg) {
    if (!msg) return;
    if (console_callback) console_callback(msg);
    else printf("%s", msg);
}

// Mensajes internos / depuración -> solo si runtime_debug_enabled == 1
void runtime_log(const char *msg) {
    if (!msg) return;
    if (!runtime_debug_enabled) return;
    if (console_callback) console_callback(msg);
    else printf("%s", msg);
}

// Tabla de símbolos para variables
typedef struct runtime_symbol {
    char *name;
    int type;  // 0=int, 1=float, 2=string, 3=boolean, 4=double
    union {
        int int_val;
        float float_val;
        double double_val;
        char *string_val;
        int bool_val;
        void *array_val;
    } value;
    struct runtime_symbol *next;
} runtime_symbol_t;

static runtime_symbol_t *symbol_table = NULL;

// Tabla de arrays en tiempo de ejecución
typedef struct {
    int elem_type; // usar códigos compatibles con sym.type o semantic types
    int length;
    int *ints;     // por ahora solo soporte int[]
} runtime_array_t;

#define TYPE_ARRAY_INT 100

typedef struct array_map {
    ast_node *expr;
    runtime_array_t *arr;
    struct array_map *next;
} array_map_t;
static array_map_t *array_map_head = NULL;

// Declaraciones forward
void show_symbol_table(void);
void cleanup_runtime(void);
int is_string_expression(ast_node *node);     
char* get_string_value(ast_node *node);   
void convert_symbol_to_string(runtime_symbol_t *sym, char *str);
void convert_to_string(ast_node *node, char *str);
void build_concatenated_string(ast_node *expr, char *result);
//auxiliares 
int builtin_invoke_int(const char *fullname, ast_node *arg, int *out_int);
int builtin_invoke_double(const char *fullname, ast_node *arg, double *out_double);
char* builtin_invoke_string(const char *fullname, ast_node *arg);
int builtin_dispatch(const char *fullname, struct ast_node *arg, int *out_int, double *out_double, char **out_str);
static int handle_increment_decrement(ast_node *expr, int delta, int is_post);
static double eval_node_as_double(ast_node *n);
static int node_is_floatish(ast_node *n);
static int node_is_boolean_expression(ast_node *n);

// Función simplificada para buscar el método main
ast_node* find_main_method(ast_node *program_node) {
    if (!program_node) return NULL;

    // Si ya es MAIN, devolverlo
    if (program_node->type == AST_MAIN_FUNCTION) return program_node;

    // Si es AST_PROGRAM y contiene function_def.body que es MAIN, devolver ese MAIN
    if (program_node->type == AST_PROGRAM && program_node->data.function_def.body) {
        if (program_node->data.function_def.body->type == AST_MAIN_FUNCTION) {
            return program_node->data.function_def.body;
        }
        // Si el body es una lista de statements, no hay nodo MAIN separado:
        // devolver el body (lista de statements) para ejecutar solo una vez.
        return program_node->data.function_def.body;
    }

    // Fallback: devolver el nodo raíz
    return program_node;
}

// Función para buscar/crear variables en la tabla de símbolos
runtime_symbol_t* find_or_create_symbol(const char *name) {
    runtime_symbol_t *current = symbol_table;
    
    // Buscar si ya existe
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    
    // Crear nuevo símbolo (tipo desconocido hasta que se declare)
    runtime_symbol_t *new_symbol = malloc(sizeof(runtime_symbol_t));
    new_symbol->name = strdup(name);
    new_symbol->type = -1; // -1 = unknown
    new_symbol->value.int_val = 0;
    new_symbol->value.string_val = NULL;
    new_symbol->value.array_val = NULL;
    new_symbol->next = symbol_table;
    symbol_table = new_symbol;
    
    return new_symbol;
}



// ----------------- Helpers / builtins mínimos -----------------

static int handle_increment_decrement(ast_node *expr, int delta, int is_post) {
    if (!expr->data.op.left || expr->data.op.left->type != AST_VARIABLE) {
        return evaluate_expression(expr->data.op.left);
    }
    
    runtime_symbol_t *sym = find_or_create_symbol(expr->data.op.left->data.var_name);
    int old_value = 0;
    
    switch (sym->type) {
        case 0: // int
            old_value = sym->value.int_val;
            sym->value.int_val += delta;
            return is_post ? old_value : sym->value.int_val;
            
        case 1: // float
            old_value = (int)sym->value.float_val;
            sym->value.float_val += delta;
            return is_post ? old_value : (int)sym->value.float_val;
            
        case 4: // double
            old_value = (int)sym->value.double_val;
            sym->value.double_val += delta;
            return is_post ? old_value : (int)sym->value.double_val;
            
        default:
            return evaluate_expression(expr->data.op.left);
    }
}


char *runtime_eval_as_string(struct ast_node *arg) {
    static char buf[1024];
    if (!arg) { buf[0]='\0'; return buf; }

    if (arg->type == AST_STRING_LITERAL) {
        strncpy(buf, arg->data.string_value ? arg->data.string_value : "", sizeof(buf)-1);
        buf[sizeof(buf)-1] = '\0';
        return buf;
    }

    // Intentar usar get_string_value si existe
    #ifdef HAVE_GET_STRING_VALUE
    char *s = get_string_value(arg);
    if (s) {
        strncpy(buf, s, sizeof(buf)-1);
        buf[sizeof(buf)-1] = '\0';
        return buf;
    }
    #endif

    // Fallback: evaluar como número/boolean y convertir a string
    {
        int v = 0;
        // evita llamada recursiva infinita si evaluate_expression usa runtime_eval_as_string
        v = evaluate_expression(arg);
        snprintf(buf, sizeof(buf), "%d", v);
        return buf;
    }
}

int builtin_dispatch(const char *fullname, struct ast_node *arg, int *out_int, double *out_double, char **out_str) {
    if (!fullname) return -1;

    // Integer.parseInt
    if ((strcmp(fullname, "Integer.parseInt") == 0 || strcmp(fullname, "Integer.parse_int") == 0) && out_int) {
        Char *s = runtime_eval_as_string(arg);
        if (!s) { *out_int = 0; return 0; }
        char *endptr = NULL;
        long val = strtol(s, &endptr, 10);
        if (endptr == s || *endptr != '\0') {
            // parse error -> log and keep 0
            char msg[256];
            snprintf(msg, sizeof(msg), "⚠️ Integer.parseInt error: '%s' no es entero válido\n", s);
            runtime_log(msg);
            *out_int = 0;
            return -2; // indicar fallo de parse
        }
        *out_int = (int)val;
        return 0;
    }

    // Double.parseDouble
    if ((strcmp(fullname, "Double.parseDouble") == 0 || strcmp(fullname, "Double.parse_double") == 0) && out_double) {
        if ((strcmp(fullname, "Double.parseDouble") == 0 || strcmp(fullname, "Double.parse_double") == 0) && out_double) {
        char *s = runtime_eval_as_string(arg);
        if (!s) { *out_double = 0.0; return 1; }
        char *endptr = NULL;
        double dv = strtod(s, &endptr);
        if (endptr == s || *endptr != '\0') {
            char msg[256];
            snprintf(msg, sizeof(msg), "⚠️ Double.parseDouble error: '%s' no es double válido\n", s);
            runtime_log(msg);
            *out_double = 0.0;
            return -2;
        }
        *out_double = dv;
        return 1;
    }

    // String.valueOf
    if ((strcmp(fullname, "String.valueOf") == 0 || strcmp(fullname, "String.value_of") == 0) && out_str) {
        char *s = runtime_eval_as_string(arg);
        *out_str = strdup(s ? s : "");
        return 2;
    }

    return -1;
}

static runtime_array_t *runtime_array_new_empty(int elem_type, int size) {
    if (size < 0) return NULL;
    runtime_array_t *arr = calloc(1, sizeof(runtime_array_t));
    arr->elem_type = elem_type;
    arr->length = size;
    if (elem_type == 0) { // int[]
        if (size > 0) arr->ints = calloc(size, sizeof(int));
        else arr->ints = NULL;
    }
    return arr;
}

static runtime_array_t *runtime_array_from_init_list(ast_node *init_list, int elem_type) {
    // Contar elementos
    int count = 0;
    ast_node *cur = init_list;
    while (cur) { count++; cur = cur->next; }
    runtime_array_t *arr = runtime_array_new_empty(elem_type, count);
    cur = init_list;
    for (int i = 0; i < count && cur; i++, cur = cur->next) {
        if (elem_type == 0) { // int[]
            arr->ints[i] = evaluate_expression(cur);
        }
    }
    return arr;
}

static void array_map_store(ast_node *expr, runtime_array_t *arr) {
    if (!expr || !arr) return;
    array_map_t *m = malloc(sizeof(array_map_t));
    m->expr = expr;
    m->arr = arr;
    m->next = array_map_head;
    array_map_head = m;
}

static runtime_array_t *array_map_get(ast_node *expr) {
    for (array_map_t *m = array_map_head; m; m = m->next) {
        if (m->expr == expr) return m->arr;
    }
    return NULL;
}

static runtime_array_t *array_map_take(ast_node *expr) {
    array_map_t **pp = &array_map_head;
    while (*pp) {
        if ((*pp)->expr == expr) {
            runtime_array_t *arr = (*pp)->arr;
            array_map_t *tofree = *pp;
            *pp = tofree->next;
            // No liberar arr: la propiedad se transfiere al llamador.
            free(tofree);
            return arr;
        }
        pp = &(*pp)->next;
    }
    return NULL;
}

static void array_map_clear(void) {
    array_map_t *m = array_map_head;
    while (m) {
        array_map_t *n = m->next;
        if (m->arr) {
            if (m->arr->ints) free(m->arr->ints);
            free(m->arr);
            m->arr = NULL;
        }
        free(m);
        m = n;
    }
    array_map_head = NULL;
}

static void unescape_string_literal(const char *src, char *dst, size_t dstlen) {
    if (!dst || dstlen == 0) return;
    dst[0] = '\0';
    if (!src) return;

    const char *p = src;
    size_t i = 0;

    // Si la literal viene con comillas, saltarlas
    if (*p == '"') p++;

    while (*p != '\0' && i + 1 < dstlen) {
        if (*p == '"' && *(p + 1) == '\0') break; // comilla final
        if (*p == '\\' && *(p + 1) != '\0') {
            p++;
            switch (*p) {
                case 'n': dst[i++] = '\n'; break;
                case 't': dst[i++] = '\t'; break;
                case 'r': dst[i++] = '\r'; break;
                case '"': dst[i++] = '"'; break;
                case '\\': dst[i++] = '\\'; break;
                default: dst[i++] = *p; break;
            }
            p++;
        } else {
            dst[i++] = *p++;
        }
    }
    dst[i] = '\0';
}


// Función para evaluar expresiones
int evaluate_expression(ast_node *expr) {
    if (!expr) return 0;
    
    switch (expr->type) {
        case AST_INT_LITERAL:
            return expr->data.int_value;
            
        case AST_FLOAT_LITERAL:
            return (int)expr->data.float_value; // Convertir a int por simplicidad

        case AST_DOUBLE_LITERAL:
            return (int)expr->data.double_value; // Convertir a int por simplicidad
        
        case AST_BOOL_LITERAL:
            return expr->data.bool_value; 

        case AST_VARIABLE: {
            
            runtime_symbol_t *sym = find_or_create_symbol(expr->data.var_name);

            // RETORNAR SEGÚN EL TIPO DE LA VARIABLE
            switch (sym->type) {
                case 0: return sym->value.int_val;           // int
                case 1: return (int)sym->value.float_val;    // float → int
                case 2: return strlen(sym->value.string_val ? sym->value.string_val : ""); // string → longitud
                case 3: return sym->value.bool_val;          // boolean
                case 4: return (int)sym->value.double_val;   // double → int
                default: return 0;
            }
        }

        case AST_ARRAY_ACCESS: {
            // expr->data.array_access.array_name and index expression
            const char *name = expr->data.array_access.array_name;
            ast_node *index_expr = expr->data.array_access.index; 
            if (!name || !index_expr) return 0;
            runtime_symbol_t *sym = find_or_create_symbol(name);
            if (!sym || sym->type != TYPE_ARRAY_INT) return 0;
            runtime_array_t *arr = (runtime_array_t*)sym->value.array_val;
            if (!arr) return 0;
            int idx = evaluate_expression(index_expr);
            if (idx < 0 || idx >= arr->length) {
                char msg[256];
                snprintf(msg, sizeof(msg), "⚠️ Array index out of bounds: %s[%d] (len=%d)\n", name, idx, arr->length);
                runtime_log(msg);
                return 0;
            }
            return arr->ints[idx];
        }

        case AST_METHOD_CALL: {
            char recv_name[256] = "";
            ast_node *recv = expr->data.method_call.receiver;
            if (recv) {
                if (recv->type == AST_VARIABLE && recv->data.var_name) {
                    strncpy(recv_name, recv->data.var_name, sizeof(recv_name)-1);
                    recv_name[sizeof(recv_name)-1] = '\0';
                } else {
                    char tmp[256];
                    strncpy(tmp, get_string_value(recv), sizeof(tmp)-1);
                    tmp[sizeof(tmp)-1] = '\0';
                    strncpy(recv_name, tmp, sizeof(recv_name)-1);
                    recv_name[sizeof(recv_name)-1] = '\0';
                }
            }
            const char *mname = expr->data.method_call.method_name ? expr->data.method_call.method_name : "";

            // StringBuilder.append(receiver.append(arg))
            if (recv_name[0] != '\0' && strcmp(mname, "append") == 0) {
                runtime_symbol_t *recv_sym = find_or_create_symbol(recv_name);
                char *argstr = runtime_eval_as_string(expr->data.method_call.arg);
                if (recv_sym->type != TYPE_STRING) {
                    recv_sym->type = TYPE_STRING;
                    recv_sym->value.string_val = strdup(argstr ? argstr : "");
                } else {
                    size_t cur = strlen(recv_sym->value.string_val ? recv_sym->value.string_val : "");
                    size_t add = strlen(argstr ? argstr : "");
                    char *n = malloc(cur + add + 1);
                    if (!n) return 0;
                    n[0] = '\0';
                    if (recv_sym->value.string_val) { strcpy(n, recv_sym->value.string_val); }
                    strcat(n, argstr ? argstr : "");
                    free(recv_sym->value.string_val);
                    recv_sym->value.string_val = n;
                }
                // devuelve la longitud como valor entero (evaluate_expression requiere int)
                return (int)strlen(recv_sym->value.string_val ? recv_sym->value.string_val : "");
            }

            // toString sobre un "StringBuilder" o variable string
            if (recv_name[0] != '\0' && strcmp(mname, "toString") == 0) {
                runtime_symbol_t *recv_sym = find_or_create_symbol(recv_name);
                if (recv_sym->type == TYPE_STRING && recv_sym->value.string_val) {
                    expr->type = AST_STRING_LITERAL;
                    expr->data.string_value = strdup(recv_sym->value.string_val);
                    return (int)strlen(expr->data.string_value);
                } else {
                    expr->type = AST_STRING_LITERAL;
                    expr->data.string_value = strdup("");
                    return 0;
                }
            }

            // length() para arrays o strings (receiver.length)
            if (recv_name[0] != '\0' && (strcmp(mname, "length") == 0 || strcmp(mname, "length()") == 0)) {
                runtime_symbol_t *recv_sym = find_or_create_symbol(recv_name);
                if (recv_sym->type == TYPE_ARRAY_INT && recv_sym->value.array_val) {
                    runtime_array_t *arr = (runtime_array_t*)recv_sym->value.array_val;
                    return arr->length;
                }
                if (recv_sym->type == TYPE_STRING && recv_sym->value.string_val) {
                    return (int)strlen(recv_sym->value.string_val);
                }
            }

            // Arrays.toString / Arrays.deepToString(arg)
            if (strcmp(recv_name, "Arrays") == 0 &&
                (strcmp(mname, "toString") == 0 || strcmp(mname, "deepToString") == 0) &&
                expr->data.method_call.arg) {

                char outbuf[2048];
                outbuf[0] = '\0';
                ast_node *arg = expr->data.method_call.arg;

                if (arg->type == AST_VARIABLE && arg->data.var_name) {
                    runtime_symbol_t *sym = find_or_create_symbol(arg->data.var_name);
                    if (sym && sym->type == TYPE_ARRAY_INT && sym->value.array_val) {
                        runtime_array_t *arr = (runtime_array_t*)sym->value.array_val;
                        strcat(outbuf, "[");
                        for (int i = 0; i < arr->length; ++i) {
                            char tmp[64];
                            snprintf(tmp, sizeof(tmp), "%d", arr->ints[i]);
                            strcat(outbuf, tmp);
                            if (i + 1 < arr->length) strcat(outbuf, ", ");
                        }
                        strcat(outbuf, "]");
                        expr->type = AST_STRING_LITERAL;
                        expr->data.string_value = strdup(outbuf);
                        return (int)strlen(outbuf);
                    }
                } else if (arg->type == AST_ARRAY_ACCESS) {
                    int v = evaluate_expression(arg);
                    snprintf(outbuf, sizeof(outbuf), "%d", v);
                    expr->type = AST_STRING_LITERAL;
                    expr->data.string_value = strdup(outbuf);
                    return (int)strlen(outbuf);
                }
                // fallback: devolver cadena vacía transformando el nodo
                expr->type = AST_STRING_LITERAL;
                expr->data.string_value = strdup("");
                return 0;
            }

            // Fallback a builtin_dispatch (Integer.parseInt, Double.parseDouble, String.valueOf, etc.)
            {
                char fullname[512];
                snprintf(fullname, sizeof(fullname), "%s.%s", recv_name, mname);
                int out_i = 0; double out_d = 0; char *out_s = NULL;
                int t = builtin_dispatch(fullname, expr->data.method_call.arg, &out_i, &out_d, &out_s);
                if (t == 0) return out_i;
                if (t == 1) {
                    expr->type = AST_DOUBLE_LITERAL;
                    expr->data.double_value = out_d;
                    return (int)out_d;
                }
                if (t == 2 && out_s) {
                    expr->type = AST_STRING_LITERAL;
                    expr->data.string_value = out_s; // out_s ya es strdup en builtin_dispatch
                    return (int)strlen(out_s);
                }
            }

            // No reconocido -> 0
            return 0;
        }

        case AST_NEW_ARRAY_INIT: {
            runtime_array_t *arr = NULL;
            int elem_type = 0; // default int

            if (expr->data.new_array.elem_type && expr->data.new_array.elem_type->data.type_name) {
                char *type_name = expr->data.new_array.elem_type->data.type_name;
                if (strcmp(type_name, "int") == 0) elem_type = 0;
                else if (strcmp(type_name, "float") == 0) elem_type = 1;
                else if (strcmp(type_name, "String") == 0) elem_type = 2;
                else if (strcmp(type_name, "boolean") == 0) elem_type = 3;
                else if (strcmp(type_name, "double") == 0) elem_type = 4;
            }

            if (expr->data.new_array.init_list) {
                arr = runtime_array_from_init_list(expr->data.new_array.init_list, elem_type);
            } else if (expr->data.new_array.size_expr) {
                int size = evaluate_expression(expr->data.new_array.size_expr);
                arr = runtime_array_new_empty(elem_type, size);
            }

            if (arr) {
                // almacenar en el mapa para que la asignación/declaración lo recupere y lo guarde en el símbolo
                array_map_store(expr, arr);
                // devolver 0 (evaluate_expression no devuelve punteros). La asignación manejará guardar el puntero.
                return 0;
            }
            return 0;
        }
        
        case AST_BINARY_OP: {
            switch (expr->data.op.op) {
                case OP_PLUS: {
                    int left_is_string = is_string_expression(expr->data.op.left);
                    int right_is_string = is_string_expression(expr->data.op.right);
                    if (left_is_string || right_is_string) {
                        char *left_str = get_string_value(expr->data.op.left);
                        char *right_str = get_string_value(expr->data.op.right);
                        static char concat_result[1024];
                        snprintf(concat_result, sizeof(concat_result), "%s%s", left_str, right_str);
                        char message[1024];
                        snprintf(message, sizeof(message), " [CONCAT] '%s'\n", concat_result);
                        runtime_log(message);
                        return (int)strlen(concat_result);
                    } else {
                        if (node_is_floatish(expr->data.op.left) || node_is_floatish(expr->data.op.right)) {
                            double dv = eval_node_as_double(expr);
                            return (int)dv;
                        }
                        int left = evaluate_expression(expr->data.op.left);
                        int right = evaluate_expression(expr->data.op.right);
                        return left + right;
                    }
                }
                    
                // ⭐ RESTO DE OPERADORES NUMÉRICOS
                case OP_MINUS: {
                    if (node_is_floatish(expr->data.op.left) || node_is_floatish(expr->data.op.right)) {
                        double dv = eval_node_as_double(expr);
                        return (int)dv;
                    }
                    int left = evaluate_expression(expr->data.op.left);
                    int right = evaluate_expression(expr->data.op.right);
                    return left - right;
                }

                case OP_MULT: {
                    if (node_is_floatish(expr->data.op.left) || node_is_floatish(expr->data.op.right)) {
                        double dv = eval_node_as_double(expr);
                        char debug_msg[256];
                        snprintf(debug_msg, sizeof(debug_msg),
                                "🔍 MULT (double): %.6f\n", dv);
                        runtime_log(debug_msg);
                        return (int)dv;
                    }
                    int left = evaluate_expression(expr->data.op.left);
                    int right = evaluate_expression(expr->data.op.right);
                    int result = left * right;
                    char debug_msg[256];
                    snprintf(debug_msg, sizeof(debug_msg),
                            "🔍 MULT: %d * %d = %d\n", left, right, result);
                    runtime_log(debug_msg);
                    return result;
                }
                
                case OP_DIV: {
                    if (node_is_floatish(expr->data.op.left) || node_is_floatish(expr->data.op.right)) {
                        double dv = eval_node_as_double(expr);
                        return (int)dv;
                    }
                    int left = evaluate_expression(expr->data.op.left);
                    int right = evaluate_expression(expr->data.op.right);
                    return right != 0 ? left / right : 0;
                }

                case OP_MOD: {
                    if (node_is_floatish(expr->data.op.left) || node_is_floatish(expr->data.op.right)) {
                        double dv = eval_node_as_double(expr);
                        return (int)dv;
                    }
                    int left = evaluate_expression(expr->data.op.left);
                    int right = evaluate_expression(expr->data.op.right);
                    return right != 0 ? left % right : 0;
                }
                
                // OPERADORES RELACIONALES
                case OP_EQUALS: {
                    // 1. STRING vs STRING
                    if (is_string_expression(expr->data.op.left) && is_string_expression(expr->data.op.right)) {
                        char *left_str = get_string_value(expr->data.op.left);
                        char *right_str = get_string_value(expr->data.op.right);
                        int result = (strcmp(left_str, right_str) == 0) ? 1 : 0;
                        
                        char message[256];
                        snprintf(message, sizeof(message), " String equals: '%s' == '%s' = %s\n", 
                                left_str, right_str, result ? "true" : "false");
                        runtime_log(message);
                        return result;
                    }
                    
                    // 2. BOOLEAN vs BOOLEAN
                    else if (expr->data.op.left->type == AST_BOOL_LITERAL && expr->data.op.right->type == AST_BOOL_LITERAL) {
                        int left = expr->data.op.left->data.bool_value;
                        int right = expr->data.op.right->data.bool_value;
                        int result = (left == right) ? 1 : 0;
                        
                        char message[256];
                        snprintf(message, sizeof(message), " Boolean equals: %s == %s = %s\n", 
                                left ? "true" : "false", right ? "true" : "false", result ? "true" : "false");
                        runtime_log(message);
                        return result;
                    }
                    
                    // 3. VARIABLE BOOLEAN vs LITERAL BOOLEAN
                    else if ((expr->data.op.left->type == AST_VARIABLE || expr->data.op.left->type == AST_BOOL_LITERAL) &&
                            (expr->data.op.right->type == AST_VARIABLE || expr->data.op.right->type == AST_BOOL_LITERAL)) {
                        
                        int left = evaluate_expression(expr->data.op.left);
                        int right = evaluate_expression(expr->data.op.right);
                        
                        // Verificar si ambos son booleanos
                        runtime_symbol_t *left_sym = NULL, *right_sym = NULL;
                        int left_is_bool = 0, right_is_bool = 0;
                        
                        if (expr->data.op.left->type == AST_VARIABLE) {
                            left_sym = find_or_create_symbol(expr->data.op.left->data.var_name);
                            left_is_bool = (left_sym->type == 3); // 3 = boolean
                        } else if (expr->data.op.left->type == AST_BOOL_LITERAL) {
                            left_is_bool = 1;
                        }
                        
                        if (expr->data.op.right->type == AST_VARIABLE) {
                            right_sym = find_or_create_symbol(expr->data.op.right->data.var_name);
                            right_is_bool = (right_sym->type == 3);
                        } else if (expr->data.op.right->type == AST_BOOL_LITERAL) {
                            right_is_bool = 1;
                        }
                        
                        int result = (left == right) ? 1 : 0;
                        
                        if (left_is_bool && right_is_bool) {
                            char message[256];
                            snprintf(message, sizeof(message), " Boolean comparison: %s == %s = %s\n", 
                                    left ? "true" : "false", right ? "true" : "false", result ? "true" : "false");
                            runtime_log(message);
                        } else {
                            char message[256];
                            snprintf(message, sizeof(message), " Numeric comparison: %d == %d = %s\n", 
                                    left, right, result ? "true" : "false");
                            runtime_log(message);
                        }
                        
                        return result;
                    }
                    
                    // 4. NÚMEROS (int, float, double)
                    else {
                        int left = evaluate_expression(expr->data.op.left);
                        int right = evaluate_expression(expr->data.op.right);
                        int result = (left == right) ? 1 : 0;
                        
                        char message[256];
                        snprintf(message, sizeof(message), " Numeric equals: %d == %d = %s\n", 
                                left, right, result ? "true" : "false");
                        runtime_log(message);
                        return result;
                    }
                }
                
                case OP_NOT_EQUALS: {
                    if (is_string_expression(expr->data.op.left) && is_string_expression(expr->data.op.right)) {
                        char *left_str = get_string_value(expr->data.op.left);
                        char *right_str = get_string_value(expr->data.op.right);
                        return (strcmp(left_str, right_str) != 0) ? 1 : 0;
                    } else {
                        int left = evaluate_expression(expr->data.op.left);
                        int right = evaluate_expression(expr->data.op.right);
                        return (left != right) ? 1 : 0;
                    }
                }
                
                case OP_LESS: {
                    int left = evaluate_expression(expr->data.op.left);
                    int right = evaluate_expression(expr->data.op.right);
                    return (left < right) ? 1 : 0;
                }
                
                case OP_GREATER: {                    
                    // Obtener valores y determinar tipos
                    ast_node *left_node = expr->data.op.left;
                    ast_node *right_node = expr->data.op.right;
                    
                    double left_val = 0.0, right_val = 0.0;
                    
                    // Evaluar lado izquierdo
                    if (left_node->type == AST_DOUBLE_LITERAL) {
                        left_val = left_node->data.double_value;
                    } else if (left_node->type == AST_FLOAT_LITERAL) {
                        left_val = (double)left_node->data.float_value;
                    } else if (left_node->type == AST_VARIABLE) {
                        runtime_symbol_t *sym = find_or_create_symbol(left_node->data.var_name);
                        switch (sym->type) {
                            case 0: left_val = (double)sym->value.int_val; break;
                            case 1: left_val = (double)sym->value.float_val; break;
                            case 4: left_val = sym->value.double_val; break;
                            default: left_val = (double)evaluate_expression(left_node);
                        }
                    } else {
                        left_val = (double)evaluate_expression(left_node);
                    }
                    
                    // Evaluar lado derecho
                    if (right_node->type == AST_DOUBLE_LITERAL) {
                        right_val = right_node->data.double_value;
                    } else if (right_node->type == AST_FLOAT_LITERAL) {
                        right_val = (double)right_node->data.float_value;
                    } else if (right_node->type == AST_VARIABLE) {
                        runtime_symbol_t *sym = find_or_create_symbol(right_node->data.var_name);
                        switch (sym->type) {
                            case 0: right_val = (double)sym->value.int_val; break;
                            case 1: right_val = (double)sym->value.float_val; break;
                            case 4: right_val = sym->value.double_val; break;
                            default: right_val = (double)evaluate_expression(right_node);
                        }
                    } else {
                        right_val = (double)evaluate_expression(right_node);
                    }
                    
                    int result = (left_val > right_val) ? 1 : 0;
                    
                    char message[256];
                    snprintf(message, sizeof(message), "🔍 Greater than: %.6f > %.6f = %s\n", 
                            left_val, right_val, result ? "true" : "false");
                    runtime_log(message);
                    
                    return result;
                }
                
                case OP_LESS_EQUALS: {
                    int left = evaluate_expression(expr->data.op.left);
                    int right = evaluate_expression(expr->data.op.right);
                    return (left <= right) ? 1 : 0;
                }
                
                case OP_GREATER_EQUALS: {
                    int left = evaluate_expression(expr->data.op.left);
                    int right = evaluate_expression(expr->data.op.right);
                    return (left >= right) ? 1 : 0;
                }
                
                case OP_AND: {
                    int left = evaluate_expression(expr->data.op.left);
                    
                    char message[512];
                    snprintf(message, sizeof(message), "🔍 AND evaluation: left = %s", left ? "true" : "false");
                    
                    if (!left) {
                        // Short-circuit: si left es false, no evaluar right
                        snprintf(message + strlen(message), sizeof(message) - strlen(message), 
                                ", short-circuit = false\n");
                        runtime_log(message);
                        return 0;
                    }
                    
                    int right = evaluate_expression(expr->data.op.right);
                    int result = (left && right) ? 1 : 0;
                    
                    snprintf(message + strlen(message), sizeof(message) - strlen(message), 
                            ", right = %s, result = %s\n", 
                            right ? "true" : "false", result ? "true" : "false");
                    runtime_log(message);
                    
                    return result;
                }
                
                case OP_OR: {
                    // ⭐ IMPLEMENTAR SHORT-CIRCUIT EVALUATION
                    int left = evaluate_expression(expr->data.op.left);
                    
                    char message[512];
                    snprintf(message, sizeof(message), "🔍 OR evaluation: left = %s", left ? "true" : "false");
                    
                    if (left) {
                        // Short-circuit: si left es true, no evaluar right
                        snprintf(message + strlen(message), sizeof(message) - strlen(message), 
                                ", short-circuit = true\n");
                        runtime_log(message);
                        return 1;
                    }
                    
                    int right = evaluate_expression(expr->data.op.right);
                    int result = (left || right) ? 1 : 0;
                    
                    snprintf(message + strlen(message), sizeof(message) - strlen(message), 
                            ", right = %s, result = %s\n", 
                            right ? "true" : "false", result ? "true" : "false");
                    runtime_log(message);
                    
                    return result;
                }

                default: 
                    return 0;
            }
        }
        
        case AST_UNARY_OP: {
            int operand = 0;
            if (expr->data.op.left) {
                operand = evaluate_expression(expr->data.op.left);
            }
            
            switch (expr->data.op.op) {
                case OP_NOT: {
                    int result = !operand;
                    char message[256];
                    snprintf(message, sizeof(message), "🔄 Operador NOT: !%d = %d\n", operand, result);
                    runtime_log(message);
                    return result;
                }
                case OP_UMINUS:
                    return -operand;

                case OP_INCREMENT:
                case OP_POST_INCREMENT: {
                    return handle_increment_decrement(expr, 1, expr->data.op.op == OP_POST_INCREMENT);
                }

                case OP_DECREMENT:
                case OP_POST_DECREMENT: {
                    return handle_increment_decrement(expr, -1, expr->data.op.op == OP_POST_DECREMENT);
                }

                default:
                    return operand;
            }
        }

        case AST_STRING_EQUALS: {
            // Evaluar ambos lados como strings
            char *left_str = get_string_value(expr->data.string_equals.left_string);
            char *right_str = get_string_value(expr->data.string_equals.right_expr);
            
            // Comparar strings
            int result = (strcmp(left_str, right_str) == 0) ? 1 : 0;
            
            // Mostrar en consola
            char message[512];
            snprintf(message, sizeof(message), "🔍 String.equals(): '%s'.equals('%s') = %s\n", 
                    left_str, right_str, result ? "true" : "false");
            runtime_log(message);
            
            return result;
        }
        
        default:
            return 0;
    }
}

// Función para ejecutar declaraciones
void execute_statement(ast_node *stmt) {
    if (!stmt) {
        runtime_log("⚠️ execute_statement: stmt es NULL\n");
        return;
    }
    // ⭐ DEBUGGING CRÍTICO
    //char debug_msg[256];
    //snprintf(debug_msg, sizeof(debug_msg), "🔍 DEBUG: Ejecutando nodo tipo %d\n", stmt->type);
    //runtime_log(debug_msg);

    switch (stmt->type) {
        // REEMPLAZAR en runtime.c, línea 228:
        case AST_DECLARATION: {
            // Determinar el tipo de la variable
            int var_type = 0; // 0=int (por defecto)
            if (stmt->data.declaration.var_type && stmt->data.declaration.var_type->data.type_name) {
                char *type_name = stmt->data.declaration.var_type->data.type_name;
                if (strcmp(type_name, "int") == 0) var_type = 0;
                else if (strcmp(type_name, "float") == 0) var_type = 1;
                else if (strcmp(type_name, "String") == 0) var_type = 2;
                else if (strcmp(type_name, "boolean") == 0) var_type = 3;
                else if (strcmp(type_name, "double") == 0) var_type = 4;
                else {
                    /* Detectar tipos de arreglo (terminan en "[]"), p.ej. "int[]", "String[]", etc. */
                    size_t tn = strlen(type_name);
                    if (tn >= 2 && strcmp(type_name + tn - 2, "[]") == 0) {
                        var_type = TYPE_ARRAY_INT; /* por ahora tratamos los arrays como TYPE_ARRAY_INT en runtime */
                    }
                }
            }
            
            // Crear símbolo
            runtime_symbol_t *sym = find_or_create_symbol(stmt->data.declaration.var_name);
            sym->type = var_type;
            
            // Evaluar valor inicial según el tipo
            if (stmt->data.declaration.value) {
                // Caso array declarado: asegurar que RHS se evalúe para crear runtime_array_t
                if (var_type == TYPE_ARRAY_INT) {
                    // Si RHS es new T[]{...} forzamos evaluación (esto llenará array_map)
                    if (stmt->data.declaration.value->type == AST_NEW_ARRAY_INIT) {
                        evaluate_expression(stmt->data.declaration.value); // crea entry en array_map
                        runtime_array_t *arr = array_map_take(stmt->data.declaration.value);
                        if (arr) {
                            sym->type = TYPE_ARRAY_INT;
                            sym->value.array_val = arr;
                            char msg[256];
                            snprintf(msg, sizeof(msg), " Declaración array: %s (len=%d)\n", sym->name, arr->length);
                            runtime_log(msg);
                            break; // array asignado, listo
                        }
                    }
                    // Si no vino como AST_NEW_ARRAY_INIT, intentar otros casos (no implementado ahora)
                }
                switch (var_type) {
                    case 0: { // int
                        int value = evaluate_expression(stmt->data.declaration.value);
                        sym->value.int_val = value;
                        
                        char message[256];
                        snprintf(message, sizeof(message), " Declaración: %s = %d (int)\n", 
                                stmt->data.declaration.var_name, value);
                        runtime_log(message);
                        break;
                    }
                    
                    case 1: { // float
                        if (stmt->data.declaration.value->type == AST_FLOAT_LITERAL) {
                            sym->value.float_val = stmt->data.declaration.value->data.float_value;
                        } else {
                            sym->value.float_val = (float)evaluate_expression(stmt->data.declaration.value);
                        }
                        
                        char message[256];
                        snprintf(message, sizeof(message), " Declaración: %s = %.2f (float)\n", 
                                stmt->data.declaration.var_name, sym->value.float_val);
                        runtime_log(message);
                        break;
                    }
                    
                    case 2: { // ⭐ STRING - AQUÍ ESTÁ EL CÓDIGO QUE BUSCAS
                        if (stmt->data.declaration.value->type == AST_STRING_LITERAL) {
                            // ⭐ ALMACENAR STRING SIN COMILLAS
                            char *str_value = stmt->data.declaration.value->data.string_value;
                            if (str_value && strlen(str_value) >= 2 && str_value[0] == '"') {
                                // Remover comillas
                                int len = strlen(str_value) - 2;
                                char *clean_str = malloc(len + 1);
                                strncpy(clean_str, str_value + 1, len);
                                clean_str[len] = '\0';
                                sym->value.string_val = clean_str;
                            } else {
                                sym->value.string_val = strdup(str_value ? str_value : "");
                            }
                        } else {
                            sym->value.string_val = strdup("");
                        }
                        
                        char message[256];
                        snprintf(message, sizeof(message), " Declaración: %s = \"%s\" (String)\n", 
                                stmt->data.declaration.var_name, sym->value.string_val);
                        runtime_log(message);
                        break;
                    }
                    
                    case 3: { // boolean
                        int bool_value = evaluate_expression(stmt->data.declaration.value);
                        sym->value.bool_val = bool_value;
                        
                        char message[256];
                        snprintf(message, sizeof(message), " Declaración: %s = %s (boolean)\n", 
                                stmt->data.declaration.var_name, bool_value ? "true" : "false");
                        runtime_log(message);
                        break;
                    }
                    
                    case 4: { // double
                        if (stmt->data.declaration.value->type == AST_DOUBLE_LITERAL) {
                            sym->value.double_val = stmt->data.declaration.value->data.double_value;
                        } else if (stmt->data.declaration.value->type == AST_FLOAT_LITERAL) {
                            sym->value.double_val = (double)stmt->data.declaration.value->data.float_value;
                        } else {
                            sym->value.double_val = (double)evaluate_expression(stmt->data.declaration.value);
                        }
                        
                        char message[256];
                        snprintf(message, sizeof(message), " Declaración: %s = %.6f (double)\n", 
                                stmt->data.declaration.var_name, sym->value.double_val);
                        runtime_log(message);
                        break;
                    }
                    default:
                        // si llegó aquí por TYPE_ARRAY_INT y no se asignó antes, dejar array_val NULL
                        if (var_type == TYPE_ARRAY_INT) {
                            sym->value.array_val = NULL;
                            char msg[128];
                            snprintf(msg, sizeof(msg), " Declaración array: %s (pendiente inicialización)\n", sym->name);
                            runtime_log(msg);
                        }
                        break;
                }
            } else {
                // Sin valor inicial - usar valores por defecto
                switch (var_type) {
                    case 0: sym->value.int_val = 0; break;
                    case 1: sym->value.float_val = 0.0f; break;
                    case 2: sym->value.string_val = strdup(""); break;
                    case 3: sym->value.bool_val = 0; break;
                    case 4: sym->value.double_val = 0.0; break;
                    case TYPE_ARRAY_INT: sym->value.array_val = NULL; break;

                }
                
                char message[256];
                snprintf(message, sizeof(message), " Declaración: %s (sin inicialización)\n", 
                        stmt->data.declaration.var_name);
                runtime_log(message);
            }
            break;
        }

        //  versión simple del AST_ASSIGNMENT:
        case AST_ASSIGNMENT: {
            runtime_symbol_t *sym = find_or_create_symbol(stmt->data.assignment.var_name);

            // Si el RHS es new T[]{...} tomar el array del mapa y asignarlo al símbolo
            if (stmt->data.assignment.value && stmt->data.assignment.value->type == AST_NEW_ARRAY_INIT) {
                runtime_array_t *arr = array_map_take(stmt->data.assignment.value);
                if (arr) {
                    sym->type = TYPE_ARRAY_INT; // asumimos int[]
                    sym->value.array_val = arr;
                    char msg[256];
                    snprintf(msg, sizeof(msg), " Asignación array: %s (len=%d)\n", sym->name, arr->length);
                    runtime_log(msg);
                    break;
                }
            }

            // Determinar el tipo basado en el valor asignado (manejo explícito para literales y expresiones)
            if (stmt->data.assignment.value) {
                ast_node *v = stmt->data.assignment.value;

                if (v->type == AST_INT_LITERAL) {
                    sym->type = 0;
                    sym->value.int_val = v->data.int_value;
                }
                else if (v->type == AST_FLOAT_LITERAL) {
                    sym->type = 1;
                    sym->value.float_val = v->data.float_value;
                }
                else if (v->type == AST_DOUBLE_LITERAL) {
                    sym->type = 4;
                    sym->value.double_val = v->data.double_value;
                }
                else if (v->type == AST_STRING_LITERAL) {
                    sym->type = 2;
                    sym->value.string_val = strdup(get_string_value(v));
                }
                else if (v->type == AST_BOOL_LITERAL) {
                    sym->type = 3;
                    sym->value.bool_val = v->data.bool_value;
                }
                else {
                    // expresiones complejas: decidir según si producen float o booleano
                    if (node_is_floatish(v)) {
                        sym->type = 4;
                        sym->value.double_val = eval_node_as_double(v);
                    } else if (node_is_boolean_expression(v)) {
                        sym->type = 3;
                        sym->value.bool_val = evaluate_expression(v);
                    } else {
                        sym->type = 0;
                        sym->value.int_val = evaluate_expression(v);
                    }
                }
            }

            char message[256];
            snprintf(message, sizeof(message), " Asignación: %s = ", stmt->data.assignment.var_name);

            switch (sym->type) {
                case 0: snprintf(message + strlen(message), sizeof(message) - strlen(message), "%d\n", sym->value.int_val); break;
                case 1: snprintf(message + strlen(message), sizeof(message) - strlen(message), "%.6f\n", sym->value.float_val); break;
                case 2: snprintf(message + strlen(message), sizeof(message) - strlen(message), "\"%s\"\n", sym->value.string_val); break;
                case 3: snprintf(message + strlen(message), sizeof(message) - strlen(message), "%s\n", sym->value.bool_val ? "true" : "false"); break;
                case 4: snprintf(message + strlen(message), sizeof(message) - strlen(message), "%.6f\n", sym->value.double_val); break;
            }

            runtime_log(message);
            break;
        }

        
        case AST_IF: {
            // if (condicion) { ... } else { ... }
            int condition = evaluate_expression(stmt->data.if_stmt.condition);
            
            char message[256];
            snprintf(message, sizeof(message), "🔀 Evaluando if: condición = %s\n", 
                     condition ? "true" : "false");
            runtime_log(message);
            
            if (condition) {
                if (stmt->data.if_stmt.then_branch) {
                    runtime_log("   Ejecutando rama then\n");
                    execute_statement(stmt->data.if_stmt.then_branch);
                }
            } else {
                if (stmt->data.if_stmt.else_branch) {
                    runtime_log("   Ejecutando rama else\n");
                    execute_statement(stmt->data.if_stmt.else_branch);
                }
            }
            break;
        }
        
        case AST_BREAK: {
            runtime_break_flag = 1;
            runtime_log("🛑 Break ejecutado\n");
            break;
        }

        case AST_CONTINUE: {
            runtime_continue_flag = 1;
            runtime_log("⏭️ Continue ejecutado\n");
            break;}

        case AST_WHILE: {
            runtime_log("🔄 Iniciando bucle while\n");
            
            int iterations = 0;
            const int MAX_ITERATIONS = 1000;
            
            while (evaluate_expression(stmt->data.while_stmt.condition) && 
                iterations < MAX_ITERATIONS && 
                !runtime_break_flag) {
                
                if (runtime_continue_flag) {
                    runtime_continue_flag = 0;
                    iterations++;
                    continue;
                }
                
                char message[256];
                snprintf(message, sizeof(message), "   Iteración %d\n", iterations + 1);
                runtime_log(message);
                
                if (stmt->data.while_stmt.body) {
                    execute_statement(stmt->data.while_stmt.body);
                }
                
                if (runtime_break_flag) break;
                iterations++;
            }
            
            // Reset flags después del bucle
            runtime_break_flag = 0;
            runtime_continue_flag = 0;
            
            if (iterations >= MAX_ITERATIONS) {
                runtime_log(" Bucle while detenido (máximo de iteraciones alcanzado)\n");
            } else {
                runtime_log(" Bucle while completado\n");
            }
            break;
        }
                
        case AST_FOR: {
            runtime_log("🔄 Iniciando bucle for\n");
            
            // Ejecutar inicialización
            if (stmt->data.for_stmt.init) {
                execute_statement(stmt->data.for_stmt.init);
            }
            
            int iterations = 0;
            const int MAX_ITERATIONS = 1000;
            
            while (iterations < MAX_ITERATIONS && !runtime_break_flag) {
                // Evaluar condición - si existe y es falsa, salir
                if (stmt->data.for_stmt.condition) {
                    int cond_result = evaluate_expression(stmt->data.for_stmt.condition);
                    if (!cond_result) {
                        break;
                    }
                }
                
                // Verificar continue flag
                if (runtime_continue_flag) {
                    runtime_continue_flag = 0;
                    // Solo ejecutar el incremento y continuar
                    if (stmt->data.for_stmt.increment) {
                        execute_statement(stmt->data.for_stmt.increment);
                    }
                    iterations++;
                    continue;
                }
                
                char message[256];
                snprintf(message, sizeof(message), "   Iteración for %d\n", iterations + 1);
                runtime_log(message);
                
                // Ejecutar cuerpo
                if (stmt->data.for_stmt.body) {
                    execute_statement(stmt->data.for_stmt.body);
                }
                
                // Verificar break después del cuerpo
                if (runtime_break_flag) break;
                
                // Ejecutar incremento
                if (stmt->data.for_stmt.increment) {
                    execute_statement(stmt->data.for_stmt.increment);
                }
                
                iterations++;
            }
            
            // Reset flags después del bucle
            runtime_break_flag = 0;
            runtime_continue_flag = 0;
            
            if (iterations >= MAX_ITERATIONS) {
                runtime_log(" Bucle for detenido (máximo de iteraciones alcanzado)\n");
            } else {
                runtime_log(" Bucle for completado\n");
            }
            break;
        }
                
        case AST_RETURN: {
            // return expr;
            int return_value = 0;
            if (stmt->data.return_stmt.value) {
                return_value = evaluate_expression(stmt->data.return_stmt.value);
            }
            
            char message[256];
            snprintf(message, sizeof(message), " Return: %d\n", return_value);
            runtime_log(message);
            break;
        }
        
        case AST_COMPOUND_STMT: {
            // { statement1; statement2; ... }
            ast_node *current = stmt->data.compound.statement_list;
            while (current) {
                execute_statement(current);
                current = current->next;
            }
            break;
        }
        

        case AST_PRINT_STMT: {
            if (stmt->data.print_stmt.expression) {
                char outbuf[2048];
                outbuf[0] = '\0';

                ast_node *expr = stmt->data.print_stmt.expression;

                // Si es suma binaria usada como concatenación, construir recursivamente
                if (expr->type == AST_BINARY_OP && expr->data.op.op == OP_PLUS && is_string_expression(expr)) {
                    build_concatenated_string(expr, outbuf);
                } else {
                    // Fallback: obtener representación string de cualquier nodo
                    char *s = get_string_value(expr);
                    if (s) {
                        strncpy(outbuf, s, sizeof(outbuf)-1);
                        outbuf[sizeof(outbuf)-1] = '\0';
                    } else {
                        outbuf[0] = '\0';
                    }
                }

                // Asegurar nueva línea y enviar a consola
                char line[2112];
                snprintf(line, sizeof(line), "%s\n", outbuf);
                console_print_program(line);
            } else {
                // println() sin argumentos
                console_print_program("\n");
            }
            break;
        }

        case AST_PROGRAM: {
            //runtime_log("🔍 DEBUG: === ENTRANDO A AST_PROGRAM ===\n");
            
            // ⭐ DEBUGGING ESPECÍFICO
            /*char debug_msg[512];
            snprintf(debug_msg, sizeof(debug_msg), 
                    "🔍 AST_PROGRAM: tipo=%d, next=%p, function_def.body=%p\n", 
                    stmt->type, 
                    (void*)stmt->next,
                    (void*)stmt->data.function_def.body);
            runtime_log(debug_msg);*/
            
            // ⭐ INTENTAR TODAS LAS OPCIONES
            if (stmt->data.function_def.body) {
                runtime_log("✅ Encontrado function_def.body - EJECUTANDO\n");
                execute_statement(stmt->data.function_def.body);
            }
            else if (stmt->next) {
                runtime_log("✅ Ejecutando stmt->next\n");
                execute_statement(stmt->next);
            }
            else {
                runtime_log("⚠️ AST_PROGRAM: No se encontraron statements para ejecutar\n");
                
                // ⭐ DEBUGGING ADICIONAL - VER SI HAY OTROS CAMPOS
                //runtime_log("🔍 Intentando acceder a campos alternativos...\n");
                
                // Intentar como si fuera una lista de declaraciones
                // (dependiendo de tu estructura AST)
                if (stmt->data.declaration.var_name) {
                    runtime_log("✅ Encontrada declaración en AST_PROGRAM - EJECUTANDO\n");
                    execute_statement(stmt);
                } else {
                    runtime_log("❌ No se encontraron declaraciones en AST_PROGRAM\n");
                }
            }
            
            //runtime_log("🔍 DEBUG: === SALIENDO DE AST_PROGRAM ===\n");
            break;
        }

        // ...existing code...
        case AST_MAIN_FUNCTION: {
            if (stmt->data.function_def.body) {
                runtime_log("✅ Encontrado function_def.body en MAIN - EJECUTANDO\n");
                
                ast_node *current = stmt->data.function_def.body;
                int statement_count = 0;
                char debug_msg[256];

                while (current) {
                    statement_count++;
                    snprintf(debug_msg, sizeof(debug_msg),
                             "🔍 Ejecutando statement %d (tipo: %d)\n",
                             statement_count, current->type);
                    runtime_log(debug_msg);
                    
                    execute_statement(current);
                    current = current->next;
                }
                
                char final_msg[256];
                snprintf(final_msg, sizeof(final_msg), "✅ Ejecutados %d statements en main\n", statement_count);
                runtime_log(final_msg);
                
            } else {
                runtime_log("❌ AST_MAIN_FUNCTION: No hay cuerpo para ejecutar\n");
            }
            break;
        }

        case AST_ARRAY_DECLARATION: {
            //runtime_log("🔍 DEBUG: === DECLARACIÓN DE ARRAY ===\n");
            
            char msg[256];
            snprintf(msg, sizeof(msg), "📊 Array declarado: %s\n",
                    stmt->data.array_decl.array_name ? stmt->data.array_decl.array_name : "?");
            runtime_log(msg);
            
            // Crear símbolo para el array
            runtime_symbol_t *array_symbol = find_or_create_symbol(stmt->data.array_decl.array_name);
            // Asumir int[] por ahora
            array_symbol->type = TYPE_ARRAY_INT;
            runtime_array_t *arr = NULL;
            if (stmt->data.array_decl.size) {
                int size = evaluate_expression(stmt->data.array_decl.size);
                arr = runtime_array_new_empty(0, size);
            } else if (stmt->data.array_decl.init_values) { // <-- field name in ast.h
                arr = runtime_array_from_init_list(stmt->data.array_decl.init_values, 0);
            }
            array_symbol->value.array_val = arr;
            break;
        }
        
        
        case AST_ARRAY_ACCESS: {
            // Access usado como statement: solo loguear o evaluar si necesario
            char msg[256];
            snprintf(msg, sizeof(msg), "📊 Accediendo a: %s[índice]\n",
                    stmt->data.array_access.array_name ? stmt->data.array_access.array_name : "?");
            runtime_log(msg);
            
            // Si se desea obtener el valor, se puede llamar evaluate_expression sobre el mismo nodo
            int v = evaluate_expression(stmt);
            (void)v;
            break;
        }
        
        case AST_ARRAY_ASSIGNMENT: {
            // arrayName[index] = value;
            const char *name = stmt->data.array_assignment.array_name;
            ast_node *index_expr = stmt->data.array_assignment.index; // field name 'index'
            ast_node *value_expr = stmt->data.array_assignment.value;
            if (!name || !index_expr || !value_expr) break;
            
            runtime_symbol_t *sym = find_or_create_symbol(name);
            if (!sym || sym->type != TYPE_ARRAY_INT) {
                char err[256];
                snprintf(err, sizeof(err), "⚠️ Asignación a array inválida: %s no es array\n", name);
                runtime_log(err);
                break;
            }
            runtime_array_t *arr = (runtime_array_t*)sym->value.array_val;
            if (!arr) {
                char err[256];
                snprintf(err, sizeof(err), "⚠️ Asignación a array inválida: %s no inicializado\n", name);
                runtime_log(err);
                break;
            }
            int idx = evaluate_expression(index_expr);
            if (idx < 0 || idx >= arr->length) {
                char err[256];
                snprintf(err, sizeof(err), "⚠️ Índice fuera de rango: %s[%d] (len=%d)\n", name, idx, arr->length);
                runtime_log(err);
                break;
            }
            int val = evaluate_expression(value_expr);
            arr->ints[idx] = val;
            char msg[256];
            snprintf(msg, sizeof(msg), "📊 %s[%d] = %d\n", name, idx, val);
            runtime_log(msg);
            break;
        }

        default:
            // Para cualquier expresión que no sea una declaración específica
            if (stmt->type == AST_BINARY_OP || stmt->type == AST_UNARY_OP || 
                stmt->type == AST_VARIABLE || stmt->type == AST_INT_LITERAL) {
                
                int result = evaluate_expression(stmt);
                char message[256];
                snprintf(message, sizeof(message), " Expresión evaluada: %d\n", result);
                runtime_log(message);
            }
            break;
    }
    
    // Ejecutar el siguiente statement en la secuencia
    /*if (stmt->next && stmt->type != AST_COMPOUND_STMT) {
        execute_statement(stmt->next);
    }*/
}

// Función principal del intérprete
void execute_program(ast_node *root) {
    if (!root) {
        runtime_log("❌ No hay programa para ejecutar\n");
        return;
    }
    
    runtime_log("\n🚀 === INICIANDO EJECUCIÓN === 🚀\n");
    
    // Limpiar tabla de símbolos anterior
    cleanup_runtime();

    // Habilitar debug temporalmente para pruebas (comentar/desactivar en producción)
    set_runtime_debug(0);
    
    ast_node *main_node = find_main_method(root);
    if (main_node) {
        // Ejecutar sólo el main o su body (una vez)
        execute_statement(main_node);
    } else {
        // Ejecutar root una sola vez como fallback
        execute_statement(root);
    }

    // Para la gramática actual, ejecutar directamente el programa
    //runtime_log("▶️ Ejecutando programa principal...\n");
    //execute_statement(root);
    
    runtime_log("✅ === EJECUCIÓN COMPLETADA === ✅\n\n");
    
    // Mostrar estado final de variables
    show_symbol_table();
}

// Función para mostrar la tabla de símbolos
void show_symbol_table(void) {
    if (!symbol_table) {
        runtime_log("[SYMBOLS] Tabla de símbolos: vacía\n");
        return;
    }
    
    runtime_log("[SYMBOLS] === TABLA DE SÍMBOLOS ===\n");
    runtime_symbol_t *current = symbol_table;
    
    while (current) {
        char message[1024];
        message[0] = '\0';
        
        // Determinar tipo y valor
        switch (current->type) {
            case 0: // int
                snprintf(message, sizeof(message), "  %s: int = %d\n", 
                        current->name, current->value.int_val);
                break;
            case 1: // float
                snprintf(message, sizeof(message), "  %s: float = %.2f\n", 
                        current->name, current->value.float_val);
                break;
            case 2: // string
                snprintf(message, sizeof(message), "  %s: String = \"%s\"\n", 
                        current->name, current->value.string_val ? current->value.string_val : "");
                break;
            case 3: // boolean
                snprintf(message, sizeof(message), "  %s: boolean = %s\n", 
                        current->name, current->value.bool_val ? "true" : "false");
                break;
            case 4: // double
                snprintf(message, sizeof(message), "  %s: double = %.6f\n", 
                        current->name, current->value.double_val);
                break;
            case TYPE_ARRAY_INT: {
                runtime_array_t *arr = (runtime_array_t*) current->value.array_val;
                if (!arr) {
                    snprintf(message, sizeof(message), "  %s: int[] = uninitialized\n", current->name);
                } else {
                    // Construir representación tipo [1, 2, 3]
                    char buf[512];
                    size_t off = 0;
                    off += snprintf(buf + off, sizeof(buf) - off, "[");
                    for (int i = 0; i < arr->length && off + 20 < sizeof(buf); ++i) {
                        if (i) off += snprintf(buf + off, sizeof(buf) - off, ", ");
                        off += snprintf(buf + off, sizeof(buf) - off, "%d", arr->ints[i]);
                    }
                    if (off < sizeof(buf)) snprintf(buf + off, sizeof(buf) - off, "]");
                    snprintf(message, sizeof(message), "  %s: int[] = %s\n", current->name, buf);
                }
                break;
            }
            default:
                snprintf(message, sizeof(message), "  %s: unknown = ?\n", current->name);
        }
        
        runtime_log(message);
        current = current->next;
    }
    
    runtime_log("========================\n");
}

// Función para limpiar la tabla de símbolos
void cleanup_runtime(void) {
    runtime_symbol_t *current = symbol_table;
    while (current) {
        runtime_symbol_t *next = current->next;

        if (current->name) {
            free(current->name);
            current->name = NULL;
        }

        // Liberar strings si corresponde
        if (current->type == 2 && current->value.string_val) { free(current->value.string_val); current->value.string_val = NULL; }

        // Liberar arrays si corresponde
        if (current->type == TYPE_ARRAY_INT && current->value.array_val) {
            runtime_array_t *arr = (runtime_array_t*)current->value.array_val;
            if (arr->ints) free(arr->ints);
            free(arr);
            current->value.array_val = NULL;
        }

        // Desconectar y liberar el nodo
        current->next = NULL;
        free(current);
        current = next;
    }
    symbol_table = NULL;

    // Liberar cualquier array que quedó en el mapa (no asignado a símbolo)
    array_map_clear();

    runtime_log(" Tabla de símbolos limpiada correctamente\n");
}


// Función para verificar si una expresión es de tipo string
int is_string_expression(ast_node *node) {
    if (!node) return 0;
    
    switch (node->type) {
        case AST_STRING_LITERAL:
            return 1;
            
        case AST_VARIABLE: {
            // Buscar el tipo en la tabla de símbolos
            runtime_symbol_t *sym = find_or_create_symbol(node->data.var_name);
            return (sym->type == 2); // 2 = string
        }
        
        case AST_BINARY_OP: {
            // Si es concatenación, verificar si algún operando es string
            if (node->data.op.op == OP_PLUS) {
                return is_string_expression(node->data.op.left) || 
                       is_string_expression(node->data.op.right);
            }
            return 0;
        }
        
        default:
            return 0;
    }
}

// Función para obtener el valor string de una expresión
char* get_string_value(ast_node *node) {
    static char buf[1024];
    if (!node) { buf[0] = '\0'; return buf; }

    switch (node->type) {
        case AST_STRING_LITERAL:
            unescape_string_literal(node->data.string_value, buf, sizeof(buf));
            return buf;
        case AST_INT_LITERAL:
            snprintf(buf, sizeof(buf), "%d", node->data.int_value);
            return buf;
        case AST_FLOAT_LITERAL:
            snprintf(buf, sizeof(buf), "%.6f", node->data.float_value);
            return buf;
        case AST_DOUBLE_LITERAL:
            snprintf(buf, sizeof(buf), "%.6f", node->data.double_value);
            return buf;
        case AST_BOOL_LITERAL:
            snprintf(buf, sizeof(buf), "%s", node->data.bool_value ? "true" : "false");
            return buf;
        case AST_VARIABLE: {
            runtime_symbol_t *sym = find_or_create_symbol(node->data.var_name);
            if (!sym) { buf[0] = '\0'; return buf; }
            switch (sym->type) {
                case TYPE_INT:    snprintf(buf, sizeof(buf), "%d", sym->value.int_val); break;
                case TYPE_FLOAT:  snprintf(buf, sizeof(buf), "%.6f", sym->value.float_val); break;
                case TYPE_DOUBLE: snprintf(buf, sizeof(buf), "%.6f", sym->value.double_val); break;
                case TYPE_STRING: strncpy(buf, sym->value.string_val ? sym->value.string_val : "", sizeof(buf)-1); buf[sizeof(buf)-1] = '\0'; break;
                case TYPE_BOOLEAN: snprintf(buf, sizeof(buf), "%s", sym->value.bool_val ? "true" : "false"); break;
                case TYPE_ARRAY_INT: snprintf(buf, sizeof(buf), "[array:%p]", sym->value.array_val); break;
                default: buf[0] = '\0'; break;
            }
            return buf;
        }
        default:
            // For other expressions evaluate as int and format
            {
                /* Primero evaluar (puede mutar el nodo, p.ej. method.toString()) */
                int ev = evaluate_expression(node);

                /* Si la evaluación transformó el nodo en un literal string, devolverlo */
                if (node->type == AST_STRING_LITERAL && node->data.string_value) {
                    unescape_string_literal(node->data.string_value, buf, sizeof(buf));
                    return buf;
                }

                /* Si es booleano -> formatear true/false */
                if (node_is_boolean_expression(node)) {
                    snprintf(buf, sizeof(buf), "%s", ev ? "true" : "false");
                    return buf;
                }

                /* Si produce double/float -> obtener su valor real */
                if (node_is_floatish(node)) {
                    double dv = eval_node_as_double(node);
                    snprintf(buf, sizeof(buf), "%.6f", dv);
                    return buf;
                }

                /* Fallback: entero */
                snprintf(buf, sizeof(buf), "%d", ev);
                return buf;
            }
    }
}

void build_concatenated_string(ast_node *expr, char *result) {
    if (!result) return;
    result[0] = '\0';
    if (!expr) return;

    // Si es binaria y es '+', concatenar recursivamente
    if (expr->type == AST_BINARY_OP && expr->data.op.op == OP_PLUS) {
        char left[1024], right[1024];
        build_concatenated_string(expr->data.op.left, left);
        build_concatenated_string(expr->data.op.right, right);
        // Si subexpresiones vacías, intentar obtener su string directo
        if (left[0] == '\0' && expr->data.op.left) convert_to_string(expr->data.op.left, left);
        if (right[0] == '\0' && expr->data.op.right) convert_to_string(expr->data.op.right, right);
        snprintf(result, 1024, "%s%s", left, right);
        return;
    }

    // Sino, es un nodo que convertimos a string
    convert_to_string(expr, result);
}

void convert_to_string(ast_node *node, char *str) {
    if (!str) return;
    if (!node) { str[0] = '\0'; return; }
    char *v = get_string_value(node);
    strncpy(str, v, 512-1);
    str[512-1] = '\0';
}

void convert_symbol_to_string(runtime_symbol_t *sym, char *str) {
    if (!sym || !str) {
        strcpy(str, "");
        return;
    }
    
    switch (sym->type) {
        case 0: // int
            sprintf(str, "%d", sym->value.int_val);
            break;
        case 1: // float
            sprintf(str, "%.2f", sym->value.float_val);
            break;
        case 2: // string
            strcpy(str, sym->value.string_val ? sym->value.string_val : "");
            break;
        case 3: // boolean
            strcpy(str, sym->value.bool_val ? "true" : "false");
            break;
        case 4: // double
            sprintf(str, "%.6f", sym->value.double_val);
            break;
        default:
            strcpy(str, "");
    }
}

static double eval_node_as_double(ast_node *n) {
    if (!n) return 0.0;
    switch (n->type) {
        case AST_DOUBLE_LITERAL: return n->data.double_value;
        case AST_FLOAT_LITERAL:  return (double)n->data.float_value;
        case AST_INT_LITERAL:    return (double)n->data.int_value;
        case AST_BOOL_LITERAL:   return n->data.bool_value ? 1.0 : 0.0;
        case AST_VARIABLE: {
            runtime_symbol_t *s = find_or_create_symbol(n->data.var_name);
            if (!s) return 0.0;
            switch (s->type) {
                case 0: return (double)s->value.int_val;
                case 1: return (double)s->value.float_val;
                case 4: return s->value.double_val;
                default: return (double)evaluate_expression(n);
            }
        }
        case AST_BINARY_OP: {
            double L = eval_node_as_double(n->data.op.left);
            double R = eval_node_as_double(n->data.op.right);
            switch (n->data.op.op) {
                case OP_PLUS:  return L + R;
                case OP_MINUS: return L - R;
                case OP_MULT:  return L * R;
                case OP_DIV:   return R != 0.0 ? (L / R) : 0.0;
                case OP_MOD:   return (R != 0.0) ? (double)((long)L % (long)R) : 0.0;
                default: return (double)evaluate_expression(n);
            }
        }
        case AST_UNARY_OP:
            return -eval_node_as_double(n->data.op.left);
        default:
            return (double)evaluate_expression(n);
    }
}

// ...existing code...
static int node_is_floatish(ast_node *n) {
    if (!n) return 0;
    if (n->type == AST_FLOAT_LITERAL || n->type == AST_DOUBLE_LITERAL) return 1;
    if (n->type == AST_VARIABLE) {
        runtime_symbol_t *s = find_or_create_symbol(n->data.var_name);
        if (!s) return 0;
        return (s->type == 1 || s->type == 4);
    }
    if (n->type == AST_BINARY_OP) {
        return node_is_floatish(n->data.op.left) || node_is_floatish(n->data.op.right);
    }
    if (n->type == AST_UNARY_OP) return node_is_floatish(n->data.op.left);
    return 0;
}

// NEW: detecta si un nodo produce un valor booleano
static int node_is_boolean_expression(ast_node *n) {
    if (!n) return 0;
    if (n->type == AST_BOOL_LITERAL) return 1;
    if (n->type == AST_UNARY_OP && n->data.op.op == OP_NOT) return 1;
    if (n->type == AST_BINARY_OP) {
        switch (n->data.op.op) {
            case OP_EQUALS:
            case OP_NOT_EQUALS:
            case OP_LESS:
            case OP_GREATER:
            case OP_LESS_EQUALS:
            case OP_GREATER_EQUALS:
            case OP_AND:
            case OP_OR:
                return 1;
            default:
                return 0;
        }
    }
    return 0;
}
