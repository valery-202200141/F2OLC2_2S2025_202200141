#include "../include/ast.h" 
#include "../include/parser.h" // Para los tokens
#include <stdlib.h>
#include <string.h>

/******************************
 *   FUNCIONES DE CREACIÓN    *
 ******************************/

// Literales y valores básicos
ast_node* new_ast_int_literal(int value) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_INT_LITERAL;
    node->data.int_value = value;
    node->next = NULL;
    return node;
}

ast_node* new_ast_float_literal(float value) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_FLOAT_LITERAL;
    node->data.float_value = value;
    node->next = NULL;
    return node;
}

ast_node* new_ast_double_literal(double value) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_DOUBLE_LITERAL;
    node->data.double_value = value;
    node->next = NULL;
    return node;
}

ast_node* new_ast_string_literal(char *value) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_STRING_LITERAL;
    node->data.string_value = strdup(value); // Copia la string
    node->next = NULL;
    return node;
}

ast_node* new_ast_char_literal(char value) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_CHAR_LITERAL;
    node->data.char_value = value;
    node->next = NULL;
    return node;
}

ast_node* new_ast_bool_literal(int value) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_BOOL_LITERAL;
    node->data.bool_value = value;
    node->next = NULL;
    return node;
}

ast_node* new_ast_null_literal(void) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_NULL_LITERAL;
    node->next = NULL;
    return node;
}

ast_node* new_ast_variable(char *name) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_VARIABLE;
    node->data.var_name = strdup(name); // Copia el nombre
    node->next = NULL;
    return node;
}

ast_node* new_ast_type(char *type_name) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_TYPE;
    node->data.type_name = strdup(type_name); // Copia el nombre del tipo
    node->next = NULL;
    return node;
}

// Expresiones
ast_node* new_ast_binary_op(operator_type op, ast_node *left, ast_node *right) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_BINARY_OP;
    node->data.op.op = op;
    node->data.op.left = left;
    node->data.op.right = right;
    node->next = NULL;
    return node;
}

ast_node* new_ast_unary_op(operator_type op, ast_node *operand) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_UNARY_OP;
    node->data.op.op = op;
    node->data.op.left = operand; // Usamos left para el operando
    node->data.op.right = NULL;
    node->next = NULL;
    return node;
}

// Declaraciones y asignaciones
ast_node* new_ast_declaration(ast_node *type, char *name, ast_node *value) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_DECLARATION;
    node->data.declaration.var_type = type;
    node->data.declaration.var_name = strdup(name);
    node->data.declaration.value = value;
    node->next = NULL;
    return node;
}

ast_node* new_ast_assign(char *name, ast_node *value) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_ASSIGNMENT;
    node->data.assignment.var_name = strdup(name);
    node->data.assignment.value = value;
    node->next = NULL;
    return node;
}


// Estructuras de control

ast_node* new_ast_if(ast_node *condition, ast_node *then_branch, ast_node *else_branch) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_IF;
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.then_branch = then_branch;
    node->data.if_stmt.else_branch = else_branch;
    node->next = NULL;
    return node;
}

ast_node* new_ast_while(ast_node *condition, ast_node *body) {
    ast_node *node = malloc(sizeof(ast_node));
    if (!node) return NULL;
    
    node->type = AST_WHILE;
    node->data.while_stmt.condition = condition;
    node->data.while_stmt.body = body;
    node->next = NULL;
    node->line = 0;
    
    return node;
}

ast_node* new_ast_do_while(ast_node *condition, ast_node *body) {
    ast_node *node = malloc(sizeof(ast_node));
    if (!node) return NULL;
    
    node->type = AST_DO_WHILE;
    node->data.do_while_stmt.condition = condition;
    node->data.do_while_stmt.body = body;
    node->next = NULL;
    node->line = 0;
    
    return node;
}

ast_node* new_ast_for(ast_node *init, ast_node *condition, ast_node *increment, ast_node *body) {
    ast_node *node = malloc(sizeof(ast_node));
    if (!node) return NULL;
    
    node->type = AST_FOR;
    node->data.for_stmt.init = init;
    node->data.for_stmt.condition = condition;
    node->data.for_stmt.increment = increment;
    node->data.for_stmt.body = body;
    node->next = NULL;
    node->line = 0;
    
    return node;
}

