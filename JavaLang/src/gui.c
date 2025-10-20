#include "../include/gui.h"
#include "../include/parser.h"
#include "../include/lexer_utils.h"
#include "../include/ast.h"
#include "../include/semantic.h"
#include "../include/runtime.h"
#include "../include/errores.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>      
#include <unistd.h>     
#include <stdarg.h>
#include <glib.h>      // Para g_utf8_make_valid

// Variable global para los widgets
static AppWidgets *widgets = NULL;
static int execution_in_progress = 0; // <- guard para evitar reentradas


// Declaraciones de funciones del parser
extern int parse_from_string(const char *input);
extern ast_node* get_ast_root(void);
extern void cleanup_parser(void);
extern void execute_program(ast_node *root); 
extern void setup_lexer_for_string(const char *input);
extern int yyparse(void);
extern void yyrestart(FILE *input_file);
extern ast_node *root;
extern int input_len;  // Para debugging
int analyze_code_for_semantic_errors(const char *code);



// Variables globales para buffers (para compatibilidad)
GtkTextBuffer *console_buffer = NULL;
GtkTextBuffer *source_buffer = NULL;


// =================== FUNCIONES BÁSICAS DE GUI ===================
// Función para agregar texto a la consola
void append_to_console(const char *text) {
    if (console_buffer) {
        GtkTextIter end;
        gtk_text_buffer_get_end_iter(console_buffer, &end);
        // Asegurar la cadena es UTF-8 válida para evitar Gtk-CRITICAL
        gchar *safe = g_utf8_make_valid(text, -1);
        gtk_text_buffer_insert(console_buffer, &end, safe, -1);
        g_free(safe);       
        //desplazar al final
        GtkTextMark *mark = gtk_text_buffer_create_mark(console_buffer, NULL, &end, FALSE);
        GtkTextView *tv = GTK_TEXT_VIEW(widgets->console_view);
        gtk_text_view_scroll_to_mark(tv, mark, 0.0, FALSE, 0.0, 1.0);
        gtk_text_buffer_delete_mark(console_buffer, mark);
    } else {
        // Fallback a stdout para debugging
        printf("%s", text);
    }
}

// ------------------ Thread-safe console appender ------------------
typedef struct { char *text; } IdleMsg;
static gboolean append_idle_cb(gpointer data) {
    IdleMsg *m = (IdleMsg*)data;
    if (m && m->text) {
        append_to_console(m->text);
        g_free(m->text);
    }
    g_free(m);
    return G_SOURCE_REMOVE;
}

void append_to_console_threadsafe(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    char *buf = g_strdup_vprintf(fmt, ap);
    va_end(ap);
    if (!buf) return;
    IdleMsg *m = g_malloc(sizeof(IdleMsg));
    m->text = buf;
    g_idle_add(append_idle_cb, m);
}

static void console_adapter(const char *msg) {
    if (!msg) return;
    append_to_console_threadsafe("%s", msg);
}

// Función para limpiar la consola
void clear_console(void) {
    if (widgets && widgets->console_buffer) {
        gtk_text_buffer_set_text(widgets->console_buffer, "", -1);
    }
}



// =================== FUNCIONES DE ARCHIVO ===================
// Agregar esta función después de clear_console()
void open_file_dialog(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Abrir archivo .usl",
                                        GTK_WINDOW(widgets->window),
                                        action,
                                        "_Cancelar",
                                        GTK_RESPONSE_CANCEL,
                                        "_Abrir",
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);

    // Filtro para archivos .usl
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Archivos USL (*.usl)");
    gtk_file_filter_add_pattern(filter, "*.usl");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    // Filtro para todos los archivos
    GtkFileFilter *filter_all = gtk_file_filter_new();
    gtk_file_filter_set_name(filter_all, "Todos los archivos");
    gtk_file_filter_add_pattern(filter_all, "*");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter_all);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        
        // Leer el archivo
        FILE *file = fopen(filename, "r");
        if (file) {
            // Obtener tamaño del archivo
            fseek(file, 0, SEEK_END);
            long file_size = ftell(file);
            fseek(file, 0, SEEK_SET);
            
            // Leer contenido
            char *content = malloc(file_size + 1);
            fread(content, 1, file_size, file);
            content[file_size] = '\0';
            fclose(file);
            
            // Cargar en el editor
            gtk_text_buffer_set_text(widgets->source_buffer, content, -1);
            
            // Mostrar mensaje
            char message[512];
            snprintf(message, sizeof(message), "📁 Archivo cargado: %s\n", filename);
            clear_console();
            append_to_console(message);
            
            free(content);
        } else {
            append_to_console("❌ Error al abrir el archivo\n");
        }
        
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

// Función para guardar archivo
void save_file_dialog(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Guardar archivo .usl",
                                        GTK_WINDOW(widgets->window),
                                        action,
                                        "_Cancelar",
                                        GTK_RESPONSE_CANCEL,
                                        "_Guardar",
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);

    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);

    // Filtro para archivos .usl
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "Archivos USL (*.usl)");
    gtk_file_filter_add_pattern(filter, "*.usl");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        
        // Obtener contenido del editor
        GtkTextIter start, end;
        gtk_text_buffer_get_start_iter(widgets->source_buffer, &start);
        gtk_text_buffer_get_end_iter(widgets->source_buffer, &end);
        gchar *content = gtk_text_buffer_get_text(widgets->source_buffer, &start, &end, FALSE);
        
        // Guardar archivo
        FILE *file = fopen(filename, "w");
        if (file) {
            fprintf(file, "%s", content);
            fclose(file);
            
            char message[512];
            snprintf(message, sizeof(message), "💾 Archivo guardado: %s\n", filename);
            append_to_console(message);
        } else {
            append_to_console("❌ Error al guardar el archivo\n");
        }
        
        g_free(content);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}


// =================== FUNCION DE EJECUCCION ===================
// Función principal para ejecutar código

// helper que re-habilita UI desde el hilo principal
static gboolean finish_ui_update(gpointer user_data) {
    if (widgets && widgets->execute_button) {
        gtk_widget_set_sensitive(GTK_WIDGET(widgets->execute_button), TRUE);
    }
    execution_in_progress = 0;
    return G_SOURCE_REMOVE;
}

static gpointer execute_worker(gpointer data) {
    // 'data' es gchar* sanitized (heap), se liberará aquí
    gchar *sanitized = (gchar*)data;

    append_to_console_threadsafe("🚀 Iniciando ejecución...\n");
    init_error_system();

    // FASE 1: léxico
    analyze_lexical_errors(sanitized);

    // FASE 2: parse
    setup_lexer_for_string(sanitized);
    yyrestart(NULL);
    int parse_result = yyparse();

    if (parse_result != 0) {
        append_to_console_threadsafe("❌ Errores sintácticos encontrados\n");
        int sem_count = analyze_code_for_semantic_errors(sanitized);
        if (sem_count > 0) append_to_console_threadsafe("❌ Errores semánticos detectados\n");
        else append_to_console_threadsafe("✅ Análisis semántico básico: sin errores aparentes\n");
    } else {
        append_to_console_threadsafe("✅ Análisis sintáctico: EXITOSO\n");
        ast_node *ast_root = get_ast_root();
        if (ast_root) {
            semantic_analysis(ast_root);
            append_to_console_threadsafe("🔍 Ejecutando programa...\n");
            // --- INICIAR ARM64 .s AQUÍ ---
            system("mkdir -p reports");
            runtime_codegen_start("reports/out_arm64.s");

            execute_program(ast_root);
             // --- CERRAR ARM64 .s AQUÍ ---
            runtime_codegen_finish();
            append_to_console_threadsafe("✅ Código ARM64 generado: reports/out_arm64.s\n");
        } else {
            append_to_console_threadsafe("⚠️ No hay AST disponible para ejecución\n");
        }
    }

    append_to_console_threadsafe("✅ Análisis completado\n");

    // liberar y reactivar UI en hilo principal
    g_idle_add(finish_ui_update, NULL);
    g_free(sanitized);
    return NULL;
}

