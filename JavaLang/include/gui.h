#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include "ast.h"

// Estructura para manejar los widgets de la aplicación
typedef struct {
    GtkWidget *window;
    GtkWidget *notebook;  
    GtkWidget *source_view;
    GtkTextBuffer *source_buffer;
    GtkWidget *console_view;
    GtkTextBuffer *console_buffer;
    GtkWidget *ast_view;
    GtkWidget *symbols_view;
    GtkWidget *errors_view;
    GtkWidget *execute_button;
    GtkWidget *image_view;    
    GtkWidget *image_scroll;
    GtkTextBuffer *errors_buffer;
} AppWidgets;

// Funciones principales de la GUI
int main_gui(int argc, char *argv[]);
void build_gui(void);

// Funciones de manejo de eventos
void execute_code(GtkButton *button, gpointer user_data);
void on_execute_clicked(GtkButton *button, gpointer user_data);

// AGREGAR: Funciones faltantes que usas en gui.c
void on_run_clicked(GtkButton *button, gpointer user_data);
void on_symbols_clicked(GtkButton *button, gpointer user_data);
void on_ast_clicked(GtkButton *button, gpointer user_data);

// Funciones para enviar información a la GUI
void send_token_to_gui(const char* token_type, const char* token_value);
void update_ast_treeview(ast_node *ast_root);
void append_to_console(const char *text);
void clear_console(void);

// Funciones para reportes
void show_symbol_table_report(GtkButton *button, gpointer user_data);
void show_ast_graphviz(GtkButton *button, gpointer user_data);
int generate_ast_dot(ast_node *root, const char *filename);
void generate_ast_dot_node(FILE *file, ast_node *node, int *node_id, int parent_id);
const char* get_op_string(int op);
void show_error_report_gui(GtkButton *button, gpointer user_data);
void analyze_lexical_errors(const char *code);
int analyze_code_for_semantic_errors(const char *code);
void show_image_in_app(const char *image_path);
void update_errors_view(void);


// Variables globales de buffers
extern GtkTextBuffer *console_buffer;
extern GtkTextBuffer *source_buffer;

#endif