ast_node* new_ast_return(ast_node *value) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_RETURN;
    node->data.return_stmt.value = value;
    node->next = NULL;
    return node;
}


ast_node* new_ast_continue(void) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_CONTINUE;
    node->next = NULL;
    return node;
}

// Estructuras de agrupación
ast_node* new_ast_compound_stmt(ast_node *stmt_list, ast_node *stmt) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_COMPOUND_STMT;
    
    // Si stmt_list es NULL, creamos una nueva lista
    if (stmt_list == NULL) {
        node->data.compound.statement_list = stmt;
    } else {
        // Encontrar el último statement en la lista y agregar el nuevo
        ast_node *current = stmt_list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = stmt;
        node->data.compound.statement_list = stmt_list;
    }
    
    node->next = NULL;
    return node;
}

ast_node* new_ast_main_function(char *name, ast_node *body) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_MAIN_FUNCTION;
    node->data.function_def.return_type = strdup("void");
    node->data.function_def.name = strdup(name);
    node->data.function_def.parameters = NULL;
    node->data.function_def.body = body;
    node->next = NULL;
    return node;
}

ast_node* new_ast_print_stmt(ast_node *expr) {
    ast_node *node = malloc(sizeof(ast_node));
    if (!node) {
        printf("❌ Error: malloc falló en new_ast_print_stmt\n");
        return NULL;
    }
    
    memset(node, 0, sizeof(ast_node));
    
    node->type = AST_PRINT_STMT;
    node->data.print_stmt.expression = expr;
    node->next = NULL;
    return node;
}

ast_node* new_ast_array_declaration(ast_node *type, char *name, ast_node *size) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_ARRAY_DECLARATION;
    node->data.array_decl.element_type = type;
    node->data.array_decl.array_name = strdup(name);
    node->data.array_decl.size = size;
    node->data.array_decl.init_values = NULL;
    node->next = NULL;
    return node;
}

ast_node* new_ast_array_declaration_with_init(ast_node *type, char *name, ast_node *size, ast_node *init) {
    ast_node *node = new_ast_array_declaration(type, name, size);
    node->data.array_decl.init_values = init;
    return node;
}

ast_node* new_ast_array_access(char *name, ast_node *index) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_ARRAY_ACCESS;
    node->data.array_access.array_name = strdup(name);
    node->data.array_access.index = index;
    node->next = NULL;
    return node;
}

ast_node* new_ast_array_init(ast_node *values) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_ARRAY_INIT;
    node->data.array_decl.init_values = values;
    node->next = NULL;
    return node;
}

ast_node* new_ast_array_assignment(char *array_name, ast_node *index, ast_node *value){
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_ARRAY_ASSIGNMENT;
    node->data.array_assignment.array_name = strdup(array_name);
    node->data.array_assignment.index = index;
    node->data.array_assignment.value = value;
    node->next = NULL;
    return node;
}

ast_node* new_ast_string_equals(ast_node *left_string, ast_node *right_expr) {
    ast_node *node = malloc(sizeof(ast_node));
    node->type = AST_STRING_EQUALS;
    node->data.string_equals.left_string = left_string;
    node->data.string_equals.right_expr = right_expr;
    node->next = NULL;
    return node;
}

ast_node* new_ast_new_object(const char *class_name) {
    ast_node *n = calloc(1, sizeof(ast_node));
    if (!n) return NULL;
    n->type = AST_NEW_OBJECT;
    n->line = 0;
    n->next = NULL;
    n->data.new_object.class_name = class_name ? strdup(class_name) : NULL;
    return n;
}

ast_node* new_ast_break(void) {
    ast_node *n = calloc(1, sizeof(ast_node));
    if (!n) return NULL;
    n->type = AST_BREAK;
    n->line = 0;
    n->next = NULL;
    return n;
}

ast_node* new_ast_new_array(ast_node *elem_type, ast_node *size_expr) {
    ast_node *n = calloc(1, sizeof(ast_node));
    if (!n) return NULL;
    n->type = AST_NEW_ARRAY; /* añade este enum en ast.h si falta */
    n->line = 0;
    n->next = NULL;
    n->data.new_array.elem_type = elem_type;
    n->data.new_array.size_expr = size_expr;
    return n;
}

