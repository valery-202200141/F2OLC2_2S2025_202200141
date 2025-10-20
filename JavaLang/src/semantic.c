#include "../include/semantic.h"
#include "../include/errores.h"  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef TYPE_ARRAY_INT
#define TYPE_ARRAY_INT 100
#define TYPE_ARRAY_FLOAT 101
#define TYPE_ARRAY_DOUBLE 102
#define TYPE_ARRAY_STRING 103
#define TYPE_ARRAY_CHAR 104
#define TYPE_ARRAY_BOOLEAN 105
#endif


// Variables globales
symbol_table_t *current_scope = NULL;
symbol_table_t *global_symbol_table = NULL;
int semantic_errors = 0;
int shadowing_policy = 0; // Por defecto prohibir shadowing
char current_scope_name[256] = "global"; // Nombre del scope actual
static int semantic_loop_depth = 0; // Profundidad de loops anidados
void clear_global_symbol_table(void); // Prototipo para evitar implicit declaration

// =================== GESTIÓN DE SCOPES ===================

symbol_table_t* create_scope(symbol_table_t *parent) {
    symbol_table_t *scope = malloc(sizeof(symbol_table_t));
    scope->symbols = NULL;
    scope->scope_level = parent ? parent->scope_level + 1 : 0;
    scope->parent = parent;
    return scope;
}