void execute_code(GtkButton *button, gpointer user_data) {
    if (execution_in_progress) {
        append_to_console("⚠️ Ejecución ya en progreso\n");
        return;
    }
    execution_in_progress = 1;

    if (widgets && widgets->execute_button) {
        gtk_widget_set_sensitive(GTK_WIDGET(widgets->execute_button), FALSE);
    }

    // Obtener el código del área de texto (hacer esto en hilo principal)
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets->source_view));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gchar *code = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    gchar *sanitized = g_utf8_make_valid(code, -1);
    g_free(code);

    // Lanzar hilo que hará el trabajo pesado. el worker liberará 'sanitized'
    GThread *t = g_thread_new("javalang-worker", execute_worker, sanitized);
    g_thread_unref(t);
}

// =================== FUNCIONES DE REPORTE ===================
char* generate_symbols_html(void) {
    const size_t CAP = 65536;
    char *html_content = malloc(CAP);
    if (!html_content) return NULL;
    size_t off = 0;
    html_content[0] = '\0';

    off += snprintf(html_content + off, CAP - off,
        "<!DOCTYPE html>"
        "<html><head>"
        "<meta charset='UTF-8'>"
        "<title>Tabla de Símbolos</title>"
        "<style>"
        "body { font-family: 'Segoe UI', Arial, sans-serif; margin: 20px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); min-height: 100vh; }"
        ".container { background: white; border-radius: 10px; padding: 20px; box-shadow: 0 10px 25px rgba(0,0,0,0.2); }"
        "h1 { color: #2c3e50; text-align: center; margin-bottom: 30px; font-size: 2.5em; }"
        "table { width: 100%; border-collapse: collapse; margin: 20px 0; }"
        "th { background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; padding: 15px; text-align: left; font-weight: bold; }"
        "td { padding: 12px 15px; border-bottom: 1px solid #e0e0e0; }"
        "tr:nth-child(even) { background: #f8f9fa; }"
        "tr:hover { background: #e3f2fd; transform: scale(1.02); transition: all 0.3s ease; }"
        ".symbol-name { font-weight: bold; color: #2c3e50; }"
        ".symbol-type { color: #27ae60; font-weight: bold; }"
        ".symbol-scope { color: #8e44ad; }"
        ".empty { text-align: center; color: #7f8c8d; font-style: italic; padding: 50px; font-size: 1.2em; }"
        ".stats { display: flex; justify-content: space-around; margin: 20px 0; }"
        ".stat { text-align: center; padding: 15px; background: #ecf0f1; border-radius: 8px; }"
        ".stat-number { font-size: 2em; font-weight: bold; color: #3498db; }"
        ".stat-label { color: #7f8c8d; }"
        "</style>"
        "</head><body>"
        "<div class='container'>"
        "<h1>📊 Tabla de Símbolos - JavaLang</h1>");

    if (!global_symbol_table || !global_symbol_table->symbols) {
        off += snprintf(html_content + off, CAP - off,
            "<div class='empty'>"
            "❌ No hay símbolos disponibles<br>"
            "💡 Ejecute un análisis sintáctico primero"
            "</div>");
    } else {
        int total_symbols = 0;
        symbol_t *current = global_symbol_table->symbols;
        while (current) { total_symbols++; current = current->next; }

        off += snprintf(html_content + off, CAP - off,
            "<div class='stats'><div class='stat'><div class='stat-number'>%d</div><div class='stat-label'>Total Símbolos</div></div></div>",
            total_symbols);

        off += snprintf(html_content + off, CAP - off,
            "<table><thead><tr><th>🏷️ Nombre</th><th>🔧 Tipo</th><th>📂 Ámbito</th><th>📍 Línea</th></tr></thead><tbody>");

        current = global_symbol_table->symbols;
        while (current && off + 256 < CAP) {
            const char *name = current->name ? current->name : "?";
            const char *type_str = type_to_string(current->type);
            const char *scope = current->scope_name ? current->scope_name : "global";
            off += snprintf(html_content + off, CAP - off,
                "<tr><td class='symbol-name'>%s</td><td class='symbol-type'>%s</td><td class='symbol-scope'>%s</td><td>%d</td></tr>",
                name, type_str, scope, current->line);
            current = current->next;
        }

        off += snprintf(html_content + off, CAP - off, "</tbody></table>");
    }

    off += snprintf(html_content + off, CAP - off, "</div></body></html>");

    return html_content;
}



//Generar PNG de la tabla de símbolos
void generate_symbols_png(GtkButton *button, gpointer user_data) {
    append_to_console("\n=== GENERANDO PNG DE TABLA DE SÍMBOLOS ===\n");
    
    // Generar HTML
    char *html_content = generate_symbols_html();
    
    // ⭐ CAMBIAR RUTA: usar carpeta reports/ en lugar de /tmp/
    system("mkdir -p reports"); // Crear carpeta si no existe
    
    const char *html_file = "reports/symbols_table.html";  // ⭐ NUEVA RUTA
    const char *png_file = "reports/symbols_table.png";    // ⭐ NUEVA RUTA
    
    FILE *file = fopen(html_file, "w");
    if (!file) {
        append_to_console("❌ Error al crear archivo HTML en reports/\n");
        return;
    }
    
    fprintf(file, "%s", html_content);
    fclose(file);
    
    append_to_console("✅ Archivo HTML creado: reports/symbols_table.html\n");
    
    // Generar PNG usando múltiples métodos
    char command[1024];
    int result = -1;
    
    // ⭐ MÉTODO 1: wkhtmltoimage
    append_to_console("🔄 Generando PNG con wkhtmltoimage...\n");
    snprintf(command, sizeof(command), 
             "wkhtmltoimage --width 1200 --height 800 --quality 100 "
             "--enable-local-file-access %s %s 2>/dev/null", 
             html_file, png_file);
    result = system(command);
    
    // ⭐ MÉTODO 2: Firefox headless (si wkhtml falla)
    if (result != 0) {
        append_to_console("🔄 Intentando con Firefox headless...\n");
        char full_path[512];  // ⭐ AGREGAR ESTA LÍNEA ANTES DE getcwd()
        getcwd(full_path, sizeof(full_path));
        snprintf(command, sizeof(command), 
                 "timeout 10s firefox --headless --window-size=1200,800 "
                 "--screenshot=%s file://%s/%s 2>/dev/null", 
                 png_file, full_path, html_file);
        result = system(command);
        
        // ⭐ TAMBIÉN CORREGIR LA LÍNEA 456 (aproximadamente)
        // CAMBIAR:
        // char browser_cmd[512];
        // getcwd(full_path, sizeof(full_path));
        
        // POR:
        if (access(png_file, F_OK) != 0) {
            char browser_cmd[512];
            char full_path2[512];  // ⭐ NUEVA VARIABLE LOCAL
            getcwd(full_path2, sizeof(full_path2));
            snprintf(browser_cmd, sizeof(browser_cmd), "xdg-open file://%s/%s", full_path2, html_file);
            system(browser_cmd);
        }
    }

    // ⭐ VERIFICAR RESULTADO
    if (access(png_file, F_OK) == 0) {
        append_to_console("✅ PNG generado exitosamente: reports/symbols_table.png\n");
        
        // ⭐ MOSTRAR EN LA PESTAÑA DE IMAGEN TAMBIÉN
        show_image_in_app(png_file);
        
        append_to_console("🖼️ Imagen mostrada en pestaña 'Imagen'\n");
    } else {
        append_to_console("❌ Error al generar PNG\n");
        append_to_console("💡 Instala wkhtmltopdf: sudo apt-get install wkhtmltopdf\n");
        
        // Abrir HTML en navegador como alternativa
        char browser_cmd[512];  // ⭐ AGREGAR ESTA LÍNEA
        char full_path[512];
        getcwd(full_path, sizeof(full_path));
        snprintf(browser_cmd, sizeof(browser_cmd), "xdg-open file://%s/%s", full_path, html_file);
        system(browser_cmd);
        append_to_console("🌐 HTML abierto en navegador\n");
    }
}

