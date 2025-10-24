// ...existing code...
#include "../include/runtime.h"
#include "../include/ast.h"
#include "../include/gui.h"
#include "../include/semantic.h"
#include "../include/codegen_arm64.h"
#include "../include/codegen_ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdint.h> 

#ifndef TYPE_INT
#define TYPE_INT 0
#define TYPE_FLOAT 1
#define TYPE_STRING 2
#define TYPE_BOOLEAN 3
#define TYPE_DOUBLE 4
#endif


#ifndef TYPE_ARRAY_INT
#define TYPE_ARRAY_INT 100
#define TYPE_ARRAY_FLOAT 101
#define TYPE_ARRAY_DOUBLE 102
#define TYPE_ARRAY_STRING 103
#define TYPE_ARRAY_CHAR 104
#define TYPE_ARRAY_BOOLEAN 105
#endif

// Tabla de símbolos para variables
typedef struct runtime_symbol {
    char *name;
    int type;  // 0=int, 1=float, 2=string, 3=boolean, 4=double, TYPE_ARRAY_INT for arrays
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



// Tabla de arrays en tiempo de ejecución
typedef struct {
    int elem_type; // usar códigos compatibles con sym.type o semantic types
    int length;
    int *ints;     // por ahora solo soporte int[]
    char **strings;
} runtime_array_t;

#define TYPE_ARRAY_INT 100

typedef struct array_map {
    ast_node *expr;
    runtime_array_t *arr;
    struct array_map *next;
} array_map_t;


static array_map_t *array_map_head = NULL;
static ConsolePrintCallback console_callback = NULL;
static runtime_symbol_t **scope_stack = NULL;
static int scope_depth = 0;
static int scope_capacity = 0;

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
static CodegenARM64 g_codegen;
static int g_codegen_enabled = 0;
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

// ----------------- Código ARM64 por ejecución -----------------
void runtime_codegen_start(const char *out_path) {
    if (!out_path || !*out_path) out_path = "reports/out_arm64.s";
    if (codegen_arm64_begin(&g_codegen, out_path) == 0) {
        g_codegen_enabled = 1;
    } else {
        g_codegen_enabled = 0;
        fprintf(stderr, "[ARM64] No se pudo abrir %s\n", out_path);
    }
}


void runtime_codegen_finish(void) {
    if (g_codegen_enabled) {
        codegen_arm64_end(&g_codegen);
        g_codegen_enabled = 0;
    }
}

// Wrappers de impresión: reemplaza tus printf por estos
void rt_println_int(long v) {
    printf("%ld\n", v);
    if (g_codegen_enabled) codegen_arm64_println_int(&g_codegen, v);
}

void rt_println_double(double v) {
    printf("%f\n", v);
    if (g_codegen_enabled) codegen_arm64_println_double(&g_codegen, v);
}

void rt_println_string(const char *s) {
    printf("%s\n", s ? s : "(null)");
    if (g_codegen_enabled) codegen_arm64_println_string(&g_codegen, s);
}
static void runtime_println_string_gui(const char *s) {
    char line[2048];
    snprintf(line, sizeof(line), "%s\n", s ? s : "(null)");
    console_print_program(line);
    if (g_codegen_enabled) codegen_arm64_println_string(&g_codegen, s ? s : "(null)");
}

static void runtime_println_int_gui(long v) {
    char line[64];
    snprintf(line, sizeof(line), "%ld\n", v);
    console_print_program(line);
    if (g_codegen_enabled) codegen_arm64_println_int(&g_codegen, v);
}

static void runtime_println_double_gui(double v) {
    char line[128];
    snprintf(line, sizeof(line), "%f\n", v);
    console_print_program(line);
    if (g_codegen_enabled) codegen_arm64_println_double(&g_codegen, v);
}



/* push a new empty scope */
static void push_scope(void) {
    if (scope_depth + 1 > scope_capacity) {
        int newcap = scope_capacity == 0 ? 8 : scope_capacity * 2;
        scope_stack = realloc(scope_stack, sizeof(runtime_symbol_t*) * newcap);
        for (int i = scope_capacity; i < newcap; ++i) scope_stack[i] = NULL;
        scope_capacity = newcap;
    }
    scope_stack[scope_depth++] = NULL;
}

/* free all symbols in a scope list */
static void free_scope_list(runtime_symbol_t *list) {
    runtime_symbol_t *cur = list;
    while (cur) {
        runtime_symbol_t *n = cur->next;
        if (cur->name) free(cur->name);
        if (cur->type == TYPE_STRING && cur->value.string_val) free(cur->value.string_val);
        if (cur->type == TYPE_ARRAY_INT && cur->value.array_val) {
            runtime_array_t *arr = (runtime_array_t*)cur->value.array_val;
            if (arr->ints) free(arr->ints);
            if (arr->strings) {
                for (int i = 0; i < arr->length; ++i) if (arr->strings[i]) free(arr->strings[i]);
                free(arr->strings);
            }
            free(arr);;
        }
        free(cur);
        cur = n;
    }
}

/* pop the top scope and free its symbols */
static void pop_scope(void) {
    if (scope_depth <= 0) return;
    runtime_symbol_t *top = scope_stack[--scope_depth];
    free_scope_list(top);
    scope_stack[scope_depth] = NULL;
}


/* create and insert a symbol in the current (top) scope; returns the new symbol */
static runtime_symbol_t* create_symbol_in_current_scope(const char *name) {
    if (!name) return NULL;
    if (scope_depth == 0) push_scope();
    runtime_symbol_t *new_symbol = malloc(sizeof(runtime_symbol_t));
    memset(new_symbol, 0, sizeof(runtime_symbol_t));
    new_symbol->name = strdup(name);
    new_symbol->type = -1;
    new_symbol->value.int_val = 0;
    new_symbol->value.string_val = NULL;
    new_symbol->value.array_val = NULL;
    /* insert at head of top scope list */
    new_symbol->next = scope_stack[scope_depth - 1];
    scope_stack[scope_depth - 1] = new_symbol;
    return new_symbol;
}


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
static void unescape_string_literal(const char *src, char *dst, size_t dstlen);

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

static runtime_symbol_t* find_symbol_local(const char *name) {
    if (!name) return NULL;
    for (int i = scope_depth - 1; i >= 0; --i) {
        runtime_symbol_t *cur = scope_stack[i];
        while (cur) {
            if (strcmp(cur->name, name) == 0) return cur;
            cur = cur->next;
        }
    }
    return NULL;
}

int runtime_codegen_generate_from_ast(ast_node *root, const char *out_path) {
    return codegen_arm64_generate(root, out_path ? out_path : "reports/out_arm64.s");
}

// Función para buscar/crear variables en la tabla de símbolos
runtime_symbol_t* find_or_create_symbol(const char *name) {
    if (!name) return NULL;
    runtime_symbol_t *sym = find_symbol_local(name);
    if (sym) return sym;
    runtime_symbol_t *created = create_symbol_in_current_scope(name);
    // Log de creación (solo visible si debug activado)
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "🔧 Created symbol '%s' at scope_depth=%d\n", name, scope_depth-1);
        runtime_log(msg);
    }
    return created;
}

// ----------------- Helpers / builtins mínimos -----------------

