#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/errores.h"
#include "../include/gui.h"
#include <ctype.h>    
#include <unistd.h>   

// Variables globales
error_entry_t *error_list = NULL;
int error_count = 0;
int current_line = 1;
int current_column = 1;

// Inicializar sistema de errores
void init_error_system(void) {
    clear_errors();
    error_count = 0;
    current_line = 1;
    current_column = 1;
}

// Limpiar lista de errores
void clear_errors(void) {
    error_entry_t *current = error_list;
    while (current) {
        error_entry_t *temp = current;
        current = current->next;
        free(temp);
    }
    error_list = NULL;
    error_count = 0;
}

// Función auxiliar para agregar error a la lista
// En la función add_error(), cambiar:
static void add_error(error_type_t type, int line, int column, const char *msg, const char *scope) {
    error_entry_t *new_error = malloc(sizeof(error_entry_t));
    if (!new_error) return;
    
    new_error->numero = ++error_count;
    new_error->tipo = type;
    strncpy(new_error->descripcion, msg, sizeof(new_error->descripcion) - 1);
    new_error->descripcion[sizeof(new_error->descripcion) - 1] = '\0';
    
    // ⭐ USAR EL SCOPE REAL QUE LE PASES, NO FORZAR "Global"
    strncpy(new_error->ambito, scope ? scope : "Global", sizeof(new_error->ambito) - 1);
    new_error->ambito[sizeof(new_error->ambito) - 1] = '\0';
    
    new_error->linea = line;
    new_error->columna = column;
    new_error->next = error_list;
    
    error_list = new_error;
}

// Reportar error sintáctico
void report_syntax_error(int line, int column, const char *msg, const char *token) {
    char full_msg[512];
    if (token && strlen(token) > 0) {
        snprintf(full_msg, sizeof(full_msg), "%s. Token: '%s'", msg, token);
    } else {
        strncpy(full_msg, msg, sizeof(full_msg) - 1);
        full_msg[sizeof(full_msg) - 1] = '\0';
    }
    
    add_error(ERROR_SINTACTICO, line, column, full_msg, "Parser");
    
    // También enviar a la GUI si está disponible
    if (append_to_console) {
        char gui_msg[256];
        snprintf(gui_msg, sizeof(gui_msg), "❌ ERROR SINTÁCTICO [%d:%d]: %s\n", line, column, full_msg);
        append_to_console(gui_msg);
    }
}

// Reportar error semántico
void report_semantic_error(int line, int column, const char *msg, const char *scope) {
    add_error(ERROR_SEMANTICO, line, column, msg, scope ? scope : "Global");
    
    if (append_to_console) {
        char gui_msg[256];
        snprintf(gui_msg, sizeof(gui_msg), "❌ ERROR SEMÁNTICO [%d:%d]: %s\n", line, column, msg);
        append_to_console(gui_msg);
    }
}

// Reportar error léxico
void report_lexical_error(int line, int column, const char *msg, const char *token) {
    char full_msg[512];
    if (token && strlen(token) > 0) {
        snprintf(full_msg, sizeof(full_msg), "%s. Token: '%s'", msg, token);
    } else {
        strncpy(full_msg, msg, sizeof(full_msg) - 1);
        full_msg[sizeof(full_msg) - 1] = '\0';
    }
    
    add_error(ERROR_LEXICO, line, column, full_msg, "Lexer");
    
    if (append_to_console) {
        char gui_msg[256];
        snprintf(gui_msg, sizeof(gui_msg), "❌ ERROR LÉXICO [%d:%d]: %s\n", line, column, full_msg);
        append_to_console(gui_msg);
    }
}

// Reportar error de runtime
void report_runtime_error(int line, int column, const char *msg, const char *scope) {
    add_error(ERROR_RUNTIME, line, column, msg, scope ? scope : "Runtime");
    
    if (append_to_console) {
        char gui_msg[256];
        snprintf(gui_msg, sizeof(gui_msg), "❌ ERROR RUNTIME [%d:%d]: %s\n", line, column, msg);
        append_to_console(gui_msg);
    }
}

