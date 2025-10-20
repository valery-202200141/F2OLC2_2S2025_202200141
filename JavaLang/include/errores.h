#ifndef ERRORES_H
#define ERRORES_H

// Tipos de errores
typedef enum {
    ERROR_SINTACTICO,
    ERROR_SEMANTICO,
    ERROR_LEXICO,
    ERROR_RUNTIME
} error_type_t;

// Estructura para almacenar errores
typedef struct error_entry {
    int numero;
    error_type_t tipo;
    char descripcion[256];
    char ambito[64];
    int linea;
    int columna;
    struct error_entry *next;
} error_entry_t;

// Variables globales para manejo de errores
extern error_entry_t *error_list;
extern int error_count;
extern int current_line;
extern int current_column;

// Funciones para reportar errores
void report_syntax_error(int line, int column, const char *msg, const char *token);
void report_semantic_error(int line, int column, const char *msg, const char *scope);
void report_lexical_error(int line, int column, const char *msg, const char *token);
void report_runtime_error(int line, int column, const char *msg, const char *scope);

// Funciones de gestión de errores
void init_error_system(void);
void clear_errors(void);
void print_error_table(void);
char* generate_error_html(void);
void show_error_report(void);

// Funciones auxiliares
const char* get_error_type_string(error_type_t type);
void set_current_position(int line, int column);

#endif