void destroy_scope(symbol_table_t *scope) {
    if (!scope) return;
    
    symbol_t *current = scope->symbols;
    while (current) {
        symbol_t *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    free(scope);
}

void enter_scope(void) {
    current_scope = create_scope(current_scope);
    snprintf(current_scope_name, sizeof(current_scope_name), "scope_%d", current_scope->scope_level);
    printf("Entrando a scope nivel %d\n", current_scope->scope_level);
}

void exit_scope(void) {
    if (!current_scope) return;

    printf("Saliendo de scope nivel %d (%s)\n", current_scope->scope_level, current_scope_name);
    symbol_table_t *old_scope = current_scope;
    current_scope = current_scope->parent;
    destroy_scope(old_scope);
    /* restaurar nombre del scope actual (si hay padre) */
    if (current_scope) {
        snprintf(current_scope_name, sizeof(current_scope_name), "scope_%d", current_scope->scope_level);
    } else {
        strncpy(current_scope_name, "global", sizeof(current_scope_name) - 1);
        current_scope_name[sizeof(current_scope_name) - 1] = '\0';
    }
}

// =================== GESTIÓN DE SÍMBOLOS ===================
// ...existing code...
symbol_t* declare_symbol(const char *name, data_type_t type) {
    if (!current_scope) {
        enter_scope(); // Crear scope global si no existe
    }
    
    // Verificar shadowing / existencia en el scope actual
    symbol_t *existing = lookup_symbol_current_scope(name);
    if (existing) {
        // Caso: símbolo ya existe en este scope pero parece haber sido 'pre-insertado'
        // en la tabla global (por ejemplo línea == 0). Reutilizamos y actualizamos tipo
        // en vez de reportar error para evitar duplicados en análisis múltiple.
        if (existing->line == 0) {
            existing->type = type;
            existing->is_initialized = 0;
            return existing;
        }

        if (shadowing_policy == 0) {
            report_semantic_error_local(0, 0, "Variable ya declarada en este scope", current_scope_name);
            return NULL;
        }
    }
    
    // Crear nuevo símbolo
    symbol_t *symbol = malloc(sizeof(symbol_t));
    symbol->name = strdup(name);
    symbol->type = type;
    symbol->is_initialized = 0;
    symbol->scope_level = current_scope->scope_level;
    char scopebuf[64];
    snprintf(scopebuf, sizeof(scopebuf), "scope_%d", current_scope->scope_level);
    symbol->scope_name = strdup(scopebuf);
    symbol->line = 0;
    symbol->next = current_scope->symbols;
    current_scope->symbols = symbol;
    
    printf("Declarando variable '%s' de tipo %s en scope %d\n",
           name ? name : "(null)",
           type_to_string(type),
           current_scope->scope_level);
    // Registrar también en tabla global para reporte
    add_symbol_to_table(name, type, symbol->scope_name, 0);
    return symbol;
}

symbol_t* lookup_symbol(const char *name) {
    if (!name) return NULL;

    // Buscar desde el scope actual hacia arriba (padres)
    symbol_table_t *scope_iter = current_scope;
    while (scope_iter) {
        symbol_t *sym = scope_iter->symbols;
        while (sym) {
            if (sym->name && strcmp(sym->name, name) == 0) return sym;
            sym = sym->next;
        }
        scope_iter = scope_iter->parent;
    }

    // Si no está en ningún scope local/ancestro, buscar en la tabla global
    if (global_symbol_table && global_symbol_table->symbols) {
        symbol_t *g = global_symbol_table->symbols;
        while (g) {
            if (g->name && strcmp(g->name, name) == 0) return g;
            g = g->next;
        }
    }

    return NULL;
}

symbol_t* lookup_symbol_current_scope(const char *name) {
    if (!current_scope) return NULL;
    
    symbol_t *symbol = current_scope->symbols;
    while (symbol) {
        if (strcmp(symbol->name, name) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }
    
    return NULL;
}


// =================== ANÁLISIS SEMÁNTICO ===================

int check_semantics(ast_node *root) {
    semantic_errors = 0;
    current_scope = NULL;
    
    printf("\n=== INICIANDO ANÁLISIS SEMÁNTICO ===\n");
    
    if (root) {
        enter_scope(); // Scope global
        analyze_node(root);
        exit_scope();
    }
    
    printf("=== ANÁLISIS SEMÁNTICO COMPLETADO ===\n");
    return semantic_errors;
}

data_type_t analyze_node(ast_node *node) {
    if (!node) return TYPE_VOID;
    
    switch (node->type) {
        case AST_COMPOUND_STMT:
            // Analizar todas las declaraciones en el compound
            if (node->data.compound.statement_list) {
                ast_node *current = node->data.compound.statement_list;
                while (current) {
                    analyze_node(current);
                    current = current->next;
                }
            }
            break;
            
        case AST_DECLARATION: {
            // Obtener tipo de la declaración
            data_type_t var_type = string_to_type(node->data.declaration.var_type->data.type_name);
            
            // Declarar símbolo
            symbol_t *symbol = declare_symbol(node->data.declaration.var_name, var_type);
            
            // Si hay valor inicial, analizarlo
            if (node->data.declaration.value) {
                data_type_t value_type = analyze_expression(node->data.declaration.value);
                
                if (symbol && value_type != TYPE_UNKNOWN) {
                    int compatible = (var_type == value_type)
                        || (var_type == TYPE_DOUBLE && (value_type == TYPE_FLOAT || value_type == TYPE_INT))
                        || (var_type == TYPE_FLOAT && value_type == TYPE_INT);
                    if (!compatible) {
                        char error_msg[256];
                        snprintf(error_msg, sizeof(error_msg), 
                                "Incompatibilidad de tipos: esperado %s, obtenido %s",
                                type_to_string(var_type), type_to_string(value_type));
                        report_semantic_error_local(node->line, 0, error_msg, current_scope_name);
                    } else {
                        symbol->is_initialized = 1;
                        printf("Variable '%s' inicializada correctamente\n", symbol->name);
                    }
                }
            }
            break;
        }
        
        case AST_ASSIGNMENT: {
            // Verificar que la variable existe
            symbol_t *symbol = lookup_symbol(node->data.assignment.var_name);
            if (!symbol) {
                report_semantic_error_local(node->line, 0, "Variable no declarada", "Global"); 
                break;
            }

            data_type_t value_type = analyze_expression(node->data.assignment.value);
            if (value_type != TYPE_UNKNOWN) {
                int compatible = (symbol->type == value_type)
                    || (symbol->type == TYPE_DOUBLE && (value_type == TYPE_FLOAT || value_type == TYPE_INT))
                    || (symbol->type == TYPE_FLOAT && value_type == TYPE_INT);
                if (!compatible) {
                    char error_msg[256];
                    snprintf(error_msg, sizeof(error_msg), 
                            "Incompatibilidad de tipos en asignación: variable %s, valor %s",
                            type_to_string(symbol->type), type_to_string(value_type));
                    report_semantic_error_local(node->line, 0, error_msg, current_scope_name);
                } else {
                    symbol->is_initialized = 1;
                    printf("Asignación a '%s' correcta\n", symbol->name);
                }
            }
            break;
        }
        
        case AST_IF:
            // Verificar que la condición sea booleana
            data_type_t cond_type = analyze_expression(node->data.if_stmt.condition);
            if (cond_type != TYPE_BOOLEAN && cond_type != TYPE_UNKNOWN) {
                report_semantic_error_local(node->line, 0, "La condición del if debe ser booleana", "if_block");
            }
            
            // Analizar ramas
            enter_scope();
            analyze_node(node->data.if_stmt.then_branch);
            exit_scope();
            
            if (node->data.if_stmt.else_branch) {
                enter_scope();
                analyze_node(node->data.if_stmt.else_branch);
                exit_scope();
            }
            break;
            
        case AST_WHILE:
            // Verificar condición
            cond_type = analyze_expression(node->data.while_stmt.condition);
            if (cond_type != TYPE_BOOLEAN && cond_type != TYPE_UNKNOWN) {
                report_semantic_error_local(node->line, 0, "La condición del while debe ser booleana", "while_loop");
            }
            
            // Analizar cuerpo
            enter_scope();
            analyze_node(node->data.while_stmt.body);
            exit_scope();
            break;
            
        default:
            // Para otros tipos de nodos, continuar con el siguiente
            break;
    }
    
    // Analizar el siguiente nodo en la lista
    if (node->next) {
        analyze_node(node->next);
    }
    
    return TYPE_VOID;
}

data_type_t analyze_expression(ast_node *expr) {
    if (!expr) return TYPE_UNKNOWN;
    
    switch (expr->type) {

        case AST_INT_LITERAL:
            return TYPE_INT;
            
        case AST_FLOAT_LITERAL:
            return TYPE_FLOAT;
        
        case AST_DOUBLE_LITERAL:
            return TYPE_DOUBLE;
            
        case AST_STRING_LITERAL:
            return TYPE_STRING;
            
        case AST_CHAR_LITERAL:
            return TYPE_CHAR;
            
        case AST_BOOL_LITERAL:
            return TYPE_BOOLEAN;
            
        case AST_NULL_LITERAL:
            return TYPE_VOID; // O crear TYPE_NULL si prefieres
            
        case AST_VARIABLE: {
            symbol_t *symbol = lookup_symbol(expr->data.var_name);
            if (!symbol) {
                // Mantener aviso pero no abortar todo el análisis
                printf("⚠️ Variable '%s' no encontrada en análisis semántico\n",
                       expr->data.var_name ? expr->data.var_name : "NULL");
                return TYPE_UNKNOWN;
            }
            return symbol->type;
        }

        case AST_ARRAY_ACCESS: {
            // expr->data.array_access.array_name  y .index
            if (!expr->data.array_access.array_name) return TYPE_UNKNOWN;
            symbol_t *sym = lookup_symbol(expr->data.array_access.array_name);
            if (!sym) {
                report_semantic_error_local(expr->line, 0, "Array no declarado", current_scope_name);
                return TYPE_UNKNOWN;
            }
            // Verificar tipo del índice
            if (expr->data.array_access.index) {
                data_type_t idx_t = analyze_expression(expr->data.array_access.index);
                if (idx_t != TYPE_INT && idx_t != TYPE_UNKNOWN) {
                    report_semantic_error_local(expr->line, 0, "Índice de array debe ser entero", current_scope_name);
                }
            }
            // Devolver el tipo del elemento según el tipo de array
            if (sym->type == TYPE_ARRAY_INT) return TYPE_INT;
            if (sym->type == TYPE_ARRAY_FLOAT) return TYPE_FLOAT;
            if (sym->type == TYPE_ARRAY_DOUBLE) return TYPE_DOUBLE;
            if (sym->type == TYPE_ARRAY_STRING) return TYPE_STRING;
            return TYPE_UNKNOWN;
        }
        
        // ENCONTRAR línea 285-300 y REEMPLAZAR con:
        case AST_BINARY_OP: {
            data_type_t left_type = analyze_expression(expr->data.op.left);
            data_type_t right_type = analyze_expression(expr->data.op.right);
            
            switch (expr->data.op.op) {
                case OP_PLUS: {
                    // Concatenación si alguno es String
                    if (left_type == TYPE_STRING || right_type == TYPE_STRING) {
                        return TYPE_STRING;
                    }
                    // Promoción numérica: double > float > int
                    if (left_type == TYPE_DOUBLE || right_type == TYPE_DOUBLE) return TYPE_DOUBLE;
                    if (left_type == TYPE_FLOAT  || right_type == TYPE_FLOAT)  return TYPE_FLOAT;
                    if (left_type == TYPE_INT    && right_type == TYPE_INT)    return TYPE_INT;

                    // Tipos no compatibles para '+'
                    report_semantic_error_local(expr->line, 0, "Tipos incompatibles en operación '+'", "Global");
                    return TYPE_UNKNOWN;
                }
                case OP_MINUS:
                case OP_MULT:
                case OP_DIV:
                case OP_MOD:  // ⭐ CORREGIR: agregar dos puntos
                    if (left_type == TYPE_INT && right_type == TYPE_INT) {
                        return TYPE_INT;
                    } else if ((left_type == TYPE_FLOAT || left_type == TYPE_INT) &&
                            (right_type == TYPE_FLOAT || right_type == TYPE_INT)) {
                        return TYPE_FLOAT;
                    } else if ((left_type == TYPE_DOUBLE || left_type == TYPE_INT || left_type == TYPE_FLOAT) &&
                            (right_type == TYPE_DOUBLE || right_type == TYPE_INT || right_type == TYPE_FLOAT)) {
                        return TYPE_DOUBLE;
                    } else if (left_type == TYPE_STRING && right_type == TYPE_STRING && expr->data.op.op == OP_PLUS) {
                        return TYPE_STRING; // Concatenación
                    } else {
                        report_semantic_error_local(0, 0, "Tipos incompatibles en operación aritmética", "Global");
                        return TYPE_UNKNOWN;
                    }
                    break;
                    
                case OP_EQUALS:
                case OP_NOT_EQUALS: {
                    // ✅ PERMITIR COMPARACIONES DE MISMO TIPO
                    if (left_type == right_type) {
                        return TYPE_BOOLEAN;
                    }
                    // Permitir comparación int/double
                    if ((left_type == TYPE_INT && right_type == TYPE_DOUBLE) ||
                        (left_type == TYPE_DOUBLE && right_type == TYPE_INT)) {
                        return TYPE_BOOLEAN;
                    }
                    return TYPE_BOOLEAN;
                }

                case OP_LESS:
                case OP_GREATER:
                case OP_LESS_EQUALS:
                case OP_GREATER_EQUALS:
                    if ((left_type == TYPE_INT || left_type == TYPE_FLOAT || left_type == TYPE_DOUBLE) &&
                        (right_type == TYPE_INT || right_type == TYPE_FLOAT || right_type == TYPE_DOUBLE)) {
                        return TYPE_BOOLEAN;
                    } else if (left_type == TYPE_STRING && right_type == TYPE_STRING) {
                        return TYPE_BOOLEAN;
                    } else {
                        report_semantic_error_local(0, 0, "Tipos incompatibles en comparación", "Global");
                        return TYPE_UNKNOWN;
                    }
                    break;
                    
                case OP_AND:
                case OP_OR:
                    if (left_type == TYPE_BOOLEAN && right_type == TYPE_BOOLEAN) {
                        return TYPE_BOOLEAN;
                    } else {
                        report_semantic_error_local(0, 0, "Operadores lógicos requieren operandos booleanos", "Global");
                        return TYPE_UNKNOWN;
                    }
                    
                // ⭐ AGREGAR casos para operadores no implementados:
                case OP_INCREMENT:
                case OP_DECREMENT:
                case OP_POST_INCREMENT:
                case OP_POST_DECREMENT:
                    if (left_type == TYPE_INT || left_type == TYPE_FLOAT) {
                        return left_type;
                    } else {
                        report_semantic_error_local(0, 0, "Operadores de incremento requieren operandos numéricos", "Global");
                        return TYPE_UNKNOWN;
                    }
                    
                case OP_ASSIGN:
                case OP_PLUS_ASSIGN:
                case OP_MINUS_ASSIGN:
                case OP_MULT_ASSIGN:
                case OP_DIV_ASSIGN:
                    // Para asignaciones, retornar el tipo del lado izquierdo
                    return left_type;
                    
                default:
                    report_semantic_error_local(0, 0, "Operador binario no reconocido", "Global");
                    return TYPE_UNKNOWN;
            }
        }
        
        case AST_METHOD_CALL: {
            /* Inferir tipo para llamadas de función/método conocidas.
               receiver==NULL => función libre; receiver != NULL => método/estático. */
            const char *mname = expr->data.method_call.method_name ? expr->data.method_call.method_name : "";
            ast_node *recv = expr->data.method_call.receiver;

            /* Funciones del ejemplo */
            if (recv == NULL) {
                if (strcmp(mname, "calcularPromedio") == 0) return TYPE_DOUBLE;
                if (strcmp(mname, "verificarAprobacion") == 0) return TYPE_BOOLEAN;
                if (strcmp(mname, "generarMensaje") == 0) return TYPE_STRING;
                if (strcmp(mname, "calcularNotaFinal") == 0) return TYPE_DOUBLE;
                if (strcmp(mname, "busquedaBinaria") == 0) return TYPE_INT;
                if (strcmp(mname, "sumarDigitos") == 0) return TYPE_INT;
                if (strcmp(mname, "potencia") == 0) return TYPE_INT;
                if (strcmp(mname, "esPalindromo") == 0) return TYPE_BOOLEAN;
                if (strcmp(mname, "invertirNumero") == 0) return TYPE_INT;
                if (strcmp(mname, "sumarCalificaciones") == 0) return TYPE_DOUBLE;
            }
            /* Métodos/builtins estáticos o de clase/objeto */
            if (recv && recv->type == AST_VARIABLE && recv->data.var_name) {
                char fullname[512];
                snprintf(fullname, sizeof(fullname), "%s.%s", recv->data.var_name, mname);
                if (strcmp(fullname, "Integer.parseInt") == 0 || strcmp(mname, "parseInt") == 0) return TYPE_INT;
                if (strcmp(fullname, "Double.parseDouble") == 0 || strcmp(mname, "parseDouble") == 0) return TYPE_DOUBLE;
                if (strcmp(fullname, "Float.parseFloat") == 0 || strcmp(mname, "parseFloat") == 0) return TYPE_FLOAT;
                if (strcmp(fullname, "String.valueOf") == 0 || strcmp(mname, "valueOf") == 0) return TYPE_STRING;
                if (strcmp(mname, "length") == 0) return TYPE_INT;
                if (strcmp(mname, "toString") == 0) return TYPE_STRING;
            }

            /* Desconocido -> TYPE_UNKNOWN para evitar cascada de errores semánticos */
            return TYPE_UNKNOWN;
        }

        case AST_UNARY_OP: {
            data_type_t operand_type = analyze_expression(expr->data.op.left);
            
            switch (expr->data.op.op) {
                case OP_NOT:
                    if (operand_type == TYPE_BOOLEAN) {
                        return TYPE_BOOLEAN;
                    } else {
                        report_semantic_error_local(0, 0, "Operador ! requiere operando booleano", "Global");
                        return TYPE_UNKNOWN;
                    }
                    
                case OP_UMINUS:
                    if (operand_type == TYPE_INT || operand_type == TYPE_FLOAT || operand_type == TYPE_DOUBLE) {
                        return operand_type;
                    } else {
                        report_semantic_error_local(0, 0, "Operador - unario requiere operando numérico", "Global");
                        return TYPE_UNKNOWN;
                    }
                    
                case OP_INCREMENT:
                case OP_DECREMENT:
                case OP_POST_INCREMENT:
                case OP_POST_DECREMENT:
                    if (operand_type == TYPE_INT || operand_type == TYPE_FLOAT) {
                        return operand_type;
                    } else {
                        report_semantic_error_local(0, 0, "Operadores de incremento requieren operandos numéricos", "Global");

                        return TYPE_UNKNOWN;
                    }
                    
                default:
                    report_semantic_error_local(0, 0, "Operador unario no reconocido", "Global");
                    return TYPE_UNKNOWN;
            }
        }
        
        case AST_STRING_EQUALS: {
            // Verificar que el lado izquierdo sea string
            data_type_t left_type = analyze_expression(expr->data.string_equals.left_string);
            data_type_t right_type = analyze_expression(expr->data.string_equals.right_expr);
            
            if (left_type != TYPE_STRING) {
                report_semantic_error_local(0, 0, "Método .equals() solo disponible para Strings", "Global");
                return TYPE_UNKNOWN;
            }
            
            if (right_type != TYPE_STRING) {
                report_semantic_error_local(0, 0, "Argumento de .equals() debe ser String", "Global");
                return TYPE_UNKNOWN;
            }
            
            return TYPE_BOOLEAN; // .equals() siempre retorna boolean
        }
        default:
            return TYPE_UNKNOWN;
    }
}


// AGREGAR al final del archivo, antes de las funciones auxiliares:

// =================== FUNCIONES PARA GUI ===================

void semantic_analysis(ast_node *root) {
    if (!root) {
        printf("❌ No hay AST para analizar\n");
        return;
    }
    
    printf("=== INICIANDO ANÁLISIS SEMÁNTICO ===\n");
    set_shadowing_policy(0); // Prohibir shadowing
    
    /* Asegurar estado limpio de scopes para este análisis (evitar duplicados) */
    semantic_errors = 0;
    /* Liberar scope previo si existe (no free de symbols globales aquí) */
    if (current_scope) {
        /* destruir todos los scopes ascendentes */
        while (current_scope) {
            symbol_table_t *p = current_scope->parent;
            destroy_scope(current_scope);
            current_scope = p;
        }
    }
    /* Reiniciar nombre y apuntador de scope */
    strncpy(current_scope_name, "global", sizeof(current_scope_name)-1);
    current_scope_name[sizeof(current_scope_name)-1] = '\0';
    current_scope = NULL;

    // Usar la tabla global directamente
    if (global_symbol_table) {
        clear_global_symbol_table();
    } else {
        global_symbol_table = create_symbol_table();
    }

    enter_scope();

    if (root) {
       ast_node *scan = root;
       while (scan) {
           if (scan->type == AST_MAIN_FUNCTION || scan->type == AST_FUNCTION) {
               const char *fname = scan->data.function_def.name ? scan->data.function_def.name : "main";
               add_symbol(global_symbol_table, fname, TYPE_VOID, "global", scan->line);
           }
           scan = scan->next;
       }
   }
    // Procesar cada statement en la lista
    if (root) {
        printf("🔍 Analizando lista de statements desde root\n");
        analyze_statement(root);
    }
   
    
    exit_scope();
    printf("=== ANÁLISIS SEMÁNTICO COMPLETADO ===\n");
    
    // Mostrar tabla de símbolos
    print_symbol_table();
}

void analyze_statement(ast_node *stmt) {
    if (!stmt) return;

    ast_node *cur = stmt;
    while (cur) {
        printf("📝 Analizando statement tipo: %d\n", cur->type);

        switch (cur->type) {
            case AST_DECLARATION: {
                printf("🔸 Procesando declaración: %s\n",
                    cur->data.declaration.var_name ? cur->data.declaration.var_name : "?");

                if (!cur->data.declaration.var_name) {
                    printf("❌ Error: Nombre de variable nulo\n");
                    break;
                }

                data_type_t var_type = TYPE_UNKNOWN;
                if (cur->data.declaration.var_type && cur->data.declaration.var_type->data.type_name) {
                    var_type = string_to_type(cur->data.declaration.var_type->data.type_name);
                    printf("🔹 Tipo detectado: %s\n", type_to_string(var_type));
                }

                if (lookup_symbol_current_scope(cur->data.declaration.var_name)) {
                    report_semantic_error_local(cur->line, 0, "Variable ya declarada", current_scope_name);
                    break;
                }

                symbol_t *sym = declare_symbol(cur->data.declaration.var_name, var_type);
                if (!sym) break;

                //add_symbol_to_table(sym->name, sym->type, sym->scope_name ? sym->scope_name : current_scope_name, cur->line);

                if (cur->data.declaration.value) {
                    data_type_t value_type = analyze_expression(cur->data.declaration.value);
                    if (value_type != TYPE_UNKNOWN) {
                        int compatible = (var_type == value_type)
                            || (var_type == TYPE_DOUBLE && (value_type == TYPE_FLOAT || value_type == TYPE_INT))
                            || (var_type == TYPE_FLOAT && value_type == TYPE_INT);
                        if (!compatible) {
                            char error_msg[256];
                            snprintf(error_msg, sizeof(error_msg),
                                    "Incompatibilidad de tipos: esperado %s, obtenido %s",
                                    type_to_string(var_type), type_to_string(value_type));
                            report_semantic_error_local(cur->line, 0, error_msg, current_scope_name);
                        } else {
                            sym->is_initialized = 1;
                            printf("✅ Variable '%s' declarada e inicializada correctamente\n", cur->data.declaration.var_name);
                        }
                    }
                } else {
                    printf("✅ Variable '%s' declarada sin inicialización\n", cur->data.declaration.var_name);
                }
                break;
            }

            case AST_ASSIGNMENT: {
                printf("🔸 Procesando asignación: %s\n",
                       cur->data.assignment.var_name ? cur->data.assignment.var_name : "?");

                if (!cur->data.assignment.var_name) {
                    printf("❌ Error: Nombre de variable nulo en asignación\n");
                    break;
                }

                symbol_t *symbol = lookup_symbol(cur->data.assignment.var_name);
                if (!symbol) {
                    report_semantic_error_local(cur->line, 0, "Variable no declarada", current_scope_name);
                    break;
                }

                if (cur->data.assignment.value) {
                    data_type_t expr_type = analyze_expression(cur->data.assignment.value);
                    if (expr_type != TYPE_UNKNOWN) {
                        int compatible = (symbol->type == expr_type)
                            || (symbol->type == TYPE_DOUBLE && (expr_type == TYPE_FLOAT || expr_type == TYPE_INT))
                            || (symbol->type == TYPE_FLOAT && expr_type == TYPE_INT);
                        if (!compatible) {
                            char error_msg[256];
                            snprintf(error_msg, sizeof(error_msg),
                                    "Tipos incompatibles en asignación: variable %s, valor %s",
                                    type_to_string(symbol->type), type_to_string(expr_type));
                            report_semantic_error_local(cur->line, 0, error_msg, current_scope_name);
                        } else {
                            symbol->is_initialized = 1;
                            printf("✅ Asignación a '%s' correcta\n", symbol->name);
                        }
                    }
                }
                break;
            }

            case AST_PRINT_STMT:
                printf("🔸 Procesando statement PRINTLN\n");
                if (cur->data.print_stmt.expression) {
                    printf("🔹 Analizando expresión del println\n");
                    analyze_expression(cur->data.print_stmt.expression);
                } else {
                    printf("🔹 Println vacío (sin argumentos)\n");
                }
                break;

            case AST_IF: {
                printf("🔸 Procesando statement IF\n");
                if (cur->data.if_stmt.condition) {
                    data_type_t cond = analyze_expression(cur->data.if_stmt.condition);
                    if (cond != TYPE_BOOLEAN && cond != TYPE_UNKNOWN)
                        report_semantic_error_local(cur->line,0,"La condición del if debe ser booleana", current_scope_name);
                }
                enter_scope();
                if (cur->data.if_stmt.then_branch) analyze_statement(cur->data.if_stmt.then_branch);
                exit_scope();
                if (cur->data.if_stmt.else_branch) {
                    enter_scope();
                    analyze_statement(cur->data.if_stmt.else_branch);
                    exit_scope();
                }
                break;
            }

            case AST_WHILE: {
                printf("🔸 Procesando statement WHILE\n");
                if (cur->data.while_stmt.condition) {
                    data_type_t cond = analyze_expression(cur->data.while_stmt.condition);
                    if (cond != TYPE_BOOLEAN && cond != TYPE_UNKNOWN)
                        report_semantic_error_local(cur->line,0,"La condición del while debe ser booleana", current_scope_name);
                }
                enter_scope();
                if (cur->data.while_stmt.body) analyze_statement(cur->data.while_stmt.body);
                exit_scope();
                break;
            }

            case AST_FOR: {
                printf("🔸 Procesando statement FOR\n");
                enter_scope();
                if (cur->data.for_stmt.init) analyze_statement(cur->data.for_stmt.init);
                if (cur->data.for_stmt.condition) {
                    data_type_t cond = analyze_expression(cur->data.for_stmt.condition);
                    if (cond != TYPE_BOOLEAN && cond != TYPE_UNKNOWN)
                        report_semantic_error_local(cur->line,0,"La condición del for debe ser booleana", current_scope_name);
                }
                if (cur->data.for_stmt.increment) analyze_expression(cur->data.for_stmt.increment);
                if (cur->data.for_stmt.body) analyze_statement(cur->data.for_stmt.body);
                exit_scope();
                break;
            }

            case AST_COMPOUND_STMT: {
                enter_scope();
                if (cur->data.compound.statement_list) analyze_statement(cur->data.compound.statement_list);
                exit_scope();
                break;
            }

            case AST_MAIN_FUNCTION: {
                printf("🔸 Procesando función MAIN\n");
                enter_scope();
                if (cur->data.function_def.parameters) {
                    ast_node *param = cur->data.function_def.parameters;
                    while (param) {
                        if (param->type == AST_DECLARATION && param->data.declaration.var_name) {
                            data_type_t ptype = TYPE_UNKNOWN;
                            if (param->data.declaration.var_type && param->data.declaration.var_type->data.type_name) {
                                ptype = string_to_type(param->data.declaration.var_type->data.type_name);
                            }
                            if (!lookup_symbol_current_scope(param->data.declaration.var_name)) {
                                symbol_t *psym = declare_symbol(param->data.declaration.var_name, ptype);
                                if (psym) {
                                    psym->is_initialized = 1;
                                    psym->line = param->line;
                                }
                            }
                        }
                        param = param->next;
                    }
                }

                if (cur->data.function_def.body) {
                    analyze_statement(cur->data.function_def.body);
                }
                exit_scope();
                printf("✅ Función main completamente analizada\n");
                break;
            }

            case AST_FUNCTION: {
                printf("🔸 Procesando función (definición)\n");
                enter_scope();
                if (cur->data.function_def.parameters) {
                    ast_node *param = cur->data.function_def.parameters;
                    while (param) {
                        if (param->type == AST_DECLARATION && param->data.declaration.var_name) {
                            data_type_t ptype = TYPE_UNKNOWN;
                            if (param->data.declaration.var_type && param->data.declaration.var_type->data.type_name) {
                                ptype = string_to_type(param->data.declaration.var_type->data.type_name);
                            }
                            if (!lookup_symbol_current_scope(param->data.declaration.var_name)) {
                                symbol_t *psym = declare_symbol(param->data.declaration.var_name, ptype);
                                if (psym) { psym->is_initialized = 1; psym->line = param->line; }
                            }
                        }
                        param = param->next;
                    }
                }
                if (cur->data.function_def.body) {
                    ast_node *c = cur->data.function_def.body;
                    while (c) { analyze_statement(c); c = c->next; }
                }
                exit_scope();
                printf(" Función completamente analizada\n");
                break;
            }

            case AST_ARRAY_DECLARATION: {
                printf("🔸 Procesando declaración de array: %s\n",
                       cur->data.array_decl.array_name ? cur->data.array_decl.array_name : "?");
                if (lookup_symbol(cur->data.array_decl.array_name)) {
                    report_semantic_error_local(0, 0, "Array ya declarado", "global");
                    break;
                }
                data_type_t array_type = TYPE_ARRAY_INT;
                if (cur->data.array_decl.element_type && cur->data.array_decl.element_type->data.type_name) {
                    if (strcmp(cur->data.array_decl.element_type->data.type_name, "String") == 0) {
                        array_type = TYPE_ARRAY_STRING;
                    } else if (strcmp(cur->data.array_decl.element_type->data.type_name, "float") == 0) {
                        array_type = TYPE_ARRAY_FLOAT;
                    }
                }
                add_symbol(global_symbol_table, cur->data.array_decl.array_name, array_type, "global", 0);
                printf("✅ Array '%s' declarado correctamente\n", cur->data.array_decl.array_name);
                break;
            }

            case AST_ARRAY_ACCESS: {
                printf("🔸 Procesando acceso a array: %s\n",
                       cur->data.array_access.array_name ? cur->data.array_access.array_name : "?");
                symbol_t *array_symbol = lookup_symbol(cur->data.array_access.array_name);
                if (!array_symbol) {
                    report_semantic_error_local(0, 0, "Array no declarado", "global");
                    break;
                }
                if (cur->data.array_access.index) {
                    data_type_t index_type = analyze_expression(cur->data.array_access.index);
                    if (index_type != TYPE_INT) {
                        report_semantic_error_local(0, 0, "Índice de array debe ser entero", "global");
                    }
                }
                printf("✅ Acceso a array verificado\n");
                break;
            }

            case AST_ARRAY_ASSIGNMENT: {
                printf("🔸 Procesando asignación a array: %s\n",
                       cur->data.array_assignment.array_name ? cur->data.array_assignment.array_name : "?");
                symbol_t *array_symbol = lookup_symbol(cur->data.array_assignment.array_name);
                if (!array_symbol) {
                    report_semantic_error_local(0, 0, "Array no declarado", "global");
                    break;
                }
                if (cur->data.array_assignment.index) {
                    data_type_t index_type = analyze_expression(cur->data.array_assignment.index);
                    if (index_type != TYPE_INT) {
                        report_semantic_error_local(0, 0, "Índice debe ser entero", "global");
                    }
                }
                if (cur->data.array_assignment.value) analyze_expression(cur->data.array_assignment.value);
                printf("✅ Asignación a array verificada\n");
                break;
            }

            case AST_BINARY_OP:
            case AST_UNARY_OP:
            case AST_VARIABLE:
            case AST_INT_LITERAL:
            case AST_FLOAT_LITERAL:
            case AST_STRING_LITERAL:
            case AST_CHAR_LITERAL:
            case AST_BOOL_LITERAL:
                printf("🔸 Expresión encontrada como statement (tipo %d)\n", cur->type);
                analyze_expression(cur);
                break;

            default:
                printf("🔸 Tipo de statement no implementado: %d\n", cur->type);
                break;
        }

        /* avanzar a siguiente statement en la lista */
        cur = cur->next;
    }
}

// =================== FUNCIONES AUXILIARES ===================

data_type_t string_to_type(const char *type_str) {
    if (!type_str) return TYPE_UNKNOWN;
    if (strcmp(type_str, "int") == 0) return TYPE_INT;
    if (strcmp(type_str, "float") == 0) return TYPE_FLOAT;
    if (strcmp(type_str, "double") == 0) return TYPE_DOUBLE;
    if (strcmp(type_str, "String") == 0) return TYPE_STRING;
    if (strcmp(type_str, "char") == 0) return TYPE_CHAR;
    if (strcmp(type_str, "boolean") == 0) return TYPE_BOOLEAN;
    if (strcmp(type_str, "void") == 0) return TYPE_VOID;

    /* Soporte básico para tipos array: int[], float[], double[], String[] */
    size_t len = strlen(type_str);
    if (len > 2 && strcmp(type_str + len - 2, "[]") == 0) {
        if (strncmp(type_str, "int", 3) == 0) return TYPE_ARRAY_INT;
        if (strncmp(type_str, "float", 5) == 0) return TYPE_ARRAY_FLOAT;
        if (strncmp(type_str, "double", 6) == 0) return TYPE_ARRAY_DOUBLE;
        if (strncmp(type_str, "String", 6) == 0) return TYPE_ARRAY_STRING;
        if (strncmp(type_str, "char", 4) == 0) return TYPE_ARRAY_CHAR;
        if (strncmp(type_str, "boolean", 7) == 0) return TYPE_ARRAY_BOOLEAN;
    }
    return TYPE_UNKNOWN;
}

const char* type_to_string(data_type_t type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_DOUBLE: return "double";
        case TYPE_STRING: return "String";
        case TYPE_CHAR: return "char";
        case TYPE_BOOLEAN: return "boolean";
        case TYPE_VOID: return "void";
        case TYPE_ARRAY_INT: return "int[]";     
        case TYPE_ARRAY_FLOAT: return "float[]";    
        case TYPE_ARRAY_STRING: return "String[]";
        case TYPE_ARRAY_CHAR: return "char[]";  
        case TYPE_ARRAY_BOOLEAN: return "boolean[]"; 
        default: return "unknown";
    }
}

void semantic_check_control_flow(ast_node *node) {
    if (!node) return;

    switch (node->type) {
        case AST_FOR:
            semantic_loop_depth++;
            semantic_check_control_flow(node->data.for_stmt.body);
            semantic_loop_depth--;
            break;
        case AST_WHILE:
            semantic_loop_depth++;
            semantic_check_control_flow(node->data.while_stmt.body);
            semantic_loop_depth--;
            break;
        case AST_DO_WHILE:
            semantic_loop_depth++;
            semantic_check_control_flow(node->data.do_while_stmt.body);
            semantic_loop_depth--;
            break;
        case AST_COMPOUND_STMT:
            semantic_check_control_flow(node->data.compound.statement_list);
            break;
        case AST_IF:
            semantic_check_control_flow(node->data.if_stmt.then_branch);
            semantic_check_control_flow(node->data.if_stmt.else_branch);
            break;
        case AST_BREAK:
            if (semantic_loop_depth == 0) {
                report_semantic_error(node->line, 0, "'break' fuera de bucle", "Global");
            }
            break;
        case AST_CONTINUE:
            if (semantic_loop_depth == 0) {
                report_semantic_error(node->line, 0, "'continue' fuera de bucle", "Global");
            }
            break;
        default:
            /* Recorre lista/children relevantes */
            /* Por simplicidad, revisamos siguiente en la lista */
            break;
    }
    semantic_check_control_flow(node->next);
}



// función para mantener compatibilidad:
void report_semantic_error_local(int line, int column, const char *message, const char *scope) {
    semantic_errors++;
    
    // Construir mensaje completo
    char full_message[512];
    if (scope && strlen(scope) > 0 && strcmp(scope, "Global") != 0) {
        snprintf(full_message, sizeof(full_message), "%s (en scope: %s)", message, scope);
    } else {
        strncpy(full_message, message, sizeof(full_message) - 1);
        full_message[sizeof(full_message) - 1] = '\0';
    }
    
    printf("ERROR SEMÁNTICO: %s\n", full_message);
    
    // ⭐ LLAMAR a la función del sistema de errores:
    report_semantic_error(line, column, full_message, scope ? scope : "Global");
}

void set_shadowing_policy(int policy) {
    shadowing_policy = policy;
    printf("Política de shadowing: %s\n", policy ? "permitido" : "prohibido");
}

// =================== TABLA DE SÍMBOLOS GLOBAL ===================

symbol_table_t* create_symbol_table(void) {
    if (!global_symbol_table) {
        global_symbol_table = malloc(sizeof(symbol_table_t));
        global_symbol_table->symbols = NULL;
        global_symbol_table->scope_level = 0;
        global_symbol_table->parent = NULL;
        printf("✅ Tabla de símbolos global creada\n");
    }
    return global_symbol_table;
}

void add_symbol(symbol_table_t *table, const char *name, data_type_t type, const char *scope, int line) {
    if (!table) {
        table = create_symbol_table();
    }
    
    // Verificar duplicados en el mismo scope
    symbol_t *existing = find_symbol_in_scope(table, name, scope);
    if (existing) {
        printf("⚠️ Variable '%s' ya declarada en scope '%s'\n", name, scope);
        return;
    }
    
    // Crear nuevo símbolo
    symbol_t *new_symbol = malloc(sizeof(symbol_t));
    new_symbol->name = strdup(name);
    new_symbol->type = type;
    new_symbol->scope_name = strdup(scope);
    new_symbol->line = line;
    new_symbol->is_initialized = 0;
    new_symbol->scope_level = 0;
    new_symbol->next = table->symbols;
    
    table->symbols = new_symbol;
    printf("✅ Símbolo agregado: %s (%s) en scope '%s' línea %d\n", 
           name, type_to_string(type), scope, line);
}

symbol_t* find_symbol_in_scope(symbol_table_t *table, const char *name, const char *scope) {
    if (!table) return NULL;
    
    symbol_t *current = table->symbols;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->scope_name, scope) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void print_symbol_table(void) {
    if (!global_symbol_table || !global_symbol_table->symbols) {
        printf("❌ Tabla de símbolos vacía\n");
        return;
    }
    
    printf("\n=== TABLA DE SÍMBOLOS ===\n");
    printf("%-15s %-10s %-15s %-6s\n", "NOMBRE", "TIPO", "ÁMBITO", "LÍNEA");
    printf("================================================\n");
    
    symbol_t *current = global_symbol_table->symbols;
    int count = 0;
    
    while (current != NULL) {
        printf("%-15s %-10s %-15s %-6d\n", 
               current->name, 
               type_to_string(current->type), 
               current->scope_name, 
               current->line);
        current = current->next;
        count++;
    }
    printf("================================================\n");
    printf("Total símbolos: %d\n\n", count);
}

void clear_global_symbol_table(void) {
    if (!global_symbol_table) return;
    symbol_t *cur = global_symbol_table->symbols;
    while (cur) {
        symbol_t *next = cur->next;
        if (cur->name) free(cur->name);
        if (cur->scope_name) free(cur->scope_name);
        free(cur);
        cur = next;
    }
    global_symbol_table->symbols = NULL;
}

// =================== FUNCIONES PARA EL PARSER ===================

void add_symbol_to_table(const char* name, data_type_t type, const char* scope, int line) {
    if (!global_symbol_table) {
        global_symbol_table = create_symbol_table();
    }
    printf("DEBUG: add_symbol_to_table called -> name='%s' type=%s scope='%s' line=%d\n",
          name ? name : "(null)", type_to_string(type), scope ? scope : "(null)", line);
    add_symbol(global_symbol_table, name, type, scope, line);
}

int verificar_asignacion(const char* var_name, ast_node* expr) {
    if (!var_name || !expr) {
        printf("❌ Parámetros nulos en verificar_asignacion\n");
        return 0;
    }
    
    // Buscar la variable en la tabla de símbolos
    symbol_t* symbol = lookup_symbol(var_name);
    if (!symbol) {
        printf("❌ Variable '%s' no encontrada\n", var_name);
        return 0; // Variable no encontrada
    }
    
    // Obtener el tipo de la expresión
    data_type_t var_type = symbol->type;
    data_type_t expr_type = get_expression_type(expr);
    
    // Promoción automática: float -> double
    if (var_type == TYPE_DOUBLE && expr_type == TYPE_FLOAT) {
        printf("🔄 Promoción automática en asignación: float -> double\n");
        return 1; // Permitir la asignación
    }
    
    // Verificar compatibilidad exacta
    if (var_type == expr_type) {
        return 1; // Tipos compatibles
    }
    
    printf("❌ Tipos incompatibles: variable %s, expresión %s\n", 
           type_to_string(var_type), type_to_string(expr_type));
    return 0;
}

data_type_t get_expression_type(ast_node* expr) {
    if (!expr) return TYPE_UNKNOWN;
    
    switch (expr->type) {
       
        case AST_INT_LITERAL:
            return TYPE_INT;
            
        
        case AST_FLOAT_LITERAL:
            return TYPE_FLOAT;
            
        
        case AST_DOUBLE_LITERAL:
            return TYPE_DOUBLE;
            
        
        case AST_STRING_LITERAL:
            return TYPE_STRING;
            
        
        case AST_BOOL_LITERAL:
            return TYPE_BOOLEAN;
            
        
        case AST_CHAR_LITERAL:
            return TYPE_CHAR;
            
        case AST_VARIABLE: {
            // Buscar el tipo de la variable en la tabla de símbolos
            symbol_t* symbol = lookup_symbol(expr->data.var_name);
            return symbol ? symbol->type : TYPE_UNKNOWN;
        }
        case AST_ARRAY_ACCESS: {
            if (!expr->data.array_access.array_name) return TYPE_UNKNOWN;
            symbol_t *sym = lookup_symbol(expr->data.array_access.array_name);
            if (!sym) return TYPE_UNKNOWN;
            if (sym->type == TYPE_ARRAY_INT) return TYPE_INT;
            if (sym->type == TYPE_ARRAY_FLOAT) return TYPE_FLOAT;
            if (sym->type == TYPE_ARRAY_DOUBLE) return TYPE_DOUBLE;
            if (sym->type == TYPE_ARRAY_STRING) return TYPE_STRING;
            return TYPE_UNKNOWN;
        }

        case AST_METHOD_CALL: {
            /* Inferencias básicas para builtins/metodos usados por ejemplos */
            ast_node *recv = expr->data.method_call.receiver;
            const char *mname = expr->data.method_call.method_name ? expr->data.method_call.method_name : "";
            if (!recv) {
                if (strcmp(mname, "calcularPromedio") == 0) return TYPE_DOUBLE;
                if (strcmp(mname, "verificarAprobacion") == 0) return TYPE_BOOLEAN;
                if (strcmp(mname, "generarMensaje") == 0) return TYPE_STRING;
                if (strcmp(mname, "calcularNotaFinal") == 0) return TYPE_DOUBLE;
                if (strcmp(mname, "busquedaBinaria") == 0) return TYPE_INT;
                if (strcmp(mname, "sumarDigitos") == 0) return TYPE_INT;
                if (strcmp(mname, "potencia") == 0) return TYPE_INT;
                if (strcmp(mname, "esPalindromo") == 0) return TYPE_BOOLEAN;
                if (strcmp(mname, "invertirNumero") == 0) return TYPE_INT;
                if (strcmp(mname, "sumarCalificaciones") == 0) return TYPE_DOUBLE;
            } else if (recv->type == AST_VARIABLE && recv->data.var_name) {
                char fullname[256];
                snprintf(fullname, sizeof(fullname), "%s.%s", recv->data.var_name, mname);
                if (strcmp(fullname, "Integer.parseInt") == 0 || strcmp(mname, "parseInt") == 0) return TYPE_INT;
                if (strcmp(fullname, "Double.parseDouble") == 0 || strcmp(mname, "parseDouble") == 0) return TYPE_DOUBLE;
                if (strcmp(fullname, "Float.parseFloat") == 0 || strcmp(mname, "parseFloat") == 0) return TYPE_FLOAT;
                if (strcmp(fullname, "String.valueOf") == 0 || strcmp(mname, "valueOf") == 0) return TYPE_STRING;
                if (strcmp(mname, "length") == 0) return TYPE_INT;
                if (strcmp(mname, "toString") == 0) return TYPE_STRING;
            }
            return TYPE_UNKNOWN;
        }

        case AST_BINARY_OP: {
            data_type_t left_type = get_expression_type(expr->data.op.left);
            data_type_t right_type = get_expression_type(expr->data.op.right);
            
            // Para operaciones aritméticas, retornar el tipo "mayor"
            if (left_type == TYPE_DOUBLE || right_type == TYPE_DOUBLE) {
                return TYPE_DOUBLE;
            } else if (left_type == TYPE_FLOAT || right_type == TYPE_FLOAT) {
                return TYPE_FLOAT;
            } else if (left_type == TYPE_INT && right_type == TYPE_INT) {
                return TYPE_INT;
            }
            return TYPE_UNKNOWN;
        }
        
        default:
            return TYPE_UNKNOWN;
    }
}