// REEMPLAZAR toda la función show_symbol_table_report (líneas ~448-550):

// ...existing code...
void show_symbol_table_report(GtkButton *button, gpointer user_data) {
    append_to_console("\n=== GENERANDO REPORTE DE SÍMBOLOS ===\n");
    if (!widgets || !widgets->symbols_view) {
        append_to_console("❌ Vista de símbolos no disponible\n");
        return;
    }

    GtkTextBuffer *symbols_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets->symbols_view));
    gtk_text_buffer_set_text(symbols_buffer, "", -1);

    if (!global_symbol_table || !global_symbol_table->symbols) {
        const char *no_symbols_msg =
            "═══════════════════════════════════════════════════════\n"
            "           📊 TABLA DE SÍMBOLOS - JAVALANG\n"
            "═══════════════════════════════════════════════════════\n\n"
            "❌ NO HAY SÍMBOLOS DISPONIBLES\n\n"
            "💡 POSIBLES CAUSAS:\n"
            "   • No se ha ejecutado un análisis sintáctico\n"
            "   • El código tiene errores sintácticos críticos\n"
            "   • No hay declaraciones de variables\n\n"
            "🔧 SUGERENCIAS:\n"
            "   1. Presione '▶️ Ejecutar' primero\n"
            "   2. Verifique que el código tenga declaraciones\n"
            "   3. Corrija errores sintácticos si los hay\n\n"
            "═══════════════════════════════════════════════════════\n"
            "JavaLang Interpreter v1.0\n"
            "═══════════════════════════════════════════════════════";
        gtk_text_buffer_set_text(symbols_buffer, no_symbols_msg, -1);
        append_to_console("⚠️ No hay símbolos para mostrar\n");
    } else {
        // Usar buffer grande y seguro
        size_t CAP = 65536;
        char *symbols_report = malloc(CAP);
        if (!symbols_report) { append_to_console("❌ Error de memoria\n"); return; }
        size_t off = 0;
        symbols_report[0] = '\0';

        off += snprintf(symbols_report + off, CAP - off,
            "═══════════════════════════════════════════════════════\n"
            "           📊 TABLA DE SÍMBOLOS - JAVALANG\n"
            "═══════════════════════════════════════════════════════\n\n");

        // Contar símbolos
        int total_symbols = 0;
        symbol_t *current = global_symbol_table->symbols;
        while (current) { total_symbols++; current = current->next; }

        char scope_info[64];
        switch (global_symbol_table->scope_level) {
            case 0: strcpy(scope_info, "Global"); break;
            case 1: strcpy(scope_info, "Función"); break;
            case 2: strcpy(scope_info, "Bloque"); break;
            default: snprintf(scope_info, sizeof(scope_info), "Nivel %d", global_symbol_table->scope_level); break;
        }

        off += snprintf(symbols_report + off, CAP - off,
            "📊 ESTADÍSTICAS:\n   • Total de símbolos: %d\n   • Ámbito principal: %s (Nivel %d)\n\n",
            total_symbols, scope_info, global_symbol_table->scope_level);

        off += snprintf(symbols_report + off, CAP - off,
            "📋 DETALLE DE SÍMBOLOS:\n───────────────────────────────────────────────────────\n"
            "No. | Nombre      | Tipo        | Ámbito     | Línea\n"
            "────┼─────────────┼─────────────┼────────────┼──────\n");

        current = global_symbol_table->symbols;
        int count = 1;
        while (current && off + 128 < CAP) {
            off += snprintf(symbols_report + off, CAP - off,
                "%2d  | %-11s | %-11s | %-10s | %d\n",
                count,
                current->name ? current->name : "?",
                type_to_string(current->type),
                current->scope_name ? current->scope_name : "global",
                current->line);
            current = current->next;
            count++;
        }

        off += snprintf(symbols_report + off, CAP - off,
            "───────────────────────────────────────────────────────\n\n"
            "💡 INFORMACIÓN:\n"
            "   • Los símbolos se muestran en orden de declaración\n"
            "   • Tipos soportados: int, float, double, String, char, boolean\n"
            "   • Ámbito indica dónde fue declarada la variable\n\n"
            "═══════════════════════════════════════════════════════\n"
            "Generado automáticamente por JavaLang Interpreter v1.0\n"
            "═══════════════════════════════════════════════════════");

        gtk_text_buffer_set_text(symbols_buffer, symbols_report, -1);
        free(symbols_report);
        append_to_console("✅ Tabla de símbolos actualizada\n");
    }

    // Generar archivos en reports/ (mantener comportamiento previo)
    append_to_console("📁 Generando archivos en carpeta 'reports/'...\n");
    system("mkdir -p reports");

    char *html_content = generate_symbols_html();
    const char *html_path = "reports/symbols_table.html";
    if (html_content) {
        FILE *html_file = fopen(html_path, "w");
        if (html_file) { fprintf(html_file, "%s", html_content); fclose(html_file); append_to_console("✅ HTML generado: reports/symbols_table.html\n"); }
        free(html_content);
    }

    
    // ⭐ GENERAR TXT
    const char *txt_path = "reports/symbols_report.txt";
    FILE *txt_file = fopen(txt_path, "w");
    if (txt_file) {
        fprintf(txt_file, "=======================================================\n");
        fprintf(txt_file, "         REPORTE DE SÍMBOLOS - JAVALANG\n");
        fprintf(txt_file, "=======================================================\n\n");
        
        if (!global_symbol_table || !global_symbol_table->symbols) {
            fprintf(txt_file, "❌ No hay símbolos disponibles\n");
            fprintf(txt_file, "💡 Ejecute un análisis primero\n\n");
        } else {
            // Contar símbolos
            int total_symbols = 0;
            symbol_t *current = global_symbol_table->symbols;
            while (current) {
                total_symbols++;
                current = current->next;
            }
            
            fprintf(txt_file, "📊 ESTADÍSTICAS:\n");
            fprintf(txt_file, "   Total de símbolos: %d\n\n", total_symbols);
            
            fprintf(txt_file, "📋 DETALLE DE SÍMBOLOS:\n");
            fprintf(txt_file, "-------------------------------------------------------\n");
            
            current = global_symbol_table->symbols;
            int count = 1;
            while (current) {
                fprintf(txt_file, "%d. SÍMBOLO: %s\n", count,
                       current->name ? current->name : "?");
                fprintf(txt_file, "   Tipo: %s\n", type_to_string(current->type));
                fprintf(txt_file, "   Ámbito: %s\n", 
                       current->scope_name ? current->scope_name : "global");
                fprintf(txt_file, "   Línea: %d\n\n", current->line);
                
                current = current->next;
                count++;
            }
        }
        
        fprintf(txt_file, "=======================================================\n");
        fprintf(txt_file, "Generado el: %s\n", __DATE__);
        fprintf(txt_file, "JavaLang Interpreter v1.0\n");
        fprintf(txt_file, "=======================================================\n");
        
        fclose(txt_file);
        append_to_console("✅ TXT generado: reports/symbols_report.txt\n");
    }
    
    // ⭐ GENERAR PNG
    const char *png_path = "reports/symbols_table.png";
    append_to_console("🖼️ Generando PNG...\n");
    
    char screenshot_cmd[1024];
    char full_path[512];
    getcwd(full_path, sizeof(full_path));
    
    // Intentar generar PNG con Firefox
    snprintf(screenshot_cmd, sizeof(screenshot_cmd), 
             "timeout 10s firefox --headless --window-size=1200,800 "
             "--screenshot=%s file://%s/%s 2>/dev/null", 
             png_path, full_path, html_path);
    
    system(screenshot_cmd);
    sleep(1); // Esperar procesamiento
    
    if (access(png_path, F_OK) == 0) {
        append_to_console("✅ PNG generado: reports/symbols_table.png\n");
        
        // ⭐ MOSTRAR EN LA PESTAÑA DE IMAGEN
        show_image_in_app(png_path);
        
        append_to_console("🖼️ Imagen mostrada en pestaña 'Imagen'\n");
    } else {
        append_to_console("⚠️ PNG no generado automáticamente\n");
        append_to_console("💡 Comando manual: firefox --headless --screenshot=reports/symbols_table.png file://$(pwd)/reports/symbols_table.html\n");
    }
    
    // ⭐ CAMBIAR AUTOMÁTICAMENTE A LA PESTAÑA DE SÍMBOLOS
    gtk_notebook_set_current_page(GTK_NOTEBOOK(widgets->notebook), 1); // Símbolos
    
    // ⭐ MOSTRAR RESUMEN FINAL
    append_to_console("\n📊 Archivos de símbolos generados:\n");
    append_to_console("   📄 HTML: reports/symbols_table.html\n");
    append_to_console("   📝 TXT:  reports/symbols_report.txt\n");
    append_to_console("   🖼️ PNG:  reports/symbols_table.png\n");
    append_to_console("   📊 Vista actualizada en pestaña 'Símbolos'\n");
}