ast_node* new_ast_new_array_with_init(ast_node *elem_type, ast_node *init_list) {
    ast_node *n = calloc(1, sizeof(ast_node));
    if (!n) return NULL;
    n->type = AST_NEW_ARRAY_INIT;
    n->line = 0;
    n->next = NULL;
    n->data.new_array.elem_type = elem_type;
    n->data.new_array.init_list = init_list;
    return n;
}
ast_node* new_ast_foreach(ast_node *var_type, char *var_name, ast_node *collection, ast_node *body) {
    ast_node *n = calloc(1, sizeof(ast_node));
    if (!n) return NULL;
    n->type = AST_FOREACH;
    n->line = 0;
    n->next = NULL;
    n->data.foreach_stmt.var_type = var_type;
    n->data.foreach_stmt.var_name = var_name ? strdup(var_name) : NULL;
    n->data.foreach_stmt.collection = collection;
    n->data.foreach_stmt.body = body;
    return n;
}

ast_node* new_ast_function(const char *name, ast_node *body) {
    ast_node *node = calloc(1, sizeof(ast_node));
    if (!node) return NULL;
    /* Reutilizamos la estructura usada por main_function */
    node->type = AST_MAIN_FUNCTION; /* si prefieres, añade AST_FUNCTION en include/ast.h y úsalo */
    node->type = AST_FUNCTION;
    node->data.function_def.return_type = strdup("void"); /* parser no pasa el tipo aquí */
    node->data.function_def.name = name ? strdup(name) : NULL;
    node->data.function_def.parameters = NULL;
    node->data.function_def.body = body;
    node->next = NULL;
    node->line = 0;
    return node;
}


/******************************
 *   FUNCIONES DE UTILIDAD    *
 ******************************/
void free_ast(ast_node *node) {
    if (node == NULL) return;

    switch (node->type) {
        case AST_STRING_LITERAL:
            if (node->data.string_value) free(node->data.string_value);
            break;
        case AST_VARIABLE:
            if (node->data.var_name) free(node->data.var_name);
            break;
        case AST_TYPE:
            if (node->data.type_name) free(node->data.type_name);
            break;
        case AST_BINARY_OP:
            free_ast(node->data.op.left);
            free_ast(node->data.op.right);
            break;
        case AST_UNARY_OP:
            free_ast(node->data.op.left);
            break;
        case AST_DECLARATION:
            free_ast(node->data.declaration.var_type);
            if (node->data.declaration.var_name) free(node->data.declaration.var_name);
            free_ast(node->data.declaration.value);
            break;
        case AST_ASSIGNMENT:
            if (node->data.assignment.var_name) free(node->data.assignment.var_name);
            free_ast(node->data.assignment.value);
            break;
        case AST_IF:
            free_ast(node->data.if_stmt.condition);
            free_ast(node->data.if_stmt.then_branch);
            free_ast(node->data.if_stmt.else_branch);
            break;
        case AST_WHILE:
            free_ast(node->data.while_stmt.condition);
            free_ast(node->data.while_stmt.body);
            break;
        case AST_DO_WHILE:
            free_ast(node->data.do_while_stmt.condition);
            free_ast(node->data.do_while_stmt.body);
            break;
        case AST_FOR:
            free_ast(node->data.for_stmt.init);
            free_ast(node->data.for_stmt.condition);
            free_ast(node->data.for_stmt.increment);
            free_ast(node->data.for_stmt.body);
            break;
        case AST_RETURN:
            free_ast(node->data.return_stmt.value);
            break;
        case AST_COMPOUND_STMT:
            free_ast(node->data.compound.statement_list);
            break;
        case AST_PRINT_STMT:
            free_ast(node->data.print_stmt.expression);
            break;
        case AST_MAIN_FUNCTION:
            if (node->data.function_def.return_type) free(node->data.function_def.return_type);
            if (node->data.function_def.name) free(node->data.function_def.name);
            free_ast(node->data.function_def.parameters);
            free_ast(node->data.function_def.body);
            break;
        case AST_ARRAY_DECLARATION:
            free_ast(node->data.array_decl.element_type);
            if (node->data.array_decl.array_name) free(node->data.array_decl.array_name);
            free_ast(node->data.array_decl.size);
            free_ast(node->data.array_decl.init_values);
            break;
        case AST_ARRAY_ACCESS:
            if (node->data.array_access.array_name) free(node->data.array_access.array_name);
            free_ast(node->data.array_access.index);
            break;
        case AST_ARRAY_ASSIGNMENT:
            if (node->data.array_assignment.array_name) free(node->data.array_assignment.array_name);
            free_ast(node->data.array_assignment.index);
            free_ast(node->data.array_assignment.value);
            break;
        case AST_NEW_ARRAY:
            free_ast(node->data.new_array.elem_type);
            free_ast(node->data.new_array.size_expr);
            break;
        case AST_NEW_ARRAY_INIT:
            free_ast(node->data.new_array.elem_type);
            free_ast(node->data.new_array.init_list);
            break;
        case AST_FOREACH:
            free_ast(node->data.foreach_stmt.var_type);
            if (node->data.foreach_stmt.var_name) free(node->data.foreach_stmt.var_name);
            free_ast(node->data.foreach_stmt.collection);
            free_ast(node->data.foreach_stmt.body);
            break;
        case AST_STRING_EQUALS:
            free_ast(node->data.string_equals.left_string);
            free_ast(node->data.string_equals.right_expr);
            break;
        case AST_NEW_OBJECT:
            if (node->data.new_object.class_name) free(node->data.new_object.class_name);
            break;
        case AST_BREAK:
        case AST_CONTINUE:
            /* no extra members */
            break;
        default:
            /* literales y nodos simples no requieren frees extras */
            break;
    }

    /* liberar siguiente y finalmente el nodo */
    if (node->next) free_ast(node->next);
    free(node);
}


