#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

// =================== TIPOS DE DATOS ===================

typedef enum {
    TYPE_UNKNOWN,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_CHAR,
    TYPE_BOOLEAN,
    TYPE_VOID,
    TYPE_FUNCTION,
    TYPE_ARRAY_INT,
    TYPE_ARRAY_FLOAT,     
    TYPE_ARRAY_STRING,   
    TYPE_ARRAY_CHAR,     
    TYPE_ARRAY_BOOLEAN 
} data_type_t;

// =================== ESTRUCTURA DE SÍMBOLOS ===================

// CORREGIR: Una sola definición de symbol
typedef struct symbol {
    char *name;              // Nombre del símbolo
    data_type_t type;        // Tipo de dato (CORREGIDO: era symbol_type)
    char *scope_name;        // Nombre del scope donde se declaró
    int line;                // Línea donde se declaró
    int is_initialized;      // Si ha sido inicializada
    int scope_level;         // Nivel del scope
    struct symbol *next;     // Lista enlazada
} symbol_t;

// =================== TABLA DE SÍMBOLOS ===================

typedef struct symbol_table {
    symbol_t *symbols;       // Lista de símbolos
    int scope_level;         // Nivel del scope
    struct symbol_table *parent; // Scope padre
} symbol_table_t;

// =================== VARIABLES GLOBALES ===================

// AGREGAR: Declaración externa
extern symbol_table_t *global_symbol_table;
extern symbol_table_t *current_scope;
extern int semantic_errors;
extern int shadowing_policy;

// =================== FUNCIONES DE GESTIÓN DE SCOPES ===================

symbol_table_t* create_scope(symbol_table_t *parent);
void destroy_scope(symbol_table_t *scope);
void enter_scope(void);
void exit_scope(void);
extern char current_scope_name[256];

// =================== FUNCIONES DE GESTIÓN DE SÍMBOLOS ===================

symbol_t* declare_symbol(const char *name, data_type_t type);
symbol_t* lookup_symbol(const char *name);
symbol_t* lookup_symbol_current_scope(const char *name);

// =================== ANÁLISIS SEMÁNTICO ===================

int check_semantics(ast_node *root);
data_type_t analyze_node(ast_node *node);
data_type_t analyze_expression(ast_node *expr);

// =================== TABLA DE SÍMBOLOS GLOBAL ===================

symbol_table_t* create_symbol_table(void);
void add_symbol(symbol_table_t *table, const char *name, data_type_t type, const char *scope, int line);
symbol_t* find_symbol_in_scope(symbol_table_t *table, const char *name, const char *scope);

// CORREGIR: Una sola declaración de print_symbol_table
void print_symbol_table(void);
void semantic_analysis(ast_node *root);
void analyze_statement(ast_node *stmt);

// =================== FUNCIONES AUXILIARES ===================

data_type_t string_to_type(const char *type_str);
const char* type_to_string(data_type_t type);
void report_semantic_error(int line, int column, const char *message, const char *scope);
void set_shadowing_policy(int policy);

// =================== FUNCIONES PARA EL PARSER ===================

void add_symbol_to_table(const char* name, data_type_t type, const char* scope, int line);
// Funciones para verificación de tipos
int verificar_asignacion(const char* var_name, ast_node* expr);
data_type_t get_expression_type(ast_node* expr);
data_type_t string_to_type(const char *type_str);
const char* type_to_string(data_type_t type);
void clear_global_symbol_table(void);


// Función para reportar errores semánticos localmente
void report_semantic_error_local(int line, int column, const char *message, const char *scope);

#endif // SEMANTIC_H