void show_ast_graphviz(GtkButton *button, gpointer user_data) {
    // clear_console();
    append_to_console("=== GENERANDO AST CON GRAPHVIZ ===\n\n");
    
    ast_node *root = get_ast_root();
    if (!root) {
        append_to_console("❌ No hay AST disponible\n");
        append_to_console("💡 Primero ejecuta un análisis para generar el AST\n");
        return;
    }
    
    // Generar archivo .dot
    const char *dot_file = "/tmp/ast.dot";
    const char *png_file = "/tmp/ast.png";
    
    if (generate_ast_dot(root, dot_file)) {
        append_to_console("✅ Archivo .dot generado: /tmp/ast.dot\n");
        
        // Ejecutar Graphviz para generar imagen
        char command[512];
        snprintf(command, sizeof(command), "dot -Tpng %s -o %s", dot_file, png_file);
        
        append_to_console("🔄 Ejecutando Graphviz...\n");
        int result = system(command);
        
        if (result == 0) {
            append_to_console("✅ Imagen AST generada: /tmp/ast.png\n");
            
            // Mostrar imagen en visor predeterminado
            snprintf(command, sizeof(command), "xdg-open %s", png_file);
            system(command);
            
            append_to_console("🖼️ Imagen abierta en visor predeterminado\n");
        } else {
            append_to_console("❌ Error al ejecutar Graphviz\n");
            append_to_console("💡 Instala Graphviz: sudo apt-get install graphviz\n");
        }
    } else {
        append_to_console("❌ Error al generar archivo .dot\n");
    }
}


// =================== FUNCIONES PARA GRAPHVIZ ===================
int generate_ast_dot(ast_node *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        return 0;
    }
    
    fprintf(file, "digraph AST {\n");
    fprintf(file, "    node [shape=box, style=filled, fillcolor=lightblue];\n");
    fprintf(file, "    edge [color=darkblue];\n\n");
    
    int node_id = 0;
    generate_ast_dot_node(file, root, &node_id, -1);
    
    fprintf(file, "}\n");
    fclose(file);
    
    return 1;
}