// ...existing code...
void print_ast(ast_node *node, int indent) {
    if (node == NULL) return;
    
    // Imprimir indentación
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
    
    switch (node->type) {
        case AST_INT_LITERAL:
            printf("INT_LITERAL: %d\n", node->data.int_value);
            break;

        
        case AST_IF:
            printf("IF_STATEMENT\n");
            print_ast(node->data.if_stmt.condition, indent + 1);
            printf("THEN:\n");
            print_ast(node->data.if_stmt.then_branch, indent + 1);
            if (node->data.if_stmt.else_branch != NULL) {
                printf("ELSE:\n");
                print_ast(node->data.if_stmt.else_branch, indent + 1);
            }
            break;

        // ----- ADICIONES: manejar nodos que estaban faltando -----
        case AST_PRINT_STMT:
            printf("PRINT_STMT\n");
            if (node->data.print_stmt.expression) {
                print_ast(node->data.print_stmt.expression, indent + 1);
            }
            break;

        case AST_ARRAY_DECLARATION:
            printf("ARRAY_DECL: %s\n", node->data.array_decl.array_name ? node->data.array_decl.array_name : "(anon)");
            if (node->data.array_decl.element_type) print_ast(node->data.array_decl.element_type, indent + 1);
            if (node->data.array_decl.size) print_ast(node->data.array_decl.size, indent + 1);
            if (node->data.array_decl.init_values) print_ast(node->data.array_decl.init_values, indent + 1);
            break;

        case AST_ARRAY_INIT:
            printf("ARRAY_INIT\n");
            print_ast(node->data.array_decl.init_values, indent + 1);
            break;

        case AST_ARRAY_ACCESS:
            printf("ARRAY_ACCESS: %s\n", node->data.array_access.array_name ? node->data.array_access.array_name : "(null)");
            if (node->data.array_access.index) print_ast(node->data.array_access.index, indent + 1);
            break;

        case AST_ARRAY_ASSIGNMENT:
            printf("ARRAY_ASSIGNMENT: %s\n", node->data.array_assignment.array_name ? node->data.array_assignment.array_name : "(null)");
            if (node->data.array_assignment.index) print_ast(node->data.array_assignment.index, indent + 1);
            if (node->data.array_assignment.value) print_ast(node->data.array_assignment.value, indent + 1);
            break;

        case AST_FOREACH:
            printf("FOREACH: %s %s :\n",
                   node->data.foreach_stmt.var_type && node->data.foreach_stmt.var_type->data.type_name ? node->data.foreach_stmt.var_type->data.type_name : "(type)",
                   node->data.foreach_stmt.var_name ? node->data.foreach_stmt.var_name : "(it)");
            if (node->data.foreach_stmt.collection) print_ast(node->data.foreach_stmt.collection, indent + 1);
            if (node->data.foreach_stmt.body) print_ast(node->data.foreach_stmt.body, indent + 1);
            break;

        case AST_NEW_ARRAY:
            printf("NEW_ARRAY\n");
            if (node->data.new_array.elem_type) print_ast(node->data.new_array.elem_type, indent + 1);
            if (node->data.new_array.size_expr) print_ast(node->data.new_array.size_expr, indent + 1);
            break;

        case AST_NEW_ARRAY_INIT:
            printf("NEW_ARRAY_INIT\n");
            if (node->data.new_array.init_list) print_ast(node->data.new_array.init_list, indent + 1);
            break;

        case AST_NEW_OBJECT:
            printf("NEW_OBJECT: %s\n", node->data.new_object.class_name ? node->data.new_object.class_name : "(class)");
            break;

        case AST_BREAK:
            printf("BREAK\n");
            break;

        case AST_CONTINUE:
            printf("CONTINUE\n");
            break;

        case AST_FOR:
            printf("FOR_LOOP\n");
            if (node->data.for_stmt.init) { printf("- Init:\n"); print_ast(node->data.for_stmt.init, indent + 1); }
            if (node->data.for_stmt.condition) { printf("- Condition:\n"); print_ast(node->data.for_stmt.condition, indent + 1); }
            if (node->data.for_stmt.increment) { printf("- Increment:\n"); print_ast(node->data.for_stmt.increment, indent + 1); }
            if (node->data.for_stmt.body) { printf("- Body:\n"); print_ast(node->data.for_stmt.body, indent + 1); }
            break;

        case AST_WHILE:
            printf("WHILE_LOOP\n");
            if (node->data.while_stmt.condition) { printf("- Condition:\n"); print_ast(node->data.while_stmt.condition, indent + 1); }
            if (node->data.while_stmt.body) { printf("- Body:\n"); print_ast(node->data.while_stmt.body, indent + 1); }
            break;

        case AST_DO_WHILE:
            printf("DO_WHILE_LOOP\n");
            if (node->data.do_while_stmt.body) { printf("- Body:\n"); print_ast(node->data.do_while_stmt.body, indent + 1); }
            if (node->data.do_while_stmt.condition) { printf("- Condition:\n"); print_ast(node->data.do_while_stmt.condition, indent + 1); }
            break;

        case AST_RETURN:
            printf("RETURN\n");
            if (node->data.return_stmt.value) print_ast(node->data.return_stmt.value, indent + 1);
            break;

        // ...existing code...
        default:
            printf("UNKNOWN_NODE_TYPE: %d\n", node->type);
            break;
    }
    
    // Imprimir el siguiente nodo en la lista
    if (node->next != NULL) {
        print_ast(node->next, indent);
    }
}