static int handle_increment_decrement(ast_node *expr, int delta, int is_post) {
    if (!expr || !expr->data.op.left || expr->data.op.left->type != AST_VARIABLE) {
        if (expr && expr->data.op.left) return evaluate_expression(expr->data.op.left);
        return 0;
    }
    
    const char *varname = expr->data.op.left->data.var_name;
    /* Buscar la variable existente en los scopes; NO crear una nueva */
    runtime_symbol_t *sym = find_symbol_local(varname);
    if (!sym) {
        /* variable no encontrada -> no modificar, devolver lectura segura */
        char msg[256];
        snprintf(msg, sizeof(msg), "⚠️ ++/-- sobre variable no declarada: %s\n", varname);
        runtime_log(msg);
        return evaluate_expression(expr->data.op.left);
    }

    /* Logging: antes y después */
    if (sym->type == TYPE_INT) {
        int before = sym->value.int_val;
        sym->value.int_val += delta;
        int after = sym->value.int_val;
        char msg[256];
        snprintf(msg, sizeof(msg), "++/-- on '%s' (int) : %d -> %d (post=%d)\n", varname, before, after, is_post);
        runtime_log(msg);
        return is_post ? before : after;
    }
    if (sym->type == TYPE_FLOAT) {
        float beforef = sym->value.float_val;
        sym->value.float_val += delta;
        float afterf = sym->value.float_val;
        char msg[256];
        snprintf(msg, sizeof(msg), "++/-- on '%s' (float) : %.6f -> %.6f (post=%d)\n", varname, beforef, afterf, is_post);
        runtime_log(msg);
        return is_post ? (int)beforef : (int)afterf;
    }
    if (sym->type == TYPE_DOUBLE) {
        double befored = sym->value.double_val;
        sym->value.double_val += delta;
        double afterd = sym->value.double_val;
        char msg[256];
        snprintf(msg, sizeof(msg), "++/-- on '%s' (double) : %.6f -> %.6f (post=%d)\n", varname, befored, afterd, is_post);
        runtime_log(msg);
        return is_post ? (int)befored : (int)afterd;
    }

    /* Si llega aquí, no es numérico */
    runtime_log("⚠️ ++/-- sobre tipo no numérico\n");
    return evaluate_expression(expr->data.op.left);
}


char *runtime_eval_as_string(struct ast_node *arg) {
    static char buf[1024];
    if (!arg) { buf[0]='\0'; return buf; }

    /* Si es literal de cadena, devolver su contenido sin las comillas */
    if (arg->type == AST_STRING_LITERAL) {
        unescape_string_literal(arg->data.string_value, buf, sizeof(buf));
        return buf;
    }

    /* Intentar obtener una representación string de la expresión (variables, concat, métodos, arrays, etc.) */
    {
        char *s = get_string_value(arg);
        if (s && s[0] != '\0') {
            strncpy(buf, s, sizeof(buf)-1);
            buf[sizeof(buf)-1] = '\0';
            return buf;
        }
    }

    /* Fallback: evaluar como número/boolean y convertir a string */
    {
        int v = evaluate_expression(arg);
        snprintf(buf, sizeof(buf), "%d", v);
        return buf;
    }
}