// función generate_ast_dot_node()
void generate_ast_dot_node(FILE *file, ast_node *node, int *node_id, int parent_id) {
    if (!node) return;
    
    int current_id = (*node_id)++;
    
    switch (node->type) {
        case AST_DECLARATION:
            fprintf(file, "    n%d [label=\"%s\", fillcolor=lightblue];\n", 
            current_id, 
            node->data.declaration.var_name ? node->data.declaration.var_name : "?");
    break;
            
        case AST_ASSIGNMENT:
            fprintf(file, "    n%d [label=\"%s\"];\n", 
                   current_id, 
                   node->data.assignment.var_name ? node->data.assignment.var_name : "?");
            break;

        case AST_INT_LITERAL:
            fprintf(file, "    n%d [label=\"%d\", fillcolor=lightgreen];\n", 
                   current_id, node->data.int_value);
            break;
            
        case AST_FLOAT_LITERAL:
            fprintf(file, "    n%d [label=\"%.2f\", fillcolor=lightgreen];\n", 
                   current_id, node->data.float_value);
            break;
            
        case AST_DOUBLE_LITERAL:
            fprintf(file, "    n%d [label=\"%.2lf\", fillcolor=lightgreen];\n", 
                   current_id, node->data.double_value);
            break;

        case AST_STRING_LITERAL:
            fprintf(file, "    n%d [label=\"%s\", fillcolor=lightgreen];\n", 
                   current_id, node->data.string_value ? node->data.string_value : "");
            break;
            
        case AST_CHAR_LITERAL:
            fprintf(file, "    n%d [label=\"%c\", fillcolor=lightgreen];\n", 
                   current_id, node->data.char_value);
            break;
            
        case AST_BOOL_LITERAL:
            fprintf(file, "    n%d [label=\"%s\", fillcolor=lightgreen];\n", 
                   current_id, node->data.int_value ? "true" : "false");
            break;
            
        case AST_NULL_LITERAL:
            fprintf(file, "    n%d [label=\"NULL\", fillcolor=lightgray];\n", current_id);
            break;
            
        case AST_VARIABLE:
            fprintf(file, "    n%d [label=\"%s\", fillcolor=lightyellow];\n", 
                   current_id, node->data.var_name ? node->data.var_name : "?");
            break;
            
        case AST_TYPE:
            fprintf(file, "    n%d [label=\"%s\", fillcolor=lightcyan];\n", 
                   current_id, node->data.type_name ? node->data.type_name : "?");
            break;
            
        case AST_BINARY_OP:
            fprintf(file, "    n%d [label=\"%s\", fillcolor=orange];\n", 
                   current_id, get_op_string(node->data.op.op));
            break;
            
        case AST_UNARY_OP:
            // CORREGIR: usar 'op' en lugar de 'unary_op'
            fprintf(file, "    n%d [label=\"%s\", fillcolor=orange];\n", 
                   current_id, get_op_string(node->data.op.op));
            break;
            
        case AST_IF:
            fprintf(file, "    n%d [label=\"IF\", fillcolor=pink];\n", current_id);
            break;
            
        case AST_WHILE:
            fprintf(file, "    n%d [label=\"WHILE\", fillcolor=pink];\n", current_id);
            break;
            
        case AST_DO_WHILE:
            fprintf(file, "    n%d [label=\"DO-WHILE\", fillcolor=pink];\n", current_id);
            break;
            
        case AST_FOR:
            fprintf(file, "    n%d [label=\"FOR\", fillcolor=pink];\n", current_id);
            break;
            
        case AST_RETURN:
            fprintf(file, "    n%d [label=\"RETURN\", fillcolor=lightpink];\n", current_id);
            break;
            
        case AST_BREAK:
            fprintf(file, "    n%d [label=\"BREAK\", fillcolor=lightpink];\n", current_id);
            break;
            
        case AST_CONTINUE:
            fprintf(file, "    n%d [label=\"CONTINUE\", fillcolor=lightpink];\n", current_id);
            break;
            
        case AST_COMPOUND_STMT:
            fprintf(file, "    n%d [label=\"BLOQUE\"];\n", current_id);
            break;
            
        case AST_PROGRAM:
            fprintf(file, "    n%d [label=\"PROGRAMA\", fillcolor=lightblue];\n", current_id);
            break;

        case AST_PRINT_STMT:
            fprintf(file, "    n%d [label=\"println\", fillcolor=lightcoral];\n", current_id);
            break;

        case AST_STRING_EQUALS:
            fprintf(file, "    n%d [label=\".equals()\", fillcolor=lightcoral];\n", current_id);
            break;

        case AST_MAIN_FUNCTION:
            fprintf(file, "    n%d [label=\"%s\", fillcolor=lightcyan, style=filled];\n", 
                   current_id, 
                   node->data.function_def.name ? node->data.function_def.name : "main");
            break;

        case AST_ARRAY_DECLARATION:
            fprintf(file, "    n%d [label=\"ARRAY: %s[%d]\", fillcolor=lightblue, shape=box];\n", 
                current_id, 
                node->data.array_decl.array_name ? node->data.array_decl.array_name : "array",
                node->data.array_decl.size ? node->data.array_decl.size->data.int_value : 0);
            break;

        case AST_ARRAY_ACCESS:
            fprintf(file, "    n%d [label=\"ACCESS: %s[]\", fillcolor=lightyellow, shape=ellipse];\n", 
                current_id, 
                node->data.array_access.array_name ? node->data.array_access.array_name : "array");
            break;

        case AST_ARRAY_INIT:
            fprintf(file, "    n%d [label=\"INIT: { ... }\", fillcolor=lightgreen, shape=diamond];\n", current_id);
            break;

        case AST_ARRAY_ASSIGNMENT:
            fprintf(file, "    n%d [label=\"ARRAY_ASSIGN: %s[]\", fillcolor=orange, shape=box];\n", 
                current_id,
                node->data.array_assignment.array_name ? node->data.array_assignment.array_name : "array");
            break;
            
        
        default:
            fprintf(file, "    n%d [label=\"NODO\\n%d\"];\n", current_id, node->type);
            break;
    }
    
    // Conectar con el padre
    if (parent_id >= 0) {
        fprintf(file, "    n%d -> n%d;\n", parent_id, current_id);
    }
    
    // Generar hijos según el tipo
    switch (node->type) {
        case AST_DECLARATION:
            if (node->data.declaration.var_type) {
                generate_ast_dot_node(file, node->data.declaration.var_type, node_id, current_id);
            }
            if (node->data.declaration.value) {
                generate_ast_dot_node(file, node->data.declaration.value, node_id, current_id);
            }
            break;
            
        case AST_ASSIGNMENT:
            if (node->data.assignment.value) {
                generate_ast_dot_node(file, node->data.assignment.value, node_id, current_id);
            }
            break;
            
        case AST_BINARY_OP:
            if (node->data.op.left) {
                generate_ast_dot_node(file, node->data.op.left, node_id, current_id);
            }
            if (node->data.op.right) {
                generate_ast_dot_node(file, node->data.op.right, node_id, current_id);
            }
            break;
            
        case AST_UNARY_OP:
            // CORREGIR: usar 'op.left' en lugar de 'unary_op.operand'
            if (node->data.op.left) {
                generate_ast_dot_node(file, node->data.op.left, node_id, current_id);
            }
            break;
            
        case AST_IF:
            if (node->data.if_stmt.condition) {
                generate_ast_dot_node(file, node->data.if_stmt.condition, node_id, current_id);
            }
            if (node->data.if_stmt.then_branch) {
                generate_ast_dot_node(file, node->data.if_stmt.then_branch, node_id, current_id);
            }
            if (node->data.if_stmt.else_branch) {
                generate_ast_dot_node(file, node->data.if_stmt.else_branch, node_id, current_id);
            }
            break;
            
        case AST_WHILE:
            if (node->data.while_stmt.condition) {
                generate_ast_dot_node(file, node->data.while_stmt.condition, node_id, current_id);
            }
            if (node->data.while_stmt.body) {
                generate_ast_dot_node(file, node->data.while_stmt.body, node_id, current_id);
            }
            break;
            
        case AST_COMPOUND_STMT:
            if (node->data.compound.statement_list) {
                generate_ast_dot_node(file, node->data.compound.statement_list, node_id, current_id);
            }
            break;

        case AST_PRINT_STMT:
            if (node->data.print_stmt.expression) {
                generate_ast_dot_node(file, node->data.print_stmt.expression, node_id, current_id);
            }
            break;

        case AST_STRING_EQUALS:
            if (node->data.string_equals.left_string) {
                generate_ast_dot_node(file, node->data.string_equals.left_string, node_id, current_id);
            }
            if (node->data.string_equals.right_expr) {
                generate_ast_dot_node(file, node->data.string_equals.right_expr, node_id, current_id);
            }
            break;

        case AST_MAIN_FUNCTION:
            if (node->data.function_def.body) {
                generate_ast_dot_node(file, node->data.function_def.body, node_id, current_id);
            }
            break;

        case AST_ARRAY_DECLARATION:
            // Conectar tipo del elemento
            if (node->data.array_decl.element_type) {
                generate_ast_dot_node(file, node->data.array_decl.element_type, node_id, current_id);
            }
            // Conectar tamaño
            if (node->data.array_decl.size) {
                generate_ast_dot_node(file, node->data.array_decl.size, node_id, current_id);
            }
            // Conectar inicialización
            if (node->data.array_decl.init_values) {
                generate_ast_dot_node(file, node->data.array_decl.init_values, node_id, current_id);
            }
            break;

        case AST_ARRAY_ACCESS:
            // Conectar índice
            if (node->data.array_access.index) {
                generate_ast_dot_node(file, node->data.array_access.index, node_id, current_id);
            }
            break;

        case AST_ARRAY_INIT:
            // Conectar lista de valores iniciales
            if (node->data.array_decl.init_values) {
                generate_ast_dot_node(file, node->data.array_decl.init_values, node_id, current_id);
            }
            break;
            
        case AST_ARRAY_ASSIGNMENT:
            // Conectar índice
            if (node->data.array_assignment.index) {
                generate_ast_dot_node(file, node->data.array_assignment.index, node_id, current_id);
            }
            // Conectar valor
            if (node->data.array_assignment.value) {
                generate_ast_dot_node(file, node->data.array_assignment.value, node_id, current_id);
            }
            break;
            
            
        default:
            // No hijos específicos
            break;
    }
    
    // Procesar siguiente nodo
    if (node->next) {
        generate_ast_dot_node(file, node->next, node_id, parent_id);
    }
}