/******************************
 *   CONVERSIÓN DE TOKENS     *
 ******************************/

operator_type token_to_binary_op(int token) {
    switch (token) {
        case PLUS: return OP_PLUS;
        case MINUS: return OP_MINUS;
        case MULT: return OP_MULT;
        case DIV: return OP_DIV;
        case MOD: return OP_MOD;
        case EQUALS: return OP_EQUALS;
        case NOT_EQUALS: return OP_NOT_EQUALS;
        case LESS: return OP_LESS;
        case GREATER: return OP_GREATER;
        case LESS_EQUALS: return OP_LESS_EQUALS;
        case GREATER_EQUALS: return OP_GREATER_EQUALS;
        case AND: return OP_AND;
        case OR: return OP_OR;
        default: return OP_PLUS; // Default, no debería ocurrir
    }
}

operator_type token_to_unary_op(int token) {
    switch (token) {
        case NOT: return OP_NOT;
        case MINUS: return OP_UMINUS;
        case INCREMENT: return OP_INCREMENT;
        case DECREMENT: return OP_DECREMENT;
        default: return OP_NOT; // Default, no debería ocurrir
    }
}

ast_node* new_ast_method_call(ast_node *receiver, const char *method_name, ast_node *arg) {
    ast_node *n = calloc(1, sizeof(ast_node));
    if (!n) return NULL;
    n->type = AST_METHOD_CALL;
    n->line = 0;
    n->next = NULL;
    n->data.method_call.receiver = receiver;
    n->data.method_call.method_name = method_name ? strdup(method_name) : NULL;
    n->data.method_call.arg = arg;
    return n;
}