int builtin_dispatch(const char *fullname, struct ast_node *arg, int *out_int, double *out_double, char **out_str) {
    if (!fullname) return -1;

    // Integer.parseInt
    if ((strcmp(fullname, "Integer.parseInt") == 0 || strcmp(fullname, "Integer.parse_int") == 0) && out_int) {
        char *s = runtime_eval_as_string(arg);
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

    // Arrays.indexOf(collection, value)
    if (strcmp(fullname, "Arrays.indexOf") == 0 && arg) {
        ast_node *first = arg;
        ast_node *second = arg->next;
        if (!first || !second) { if (out_int) *out_int = -1; return 0; }

        if (first->type == AST_VARIABLE) {
            runtime_symbol_t *sym = find_symbol_local(first->data.var_name);
            if (sym && sym->value.array_val) {
                runtime_array_t *a = (runtime_array_t*)sym->value.array_val;
                if (!a) { if (out_int) *out_int = -1; return 0; }

                // int[]
                if (a->elem_type == 0) {
                    int target = evaluate_expression(second);
                    for (int i = 0; i < a->length; ++i) {
                        if (a->ints && a->ints[i] == target) { if (out_int) *out_int = i; return 0; }
                    }
                    if (out_int) *out_int = -1;
                    return 0;
                }

                // String[]
                if (a->elem_type == TYPE_STRING) {
                    char *target = runtime_eval_as_string(second);
                    for (int i = 0; i < a->length; ++i) {
                        if (a->strings && a->strings[i] && strcmp(a->strings[i], target) == 0) {
                            if (out_int) *out_int = i;
                            return 0;
                        }
                    }
                    if (out_int) *out_int = -1;
                    return 0;
                }
            }
        }

        if (out_int) *out_int = -1;
        return 0;
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
    } else if (elem_type == TYPE_STRING) { // string[]
        if (size > 0) {
            arr->strings = calloc(size, sizeof(char*));
            for (int i = 0; i < size; ++i) arr->strings[i] = NULL;
        } else arr->strings = NULL;
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
        } else if (elem_type == TYPE_STRING) {
            // obtener representación string de la expresión (literales o variables)
            char *s = runtime_eval_as_string(cur);
            arr->strings[i] = s ? strdup(s) : strdup("");
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
            if (m->arr->strings) {
                for (int i = 0; i < m->arr->length; ++i) if (m->arr->strings[i]) free(m->arr->strings[i]);
                free(m->arr->strings);
            }
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

            runtime_symbol_t *sym = find_symbol_local(expr->data.var_name);
            if (!sym) {
                char msg[256];
                snprintf(msg, sizeof(msg), "⚠️ Lectura de variable no declarada: %s (devuelvo 0)\n", expr->data.var_name);
                runtime_log(msg);
                return 0;
            }

            // --- DEBUG: mostrar tipo/valor al leer la variable ---
            {
                char dbg[256];
                switch (sym->type) {
                    case 0: snprintf(dbg, sizeof(dbg), "READ var='%s' type=int value=%d\n", sym->name, sym->value.int_val); break;
                    case 1: snprintf(dbg, sizeof(dbg), "READ var='%s' type=float value=%f\n", sym->name, sym->value.float_val); break;
                    case 2: snprintf(dbg, sizeof(dbg), "READ var='%s' type=string value=\"%s\"\n", sym->name, sym->value.string_val?sym->value.string_val:""); break;
                    case 3: snprintf(dbg, sizeof(dbg), "READ var='%s' type=boolean value=%d\n", sym->name, sym->value.bool_val); break;
                    case 4: snprintf(dbg, sizeof(dbg), "READ var='%s' type=double value=%f\n", sym->name, sym->value.double_val); break;
                    case TYPE_ARRAY_INT: snprintf(dbg, sizeof(dbg), "READ var='%s' type=int[] (ptr=%p)\n", sym->name, sym->value.array_val); break;
                    default: snprintf(dbg, sizeof(dbg), "READ var='%s' type=unknown\n", sym->name); break;
                }
                runtime_log(dbg);
            }
            // RETORNAR SEGÚN EL TIPO DE LA VARIABLE
            switch (sym->type) {
                case 0: return sym->value.int_val;           // int
                case 1: return (int)sym->value.float_val;    // float → int
                case 2: return (int)strlen(sym->value.string_val ? sym->value.string_val : ""); // string → longitud
                case 3: return sym->value.bool_val;          // boolean
                case 4: return (int)sym->value.double_val;   // double → int
                case TYPE_ARRAY_INT: return 0;
                default: return 0;
            }
        }

        case AST_ARRAY_ACCESS: {
            // expr->data.array_access.array_name and index expression
            const char *name = expr->data.array_access.array_name;
            ast_node *index_expr = expr->data.array_access.index; 
            if (!name || !index_expr) return 0;
            /* No crear símbolo al leer un array: usar solo lookup */
            runtime_symbol_t *sym = find_symbol_local(name);
            if (!sym) {
                char msg[256];
                snprintf(msg, sizeof(msg), "⚠️ Lectura de array no declarado: %s (devuelvo 0)\n", name);
                runtime_log(msg);
                return 0;
            }
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

        // ...existing code...
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
                /* No crear receiver si no existe; si no existe, inicializar a cadena vacía */
                runtime_symbol_t *recv_sym = find_symbol_local(recv_name);
                if (!recv_sym) {
                    char msg[256];
                    snprintf(msg, sizeof(msg), "⚠️ append sobre receiver no declarado: %s (creando como String)\n", recv_name);
                    runtime_log(msg);
                    recv_sym = create_symbol_in_current_scope(recv_name);
                    recv_sym->type = TYPE_STRING;
                    recv_sym->value.string_val = strdup("");
                }
                char *argstr = runtime_eval_as_string(expr->data.method_call.arg);
                if (recv_sym->type != TYPE_STRING) {
                    recv_sym->type = TYPE_STRING;
                    if (recv_sym->value.string_val) free(recv_sym->value.string_val);
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
                /* NO crear ni mutar el AST: devolver longitud o 0 */
                runtime_symbol_t *recv_sym = find_symbol_local(recv_name);
                if (recv_sym && recv_sym->type == TYPE_STRING && recv_sym->value.string_val) {
                    return (int)strlen(recv_sym->value.string_val);
                } else {
                    return 0;
                }
            }

            // length() para arrays o strings (receiver.length)
            if (recv_name[0] != '\0' && (strcmp(mname, "length") == 0 || strcmp(mname, "length()") == 0)) {
                runtime_symbol_t *recv_sym = find_symbol_local(recv_name);
                if (recv_sym && recv_sym->type == TYPE_ARRAY_INT && recv_sym->value.array_val) {
                    runtime_array_t *arr = (runtime_array_t*)recv_sym->value.array_val;
                    return arr->length;
                }
                if (recv_sym && recv_sym->type == TYPE_STRING && recv_sym->value.string_val) {
                    return (int)strlen(recv_sym->value.string_val);
                }
            }


            // array.add(value) -> ampliar array (soporte int[] y String[])
            if (recv_name[0] != '\0' && strcmp(mname, "add") == 0) {
                runtime_symbol_t *recv_sym = find_symbol_local(recv_name);
                if (!recv_sym || !recv_sym->value.array_val) return 0;
                runtime_array_t *arr = (runtime_array_t*)recv_sym->value.array_val;
                if (!arr) return 0;
                // valor a agregar: puede ser int o string
                if (arr->elem_type == 0) {
                    int v = evaluate_expression(expr->data.method_call.arg);
                    arr->ints = realloc(arr->ints, sizeof(int)*(arr->length + 1));
                    arr->ints[arr->length] = v;
                    arr->length += 1;
                    return arr->length;
                } else if (arr->elem_type == TYPE_STRING) {
                    char *s = runtime_eval_as_string(expr->data.method_call.arg);
                    arr->strings = realloc(arr->strings, sizeof(char*)*(arr->length + 1));
                    arr->strings[arr->length] = s ? strdup(s) : strdup("");
                    arr->length += 1;
                    return arr->length;
                }
                return 0;
            }
            // Arrays.toString / builtin_dispatch (Integer.parseInt, Double.parseDouble, String.valueOf, etc.)
            {
                char fullname[512];
                snprintf(fullname, sizeof(fullname), "%s.%s", recv_name, mname);
                int out_i = 0; double out_d = 0; char *out_s = NULL;
                int t = builtin_dispatch(fullname, expr->data.method_call.arg, &out_i, &out_d, &out_s);
                if (t == 0) {
                    // Integer.parseInt -> devolver entero
                    return out_i;
                }
                if (t == 1) {
                    // Double.parseDouble -> devolver cast a int (evaluate_expression devuelve int)
                    return (int)out_d;
                }
                if (t == 2 && out_s) {
                    // String.valueOf -> devolver longitud (evaluate_expression requiere int)
                    int len = (int)strlen(out_s);
                    free(out_s); // builtin_dispatch devuelve strdup, liberamos aquí
                    return len;
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
            operator_type effective_op = expr->data.op.op;
            
            switch (effective_op) {
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
                            return (int)eval_node_as_double(expr);
                        }
                        int left = evaluate_expression(expr->data.op.left);
                        int right = evaluate_expression(expr->data.op.right);
                        return left + right;
                    }
                }
                    
                // ⭐ RESTO DE OPERADORES NUMÉRICOS
                case OP_MINUS: {
                    if (node_is_floatish(expr->data.op.left) || node_is_floatish(expr->data.op.right)) {
                        return (int)eval_node_as_double(expr);
                    }
                    return evaluate_expression(expr->data.op.left) - evaluate_expression(expr->data.op.right);
                }

                case OP_MULT: {
                    if (node_is_floatish(expr->data.op.left) || node_is_floatish(expr->data.op.right)) {
                        return (int)eval_node_as_double(expr);
                    }
                    return evaluate_expression(expr->data.op.left) * evaluate_expression(expr->data.op.right);
                }
                
                case OP_DIV: {
                    if (node_is_floatish(expr->data.op.left) || node_is_floatish(expr->data.op.right)) {
                        return (int)eval_node_as_double(expr);
                    }
                    int left = evaluate_expression(expr->data.op.left);
                    int right = evaluate_expression(expr->data.op.right);
                    return right != 0 ? left / right : 0;
                }

                case OP_MOD: {
                    if (node_is_floatish(expr->data.op.left) || node_is_floatish(expr->data.op.right)) {
                        return (int)eval_node_as_double(expr);
                    }
                    int left = evaluate_expression(expr->data.op.left);
                    int right = evaluate_expression(expr->data.op.right);
                    return right != 0 ? left % right : 0;
                }
                
                // OPERADORES RELACIONALES
                case OP_EQUALS: {
                    // Simplificado: evaluar ambos lados y comparar (cubre números y booleans and strings arriba)
                    if (is_string_expression(expr->data.op.left) && is_string_expression(expr->data.op.right)) {
                        char *left_str = get_string_value(expr->data.op.left);
                        char *right_str = get_string_value(expr->data.op.right);
                        int result = (strcmp(left_str, right_str) == 0) ? 1 : 0;
                        char message[256];
                        snprintf(message, sizeof(message), " String equals: '%s' == '%s' = %s\n", left_str, right_str, result ? "true" : "false");
                        runtime_log(message);
                        return result;
                    }
                    int left = evaluate_expression(expr->data.op.left);
                    int right = evaluate_expression(expr->data.op.right);
                    int result = (left == right) ? 1 : 0;
                    char message[256];
                    snprintf(message, sizeof(message), " Numeric/Bool equals: %d == %d = %s\n", left, right, result ? "true" : "false");
                    runtime_log(message);
                    return result;
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
                    double L = eval_node_as_double(expr->data.op.left);
                    double R = eval_node_as_double(expr->data.op.right);
                    return (L < R) ? 1 : 0;
                }
                
                case OP_GREATER: {
                    double L = eval_node_as_double(expr->data.op.left);
                    double R = eval_node_as_double(expr->data.op.right);
                    return (L > R) ? 1 : 0;
                }
                
                case OP_LESS_EQUALS: {
                    double L = eval_node_as_double(expr->data.op.left);
                    double R = eval_node_as_double(expr->data.op.right);
                    return (L <= R) ? 1 : 0;
                }
                
                case OP_GREATER_EQUALS: {
                    double L = eval_node_as_double(expr->data.op.left);
                    double R = eval_node_as_double(expr->data.op.right);
                    return (L >= R) ? 1 : 0;
                }
                
                case OP_AND: {
                    int left = evaluate_expression(expr->data.op.left);
                    if (!left) return 0;
                    int right = evaluate_expression(expr->data.op.right);
                    return (left && right) ? 1 : 0;
                }
                
                case OP_OR: {
                    int left = evaluate_expression(expr->data.op.left);
                    if (left) return 1;
                    int right = evaluate_expression(expr->data.op.right);
                    return (left || right) ? 1 : 0;
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
                case OP_NOT: return !operand;
                case OP_UMINUS: return -operand;
                case OP_INCREMENT:
                case OP_POST_INCREMENT: return handle_increment_decrement(expr, 1, expr->data.op.op == OP_POST_INCREMENT);
                case OP_DECREMENT:
                case OP_POST_DECREMENT: return handle_increment_decrement(expr, -1, expr->data.op.op == OP_POST_DECREMENT);
                default: return operand;
            }
        }

        case AST_STRING_EQUALS: {
            char *left_str = get_string_value(expr->data.string_equals.left_string);
            char *right_str = get_string_value(expr->data.string_equals.right_expr);
            int result = (strcmp(left_str, right_str) == 0) ? 1 : 0;
            char message[512];
            snprintf(message, sizeof(message), "🔍 String.equals(): '%s'.equals('%s') = %s\n", left_str, right_str, result ? "true" : "false");
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

    switch (stmt->type) {
        case AST_DECLARATION: {
            int var_type = TYPE_INT;
            if (stmt->data.declaration.var_type && stmt->data.declaration.var_type->data.type_name) {
                char *type_name = stmt->data.declaration.var_type->data.type_name;
                if (strcmp(type_name, "int") == 0) var_type = TYPE_INT;
                else if (strcmp(type_name, "float") == 0) var_type = TYPE_FLOAT;
                else if (strcmp(type_name, "String") == 0) var_type = TYPE_STRING;
                else if (strcmp(type_name, "boolean") == 0) var_type = TYPE_BOOLEAN;
                else if (strcmp(type_name, "double") == 0) var_type = TYPE_DOUBLE;
                else {
                    size_t tn = strlen(type_name);
                    if (tn >= 2 && strcmp(type_name + tn - 2, "[]") == 0) {
                        if (strncmp(type_name, "int", 3) == 0) var_type = TYPE_ARRAY_INT;
                        else if (strncmp(type_name, "float", 5) == 0) var_type = TYPE_ARRAY_FLOAT;
                        else if (strncmp(type_name, "double", 6) == 0) var_type = TYPE_ARRAY_DOUBLE;
                        else if (strncmp(type_name, "String", 6) == 0) var_type = TYPE_ARRAY_STRING;
                        else var_type = -1;
                    }
                }
            }

            /* crear/obtener símbolo en scope actual */
            runtime_symbol_t *sym = find_or_create_symbol(stmt->data.declaration.var_name);
            if (!sym) break;
            sym->type = var_type;

            /* Si hay inicializador, tratar casos especiales (arrays, copia desde otra var, literales, expresiones) */
            if (stmt->data.declaration.value) {
                ast_node *v = stmt->data.declaration.value;

                /* --- ARRAY inicializers --- */
                if (var_type == TYPE_ARRAY_INT) {
                    runtime_array_t *arr = NULL;
                    if (v->type == AST_NEW_ARRAY_INIT) {
                        /* new int[] { ... } -> evaluate_expression crea arr en array_map */
                        evaluate_expression(v);
                        arr = array_map_take(v);
                    } else if (v->type == AST_ARRAY_INIT) {
                        arr = runtime_array_from_init_list(v->data.array_decl.init_values, 0);
                    } else if (v->type == AST_VARIABLE) {
                        runtime_symbol_t *rhs = find_symbol_local(v->data.var_name);
                        if (rhs && rhs->type == TYPE_ARRAY_INT) arr = (runtime_array_t*) rhs->value.array_val;
                    }
                    if (arr) {
                        sym->type = TYPE_ARRAY_INT;
                        sym->value.array_val = arr;
                        char msg[256];
                        snprintf(msg, sizeof(msg), " Asignación array (brace/new): %s (len=%d)\n", sym->name, arr->length);
                        runtime_log(msg);
                        break; /* done with this declaration */
                    }
                }

                /* --- RHS copia desde otra variable --- */
                if (v->type == AST_VARIABLE) {
                    runtime_symbol_t *rhs = find_symbol_local(v->data.var_name);
                    if (rhs) {
                        sym->type = rhs->type;
                        if (rhs->type == TYPE_STRING) {
                            if (sym->value.string_val) free(sym->value.string_val);
                            sym->value.string_val = rhs->value.string_val ? strdup(rhs->value.string_val) : strdup("");
                        } else if (rhs->type == TYPE_ARRAY_INT) {
                            sym->value.array_val = rhs->value.array_val; /* compartir puntero por ahora */
                        } else if (rhs->type == TYPE_INT) {
                            sym->value.int_val = rhs->value.int_val;
                        } else if (rhs->type == TYPE_FLOAT) {
                            sym->value.float_val = rhs->value.float_val;
                        } else if (rhs->type == TYPE_DOUBLE) {
                            sym->value.double_val = rhs->value.double_val;
                        } else if (rhs->type == TYPE_BOOLEAN) {
                            sym->value.bool_val = rhs->value.bool_val;
                        }
                        break;
                    }
                }

                /* --- Literales / expresiones normales --- */
                if (v->type == AST_INT_LITERAL) {
                    sym->type = TYPE_INT; sym->value.int_val = v->data.int_value;
                } else if (v->type == AST_FLOAT_LITERAL) {
                    sym->type = TYPE_FLOAT; sym->value.float_val = v->data.float_value;
                } else if (v->type == AST_DOUBLE_LITERAL) {
                    sym->type = TYPE_DOUBLE; sym->value.double_val = v->data.double_value;
                } else if (v->type == AST_STRING_LITERAL) {
                    sym->type = TYPE_STRING;
                    char tmp[1024]; unescape_string_literal(v->data.string_value, tmp, sizeof(tmp));
                    if (sym->value.string_val) free(sym->value.string_val);
                    sym->value.string_val = strdup(tmp);
                } else if (v->type == AST_BOOL_LITERAL) {
                    sym->type = TYPE_BOOLEAN; sym->value.bool_val = v->data.bool_value;
                } else {
                    /* expresiones generales: inferir tipo */
                    if (node_is_floatish(v)) {
                        sym->type = TYPE_DOUBLE;
                        sym->value.double_val = eval_node_as_double(v);
                    } else if (node_is_boolean_expression(v)) {
                        sym->type = TYPE_BOOLEAN;
                        sym->value.bool_val = evaluate_expression(v);
                    } else if (is_string_expression(v)) {
                        /* construir string desde la expresión */
                        if (sym->value.string_val) free(sym->value.string_val);
                        sym->type = TYPE_STRING;
                        sym->value.string_val = strdup(get_string_value(v));
                    } else {
                        sym->type = TYPE_INT;
                        sym->value.int_val = evaluate_expression(v);
                    }
                }
            } else {
                /* sin inicializador: valores por defecto */
                switch (sym->type) {
                    case TYPE_INT: sym->value.int_val = 0; break;
                    case TYPE_FLOAT: sym->value.float_val = 0.0f; break;
                    case TYPE_DOUBLE: sym->value.double_val = 0.0; break;
                    case TYPE_STRING: sym->value.string_val = strdup(""); break;
                    case TYPE_BOOLEAN: sym->value.bool_val = 0; break;
                    case TYPE_ARRAY_INT: sym->value.array_val = NULL; break;
                    default: break;
                }
            }
            break;
        }

        case AST_ASSIGNMENT: {
            const char *name = stmt->data.assignment.var_name;
            ast_node *value = stmt->data.assignment.value;
            if (!name || !value) break;

            /* localizar símbolo destino (no crear automáticamente) */
            runtime_symbol_t *sym = find_symbol_local(name);
            if (!sym) {
                char msg[256];
                snprintf(msg, sizeof(msg), "⚠️ Asignación a variable no declarada: %s (se ignora)\n", name);
                runtime_log(msg);
                break;
            }

            /* NEW array initializer -> tomar del mapa */
            if (value->type == AST_NEW_ARRAY_INIT) {
                evaluate_expression(value);
                runtime_array_t *arr = array_map_take(value);
                if (arr) {
                    sym->type = TYPE_ARRAY_INT;
                    sym->value.array_val = arr;
                    char msg[256];
                    snprintf(msg, sizeof(msg), " Asignación array (new): %s (len=%d)\n", sym->name, arr->length);
                    runtime_log(msg);
                    break;
                }
            }

            /* RHS según tipo: literales, init-list, variable, o expresión */
            if (value->type == AST_STRING_LITERAL) {
                char tmp[1024]; unescape_string_literal(value->data.string_value, tmp, sizeof(tmp));
                if (sym->type == TYPE_STRING && sym->value.string_val) free(sym->value.string_val);
                sym->type = TYPE_STRING;
                sym->value.string_val = strdup(tmp);
            } else if (value->type == AST_INT_LITERAL) {
                sym->type = TYPE_INT;
                sym->value.int_val = value->data.int_value;
            } else if (value->type == AST_FLOAT_LITERAL) {
                sym->type = TYPE_FLOAT;
                sym->value.float_val = value->data.float_value;
            } else if (value->type == AST_DOUBLE_LITERAL) {
                sym->type = TYPE_DOUBLE;
                sym->value.double_val = value->data.double_value;
            } else if (value->type == AST_BOOL_LITERAL) {
                sym->type = TYPE_BOOLEAN;
                sym->value.bool_val = value->data.bool_value;
            } else if (value->type == AST_ARRAY_INIT) {
                runtime_array_t *arr = runtime_array_from_init_list(value->data.array_decl.init_values, 0);
                if (arr) { sym->type = TYPE_ARRAY_INT; sym->value.array_val = arr; }
            } else if (value->type == AST_VARIABLE) {
                runtime_symbol_t *rhs = find_symbol_local(value->data.var_name);
                if (!rhs) {
                    char msg[256];
                    snprintf(msg, sizeof(msg), "⚠️ RHS variable no declarada: %s (se ignora)\n", value->data.var_name);
                    runtime_log(msg);
                    break;
                }
                /* copiar según tipo (strings duplicadas, arrays comparten puntero por ahora) */
                if (rhs->type == TYPE_STRING) {
                    if (sym->type == TYPE_STRING && sym->value.string_val) free(sym->value.string_val);
                    sym->type = TYPE_STRING;
                    sym->value.string_val = rhs->value.string_val ? strdup(rhs->value.string_val) : strdup("");
                } else if (rhs->type == TYPE_ARRAY_INT) {
                    sym->type = TYPE_ARRAY_INT;
                    sym->value.array_val = rhs->value.array_val;
                } else if (rhs->type == TYPE_INT) {
                    sym->type = TYPE_INT; sym->value.int_val = rhs->value.int_val;
                } else if (rhs->type == TYPE_FLOAT) {
                    sym->type = TYPE_FLOAT; sym->value.float_val = rhs->value.float_val;
                } else if (rhs->type == TYPE_DOUBLE) {
                    sym->type = TYPE_DOUBLE; sym->value.double_val = rhs->value.double_val;
                } else if (rhs->type == TYPE_BOOLEAN) {
                    sym->type = TYPE_BOOLEAN; sym->value.bool_val = rhs->value.bool_val;
                }
            } else {
                /* expresión genérica: inferir tipo */
                if (is_string_expression(value)) {
                    if (sym->type == TYPE_STRING && sym->value.string_val) free(sym->value.string_val);
                    sym->type = TYPE_STRING;
                    sym->value.string_val = strdup(get_string_value(value));
                } else if (node_is_floatish(value)) {
                    sym->type = TYPE_DOUBLE;
                    sym->value.double_val = eval_node_as_double(value);
                } else if (node_is_boolean_expression(value)) {
                    sym->type = TYPE_BOOLEAN;
                    sym->value.bool_val = evaluate_expression(value);
                } else {
                    sym->type = TYPE_INT;
                    sym->value.int_val = evaluate_expression(value);
                }
            }
            break;
        }

        case AST_IF: {
            int condition = evaluate_expression(stmt->data.if_stmt.condition);
            if (condition) {
                push_scope();
                if (stmt->data.if_stmt.then_branch) execute_statement(stmt->data.if_stmt.then_branch);
                pop_scope();
            } else {
                if (stmt->data.if_stmt.else_branch) {
                    push_scope();
                    execute_statement(stmt->data.if_stmt.else_branch);
                    pop_scope();
                }
            }
            break;
        }
        
        case AST_BREAK: runtime_break_flag = 1; break;
        case AST_CONTINUE: runtime_continue_flag = 1; break;

        case AST_WHILE: {
            /* Ejecutar: cada iteración tiene su propio scope para declaraciones locales */
            int iterations = 0;
            const int MAX_ITERATIONS = 10000;
            while (evaluate_expression(stmt->data.while_stmt.condition) && iterations < MAX_ITERATIONS && !runtime_break_flag) {
                push_scope(); /* scope temporal para la iteración */
                if (stmt->data.while_stmt.body) execute_statement(stmt->data.while_stmt.body);
                /* si se hizo continue dentro del cuerpo, limpiar flag y pop antes de continuar */
                if (runtime_continue_flag) { runtime_continue_flag = 0; pop_scope(); iterations++; continue; }
                /* pop del scope de la iteración */
                pop_scope();
                if (runtime_break_flag) break;
                iterations++;
            }
            /* asegurar flags a 0 */
            runtime_break_flag = 0; runtime_continue_flag = 0;
             break;
        }
                
        case AST_FOR: {
            /* Scope del for para init y variables del header */
            push_scope();
            if (stmt->data.for_stmt.init) execute_statement(stmt->data.for_stmt.init);
            int iterations = 0;
            const int MAX_ITERATIONS = 10000;
            while (iterations < MAX_ITERATIONS && !runtime_break_flag) {
                if (stmt->data.for_stmt.condition) {
                    int cond_result = evaluate_expression(stmt->data.for_stmt.condition);
                    if (!cond_result) break;
                }
                /* Cada iteración un scope temporal para declarations locales del body */
                push_scope();
                if (stmt->data.for_stmt.body) execute_statement(stmt->data.for_stmt.body);
                if (runtime_continue_flag) { runtime_continue_flag = 0; pop_scope(); if (stmt->data.for_stmt.increment) execute_statement(stmt->data.for_stmt.increment); iterations++; continue; }
                pop_scope();
                if (runtime_break_flag) break;
                if (stmt->data.for_stmt.increment) execute_statement(stmt->data.for_stmt.increment);
                iterations++;
            }
            pop_scope(); /* pop del scope del for (init vars) */
            runtime_break_flag = 0; runtime_continue_flag = 0;
             break;
        }
                
        case AST_RETURN: {
            // minimal: evaluate expression (no stack handling implemented)
            if (stmt->data.return_stmt.value) (void)evaluate_expression(stmt->data.return_stmt.value);
            break;
        }
        
        case AST_COMPOUND_STMT: {
            push_scope();
            ast_node *current = stmt->data.compound.statement_list;
            while (current) {
                execute_statement(current);
                /* Si se hizo 'break' o 'continue' dentro del bloque, detener la ejecución
                   de las declaraciones restantes del mismo compound (se manejará
                   por el loop superior). */
                if (runtime_break_flag || runtime_continue_flag) break;
                current = current->next;
            }
            pop_scope();
            break;
        }

        case AST_PRINT_STMT: {
            if (stmt->data.print_stmt.expression) {
                ast_node *expr = stmt->data.print_stmt.expression;
                /* DEBUG: imprimir AST y valor calculado antes del println */
                char *ast_repr = ast_to_string(expr);
                char valbuf[1024];
                valbuf[0] = '\0';
                strncpy(valbuf, get_string_value(expr), sizeof(valbuf)-1);
                valbuf[sizeof(valbuf)-1] = '\0';
                {
                    char dbg[2048];
                    snprintf(dbg, sizeof(dbg), "[RUNTIME-PRINT-DEBUG] expr_type=%d AST=%s -> value=\"%s\"\n",
                             expr->type, ast_repr ? ast_repr : "(null)", valbuf);
                    runtime_log(dbg);
                }
                if (ast_repr) free(ast_repr);

                char outbuf[2048] = {0};
                if (expr->type == AST_BINARY_OP && expr->data.op.op == OP_PLUS && is_string_expression(expr)) {
                    build_concatenated_string(expr, outbuf);
                } else {
                    strncpy(outbuf, valbuf, sizeof(outbuf)-1);
                }
                runtime_println_string_gui(outbuf);
            } else {
                runtime_println_string_gui("");
            }
            break;
        }

        case AST_PROGRAM: {
            /* Ejecutar lista de statements protegiendo contra flags de control */
            if (stmt->data.function_def.body) {
                ast_node *cur = stmt->data.function_def.body;
                while (cur) {
                    execute_statement(cur);
                    if (runtime_break_flag || runtime_continue_flag) break;
                    cur = cur->next;
                }
            } else if (stmt->next) {
                ast_node *cur = stmt->next;
                while (cur) {
                    execute_statement(cur);
                    if (runtime_break_flag || runtime_continue_flag) break;
                    cur = cur->next;
                }
            }
            break;
        }

        case AST_MAIN_FUNCTION: {
            push_scope();
            if (stmt->data.function_def.body) {
                ast_node *current = stmt->data.function_def.body;
                while (current) {
                    execute_statement(current);
                    if (runtime_break_flag || runtime_continue_flag) break;
                    current = current->next;
                }
            }
            pop_scope();
            break;
        }

        case AST_ARRAY_DECLARATION: {
            runtime_symbol_t *array_symbol = find_or_create_symbol(stmt->data.array_decl.array_name);
            array_symbol->type = TYPE_ARRAY_INT;
            runtime_array_t *arr = NULL;
            if (stmt->data.array_decl.size) {
                int size = evaluate_expression(stmt->data.array_decl.size);
                arr = runtime_array_new_empty(0, size);
            } else if (stmt->data.array_decl.init_values) {
                arr = runtime_array_from_init_list(stmt->data.array_decl.init_values, 0);
            }
            array_symbol->value.array_val = arr;
            break;
        }

        case AST_ARRAY_ACCESS: {
            (void)evaluate_expression(stmt);
            break;
        }
        
        case AST_ARRAY_ASSIGNMENT: {
            const char *name = stmt->data.array_assignment.array_name;
            ast_node *index_expr = stmt->data.array_assignment.index;
            ast_node *value_expr = stmt->data.array_assignment.value;
            if (!name || !index_expr || !value_expr) break;
            runtime_symbol_t *sym = find_or_create_symbol(name);
            if (!sym || sym->type != TYPE_ARRAY_INT) { runtime_log("⚠️ Asignación array inválida\n"); break; }
            runtime_array_t *arr = (runtime_array_t*)sym->value.array_val;
            if (!arr) { runtime_log("⚠️ Array no inicializado\n"); break; }
            int idx = evaluate_expression(index_expr);
            if (idx < 0 || idx >= arr->length) { runtime_log("⚠️ Índice fuera de rango\n"); break; }
            int val = evaluate_expression(value_expr);
            arr->ints[idx] = val;
            break;
        }

        
        case AST_FOREACH: {
            ast_node *type_node = stmt->data.foreach_stmt.var_type;
            char *loop_name = stmt->data.foreach_stmt.var_name;
            ast_node *collection = stmt->data.foreach_stmt.collection;
            ast_node *body = stmt->data.foreach_stmt.body;
            if (!loop_name || !collection) break;

            /* Obtener runtime array desde variable o new-array/init */
            runtime_array_t *arr = NULL;
            if (collection->type == AST_VARIABLE) {
                runtime_symbol_t *arr_sym = find_symbol_local(collection->data.var_name);
                if (arr_sym && arr_sym->type == TYPE_ARRAY_INT) arr = (runtime_array_t*)arr_sym->value.array_val;
            } else if (collection->type == AST_NEW_ARRAY_INIT) {
                evaluate_expression(collection);
                arr = array_map_take(collection);
            } else if (collection->type == AST_ARRAY_INIT) {
                arr = runtime_array_from_init_list(collection->data.array_decl.init_values, 0);
            }

            if (!arr) {
                runtime_log("⚠️ foreach: colección no iterable o no inicializada\n");
                break;
            }

            /* Iterar elementos */
            for (int i = 0; i < arr->length; ++i) {
                push_scope();
                /* crear variable de iteración en el scope de la iteración */
                runtime_symbol_t *iter_sym = create_symbol_in_current_scope(loop_name);
                iter_sym->type = TYPE_INT;
                iter_sym->value.int_val = arr->ints[i];
                /* ejecutar cuerpo */
                if (body) execute_statement(body);
                /* manejar continue/break */
                if (runtime_continue_flag) { runtime_continue_flag = 0; pop_scope(); continue; }
                if (runtime_break_flag) { pop_scope(); break; }
                pop_scope();
            }
            /* limpiar flags */
            runtime_break_flag = 0;
            runtime_continue_flag = 0;
            break;
        }

        case AST_METHOD_CALL: {
            const char *m = stmt->data.method_call.method_name;
            if (m && (!strcmp(m, "print") || !strcmp(m, "println"))) {
                ast_node *arg = stmt->data.method_call.arg;
                if (!arg) {
                    runtime_println_string_gui("");
                } else {
                    char *s = get_string_value(arg);
                    runtime_println_string_gui(s ? s : "");
                }
            } else {
                (void)evaluate_expression(stmt); // otros métodos -> evalúa sin imprimir
            }
            break;
        }

        default:
            if (stmt->type == AST_BINARY_OP || stmt->type == AST_UNARY_OP || stmt->type == AST_VARIABLE || stmt->type == AST_INT_LITERAL) {
                (void)evaluate_expression(stmt);
            }
            break;
    }
}

// Función principal del intérprete
// ...existing code...
// Función principal del intérprete
void execute_program(ast_node *root) {
    if (!root) { runtime_log("❌ No hay programa para ejecutar\n"); return; }
    runtime_log("\n🚀 === INICIANDO EJECUCIÓN === 🚀\n");
    
    runtime_codegen_generate_from_ast(root, "reports/out_arm64.s");
    /* limpiar estado previo */
    cleanup_runtime();

    /* Crear scope global runtime e inicializar símbolos desde la tabla semántica global
       para evitar crear símbolos duplicados en ejecución y evitar shadowing accidental. */
    push_scope(); /* scope global runtime */

    if (global_symbol_table && global_symbol_table->symbols) {
        runtime_log(" 🔧 Inicializando símbolos runtime desde semantic.global_symbol_table\n");
        symbol_t *gs = global_symbol_table->symbols;
        while (gs) {
        runtime_symbol_t *rs = create_symbol_in_current_scope(gs->name);
            if (rs) {
                switch (gs->type) {
                    case TYPE_INT:
                        rs->type = TYPE_INT; rs->value.int_val = 0; break;
                    case TYPE_FLOAT:
                        rs->type = TYPE_FLOAT; rs->value.float_val = 0.0f; break;
                    case TYPE_DOUBLE:
                        rs->type = TYPE_DOUBLE; rs->value.double_val = 0.0; break;
                    case TYPE_STRING:
                        rs->type = TYPE_STRING; rs->value.string_val = strdup(""); break;
                    case TYPE_BOOLEAN:
                        rs->type = TYPE_BOOLEAN; rs->value.bool_val = 0; break;
                    case TYPE_ARRAY_INT:
                        rs->type = TYPE_ARRAY_INT; rs->value.array_val = NULL; break;
                    case TYPE_ARRAY_FLOAT:
                    case TYPE_ARRAY_DOUBLE:
                    case TYPE_ARRAY_STRING:
                    case TYPE_ARRAY_CHAR:
                    case TYPE_ARRAY_BOOLEAN:
                        //marcar como array aunque runtime solo soporte int[] internamente por ahora 
                        rs->type = TYPE_ARRAY_INT;
                        rs->value.array_val = NULL;
                        break;
                    default:
                        rs->type = -1; break;
                }
            }
            gs = gs->next;
         }
    } 

    /* Desactivar debug por defecto en ejecución normal */
    set_runtime_debug(0);

    ast_node *main_node = find_main_method(root);
    if (main_node){
        /* DEBUG: imprimir AST del main para verificar el switch "Analisis por edad" */
        print_ast(main_node, 0);
        execute_statement(main_node);
    } else execute_statement(root);

    runtime_log("✅ === EJECUCIÓN COMPLETADA === ✅\n\n");
    show_symbol_table();
}

// Función para mostrar la tabla de símbolos
void show_symbol_table(void) {
    if (scope_depth == 0) {
        runtime_log("[SYMBOLS] Tabla de símbolos: vacía\n");
        return;
    }
    runtime_log("[SYMBOLS] === TABLA DE SÍMBOLOS (por scope, top->bottom) ===\n");
    for (int i = scope_depth - 1; i >= 0; --i) {
        char header[64];
        snprintf(header, sizeof(header), "  Scope depth %d:\n", i);
        runtime_log(header);
        runtime_symbol_t *cur = scope_stack[i];
        while (cur) {
            char message[1024]; message[0] = '\0';
            switch (cur->type) {
                case 0: snprintf(message, sizeof(message), "    %s: int = %d\n", cur->name, cur->value.int_val); break;
                case 1: snprintf(message, sizeof(message), "    %s: float = %.6f\n", cur->name, cur->value.float_val); break;
                case 2: snprintf(message, sizeof(message), "    %s: String = \"%s\"\n", cur->name, cur->value.string_val ? cur->value.string_val : ""); break;
                case 3: snprintf(message, sizeof(message), "    %s: boolean = %s\n", cur->name, cur->value.bool_val ? "true" : "false"); break;
                case 4: snprintf(message, sizeof(message), "    %s: double = %.6f\n", cur->name, cur->value.double_val); break;
                case TYPE_ARRAY_INT: {
                    runtime_array_t *arr = (runtime_array_t*) cur->value.array_val;
                    if (!arr) snprintf(message, sizeof(message), "    %s: int[] = uninitialized\n", cur->name);
                    else {
                        char buf[512]; size_t off = 0;
                        off += snprintf(buf + off, sizeof(buf) - off, "[");
                        for (int j = 0; j < arr->length; ++j) {
                            if (j) off += snprintf(buf + off, sizeof(buf) - off, ", ");
                            off += snprintf(buf + off, sizeof(buf) - off, "%d", arr->ints[j]);
                            if (off >= sizeof(buf)) break;
                        }
                        if (off < sizeof(buf)) snprintf(buf + off, sizeof(buf) - off, "]");
                        snprintf(message, sizeof(message), "    %s: int[] = %s\n", cur->name, buf);
                    }
                    break;
                }
                default: snprintf(message, sizeof(message), "    %s: unknown = ?\n", cur->name); break;
            }
            runtime_log(message);
            cur = cur->next;
        }
    }
    runtime_log("========================\n");
}

// Función para limpiar la tabla de símbolos
void cleanup_runtime(void) {
    for (int i = 0; i < scope_depth; ++i) {
        free_scope_list(scope_stack[i]);
        scope_stack[i] = NULL;
    }
    free(scope_stack);
    scope_stack = NULL;
    scope_depth = 0;
    scope_capacity = 0;
    array_map_clear();
    runtime_log(" Tabla de símbolos limpiada correctamente\n");
}

// Función para verificar si una expresión es de tipo string
int is_string_expression(ast_node *node) {
    if (!node) return 0;
    switch (node->type) {
        case AST_STRING_LITERAL: return 1;
        case AST_VARIABLE: {
            /* NO crear símbolo solo para consultar tipo -> buscar en scopes */
            runtime_symbol_t *sym = find_symbol_local(node->data.var_name);
            return (sym && (sym->type == TYPE_STRING || sym->type == 2));
        }
        case AST_BINARY_OP:
            if (node->data.op.op == OP_PLUS) return is_string_expression(node->data.op.left) || is_string_expression(node->data.op.right);
            return 0;
        default: return 0;
    }
}

// Función para obtener el valor string de una expresión
char* get_string_value(ast_node *node) {
    #define GSV_RING_SIZE 8
    static char ring[GSV_RING_SIZE][1024];
    static int ring_idx = 0;
    char *buf = ring[(ring_idx++) % GSV_RING_SIZE];
    buf[0] = '\0';
    if (!node) return buf;

    switch (node->type) {
        case AST_STRING_LITERAL:
            unescape_string_literal(node->data.string_value, buf, sizeof(ring[0]));
            return buf;
        case AST_INT_LITERAL:
            snprintf(buf, sizeof(ring[0]), "%d", node->data.int_value);
            return buf;
        case AST_FLOAT_LITERAL:
            snprintf(buf, sizeof(ring[0]), "%.6f", node->data.float_value);
            return buf;
        case AST_DOUBLE_LITERAL:
            snprintf(buf, sizeof(ring[0]), "%.6f", node->data.double_value);
            return buf;
        case AST_BOOL_LITERAL:
            snprintf(buf, sizeof(ring[0]), "%s", node->data.bool_value ? "true" : "false");
            return buf;
        case AST_VARIABLE: {
            runtime_symbol_t *sym = find_symbol_local(node->data.var_name);
            if (!sym) { buf[0] = '\0'; return buf; }
            switch (sym->type) {
                case TYPE_INT: snprintf(buf, sizeof(ring[0]), "%d", sym->value.int_val); break;
                case TYPE_FLOAT: snprintf(buf, sizeof(ring[0]), "%.6f", sym->value.float_val); break;
                case TYPE_DOUBLE: snprintf(buf, sizeof(ring[0]), "%.6f", sym->value.double_val); break;
                case TYPE_STRING: strncpy(buf, sym->value.string_val ? sym->value.string_val : "", sizeof(ring[0]) - 1); buf[sizeof(ring[0]) - 1] = '\0'; break;
                case TYPE_BOOLEAN: snprintf(buf, sizeof(ring[0]), "%s", sym->value.bool_val ? "true" : "false"); break;
                case TYPE_ARRAY_INT: snprintf(buf, sizeof(ring[0]), "[array:%p]", sym->value.array_val); break;
                default: buf[0] = '\0'; break;
            }
            return buf;
        }

        case AST_METHOD_CALL: {
            // Resolver llamadas que devuelven string (String.valueOf, Arrays.toString, toString, etc.)
            char recv_name[256] = "";
            if (node->data.method_call.receiver && node->data.method_call.receiver->type == AST_VARIABLE) {
                strncpy(recv_name, node->data.method_call.receiver->data.var_name, sizeof(recv_name)-1);
                recv_name[sizeof(recv_name)-1] = '\0';
            } else {
                recv_name[0] = '\0';
            }
            const char *mname = node->data.method_call.method_name ? node->data.method_call.method_name : "";

            // toString()
            if (strcmp(mname, "toString") == 0) {
                if (recv_name[0] != '\0') {
                    runtime_symbol_t *recv_sym = find_symbol_local(recv_name);
                    if (recv_sym && recv_sym->type == TYPE_STRING && recv_sym->value.string_val) {
                        strncpy(buf, recv_sym->value.string_val, sizeof(ring[0]) - 1);
                        buf[sizeof(ring[0]) - 1] = '\0';
                        return buf;
                    }
                }
                buf[0] = '\0';
                return buf;
            }

            // String.valueOf(...) and other builtins that return string
            if (recv_name[0] != '\0') {
                char fullname[512];
                snprintf(fullname, sizeof(fullname), "%s.%s", recv_name, mname);
                int out_i = 0; double out_d = 0; char *out_s = NULL;
                int t = builtin_dispatch(fullname, node->data.method_call.arg, &out_i, &out_d, &out_s);
                if (t == 2 && out_s) {
                    // builtin returned strdup -> put into ring buffer and free
                    strncpy(buf, out_s, sizeof(ring[0]) - 1);
                    buf[sizeof(ring[0]) - 1] = '\0';
                    free(out_s);
                    return buf;
                }
                if (t == 0) { snprintf(buf, sizeof(ring[0]), "%d", out_i); return buf; }
                if (t == 1) { snprintf(buf, sizeof(ring[0]), "%.6f", out_d); return buf; }
            }

            // Fallback: evaluar la expresión y convertir a string
            {
                int ev = evaluate_expression(node);
                snprintf(buf, sizeof(ring[0]), "%d", ev);
                return buf;
            }
        }

        default: {
            int ev = evaluate_expression(node);
            if (node->type == AST_STRING_LITERAL && node->data.string_value) {
                unescape_string_literal(node->data.string_value, buf, sizeof(ring[0]));
                return buf;
            }
            if (node_is_boolean_expression(node)) { snprintf(buf, sizeof(ring[0]), "%s", ev ? "true" : "false"); return buf; }
            if (node_is_floatish(node)) { double dv = eval_node_as_double(node); snprintf(buf, sizeof(ring[0]), "%.6f", dv); return buf; }
            snprintf(buf, sizeof(ring[0]), "%d", ev);
            return buf;
        }
    }

}

// ...existing code...
void build_concatenated_string(ast_node *expr, char *result) {
    if (!result) return;
    result[0] = '\0';
    if (!expr) return;

    /* Aplanar árbol de OP_PLUS en una lista de nodos (orden izquierda->derecha) */
    ast_node *nodes[512];
    int n_nodes = 0;
    ast_node *stack[512];
    int sp = 0;

    stack[sp++] = expr;
    while (sp > 0) {
        ast_node *cur = stack[--sp];
        if (!cur) continue;
        if (cur->type == AST_BINARY_OP && cur->data.op.op == OP_PLUS) {
            /* push right then left para procesar left primero (LIFO) */
            if (cur->data.op.right) stack[sp++] = cur->data.op.right;
            if (cur->data.op.left)  stack[sp++] = cur->data.op.left;
        } else {
            if (n_nodes < (int)(sizeof(nodes)/sizeof(nodes[0]))) nodes[n_nodes++] = cur;
        }
    }

    /* Concatenar los valores string de cada nodo */
    size_t cap = 2048;
    size_t off = 0;
    for (int i = 0; i < n_nodes; ++i) {
        char *v = get_string_value(nodes[i]);
        if (!v) v = "";
        size_t need = strlen(v);
        if (off + need + 1 >= cap) {
            /* truncar si se excede */
            size_t can = (off < cap) ? (cap - off - 1) : 0;
            if (can > 0) {
                strncat(result, v, can);
                off += can;
            }
            break;
        } else {
            /* concatenar de forma segura */
            strcat(result, v);
            off += need;
        }
    }
    return;
}


void convert_to_string(ast_node *node, char *str) {
    if (!str) return;
    if (!node) { str[0] = '\0'; return; }
    char *v = get_string_value(node);
    strncpy(str, v, 512-1);
    str[512-1] = '\0';
}

void convert_symbol_to_string(runtime_symbol_t *sym, char *str) {
    if (!sym || !str) { strcpy(str, ""); return; }
    switch (sym->type) {
        case 0: sprintf(str, "%d", sym->value.int_val); break;
        case 1: sprintf(str, "%.2f", sym->value.float_val); break;
        case 2: strcpy(str, sym->value.string_val ? sym->value.string_val : ""); break;
        case 3: strcpy(str, sym->value.bool_val ? "true" : "false"); break;
        case 4: sprintf(str, "%.6f", sym->value.double_val); break;
        default: strcpy(str, ""); break;
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
            runtime_symbol_t *s = find_symbol_local(n->data.var_name);
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
            int effective_op = n->data.op.op;

            switch (effective_op) {
                case OP_PLUS:  return L + R;
                case OP_MINUS: return L - R;
                case OP_MULT:  return L * R;
                case OP_DIV:   return R != 0.0 ? (L / R) : 0.0;
                case OP_MOD:   return (R != 0.0) ? fmod(L, R) : 0.0;
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
        /* NO crear símbolo al inspeccionar tipo */
        runtime_symbol_t *s = find_symbol_local(n->data.var_name);
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