const char* get_op_string(int op) {
    switch (op) {
        // Operadores aritméticos
        case OP_PLUS: return "+";
        case OP_MINUS: return "-";
        case OP_MULT: return "*";
        case OP_DIV: return "/";
        case OP_MOD: return "%";        
        
        // Operadores de comparación
        case OP_EQUALS: return "==";
        case OP_NOT_EQUALS: return "!=";
        case OP_LESS: return "<";
        case OP_GREATER: return ">";
        case OP_LESS_EQUALS: return "<="; // AGREGAR
        case OP_GREATER_EQUALS: return ">="; // AGREGAR
        
        // Operadores lógicos
        case OP_AND: return "&&";
        case OP_OR: return "||";
        case OP_NOT: return "!";          // AGREGAR
        
        // Operadores unarios
        case OP_UMINUS: return "-";       // AGREGAR: unario negativo
        case OP_INCREMENT: return "++";   // AGREGAR: ++x
        case OP_POST_INCREMENT: return "++"; // AGREGAR: x++
        case OP_DECREMENT: return "--";   // AGREGAR: --x
        case OP_POST_DECREMENT: return "--"; // AGREGAR: x--
        
        default: return "?";
    }
}

// =================== CONSTRUCCIÓN DE GUI ===================
// Función para construir la interfaz gráfica
void build_gui(void) {
    gtk_container_set_border_width(GTK_CONTAINER(widgets->window), 10);
    
    // Conectar señal de cierre
    g_signal_connect(widgets->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Crear layout principal (horizontal)
    GtkWidget *main_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(widgets->window), main_hbox);
    
    // === PANEL IZQUIERDO (Código fuente) ===
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_hbox), left_vbox, TRUE, TRUE, 0);
    
    // Etiqueta para código fuente
    GtkWidget *source_label = gtk_label_new("📝 Código Fuente JavaLang");
    gtk_box_pack_start(GTK_BOX(left_vbox), source_label, FALSE, FALSE, 0);
    
    // Área de texto para código fuente con ScrolledWindow
    GtkWidget *source_scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(source_scrolled),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(left_vbox), source_scrolled, TRUE, TRUE, 0);
    
    // CORREGIR: Usar nombres consistentes con gui.h
    widgets->source_view = gtk_text_view_new();  // <-- Cambiar de source_text a source_view
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(widgets->source_view), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(source_scrolled), widgets->source_view);
    
    // Obtener el buffer
    widgets->source_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets->source_view));
    source_buffer = widgets->source_buffer; // Variable global para compatibilidad
    
    // Texto de ejemplo
    gtk_text_buffer_set_text(widgets->source_buffer, 
        "// Ejemplo de código JavaLang\n"
        "int x = 5;\n"
        "int y = 10;\n"
        "int z = x + y;\n\n"
        "if (z > 10) {\n"
        "    int w = 20;\n"
        "}", -1);
    
    // Botones
    GtkWidget *toolbar_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(left_vbox), toolbar_hbox, FALSE, FALSE, 0);
    
    widgets->execute_button = gtk_button_new_with_label("▶️ Ejecutar");
    gtk_box_pack_start(GTK_BOX(toolbar_hbox), widgets->execute_button, FALSE, FALSE, 0);
    g_signal_connect(widgets->execute_button, "clicked", G_CALLBACK(on_execute_clicked), NULL);

    
    GtkWidget *open_button = gtk_button_new_with_label("📁 Abrir");
    gtk_box_pack_start(GTK_BOX(toolbar_hbox), open_button, FALSE, FALSE, 0);
    g_signal_connect(open_button, "clicked", G_CALLBACK(open_file_dialog), NULL);

    GtkWidget *save_button = gtk_button_new_with_label("💾 Guardar");
    gtk_box_pack_start(GTK_BOX(toolbar_hbox), save_button, FALSE, FALSE, 0);
    g_signal_connect(save_button, "clicked", G_CALLBACK(save_file_dialog), NULL);
        
    // === PANEL DERECHO (Reportes) ===
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_hbox), right_vbox, TRUE, TRUE, 0);
    
    // Notebook para pestañas
    GtkWidget *notebook = gtk_notebook_new();
    gtk_box_pack_start(GTK_BOX(right_vbox), notebook, TRUE, TRUE, 0);
    
    widgets->notebook = notebook;

    // === PESTAÑA: CONSOLA ===
    GtkWidget *console_scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(console_scrolled),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    widgets->console_view = gtk_text_view_new();  // <-- Cambiar de console_text a console_view
    gtk_text_view_set_editable(GTK_TEXT_VIEW(widgets->console_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(widgets->console_view), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(console_scrolled), widgets->console_view);
    
    widgets->console_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets->console_view));
    console_buffer = widgets->console_buffer; // Variable global para compatibilidad
    
    // imprimir en consola de forma segura
    set_console_print_safe(console_adapter);
    
    GtkWidget *console_label = gtk_label_new("📋 Consola");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), console_scrolled, console_label);
    
        // === PESTAÑA: TABLA DE SÍMBOLOS === 
    GtkWidget *symbols_scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(symbols_scrolled),
                                GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

        // === PESTANA: IMAGEN DE ERRORES ===
    widgets->image_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(widgets->image_scroll),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);


    // ⭐ USAR TEXTVIEW SIMPLE (como el AST)
    widgets->symbols_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(widgets->symbols_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(widgets->symbols_view), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(symbols_scrolled), widgets->symbols_view);

    // Texto inicial
    GtkTextBuffer *symbols_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets->symbols_view));
    gtk_text_buffer_set_text(symbols_buffer, 
        "📊 Tabla de Símbolos - JavaLang\n\n"
        "💡 Presione '📊 Tabla Símbolos' para generar imagen PNG\n"
        "🖼️ La tabla se mostrará como imagen (igual que el AST)\n\n"
        "🔧 Ejecute un análisis primero para ver símbolos\n", -1);

    // ⭐ AGREGAR PESTAÑA AL NOTEBOOK
    GtkWidget *symbols_label = gtk_label_new("📊 Símbolos");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), symbols_scrolled, symbols_label);

    
    // ⭐ NUEVA PESTAÑA: ERRORES DETALLADOS
    GtkWidget *errors_scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(errors_scrolled),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    widgets->errors_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(widgets->errors_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(widgets->errors_view), FALSE);
    
    // Configurar fuente monospace
    PangoFontDescription *errors_font = pango_font_description_from_string("Courier New 10");
    //gtk_widget_override_font(widgets->errors_view, errors_font);
    pango_font_description_free(errors_font);
    
    widgets->errors_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets->errors_view));
    gtk_container_add(GTK_CONTAINER(errors_scrolled), widgets->errors_view);
    
    // Label para la pestaña de errores
    GtkWidget *errors_label = gtk_label_new("❌ Errores");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), errors_scrolled, errors_label);

    // === PESTAÑA: IMAGEN === (tu código existente)
    widgets->image_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(widgets->image_scroll),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    widgets->image_view = gtk_image_new();
    gtk_container_add(GTK_CONTAINER(widgets->image_scroll), widgets->image_view);
    
    GtkWidget *image_label = gtk_label_new("🖼️ Imagen");
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), widgets->image_scroll, image_label);

    // Botones adicionales
    GtkWidget *buttons_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(right_vbox), buttons_hbox, FALSE, FALSE, 0);

    GtkWidget *symbols_button = gtk_button_new_with_label("📊 Tabla Símbolos");
    gtk_box_pack_start(GTK_BOX(buttons_hbox), symbols_button, TRUE, TRUE, 0);
    g_signal_connect(symbols_button, "clicked", G_CALLBACK(show_symbol_table_report), NULL);
    
    GtkWidget *ast_button = gtk_button_new_with_label("🌳 Generar AST");
    gtk_box_pack_start(GTK_BOX(buttons_hbox), ast_button, TRUE, TRUE, 0);
    g_signal_connect(ast_button, "clicked", G_CALLBACK(show_ast_graphviz), NULL);

    GtkWidget *errors_button = gtk_button_new_with_label("📋 Tabla Errores");
    gtk_box_pack_start(GTK_BOX(buttons_hbox), errors_button, TRUE, TRUE, 0);
    g_signal_connect(errors_button, "clicked", G_CALLBACK(show_error_report_gui), NULL);
        
    // Mostrar todos los widgets
    gtk_widget_show_all(widgets->window);
    
    // Mensaje inicial en consola
    append_to_console("=== JavaLang Interpreter v1.0 ===\n");
    append_to_console("✅ Interfaz inicializada correctamente\n");
    append_to_console("📝 Escriba código JavaLang y presione 'Ejecutar'\n\n");
    
    printf("✅ Interfaz GTK construida correctamente\n");
}

