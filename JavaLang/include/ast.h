#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************
 *   ENUMERACIONES DE TIPOS   *
 ******************************/
typedef struct ast_node ast_node;
// Tipos de nodos del AST
typedef enum {
    // Literales y valores básicos
    AST_INT_LITERAL,
    AST_FLOAT_LITERAL,
    AST_DOUBLE_LITERAL,
    AST_STRING_LITERAL,
    AST_CHAR_LITERAL,
    AST_BOOL_LITERAL,
    AST_NULL_LITERAL,
    AST_VARIABLE,
    AST_TYPE,
    
    // Expresiones
    AST_BINARY_OP,
    AST_UNARY_OP,
    
    // Declaraciones y asignaciones
    AST_DECLARATION,
    AST_ASSIGNMENT,
    
    // Estructuras de control
    AST_IF,
    AST_WHILE,
    AST_DO_WHILE,
    AST_FOR,
    AST_RETURN,
    AST_BREAK,
    AST_CONTINUE,
    AST_MAIN_FUNCTION,
    AST_PRINT_STMT=21,

    
    // Estructuras de agrupación
    AST_COMPOUND_STMT,
    AST_ARRAY_DECLARATION,
    AST_ARRAY_ACCESS,
    AST_ARRAY_INIT,
    AST_ARRAY_ASSIGNMENT,
    AST_STRING_EQUALS,
    AST_METHOD_CALL,
    AST_NEW_ARRAY,         /* new <type>[size] */
    AST_NEW_ARRAY_INIT, 
    AST_NEW_OBJECT,
    AST_FOREACH,
    AST_FUNCTION,

    
    // Otros
    AST_PROGRAM
} ast_node_type;

// Tipos de operadores (coinciden con los tokens)
typedef enum {
    OP_PLUS, OP_MINUS, OP_MULT, OP_DIV, OP_MOD,
    OP_INCREMENT, OP_DECREMENT, OP_POST_INCREMENT,
    OP_ASSIGN, OP_PLUS_ASSIGN, OP_MINUS_ASSIGN, OP_MULT_ASSIGN, OP_DIV_ASSIGN,
    OP_EQUALS, OP_NOT_EQUALS, OP_LESS, OP_GREATER, OP_LESS_EQUALS, OP_GREATER_EQUALS,
    OP_AND, OP_OR, OP_NOT, OP_UMINUS, OP_POST_DECREMENT
} operator_type;

/******************************
 *   ESTRUCTURAS DE NODOS     *
 ******************************/

// Estructura base de todos los nodos del AST
typedef struct ast_node {
    ast_node_type type;
    int line_number; // Para reporte de errores (opcional)
    struct ast_node *next; // Para listas de statements
    
    union {
        // Literales
        int int_value;
        float float_value;
        double double_value;
        char *string_value;
        char char_value;
        int bool_value;
        
        // Variable (solo nombre)
        char *var_name;
        
        // Tipo de dato
        char *type_name;
        
        // Operadores binarios y unarios
        struct {
            operator_type op;
            struct ast_node *left;
            struct ast_node *right;
        } op;
        
        // Declaración: tipo, nombre, valor (opcional)
        struct {
            struct ast_node *var_type;
            char *var_name;
            struct ast_node *value;
        } declaration;
        
        // Asignación: nombre, valor
        struct {
            char *var_name;
            struct ast_node *value;
        } assignment;
        
        // If: condición, then, else
        struct {
            struct ast_node *condition;
            struct ast_node *then_branch;
            struct ast_node *else_branch;
        } if_stmt;
        
        // While: condición, cuerpo
        struct {
            struct ast_node *condition;
            struct ast_node *body;
        } while_stmt;
        
        // Do-While: cuerpo, condición
        struct {
            struct ast_node *body;
            struct ast_node *condition;
        } do_while_stmt;
        
        // For: init, condition, increment, body
        struct {
            struct ast_node *init;
            struct ast_node *condition;
            struct ast_node *increment;
            struct ast_node *body;
        } for_stmt;
        
        // Return: valor (puede ser NULL)
        struct {
            struct ast_node *value;
        } return_stmt;
        
        // Compound statement: lista de statements
        struct {
            struct ast_node *statement_list;
        } compound;
        
        // Programa: lista de declaraciones y funciones
        struct {
            char *return_type;
            char *name;
            struct ast_node *parameters;
            struct ast_node *body;
        } function_def;
        
        // Print statement
        struct {
            struct ast_node *expression;
        } print_stmt;

        // Arreglos
        struct {
            struct ast_node *element_type;  // tipo de elementos
            char *array_name;               // nombre del arreglo
            struct ast_node *size;          // tamaño
            struct ast_node *init_values;   // valores iniciales
        } array_decl;
        
        struct {
            char *array_name;               // nombre del arreglo
            struct ast_node *index;         // índice
        } array_access;

        struct {
            struct ast_node *elem_type;
            struct ast_node *size_expr;   /* expresión para tamaño */
            struct ast_node *init_list;   /* lista de inicializadores (opcional) */
        } new_array;

        struct {
            char *array_name;               // nombre del arreglo
            struct ast_node *index;         // índice
            struct ast_node *value;         // nuevo valor
        } array_assignment;


        // Método .equals() para strings
        struct {
            struct ast_node *left_string;   // string o variable del lado izquierdo
            struct ast_node *right_expr;    // expresión del lado derecho
        } string_equals;

        struct {
            struct ast_node *receiver;   /* expresión antes del punto */
            char *method_name;          /* nombre del método */
            struct ast_node *arg;       /* por ahora: 1 argumento */
        } method_call;

        struct {
            char *class_name; /* nombre de la clase (ej: "StringBuilder") */
        } new_object;

        struct {
            ast_node *var_type;   /* tipo (ast_node* from 'type' nonterminal) or NULL */
            char *var_name;       /* loop variable name */
            ast_node *collection; /* expression producing collection (variable/array) */
            ast_node *body;       /* statement body */
        } foreach_stmt;

    } data;
    int line;  // Línea del código fuente (opcional)
    int column; // Columna del código fuente (opcional)

} ast_node;