// Obtener string del tipo de error
const char* get_error_type_string(error_type_t type) {
    switch (type) {
        case ERROR_SINTACTICO: return "SINTÁCTICO";
        case ERROR_SEMANTICO: return "SEMÁNTICO";
        case ERROR_LEXICO: return "LÉXICO";
        case ERROR_RUNTIME: return "RUNTIME";
        default: return "DESCONOCIDO";
    }
}

// Establecer posición actual (para el lexer)
void set_current_position(int line, int column) {
    current_line = line;
    current_column = column;
}

// Imprimir tabla de errores en consola
void print_error_table(void) {
    if (!error_list) {
        printf("✅ No hay errores reportados\n");
        return;
    }
    
    printf("\n📋 === TABLA DE ERRORES ===\n");
    printf("╔════╦═══════════════════════════════════════════════════════════════╦════════════╦══════╦════════╗\n");
    printf("║ No.║ Descripción                                                   ║ Ámbito     ║ Línea║ Columna║\n");
    printf("╠════╬═══════════════════════════════════════════════════════════════╬════════════╬══════╬════════╣\n");
    
    // Invertir lista para mostrar en orden
    error_entry_t *errors_array[100]; // Máximo 100 errores
    int count = 0;
    error_entry_t *current = error_list;
    while (current && count < 100) {
        errors_array[count++] = current;
        current = current->next;
    }
    
    // Mostrar en orden inverso (del más antiguo al más reciente)
    for (int i = count - 1; i >= 0; i--) {
        error_entry_t *error = errors_array[i];
        printf("║%4d║ %-65s ║ %-10s ║%6d║%8d║\n",
               error->numero,
               error->descripcion,
               error->ambito,
               error->linea,
               error->columna);
    }
    
    printf("╚════╩═══════════════════════════════════════════════════════════════╩════════════╩══════╩════════╝\n");
    printf("Total de errores: %d\n", error_count);
}

// Generar HTML de la tabla de errores
char* generate_error_html(void) {
    static char html_content[8192];
    
    strcpy(html_content,
        "<!DOCTYPE html>"
        "<html><head>"
        "<meta charset='UTF-8'>"
        "<title>Tabla de Errores</title>"
        "<style>"
        "body { font-family: 'Segoe UI', Arial, sans-serif; margin: 20px; background: linear-gradient(135deg, #ff6b6b 0%, #ee5a24 100%); min-height: 100vh; }"
        ".container { background: white; padding: 30px; border-radius: 15px; box-shadow: 0 10px 30px rgba(0,0,0,0.3); max-width: 1200px; margin: 0 auto; }"
        "h1 { color: #e74c3c; text-align: center; margin-bottom: 30px; font-size: 28px; }"
        ".stats { background: #f8f9fa; padding: 20px; border-radius: 10px; margin-bottom: 20px; text-align: center; }"
        ".stat { display: inline-block; margin: 0 20px; }"
        ".stat-number { font-size: 36px; font-weight: bold; color: #e74c3c; }"
        ".stat-label { color: #666; font-size: 14px; }"
        "table { width: 100%; border-collapse: collapse; margin-top: 20px; }"
        "th, td { padding: 12px; text-align: left; border-bottom: 1px solid #ddd; }"
        "th { background-color: #e74c3c; color: white; font-weight: bold; }"
        "tr:nth-child(even) { background-color: #f2f2f2; }"
        "tr:hover { background-color: #ffebee; }"
        ".error-number { font-weight: bold; color: #e74c3c; }"
        ".error-desc { max-width: 400px; word-wrap: break-word; }"
        ".error-scope { color: #666; font-style: italic; }"
        ".empty { text-align: center; color: #666; font-size: 18px; padding: 40px; }"
        "</style>"
        "</head><body>"
        "<div class='container'>"
        "<h1>📋 Tabla de Errores - JavaLang</h1>");
    
    if (!error_list) {
        strcat(html_content,
            "<div class='empty'>"
            "✅ No hay errores reportados<br>"
            "🎉 Su código está libre de errores"
            "</div>");
    } else {
        // Estadísticas
        char stats[512];
        snprintf(stats, sizeof(stats),
            "<div class='stats'>"
            "<div class='stat'>"
            "<div class='stat-number'>%d</div>"
            "<div class='stat-label'>Total Errores</div>"
            "</div>"
            "</div>", error_count);
        strcat(html_content, stats);
        
        // Tabla
        strcat(html_content,
            "<table>"
            "<thead><tr>"
            "<th>🔢 No.</th>"
            "<th>📝 Descripción</th>"
            "<th>📂 Ámbito</th>"
            "<th>📍 Línea</th>"
            "<th>📐 Columna</th>"
            "</tr></thead><tbody>");
        
        // Crear array para orden correcto
        error_entry_t *errors_array[100];
        int count = 0;
        error_entry_t *current = error_list;
        while (current && count < 100) {
            errors_array[count++] = current;
            current = current->next;
        }
        
        // Filas de datos (orden inverso)
        for (int i = count - 1; i >= 0; i--) {
            error_entry_t *error = errors_array[i];
            char row[512];
            snprintf(row, sizeof(row),
                "<tr>"
                "<td class='error-number'>%d</td>"
                "<td class='error-desc'>%s</td>"
                "<td class='error-scope'>%s</td>"
                "<td>%d</td>"
                "<td>%d</td>"
                "</tr>",
                error->numero,
                error->descripcion,
                error->ambito,
                error->linea,
                error->columna);
            strcat(html_content, row);
        }
        
        strcat(html_content, "</tbody></table>");
    }
    
    strcat(html_content, "</div></body></html>");
    return html_content;
}