// =================== FUNCIÓN PRINCIPAL ===================
int main_gui(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    // AGREGAR: Crear y configurar widgets
    widgets = g_malloc0(sizeof(AppWidgets));
    
    // Crear ventana principal
    widgets->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(widgets->window), "JavaLang Interpreter v1.0");
    gtk_window_set_default_size(GTK_WINDOW(widgets->window), 1200, 800);
    gtk_window_set_position(GTK_WINDOW(widgets->window), GTK_WIN_POS_CENTER);
    
    // Inicializar tabla de símbolos global
    if (!global_symbol_table) {
        global_symbol_table = create_symbol_table();
        printf("✅ Tabla de símbolos global creada\n");
    }
    
    build_gui();
    
    gtk_main();
    
    // Limpiar al salir
    if (widgets) {
        cleanup_parser();
        g_free(widgets);
    }
    
    return 0;
}


// =================== FUNCIONES DE COMPATIBILIDAD ===================

void send_token_to_gui(const char* token_type, const char* token_value) {
    char token_message[256];
    snprintf(token_message, sizeof(token_message), "🔤 TOKEN %s: %s\n", token_type, token_value);
    append_to_console(token_message);
}

void update_ast_treeview(ast_node *ast_root) {
    printf("🌳 Actualizando vista del AST...\n");
    append_to_console("🌳 Vista del AST actualizada\n");
}

void on_execute_clicked(GtkButton *button, gpointer user_data) {
    execute_code(button, user_data);
}


void on_run_clicked(GtkButton *button, gpointer user_data) {
    execute_code(button, user_data);
}

void on_symbols_clicked(GtkButton *button, gpointer user_data) {
    show_symbol_table_report(button, user_data);
}

void on_ast_clicked(GtkButton *button, gpointer user_data) {
    show_ast_graphviz(button, user_data);
}

void show_error_report_gui(GtkButton *button, gpointer user_data) {
    show_error_report();
}


// =================== ERRORES ===================
// AGREGAR al final del archivo, antes de la última llave }:

// ⭐ NUEVA FUNCIÓN: Análisis léxico
/*void analyze_lexical_errors(const char *code) {
    printf("🔍 Analizando errores léxicos...\n");
    
    int line = 1;
    int column = 1;
    
    for (int i = 0; code[i] != '\0'; i++) {
        // ⭐ Detectar caracteres inválidos
        if (!isprint(code[i]) && code[i] != '\n' && code[i] != '\t' && code[i] != '\r') {
            char msg[100];
            snprintf(msg, sizeof(msg), "Carácter inválido: ASCII %d", (int)code[i]);
            report_lexical_error(line, column, msg, "");
        }
        
        // ⭐ Detectar strings sin cerrar
        if (code[i] == '"') {
            int j = i + 1;
            while (code[j] != '\0' && code[j] != '"' && code[j] != '\n') {
                j++;
            }
            if (code[j] != '"') {
                report_lexical_error(line, column, "String literal sin cerrar", "");
            }
        }
        
        // Actualizar posición
        if (code[i] == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
    }
    
    printf("✅ Análisis léxico completado\n");
}*/

// ⭐ NUEVA FUNCIÓN: Análisis semántico básico (sin AST)
int analyze_code_for_semantic_errors(const char *code) {
    if (!code) return 0;
    int error_count = 0;
    char *copy = strdup(code);
    if (!copy) return 0;

    char *line = strtok(copy, "\n");
    int lineno = 1;
    while (line) {
        // Buscar asignaciones de la forma: <id> = "...
        char *eq = strchr(line, '=');
        if (eq) {
            char *quote = strchr(eq, '"');
            if (quote) {
                // extraer identificador LHS (palabra anterior al '=')
                char lhs[128] = {0};
                int i = 0;
                char *p = eq - 1;
                while (p >= line && isspace((unsigned char)*p)) p--;
                while (p >= line && (isalnum((unsigned char)*p) || *p == '_')) {
                    lhs[i++] = *p;
                    p--;
                }
                if (i > 0) {
                    // invertir
                    lhs[i] = '\0';
                    for (int a = 0; a < i/2; a++) {
                        char t = lhs[a]; lhs[a] = lhs[i-1-a]; lhs[i-1-a] = t;
                    }
                    // Si la variable fue declarada como número, reportar incompatibilidad
                    char pattern_int[64];
                    snprintf(pattern_int, sizeof(pattern_int), "int %s", lhs);
                    char pattern_double[64];
                    snprintf(pattern_double, sizeof(pattern_double), "double %s", lhs);
                    char pattern_float[64];
                    snprintf(pattern_float, sizeof(pattern_float), "float %s", lhs);
                    if (strstr(code, pattern_int) || strstr(code, pattern_double) || strstr(code, pattern_float)) {
                        report_semantic_error(lineno, 0, "Incompatibilidad de tipos en la asignación", "Global");
                        error_count++;
                    }
                }
            }
        }
        line = strtok(NULL, "\n");
        lineno++;
    }
    free(copy);
    return error_count;
}