/******************************
 *   FUNCIONES DE CREACIÓN    *
 ******************************/

// Literales y valores básicos
ast_node* new_ast_int_literal(int value);
ast_node* new_ast_float_literal(float value);
ast_node* new_ast_double_literal(double value);
ast_node* new_ast_string_literal(char *value);
ast_node* new_ast_char_literal(char value);
ast_node* new_ast_bool_literal(int value);
ast_node* new_ast_null_literal(void);
ast_node* new_ast_variable(char *name);
ast_node* new_ast_type(char *type_name);

// Expresiones
ast_node* new_ast_binary_op(operator_type op, ast_node *left, ast_node *right);
ast_node* new_ast_unary_op(operator_type op, ast_node *operand);

// Declaraciones y asignaciones
ast_node* new_ast_declaration(ast_node *type, char *name, ast_node *value);
ast_node* new_ast_assign(char *name, ast_node *value);

// Estructuras de control
ast_node* new_ast_if(ast_node *condition, ast_node *then_branch, ast_node *else_branch);
ast_node* new_ast_while(ast_node *condition, ast_node *body);
ast_node* new_ast_do_while(ast_node *condition, ast_node *body);
ast_node* new_ast_for(ast_node *init, ast_node *condition, ast_node *increment, ast_node *body);
ast_node* new_ast_return(ast_node *value);
ast_node* new_ast_break(void);
ast_node* new_ast_continue(void);
ast_node* new_ast_main_function(char *name, ast_node *body);
ast_node* new_ast_print_stmt(ast_node *expr);
ast_node* new_ast_string_equals(ast_node *left_string, ast_node *right_expr);


// Estructura de arreglos

ast_node* new_ast_array_declaration(ast_node *type, char *name, ast_node *size);
ast_node* new_ast_array_declaration_with_init(ast_node *type, char *name, ast_node *size, ast_node *init);
ast_node* new_ast_array_access(char *name, ast_node *index);
ast_node* new_ast_array_init(ast_node *values);
ast_node* new_ast_array_assignment(char *array_name, ast_node *index, ast_node *value);


// Estructuras de agrupación
ast_node* new_ast_compound_stmt(ast_node *stmt_list, ast_node *stmt);
ast_node* new_ast_method_call(ast_node *receiver, const char *method_name, ast_node *arg);
ast_node* new_ast_new_object(const char *class_name);
ast_node* new_ast_function(const char *name, ast_node *body);




// Utilidades
void free_ast(ast_node *node);
void print_ast(ast_node *node, int indent);
char* ast_to_string(ast_node *node);

ast_node* new_ast_while(ast_node *condition, ast_node *body);
ast_node* new_ast_for(ast_node *init, ast_node *condition, ast_node *increment, ast_node *body);
ast_node* new_ast_do_while(ast_node *condition, ast_node *body);
ast_node* new_ast_new_array(ast_node *elem_type, ast_node *size_expr);
ast_node* new_ast_new_array_with_init(ast_node *elem_type, ast_node *init_list);
ast_node* new_ast_foreach(ast_node *var_type, char *var_name, ast_node *collection, ast_node *body);


/******************************
 *   CONVERSIÓN DE TOKENS     *
 ******************************/

// Funciones para convertir tokens de Bison a tipos del AST
operator_type token_to_binary_op(int token);
operator_type token_to_unary_op(int token);



#endif /* AST_H */