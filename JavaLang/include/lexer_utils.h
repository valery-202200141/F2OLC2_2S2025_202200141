#ifndef LEXER_UTILS_H
#define LEXER_UTILS_H

extern char *input_string;
extern char *input_ptr;
extern int input_len;

void set_input_string(const char *input);
void cleanup_lexer(void);
void setup_lexer_for_string(const char *input);  


#endif