//  Actualizar vista de errores detallada
void update_errors_view(void) {
    if (!widgets || !widgets->errors_buffer) {
        printf("❌ Buffer de errores no disponible\n");
        return;
    }
    
    // Limpiar contenido anterior
    gtk_text_buffer_set_text(widgets->errors_buffer, "", -1);
    
    if (error_count == 0) {
        // Si no hay errores, mostrar mensaje positivo
        const char *no_errors_msg = 
            "🎉 ¡EXCELENTE! NO SE ENCONTRARON ERRORES\n\n"
            "✅ Análisis léxico: CORRECTO\n"
            "✅ Análisis sintáctico: CORRECTO\n"
            "✅ Análisis semántico: CORRECTO\n\n"
            "🚀 El código está listo para ejecutar!\n\n"
            "───────────────────────────────────────────────────────\n"
            "📅 Análisis completado correctamente\n"
            "🔧 JavaLang Interpreter v1.0";
        
        gtk_text_buffer_set_text(widgets->errors_buffer, no_errors_msg, -1);
        return;
    }
    
    // Crear reporte detallado de errores
    char *error_report = malloc(8192);
    if (!error_report) return;
    
    // Encabezado
    strcpy(error_report, 
           "═══════════════════════════════════════════════════════\n"
           "           📋 REPORTE DETALLADO DE ERRORES\n"
           "═══════════════════════════════════════════════════════\n\n");
    
    // Estadísticas
    int lexico = 0, sintactico = 0, semantico = 0, runtime = 0;
    error_entry_t *current = error_list;
    while (current) {
        switch (current->tipo) {
            case ERROR_LEXICO: lexico++; break;
            case ERROR_SINTACTICO: sintactico++; break;
            case ERROR_SEMANTICO: semantico++; break;
            case ERROR_RUNTIME: runtime++; break;
        }
        current = current->next;
    }
    
    char stats[512];
    snprintf(stats, sizeof(stats),
             "📊 RESUMEN EJECUTIVO:\n"
             "   • Total de errores encontrados: %d\n"
             "   • 🔤 Errores léxicos: %d\n"
             "   • 📝 Errores sintácticos: %d\n"
             "   • 🧠 Errores semánticos: %d\n"
             "   • ⚡ Errores de runtime: %d\n\n",
             error_count, lexico, sintactico, semantico, runtime);
    strcat(error_report, stats);
    
    // Crear array de errores para mostrar en orden
    error_entry_t *errors_array[100];
    int count = 0;
    current = error_list;
    while (current && count < 100) {
        errors_array[count++] = current;
        current = current->next;
    }
    
    // Mostrar errores detallados
    strcat(error_report, 
           "📋 DETALLES POR ERROR:\n"
           "───────────────────────────────────────────────────────\n\n");
    
    for (int i = count - 1; i >= 0; i--) {
        error_entry_t *error = errors_array[i];
        char error_detail[512];
        
        const char *tipo_icono = "";
        const char *tipo_texto = "";
        switch (error->tipo) {
            case ERROR_LEXICO: 
                tipo_icono = "🔤";
                tipo_texto = "LÉXICO";
                break;
            case ERROR_SINTACTICO: 
                tipo_icono = "📝";
                tipo_texto = "SINTÁCTICO";
                break;
            case ERROR_SEMANTICO: 
                tipo_icono = "🧠";
                tipo_texto = "SEMÁNTICO";
                break;
            case ERROR_RUNTIME: 
                tipo_icono = "⚡";
                tipo_texto = "RUNTIME";
                break;
            default:
                tipo_icono = "❓";
                tipo_texto = "DESCONOCIDO";
        }
        
        snprintf(error_detail, sizeof(error_detail),
                "%d. %s ERROR %s\n"
                "    📍 Ubicación: Línea %d, Columna %d\n"
                "    📄 Descripción: %s\n"
                "    🎯 Ámbito: %s\n"
                "    ────────────────────────────────────────────────\n\n",
                error->numero, tipo_icono, tipo_texto,
                error->linea, error->columna,
                error->descripcion ? error->descripcion : "Sin descripción",
                error->ambito ? error->ambito : "Global");
        
        strcat(error_report, error_detail);
    }
    
    // Pie del reporte
    strcat(error_report, 
           "\n═══════════════════════════════════════════════════════\n"
           "💡 SUGERENCIAS:\n"
           "   • Revisa los errores léxicos primero (caracteres inválidos)\n"
           "   • Corrige los errores sintácticos (estructura del código)\n"
           "   • Verifica las declaraciones y tipos de variables\n\n"
           "🔧 JavaLang Interpreter v1.0\n"
           "═══════════════════════════════════════════════════════");
    
    // Establecer texto en el buffer
    gtk_text_buffer_set_text(widgets->errors_buffer, error_report, -1);
    
    // Liberar memoria
    free(error_report);
    
    // ⭐ CAMBIAR AUTOMÁTICAMENTE A LA PESTAÑA DE ERRORES
    gtk_notebook_set_current_page(GTK_NOTEBOOK(widgets->notebook), 2); // Pestaña 2 = Errores
    
    printf("✅ Vista de errores actualizada (%d errores)\n", error_count);
}
// ⭐ NUEVA FUNCIÓN: Mostrar imagen en la aplicación
void show_image_in_app(const char *image_path) {
    if (!widgets || !widgets->image_view) {
        printf("❌ Widget de imagen no disponible\n");
        return;
    }
    
    printf("🖼️ Cargando imagen: %s\n", image_path);
    
    // Verificar si el archivo existe
    FILE *test = fopen(image_path, "r");
    if (!test) {
        printf("❌ Archivo de imagen no existe: %s\n", image_path);
        
        // Mostrar imagen de "no encontrado"
        GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 400, 300);
        gdk_pixbuf_fill(pixbuf, 0xccccccff); // Gris claro
        
        gtk_image_set_from_pixbuf(GTK_IMAGE(widgets->image_view), pixbuf);
        g_object_unref(pixbuf);
        
        return;
    }
    fclose(test);
    
    // Cargar y redimensionar imagen
    GError *error = NULL;
    GdkPixbuf *original_pixbuf = gdk_pixbuf_new_from_file(image_path, &error);
    
    if (!original_pixbuf) {
        printf("❌ Error al cargar imagen: %s\n", error ? error->message : "Error desconocido");
        if (error) g_error_free(error);
        return;
    }
    
    // Redimensionar para que quepa bien en la ventana
    int original_width = gdk_pixbuf_get_width(original_pixbuf);
    int original_height = gdk_pixbuf_get_height(original_pixbuf);
    
    // Calcular nuevo tamaño manteniendo proporción
    int new_width = 800;
    int new_height = (original_height * new_width) / original_width;
    
    if (new_height > 600) {
        new_height = 600;
        new_width = (original_width * new_height) / original_height;
    }
    
    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(original_pixbuf, 
                                                       new_width, new_height, 
                                                       GDK_INTERP_BILINEAR);
    
    // Establecer imagen en el widget
    gtk_image_set_from_pixbuf(GTK_IMAGE(widgets->image_view), scaled_pixbuf);
    
    // Limpiar memoria
    g_object_unref(original_pixbuf);
    g_object_unref(scaled_pixbuf);
    
    //  CAMBIAR AUTOMÁTICAMENTE A LA PESTAÑA DE IMAGEN
    gtk_notebook_set_current_page(GTK_NOTEBOOK(widgets->notebook), 3);
    
    printf("✅ Imagen mostrada en la aplicación\n");
}

// ...existing code...
// ⭐ NUEVA FUNCIÓN: Análisis léxico (mejorado)
void analyze_lexical_errors(const char *code) {
    printf("🔍 Analizando errores léxicos...\n");
    int line = 1, column = 1;
    for (int i = 0; code[i] != '\0'; ) {
        unsigned char c = (unsigned char)code[i];

        // Nueva: manejar strings con escapes
        if (c == '"') {
            int j = i + 1;
            int closed = 0;
            while (code[j] != '\0') {
                if (code[j] == '\\' && code[j+1] != '\0') {
                    // salto de escape \" or \n etc.
                    j += 2;
                    continue;
                }
                if (code[j] == '"') { closed = 1; break; }
                if (code[j] == '\n') break; // no cerrada en misma línea
                j++;
            }
            if (!closed) {
                report_lexical_error(line, column, "String literal sin cerrar", "");
                // Avanzar hasta fin de línea para evitar repetir el mismo error
                while (code[i] != '\0' && code[i] != '\n') i++;
                if (code[i] == '\n') { i++; line++; column = 1; }
                continue;
            } else {
                // avanzar i hasta la comilla de cierre (incluyéndola)
                while (i <= j && code[i] != '\0') {
                    if (code[i] == '\n') { line++; column = 1; }
                    else column++;
                    i++;
                }
                continue;
            }
        }

        // detectar caracteres no imprimibles (salvo tab/CR/newline)
        if (!isprint(c) && c != '\t' && c != '\r' && c != '\n') {
            char msg[128];
            snprintf(msg, sizeof(msg), "Carácter inválido: ASCII %d", c);
            report_lexical_error(line, column, msg, "");
        }

        // actualiza posición
        if (c == '\n') { line++; column = 1; i++; }
        else { column++; i++; }
    }

    printf("✅ Análisis léxico completado\n");
}