/******************************
 *   FUNCIÓN PARA LA GUI      *
 ******************************/
char* type_token_to_string(int token) {
    switch (token) {
        case INT: return "int";
        case FLOAT: return "float";
        case STRING_TYPE: return "String";
        case CHAR: return "char";
        case BOOLEAN: return "boolean";
        case VOID: return "void";
        default: return "unknown";
    }
}
char* ast_to_string(ast_node *node) {
    if (node == NULL) return strdup("(null)");
    
    char buffer[2048]; // Buffer más grande para contenido complejo
    char *result = NULL;
    
    switch (node->type) {
        case AST_INT_LITERAL:
            snprintf(buffer, sizeof(buffer), "INT_LITERAL: %d", node->data.int_value);
            break;
            
        case AST_FLOAT_LITERAL:
            snprintf(buffer, sizeof(buffer), "FLOAT_LITERAL: %f", node->data.float_value);
            break;
            
        case AST_STRING_LITERAL:
            snprintf(buffer, sizeof(buffer), "STRING_LITERAL: \"%s\"", node->data.string_value);
            break;
            
        case AST_CHAR_LITERAL:
            snprintf(buffer, sizeof(buffer), "CHAR_LITERAL: '%c'", node->data.char_value);
            break;
            
        case AST_BOOL_LITERAL:
            snprintf(buffer, sizeof(buffer), "BOOL_LITERAL: %s", 
                    node->data.bool_value ? "true" : "false");
            break;
            
        case AST_NULL_LITERAL:
            snprintf(buffer, sizeof(buffer), "NULL_LITERAL");
            break;
            
        case AST_VARIABLE:
            snprintf(buffer, sizeof(buffer), "VARIABLE: %s", node->data.var_name);
            break;
            
        case AST_TYPE:
            snprintf(buffer, sizeof(buffer), "TYPE: %s", node->data.type_name);
            break;
        
        case AST_METHOD_CALL: {
            char *recv = node->data.method_call.receiver ? ast_to_string(node->data.method_call.receiver) : strdup("(no recv)");
            char *arg  = node->data.method_call.arg ? ast_to_string(node->data.method_call.arg) : strdup("(no arg)");
            snprintf(buffer, sizeof(buffer), "METHOD_CALL: %s.%s(%s)", recv, node->data.method_call.method_name ? node->data.method_call.method_name : "(anon)", arg);
            free(recv); free(arg);
            break;
        }
        case AST_PRINT_STMT: {
            char *e = node->data.print_stmt.expression ? ast_to_string(node->data.print_stmt.expression) : strdup("(no expr)");
            snprintf(buffer, sizeof(buffer), "PRINT_STMT: %s", e);
            free(e);
            break;
        }
        case AST_NEW_ARRAY:
            snprintf(buffer, sizeof(buffer), "NEW_ARRAY: elem_type=%s size_expr=%s",
                     node->data.new_array.elem_type ? (node->data.new_array.elem_type->data.type_name ? node->data.new_array.elem_type->data.type_name : "(type)") : "(null)",
                     node->data.new_array.size_expr ? "(expr)" : "(no size)");
            break;
        case AST_NEW_ARRAY_INIT: {
            char *init = node->data.new_array.init_list ? ast_to_string(node->data.new_array.init_list) : strdup("(no init)");
            char *etype = node->data.new_array.elem_type && node->data.new_array.elem_type->data.type_name ? node->data.new_array.elem_type->data.type_name : "(elem)";
            snprintf(buffer, sizeof(buffer), "NEW_ARRAY_INIT: %s { %s }", etype, init);
            free(init);
            break;
        }
        case AST_ARRAY_INIT: {
            char *vals = node->data.array_decl.init_values ? ast_to_string(node->data.array_decl.init_values) : strdup("(empty)");
            snprintf(buffer, sizeof(buffer), "ARRAY_INIT: %s", vals);
            free(vals);
            break;
        }
        case AST_ARRAY_DECLARATION: {
            char *etype = node->data.array_decl.element_type ? ast_to_string(node->data.array_decl.element_type) : strdup("(elem)");
            char *size  = node->data.array_decl.size ? ast_to_string(node->data.array_decl.size) : strdup("(no size)");
            snprintf(buffer, sizeof(buffer), "ARRAY_DECL: %s %s size=%s init=%s",
                     node->data.array_decl.array_name ? node->data.array_decl.array_name : "(anon)", etype, size,
                     node->data.array_decl.init_values ? "yes" : "no");
            free(etype); free(size);
            break;
        }
        case AST_ARRAY_ACCESS:
            snprintf(buffer, sizeof(buffer), "ARRAY_ACCESS: %s[...]", node->data.array_access.array_name ? node->data.array_access.array_name : "(null)");
            break;
        case AST_ARRAY_ASSIGNMENT:
            snprintf(buffer, sizeof(buffer), "ARRAY_ASSIGN: %s[...] = (value)", node->data.array_assignment.array_name ? node->data.array_assignment.array_name : "(null)");
            break;
        case AST_FUNCTION:
            snprintf(buffer, sizeof(buffer), "FUNCTION_DEF: %s", node->data.function_def.name ? node->data.function_def.name : "(anon)");
            break;
        case AST_MAIN_FUNCTION:
            snprintf(buffer, sizeof(buffer), "MAIN_FUNCTION: %s", node->data.function_def.name ? node->data.function_def.name : "(main)");
            break;
        case AST_STRING_EQUALS:
            snprintf(buffer, sizeof(buffer), "STRING_EQUALS");
            break;
        case AST_FOREACH: {
            char *col = node->data.foreach_stmt.collection ? ast_to_string(node->data.foreach_stmt.collection) : strdup("(collection)");
            snprintf(buffer, sizeof(buffer), "FOREACH: %s %s : %s", node->data.foreach_stmt.var_type && node->data.foreach_stmt.var_type->data.type_name ? node->data.foreach_stmt.var_type->data.type_name : "(type)", node->data.foreach_stmt.var_name ? node->data.foreach_stmt.var_name : "(it)", col);
            free(col);
            break;
        }
        case AST_NEW_OBJECT:
            snprintf(buffer, sizeof(buffer), "NEW_OBJECT: %s", node->data.new_object.class_name ? node->data.new_object.class_name : "(class)");
            break;
        case AST_RETURN: {
            char *v = node->data.return_stmt.value ? ast_to_string(node->data.return_stmt.value) : strdup("(void)");
            snprintf(buffer, sizeof(buffer), "RETURN: %s", v);
            free(v);
            break;
        }

        case AST_BINARY_OP: {
            const char *op_str = "UNKNOWN_OP";
            switch (node->data.op.op) {
                case OP_PLUS: op_str = "+"; break;
                case OP_MINUS: op_str = "-"; break;
                case OP_MULT: op_str = "*"; break;
                case OP_DIV: op_str = "/"; break;
                case OP_MOD: op_str = "%"; break;
                case OP_EQUALS: op_str = "=="; break;
                case OP_NOT_EQUALS: op_str = "!="; break;
                case OP_LESS: op_str = "<"; break;
                case OP_GREATER: op_str = ">"; break;
                case OP_LESS_EQUALS: op_str = "<="; break;
                case OP_GREATER_EQUALS: op_str = ">="; break;
                case OP_AND: op_str = "&&"; break;
                case OP_OR: op_str = "||"; break;
                default: break;
            }
            char *left_str = ast_to_string(node->data.op.left);
            char *right_str = ast_to_string(node->data.op.right);
            snprintf(buffer, sizeof(buffer), "BINARY_OP(%s)\n- Left: %s\n- Right: %s", 
                    op_str, left_str, right_str);
            free(left_str);
            free(right_str);
            break;
        }
            
        case AST_UNARY_OP: {
            const char *op_str = "UNKNOWN_OP";
            switch (node->data.op.op) {
                case OP_NOT: op_str = "!"; break;
                case OP_UMINUS: op_str = "-"; break;
                case OP_INCREMENT: op_str = "++"; break;
                case OP_DECREMENT: op_str = "--"; break;
                default: break;
            }
            char *operand_str = ast_to_string(node->data.op.left);
            snprintf(buffer, sizeof(buffer), "UNARY_OP(%s)\n- Operand: %s", 
                    op_str, operand_str);
            free(operand_str);
            break;
        }
            
        case AST_DECLARATION: {
            char *type_str = ast_to_string(node->data.declaration.var_type);
            char *value_str = node->data.declaration.value ? 
                             ast_to_string(node->data.declaration.value) : 
                             strdup("(no value)");
            snprintf(buffer, sizeof(buffer), "DECLARATION\n- Variable: %s\n- Type: %s\n- Value: %s",
                    node->data.declaration.var_name, type_str, value_str);
            free(type_str);
            free(value_str);
            break;
        }
            
        case AST_ASSIGNMENT: {
            char *value_str = ast_to_string(node->data.assignment.value);
            snprintf(buffer, sizeof(buffer), "ASSIGNMENT\n- Variable: %s\n- Value: %s",
                    node->data.assignment.var_name, value_str);
            free(value_str);
            break;
        }
            
        case AST_IF: {
            char *cond_str = ast_to_string(node->data.if_stmt.condition);
            char *then_str = ast_to_string(node->data.if_stmt.then_branch);
            char *else_str = node->data.if_stmt.else_branch ? 
                           ast_to_string(node->data.if_stmt.else_branch) : 
                           strdup("(no else)");
            snprintf(buffer, sizeof(buffer), "IF_STATEMENT\n- Condition: %s\n- Then: %s\n- Else: %s",
                    cond_str, then_str, else_str);
            free(cond_str);
            free(then_str);
            free(else_str);
            break;
        }
            
        case AST_WHILE: {
            char *cond_str = ast_to_string(node->data.while_stmt.condition);
            char *body_str = ast_to_string(node->data.while_stmt.body);
            snprintf(buffer, sizeof(buffer), "WHILE_LOOP\n- Condition: %s\n- Body: %s",
                    cond_str, body_str);
            free(cond_str);
            free(body_str);
            break;
        }
            
        case AST_DO_WHILE: {
            char *cond_str = ast_to_string(node->data.do_while_stmt.condition);
            char *body_str = ast_to_string(node->data.do_while_stmt.body);
            snprintf(buffer, sizeof(buffer), "DO_WHILE_LOOP\n- Body: %s\n- Condition: %s",
                    body_str, cond_str);
            free(cond_str);
            free(body_str);
            break;
        }
            
        case AST_FOR: {
            char *init_str = ast_to_string(node->data.for_stmt.init);
            char *cond_str = ast_to_string(node->data.for_stmt.condition);
            char *inc_str = ast_to_string(node->data.for_stmt.increment);
            char *body_str = ast_to_string(node->data.for_stmt.body);
            snprintf(buffer, sizeof(buffer), "FOR_LOOP\n- Init: %s\n- Condition: %s\n- Increment: %s\n- Body: %s",
                    init_str, cond_str, inc_str, body_str);
            free(init_str);
            free(cond_str);
            free(inc_str);
            free(body_str);
            break;
        }

        
            
        case AST_BREAK:
            snprintf(buffer, sizeof(buffer), "BREAK");
            break;
            
        case AST_CONTINUE:
            snprintf(buffer, sizeof(buffer), "CONTINUE");
            break;
            
        case AST_COMPOUND_STMT: {
            char *stmt_str = ast_to_string(node->data.compound.statement_list);
            snprintf(buffer, sizeof(buffer), "COMPOUND_STATEMENT\n%s", stmt_str);
            free(stmt_str);
            break;
        }
            
        default:
            snprintf(buffer, sizeof(buffer), "UNKNOWN_NODE_TYPE: %d", node->type);
            break;
    }
    
    result = strdup(buffer);
    return result;
}