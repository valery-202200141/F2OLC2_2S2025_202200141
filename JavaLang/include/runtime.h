#ifndef RUNTIME_H
#define RUNTIME_H

#include "ast.h"

typedef void (*ConsolePrintCallback)(const char* message);
// Funciones del intérprete
void execute_program(ast_node *root);
ast_node* find_main_method(ast_node *program_node);
int evaluate_expression(ast_node *expr);
void execute_statement(ast_node *stmt);
void show_symbol_table(void);
void cleanup_runtime(void);


void set_console_callback(ConsolePrintCallback callback);
void set_console_print_safe(ConsolePrintCallback callback);
void console_print_program(const char *msg);
void runtime_log(const char *msg);
void set_runtime_debug(int enabled);

// Funciones para invocar métodos built-in
int builtin_invoke_int(const char *fullname, ast_node *arg, int *out_int);
int builtin_invoke_double(const char *fullname, ast_node *arg, double *out_double);
char* builtin_invoke_string(const char *fullname, ast_node *arg);
int builtin_dispatch(const char *fullname, struct ast_node *arg, int *out_int, double *out_double, char **out_str);
char *runtime_eval_as_string(struct ast_node *arg);

// Utils expr
char* get_string_value(struct ast_node *node);
void build_concatenated_string(struct ast_node *expr, char *result);

// Hooks para generación ARM64 por ejecución
void runtime_codegen_start(const char *out_path);
void runtime_codegen_finish(void);


// Wrappers para System.out.println(...)
void rt_println_int(long v);
void rt_println_double(double v);
void rt_println_string(const char *s);


#endif