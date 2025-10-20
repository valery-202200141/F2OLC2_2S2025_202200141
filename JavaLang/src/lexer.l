%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ast.h"
#include "../include/parser.h"
#include "../include/errores.h"

extern YYSTYPE yylval;
extern char *input_string;
extern char *input_ptr;
extern int input_len;
extern int yylineno;



#define YY_INPUT(buf, result, max_size) \
{ \
    printf("🔍 YY_INPUT: input_len=%d, max_size=%d\n", input_len, max_size); \
    if (input_len <= 0) { \
        printf("❌ YY_INPUT: No hay más entrada (input_len=%d)\n", input_len); \
        result = 0; /* EOF */ \
    } else { \
        int to_copy = input_len < max_size ? input_len : max_size; \
        memcpy(buf, input_ptr, to_copy); \
        /* Sólo NUL-terminar si NO hemos copiado la página completa. */ \
        if (to_copy < max_size) buf[to_copy] = '\0'; \
        printf("📖 YY_INPUT: Copiando %d chars: '%.20s'\n", to_copy, buf); \
        input_ptr += to_copy; \
        input_len -= to_copy; \
        result = to_copy; \
    } \
}
%}

%option noyywrap

%%


"int"       { printf("TOKEN INT\n"); return INT; }
"float"     { printf("TOKEN FLOAT\n"); return FLOAT; }
"double"    { printf("TOKEN DOUBLE\n"); return DOUBLE; }
"boolean"   { printf("TOKEN BOOLEAN\n"); return BOOLEAN; }
"char"      { printf("TOKEN CHAR\n"); return CHAR; }
"String"    { printf("TOKEN ID: %s\n", yytext); yylval.string_val = strdup(yytext); return ID; }
"class"     { printf("TOKEN CLASS\n"); return CLASS; }
"public"    { printf("TOKEN PUBLIC\n"); return PUBLIC; }
"private"   { printf("TOKEN PRIVATE\n"); return PRIVATE; }
"protected" { printf("TOKEN PROTECTED\n"); return PROTECTED; }
"static"    { printf("TOKEN STATIC\n"); return STATIC; }
"final"     { printf("TOKEN FINAL\n"); return FINAL; }
"void"      { printf("TOKEN VOID\n"); return VOID; }
"System"    { printf("TOKEN SYSTEM\n"); return SYSTEM; }
"out"       { printf("TOKEN OUT\n"); return OUT; }
"println"   { printf("TOKEN PRINTLN\n"); return PRINTLN; }
"equals"    { printf("TOKEN EQUALS_METHOD\n"); return EQUALS_METHOD; }
"if"        { printf("TOKEN IF\n"); return IF; }
"else"      { printf("TOKEN ELSE\n"); return ELSE; }
"while"     { printf("TOKEN WHILE\n"); return WHILE; }
"for"       { printf("TOKEN FOR\n"); return FOR; }
"do"        { printf("TOKEN DO\n"); return DO; }
"switch"    { printf("TOKEN SWITCH\n"); return SWITCH; }
"case"      { printf("TOKEN CASE\n"); return CASE; }
"default"   { printf("TOKEN DEFAULT\n"); return DEFAULT; }
"break"     { printf("TOKEN BREAK\n"); return BREAK; }
"continue"  { printf("TOKEN CONTINUE\n"); return CONTINUE; }
"return"    { printf("TOKEN RETURN\n"); return RETURN; }
"new"       { printf("TOKEN NEW\n"); return NEW; }
"this"      { printf("TOKEN THIS\n"); return THIS; }
"true"      { printf("TOKEN TRUE\n"); return TRUE_TOKEN; }
"false"     { printf("TOKEN FALSE\n"); return FALSE_TOKEN; }
"null"      { printf("TOKEN NULL\n"); return NULL_TOKEN; }
"int[]"     { printf("TOKEN INT_ARRAY\n"); return INT_ARRAY; }
"float[]"   { printf("TOKEN FLOAT_ARRAY\n"); return FLOAT_ARRAY; }
"String[]"  { printf("TOKEN STRING_ARRAY\n"); return STRING_ARRAY; }