// Mostrar reporte de errores

void show_error_report() {
    printf("=== GENERANDO REPORTE DE ERRORES ===\n");
    
    // ⭐ CAMBIAR ruta a tu carpeta del proyecto:
    const char *html_path = "reports/errors_table.html";
    const char *txt_path = "reports/errors_report.txt";
    
    // ⭐ Crear directorio reports si no existe
    system("mkdir -p reports");
    
    // ⭐ GENERAR ARCHIVO HTML
    FILE *html_file = fopen(html_path, "w");
    if (!html_file) {
        printf("❌ Error: No se pudo crear archivo HTML en %s\n", html_path);
        return;
    }
    
    // HTML mejorado y más compatible
    fprintf(html_file, "<!DOCTYPE html>\n");
    fprintf(html_file, "<html lang='es'>\n");
    fprintf(html_file, "<head>\n");
    fprintf(html_file, "    <meta charset='UTF-8'>\n");
    fprintf(html_file, "    <title>Tabla de Errores - JavaLang</title>\n");
    fprintf(html_file, "    <style>\n");
    fprintf(html_file, "        body { font-family: Arial, sans-serif; margin: 20px; background-color: #f0f0f0; }\n");
    fprintf(html_file, "        .container { background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }\n");
    fprintf(html_file, "        h1 { color: #d32f2f; text-align: center; }\n");
    fprintf(html_file, "        .stats { background: #e3f2fd; padding: 15px; border-radius: 5px; margin: 15px 0; text-align: center; }\n");
    fprintf(html_file, "        table { width: 100%%; border-collapse: collapse; margin: 15px 0; }\n");
    fprintf(html_file, "        th { background: #1976d2; color: white; padding: 10px; }\n");
    fprintf(html_file, "        td { padding: 8px; border-bottom: 1px solid #ddd; }\n");
    fprintf(html_file, "        tr:nth-child(even) { background-color: #f5f5f5; }\n");
    fprintf(html_file, "        .error-lexico { background-color: #fff3e0; }\n");
    fprintf(html_file, "        .error-sintactico { background-color: #ffebee; }\n");
    fprintf(html_file, "        .error-semantico { background-color: #f3e5f5; }\n");
    fprintf(html_file, "    </style>\n");
    fprintf(html_file, "</head>\n");
    fprintf(html_file, "<body>\n");
    fprintf(html_file, "    <div class='container'>\n");
    fprintf(html_file, "        <h1> Reporte de Errores - JavaLang</h1>\n");
    
    // Estadísticas
    int lexico = 0, sintactico = 0, semantico = 0, runtime = 0;
    
    error_entry_t *errors_array[100];
    int count = 0;
    error_entry_t *current = error_list;
    while (current && count < 100) {
        errors_array[count++] = current;
        current = current->next;
    }
    
    current = error_list;
    while (current) {
        switch (current->tipo) {  // ⭐ USAR 'tipo' NO 'type'
            case ERROR_LEXICO: lexico++; break;        // ⭐ USAR ERROR_LEXICO
            case ERROR_SINTACTICO: sintactico++; break; // ⭐ USAR ERROR_SINTACTICO
            case ERROR_SEMANTICO: semantico++; break;  // ⭐ USAR ERROR_SEMANTICO
            case ERROR_RUNTIME: runtime++; break;
        }
        current = current->next;
    }
    
    fprintf(html_file, "        <div class='stats'>\n");
    fprintf(html_file, "            <h3> Tabla de Errores</h3>\n");
    fprintf(html_file, "            <p><strong>Total:</strong> %d errores encontrados</p>\n", error_count);
    fprintf(html_file, "            <p> Léxicos: %d |  Sintácticos: %d |  Semánticos: %d | ⚡ Runtime: %d</p>\n", 
            lexico, sintactico, semantico, runtime);
    fprintf(html_file, "        </div>\n");
    
    if (error_count == 0) {
        fprintf(html_file, "        <div style='text-align: center; color: #2e7d32; font-size: 18px; margin: 40px 0;'>\n");
        fprintf(html_file, "            ✅ ¡Excelente! No se encontraron errores.\n");
        fprintf(html_file, "        </div>\n");
    } else {
        fprintf(html_file, "        <table>\n");
        fprintf(html_file, "            <tr>\n");
        fprintf(html_file, "                <th>No.</th>\n");
        fprintf(html_file, "                <th>Tipo</th>\n");
        fprintf(html_file, "                <th>Descripcion</th>\n");
        fprintf(html_file, "                <th>Linea</th>\n");
        fprintf(html_file, "                <th>Columna</th>\n");
        fprintf(html_file, "                <th>Ambito</th>\n");
        fprintf(html_file, "            </tr>\n");
        
        for (int i = count - 1; i >= 0; i--) {  // ⭐ ORDEN INVERSO
            error_entry_t *error = errors_array[i];
            const char *tipo_texto = "";
            const char *clase_css = "";
            
            switch (error->tipo) {  
                case ERROR_LEXICO: 
                    tipo_texto = " Léxico"; 
                    clase_css = "error-lexico";
                    break;
                case ERROR_SINTACTICO: 
                    tipo_texto = " Sintáctico"; 
                    clase_css = "error-sintactico";
                    break;
                case ERROR_SEMANTICO: 
                    tipo_texto = " Semántico"; 
                    clase_css = "error-semantico";
                    break;
                case ERROR_RUNTIME: 
                    tipo_texto = "⚡ Runtime"; 
                    clase_css = "error-runtime";
                    break;
                default:
                    tipo_texto = " Desconocido";
                    clase_css = "";
            }
            
            fprintf(html_file, "            <tr class='%s'>\n", clase_css);
            fprintf(html_file, "                <td><strong>%d</strong></td>\n", error->numero);
            fprintf(html_file, "                <td>%s</td>\n", tipo_texto);
            fprintf(html_file, "                <td>%s</td>\n", error->descripcion);
            fprintf(html_file, "                <td>%d</td>\n", error->linea);
            fprintf(html_file, "                <td>%d</td>\n", error->columna);
            fprintf(html_file, "                <td>%s</td>\n", error->ambito);
            fprintf(html_file, "            </tr>\n");
        }
        fprintf(html_file, "        </table>\n");
    }
    
    fprintf(html_file, "        <div style='margin-top: 30px; text-align: center; color: #666; font-size: 12px;'>\n");
    fprintf(html_file, "            Generado por JavaLang Interpreter - %s\n", __DATE__);
    fprintf(html_file, "        </div>\n");
    fprintf(html_file, "    </div>\n");
    fprintf(html_file, "</body>\n");
    fprintf(html_file, "</html>\n");
    fclose(html_file);
    
    // ⭐ GENERAR ARCHIVO TXT (más fácil de leer)
    FILE *txt_file = fopen(txt_path, "w");
    if (txt_file) {
        fprintf(txt_file, "=======================================================\n");
        fprintf(txt_file, "           REPORTE DE ERRORES - JAVALANG\n");
        fprintf(txt_file, "=======================================================\n\n");
        fprintf(txt_file, " RESUMEN:\n");
        fprintf(txt_file, "   • Total de errores: %d\n", error_count);
        fprintf(txt_file, "   • Errores léxicos: %d\n", lexico);
        fprintf(txt_file, "   • Errores sintácticos: %d\n", sintactico);
        fprintf(txt_file, "   • Errores semánticos: %d\n", semantico);
        fprintf(txt_file, "   • Errores runtime: %d\n\n", runtime);
        
        if (error_count == 0) {
            fprintf(txt_file, "✅ ¡EXCELENTE! No se encontraron errores.\n");
            fprintf(txt_file, "   El código analizado es completamente válido.\n\n");
        } else {
            fprintf(txt_file, " DETALLE DE ERRORES:\n");
            fprintf(txt_file, "-------------------------------------------------------\n");
            
            for (int i = count - 1; i >= 0; i--) {
                error_entry_t *error = errors_array[i];
                const char *tipo = "";
                switch (error->tipo) {  // ⭐ USAR error->tipo
                    case ERROR_LEXICO: tipo = "LÉXICO"; break;
                    case ERROR_SINTACTICO: tipo = "SINTÁCTICO"; break;
                    case ERROR_SEMANTICO: tipo = "SEMÁNTICO"; break;
                    case ERROR_RUNTIME: tipo = "RUNTIME"; break;
                    default: tipo = "DESCONOCIDO"; break;
                }
                
                fprintf(txt_file, "%d. [%s] Línea %d:%d\n", 
                       error->numero, tipo, error->linea, error->columna);
                fprintf(txt_file, "   Descripción: %s\n", error->descripcion);
                fprintf(txt_file, "   Ámbito: %s\n\n", error->ambito);
            }
        }
        
        fprintf(txt_file, "=======================================================\n");
        fprintf(txt_file, "Generado el: %s\n", __DATE__);
        fprintf(txt_file, "JavaLang Interpreter v1.0\n");
        fprintf(txt_file, "=======================================================\n");
        fclose(txt_file);
    }
    
    // AGREGAR al final de la función show_error_report, ANTES de abrir navegador:

    printf("✅ Archivos generados:\n");
    printf("   📄 HTML: %s\n", html_path);
    printf("   📝 TXT:  %s\n", txt_path);
    
    update_errors_view();

    // PNG AUTOMÁTICAMENTE
    printf("🖼️  Generando PNG...\n");
    char png_path[] = "reports/errors_report.png";
    char screenshot_cmd[512];
    
    // Generar PNG con Firefox headless
    char full_html_path[512];
    getcwd(full_html_path, sizeof(full_html_path));
    strcat(full_html_path, "/");
    strcat(full_html_path, html_path);
    
    snprintf(screenshot_cmd, sizeof(screenshot_cmd), 
             "firefox --headless --window-size=1200,800 --screenshot=%s file://%s 2>/dev/null", 
             png_path, full_html_path);
    
    int result = system(screenshot_cmd);
    
    if (result == 0) {
        printf("   🖼️  PNG: %s\n", png_path);
        
        // ⭐ MOSTRAR IMAGEN EN LA APLICACIÓN
        show_image_in_app(png_path);
        
        if (append_to_console) {
            append_to_console("🖼️ Imagen de errores generada y mostrada en pestaña 'Imagen'\n");
        }
    } else {
        printf("❌ Error al generar PNG\n");
        if (append_to_console) {
            append_to_console("❌ No se pudo generar la imagen PNG\n");
        }
    }
    // ⭐ Abrir con el navegador predeterminado
    char comando[512];
    snprintf(comando, sizeof(comando), "xdg-open %s 2>/dev/null &", html_path);
    system(comando);
    
    if (append_to_console) {
        char msg[256];
        snprintf(msg, sizeof(msg), " Reportes generados en carpeta 'reports/'\n   • %s\n   • %s\n", 
                html_path, txt_path);
        append_to_console(msg);
    }
    
    printf("🌐 Abriendo reporte en navegador...\n");
}

