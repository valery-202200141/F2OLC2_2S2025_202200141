#include "../include/lexer_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables globales para manejo de entrada desde memoria
char *input_string = NULL;
char *input_ptr = NULL;
int input_len = 0;

void set_input_string(const char *input) {
    printf("📝 Configurando entrada para lexer (primeros 50 chars): %.50s...\n", input);
    
    // Limpiar entrada anterior
    if (input_string) {
        free(input_string);
    }
    
    // Configurar nueva entrada
    input_string = strdup(input);
    input_ptr = input_string;
    input_len = strlen(input);
    
    printf("📏 Longitud total: %d caracteres\n", input_len);
    printf("🎯 Primer carácter: '%c' (ASCII: %d)\n", input_string[0], input_string[0]);
}

void setup_lexer_for_string(const char *input) {
    printf("📝 setup_lexer_for_string: Redirigiendo a set_input_string\n");
    // Solo llama a set_input_string, no hagas doble trabajo
    set_input_string(input);
}

void cleanup_lexer(void) {
    if (input_string) {
        free(input_string);
        input_string = NULL;
    }
    input_ptr = NULL;
    input_len = 0;
}