"++"        { printf("TOKEN INCREMENT\n"); return INCREMENT; }
"--"        { printf("TOKEN DECREMENT\n"); return DECREMENT; }
"+="        { printf("TOKEN PLUS_ASSIGN\n"); return PLUS_ASSIGN; }
"-="        { printf("TOKEN MINUS_ASSIGN\n"); return MINUS_ASSIGN; }
"*="        { printf("TOKEN MULT_ASSIGN\n"); return MULT_ASSIGN; }
"/="        { printf("TOKEN DIV_ASSIGN\n"); return DIV_ASSIGN; }
"=="        { printf("TOKEN EQUALS\n"); return EQUALS; }
"!="        { printf("TOKEN NOT_EQUALS\n"); return NOT_EQUALS; }
"<="        { printf("TOKEN LESS_EQUALS\n"); return LESS_EQUALS; }
">="        { printf("TOKEN GREATER_EQUALS\n"); return GREATER_EQUALS; }
"&&"        { printf("TOKEN AND\n"); return AND; }
"||"        { printf("TOKEN OR\n"); return OR; }

"+"         { printf("TOKEN PLUS\n"); return PLUS; }
"-"         { printf("TOKEN MINUS\n"); return MINUS; }
"*"         { printf("TOKEN MULT\n"); return MULT; }
"/"         { printf("TOKEN DIV\n"); return DIV; }
"%"         { printf("TOKEN MOD\n"); return MOD; }
"="         { printf("TOKEN ASSIGN\n"); return ASSIGN; }
"<"         { printf("TOKEN LESS\n"); return LESS; }
">"         { printf("TOKEN GREATER\n"); return GREATER; }
"!"         { printf("TOKEN NOT\n"); return NOT; }

"("         { printf("TOKEN LPAREN\n"); return LPAREN; }
")"         { printf("TOKEN RPAREN\n"); return RPAREN; }
"{"         { printf("TOKEN LBRACE\n"); return LBRACE; }
"}"         { printf("TOKEN RBRACE\n"); return RBRACE; }
"["         { printf("TOKEN LBRACKET\n"); return LBRACKET; }
"]"         { printf("TOKEN RBRACKET\n"); return RBRACKET; }
";"         { printf("TOKEN SEMICOLON\n"); return SEMICOLON; }
","         { printf("TOKEN COMMA\n"); return COMMA; }
"."         { printf("TOKEN DOT\n"); return DOT; }
":"         { printf("TOKEN COLON\n"); return COLON; }


[0-9]+\.[0-9]+[dD]  {                                   
                        yytext[yyleng-1] = '\0'; 
                        yylval.float_val = atof(yytext); 
                        printf("TOKEN DOUBLE_LITERAL: %f\n", yylval.float_val); 
                        return DOUBLE_LITERAL; 
                    }

[0-9]+\.[0-9]+      { 
                        printf("TOKEN FLOAT_LITERAL: %s\n", yytext); 
                        yylval.float_val = atof(yytext); 
                        return FLOAT_LITERAL; 
                    }

[0-9]+              { 
                        printf("TOKEN INT_LITERAL: %s\n", yytext); 
                        yylval.int_val = atoi(yytext); 
                        return INT_LITERAL; 
                    }

\"([^\"\\]|\\.)*\"  {
                        printf("✅ STRING_LITERAL: %s\n", yytext);
                        /* Guardar el contenido SIN las comillas */
                        if (yyleng >= 2) {
                            char *tmp = malloc(yyleng - 1);
                            if (tmp) {
                                strncpy(tmp, yytext + 1, yyleng - 2);
                                tmp[yyleng - 2] = '\0';
                                yylval.string_val = tmp;
                            } else {
                                yylval.string_val = strdup("");
                            }
                        } else {
                            yylval.string_val = strdup("");
                        }
                        return STRING_LITERAL;
                    }

\"([^\"\\]|\\.)*(\n|$) {
                        printf("❌ STRING SIN CERRAR: %s\n", yytext);
                        report_lexical_error(yylineno, 0, "String literal sin cerrar", yytext);
                        return ERROR;
                    }

\'([^\'\\]|\\.)?\'  { 
                        printf("TOKEN CHAR_LITERAL: %s\n", yytext); 
                        yylval.string_val = strdup(yytext); 
                        return CHAR_LITERAL; 
                    }

[a-zA-Z_][a-zA-Z0-9_]*   { 
                            printf("TOKEN ID: %s\n", yytext); 
                            yylval.string_val = strdup(yytext); 
                            return ID; 
                        }

"//".*              { /* Comentario de línea - ignorar */ }
"/*"([^*]|\*+[^*/])*\*+"/"  { /* Comentario de bloque - ignorar */ }

[ \t\r]+            { /* Ignorar espacios y tabs */ }
\n                  {yylineno++; }

.                   { 
                        printf("ERROR: Caracter no reconocido '%s'\n", yytext);
                        report_lexical_error(yylineno, 0, "Carácter no reconocido", yytext);
                    }

%%