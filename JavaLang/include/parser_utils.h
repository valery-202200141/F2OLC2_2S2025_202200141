#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "ast.h"

// Declaraciones de las funciones wrapper para uso externo
int parse_from_string(const char *input);
ast_node* get_ast_root(void);
void cleanup_parser(void);
void reset_lexer(void);

void report_syntax_error(int line, int column, const char *msg, const char *token);
#endif