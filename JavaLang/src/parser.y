%{
#include <stdio.h>
#include <stdlib.h>
#include "../include/ast.h" 
#include "../include/lexer_utils.h"
#include "../include/parser_utils.h"
#include "../include/errores.h"
#include "../include/semantic.h"

// Declaraciones de funciones
int yylex(void);
void yyerror(const char *s);

// AGREGAR: Declaraciones externas del lexer
extern int yylineno;        // Número de línea actual
extern char *yytext;        // Texto del token actual
extern void yyrestart(FILE *input_file);  // Reiniciar lexer
extern data_type_t string_to_type(const char* type_str);
extern void add_symbol_to_table(const char* name, data_type_t type, const char* scope, int line);

// Variable global para la raíz del AST 
ast_node *root = NULL;
char* type_token_to_string(int token);

// Declaración externa 
extern symbol_table_t *global_symbol_table;
static ast_node *g_switch_expr = NULL;

static ast_node* append_switch_case(ast_node *chain, ast_node *new_case) {
    if (!chain) return new_case;
    ast_node *cur = chain;

    // Buscar la última IF en la cadena (siguiendo else_branch)
    ast_node *last_if = NULL;
    ast_node *walker = cur;
    while (walker) {
        if (walker->type == AST_IF) last_if = walker;
        // Preferir descender por else_branch cuando exista (cadena if-else-if)
        if (walker->type == AST_IF && walker->data.if_stmt.else_branch) {
            walker = walker->data.if_stmt.else_branch;
            continue;
        }
        // sino avanzar por next
        if (walker->next) { walker = walker->next; continue; }
        break;
    }

    if (last_if && last_if->data.if_stmt.else_branch == NULL) {
        // Si new_case es IF, enlazar como else_branch; si no, poner el bloque (default) como else
        last_if->data.if_stmt.else_branch = new_case;
        return chain;
    }

    // Fallback: anexar al final de la lista via next
    ast_node *last = chain;
    while (last->next) last = last->next;
    last->next = new_case;
    return chain;
}

%}

/********************** SECCIÓN DE DEFINICIONES **********************/

// Define los tipos de datos que pueden tener los símbolos
%union {
    ast_node* astNode;   // Puntero a un nodo del AST
    int int_val;         // Para valores enteros
    float float_val;     // Para valores flotantes
    double double_val;   // Para valores double
    char* string_val;    // Para strings e identificadores
}

// Declaración de tokens CON SU TIPO (deben coincidir con lexer.l)
%token <string_val> ID
%token <int_val> INT_LITERAL
%token <float_val> FLOAT_LITERAL 
%token <double_val> DOUBLE_LITERAL
%token <string_val> STRING_LITERAL CHAR_LITERAL

// Palabras reservadas (sin valor semántico asociado)
%token INT FLOAT DOUBLE BOOLEAN CHAR STRING_TYPE CLASS
%token PUBLIC PRIVATE PROTECTED STATIC FINAL VOID SYSTEM OUT PRINTLN EQUALS_METHOD
%token IF ELSE WHILE FOR DO SWITCH CASE DEFAULT BREAK CONTINUE RETURN
%token NEW THIS TRUE_TOKEN FALSE_TOKEN NULL_TOKEN 

// Operadores
%token PLUS MINUS MULT DIV MOD INCREMENT DECREMENT
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN MULT_ASSIGN DIV_ASSIGN
%token EQUALS NOT_EQUALS LESS GREATER LESS_EQUALS GREATER_EQUALS
%token AND OR NOT

// Símbolos
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token SEMICOLON COMMA DOT COLON
%token INT_ARRAY FLOAT_ARRAY DOUBLE_ARRAY STRING_ARRAY BOOLEAN_ARRAY CHAR_ARRAY

// Tokens especiales
%token ERROR

// Declara el tipo de los no-terminales que construyen nodos del AST
%type <astNode> program statement_list statement expression declaration assignment
%type <astNode> if_statement while_statement for_statement return_statement
%type <astNode> type literal
%type <astNode> main_function function_body function_decl
%type <astNode> array_declaration array_access array_initialization
%type <astNode> expression_list
%type <astNode> declaration_list
%type <astNode> for_init declaration_no_semicolon
%type <astNode> switch_statement switch_sections switch_section statement_list_opt
%type <astNode> function_list
%type <astNode> parameter_list parameter




// Define la precedencia de operadores (CRUCIAL para evitar conflictos)
// Menor precedencia -> Mayor precedencia
%left OR
%left AND
%left EQUALS NOT_EQUALS
%left LESS GREATER LESS_EQUALS GREATER_EQUALS
%left PLUS MINUS
%left MULT DIV MOD
%left INCREMENT DECREMENT
%right NOT UMINUS
%left DOT
%left LPAREN RPAREN LBRACKET RBRACKET

%start program

%%

/********************** SECCIÓN DE REGLAS GRAMATICALES **********************/

program:
    function_list statement_list_opt {
        printf("Programa con lista de funciones/decls parseado correctamente\n");
        /* Si hay funciones y statements, encadenarlas:
           las funciones quedan al inicio de la lista de nodos */
        if ($1 && $2) {
            ast_node *cur = $1;
            while (cur->next) cur = cur->next;
            cur->next = $2;
            root = $1;
        } else if ($1) {
            root = $1;
        } else {
            root = $2;
        }
        $$ = root;
    }
    | statement_list {
        printf("Programa (solo statements) parseado correctamente\n");
        root = $1;
        $$ = root;
    }
    ;

function_list:
    /* empty */ { $$ = NULL; }
    | function_list main_function {
        if (!$1) $$ = $2;
        else {
            ast_node *cur = $1;
            while (cur->next) cur = cur->next;
            cur->next = $2;
            $$ = $1;
        }
    }
    | function_list function_decl {
        if (!$1) $$ = $2;
        else {
            ast_node *cur = $1;
            while (cur->next) cur = cur->next;
            cur->next = $2;
            $$ = $1;
        }
    }
   ;

function_decl:
    /* función sin parámetros */
    type ID LPAREN RPAREN LBRACE function_body RBRACE {
        printf("Función encontrada: %s\n", $2);
        $$ = new_ast_function($2, $6);
        if ($$) $$->line = yylineno;
    }
    /* función con parámetros */
    | type ID LPAREN parameter_list RPAREN LBRACE function_body RBRACE {
        printf("Función con parámetros encontrada: %s\n", $2);
        $$ = new_ast_function($2, $7);
        if ($$) {
            /* almacenar la lista de parámetros en el nodo (new_ast_function crea nodo compatible) */
            $$->data.function_def.parameters = $4;
            $$->line = yylineno;
        }
    }
   ;


parameter:
    type ID {
        /* representamos un parámetro como una declaración sin valor */
        $$ = new_ast_declaration($1, $2, NULL);
        if ($$) $$->line = yylineno;
    }
    ;

parameter_list:
    parameter { $$ = $1; }
    | parameter_list COMMA parameter {
        ast_node *cur = $1;
        while (cur->next) cur = cur->next;
        cur->next = $3;
        $$ = $1;
    }
    ;


main_function:
    PUBLIC STATIC VOID ID LPAREN RPAREN LBRACE function_body RBRACE {
        printf("Función pública encontrada: %s\n", $4);
        $$ = new_ast_main_function($4, $8);
        if ($$) {
            $$->line = yylineno;
        }
    }
    | PUBLIC STATIC VOID ID LPAREN STRING_ARRAY ID RPAREN LBRACE function_body RBRACE {
        // Aceptar main(String[] args)
        printf("Función pública (con params) encontrada: %s\n", $4);
        $$ = new_ast_main_function($4, $10);
        if ($$) {
            $$->line = yylineno;
        }
    }
    ;

function_body:
    statement_list { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

statement_list:
    statement { 
        printf("📝 Primera declaración en lista\n");
        $$ = $1; 
    }
    | statement_list statement { 
        printf("📝 Agregando declaración a lista\n");
        if ($1 && $2) {
            // Buscar el final de la lista y agregar
            ast_node *current = $1;
            while (current->next) {
                current = current->next;
            }
            current->next = $2;
            $$ = $1;
        } else if ($2) {
            $$ = $2;
        } else {
            $$ = $1;
        }
    }
    ;

statement:
    declaration { $$ = $1; }
    | assignment { $$ = $1; }
    | if_statement { $$ = $1; }
    | while_statement { $$ = $1; }
    | for_statement { $$ = $1; }
    | return_statement { $$ = $1; }
    | switch_statement { $$ = $1; }
    | array_declaration { $$ = $1; }
    | expression SEMICOLON { $$ = $1; }
    | BREAK SEMICOLON {
        printf("Break statement\n");
        $$ = new_ast_break();
        if ($$) $$->line = yylineno;
    }
    | CONTINUE SEMICOLON {
        printf("Continue statement\n");
        $$ = new_ast_continue();
        if ($$) $$->line = yylineno;
    }
    | SYSTEM DOT OUT DOT PRINTLN LPAREN expression RPAREN SEMICOLON {
        printf("System.out.println encontrado\n");
        $$ = new_ast_print_stmt($7);
        if ($$) $$->line = yylineno;
    }
    | SYSTEM DOT OUT DOT PRINTLN LPAREN RPAREN SEMICOLON {
        printf("System.out.println vacío\n");
        $$ = new_ast_print_stmt(NULL);
        if ($$) $$->line = yylineno;
    }
    | LBRACE statement_list RBRACE {
        printf("Bloque de statements\n");
        $$ = new_ast_compound_stmt($2, NULL);
        if ($$) $$->line = yylineno;
    }
    ;

declaration:
    type ID SEMICOLON {
        printf("Declaracion simple: %s\n", $2);
        $$ = new_ast_declaration($1, $2, NULL);
        if ($$) $$->line = yylineno;
    }
    | type ID ASSIGN expression SEMICOLON {
        printf("Declaracion con inicialización: %s\n", $2);
        
        // ============= CORREGIR AQUÍ =============
        // Verificar y promover float a double automáticamente
        if ($1 && $4 && $1->data.type_name && 
            strcmp($1->data.type_name, "double") == 0 && 
            $4->type == AST_FLOAT_LITERAL) {
            printf("🔄 Promoción automática: float -> double\n");
            // Convertir el nodo literal float a double
            double promoted_value = (double)$4->data.float_value;
            // Crear nuevo nodo double
            ast_node* double_node = new_ast_double_literal(promoted_value);
            if (double_node) {
                double_node->line = $4->line;
                // Liberar el nodo float anterior
                free($4);
                $4 = double_node;
            }
        }
        // =========================================
        
        $$ = new_ast_declaration($1, $2, $4);
        if ($$) $$->line = yylineno;
    }
    | type declaration_list SEMICOLON {
        printf("Declaraciones múltiples\n");
        // Establecer el tipo para todas las declaraciones en la lista
        ast_node *current = $2;
        while (current) {
            if (current->type == AST_DECLARATION && !current->data.declaration.var_type) {
                current->data.declaration.var_type = $1;
                
                // ============= CORREGIR AQUÍ TAMBIÉN =============
                // Promoción para declaraciones múltiples
                if (current->data.declaration.value && 
                    $1->data.type_name &&
                    strcmp($1->data.type_name, "double") == 0 && 
                    current->data.declaration.value->type == AST_FLOAT_LITERAL) {
                    printf("🔄 Promoción automática en declaración múltiple: float -> double\n");
                    double promoted_value = (double)current->data.declaration.value->data.float_value;
                    ast_node* double_node = new_ast_double_literal(promoted_value);
                    if (double_node) {
                        double_node->line = current->data.declaration.value->line;
                        free(current->data.declaration.value);
                        current->data.declaration.value = double_node;
                    }
                }
                // ==============================================
            }
            if (current->next && current->next->type == AST_DECLARATION) {
                current = current->next;
            } else {
                break;
            }
        }
        $$ = $2;
    }
    ;

declaration_list:
    ID ASSIGN expression {
        printf("Primera declaración múltiple: %s\n", $1);
        $$ = new_ast_declaration(NULL, $1, $3); // tipo se asigna después
        if ($$) $$->line = yylineno;
    }
    | declaration_list COMMA ID ASSIGN expression {
        printf("Declaración múltiple adicional: %s\n", $3);
        ast_node *new_decl = new_ast_declaration(NULL, $3, $5);
        if (new_decl) {
            new_decl->line = yylineno;
            // Encontrar el final de la lista y agregar
            ast_node *current = $1;
            while (current->next) {
                current = current->next;
            }
            current->next = new_decl;
        }
        $$ = $1;
    }
    | ID {
        printf("Declaración múltiple simple: %s\n", $1);
        $$ = new_ast_declaration(NULL, $1, NULL);
        if ($$) $$->line = yylineno;
    }
    | declaration_list COMMA ID {
        printf("Declaración múltiple simple adicional: %s\n", $3);
        ast_node *new_decl = new_ast_declaration(NULL, $3, NULL);
        if (new_decl) {
            new_decl->line = yylineno;
            ast_node *current = $1;
            while (current->next) {
                current = current->next;
            }
            current->next = new_decl;
        }
        $$ = $1;
    }
    ;

declaration_no_semicolon:
    type ID {
        printf("Declaracion (for init) simple: %s\n", $2);
        $$ = new_ast_declaration($1, $2, NULL);
        if ($$) $$->line = yylineno;
    }
    | type ID ASSIGN expression {
        printf("Declaracion (for init) con inicializacion: %s\n", $2);
        $$ = new_ast_declaration($1, $2, $4);
        if ($$) $$->line = yylineno;
    }
    ;

/* Inicialización del for: puede ser declaración, expresión o vacío */
for_init:
    declaration_no_semicolon { $$ = $1; }
    | expression { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

type:
    INT { 
        printf("Tipo int parser\n");
        $$ = new_ast_type("int"); 
        }
    | FLOAT { 
        printf("Tipo float parser\n");
        $$ = new_ast_type("float"); 
        }
    | DOUBLE { 
        printf("Tipo double parser\n");
        $$ = new_ast_type("double");
        }
    | VOID { 
        printf("Tipo void parser\n");
        $$ = new_ast_type("void"); 
        }
    | BOOLEAN { 
        printf("Tipo boolean parser\n");
        $$ = new_ast_type("boolean"); 
        }
    | CHAR { 
        printf("Tipo char parser\n");
        $$ = new_ast_type("char"); 
        }
    | STRING_TYPE { 
        printf("Tipo String parser\n"); 
         $$ = new_ast_type("String");
        }
    | ID { 
        /* Soportar tipos de usuario / clases como StringBuilder */
        printf("Tipo (identificador) parser: %s\n", $1);
        $$ = new_ast_type($1);
        }
    | INT LBRACKET RBRACKET {
        printf("Tipo int[] parser\n");
        $$ = new_ast_type("int[]");
    }
    | FLOAT LBRACKET RBRACKET {
        printf("Tipo float[] parser\n");
        $$ = new_ast_type("float[]");
    }
    | DOUBLE LBRACKET RBRACKET {
        printf("Tipo double[] parser\n");
        $$ = new_ast_type("double[]");
    }
    | STRING_TYPE LBRACKET RBRACKET {
        printf("Tipo String[] parser\n");
        $$ = new_ast_type("String[]");
    }
    /* ID[] -> crear tipo dinámico "Nombre[]" */
    | ID LBRACKET RBRACKET {
        char *tmp = malloc(strlen($1) + 3);
        snprintf(tmp, strlen($1) + 3, "%s[]", $1);
        printf("Tipo (identificador) array parser: %s\n", tmp);
        $$ = new_ast_type(tmp);
        free(tmp);
    }
    | type LBRACKET RBRACKET {
        if ($1 && $1->data.type_name) {
            size_t len = strlen($1->data.type_name) + 3;
            char *tmp = malloc(len);
            snprintf(tmp, len, "%s[]", $1->data.type_name);
            printf("Tipo multi-dimensional parser: %s\n", tmp);
            $$ = new_ast_type(tmp);
            free(tmp);
        } else {
            $$ = NULL;
        }
    }
    | INT_ARRAY { $$ = new_ast_type("int[]"); }
    | FLOAT_ARRAY { $$ = new_ast_type("float[]"); }
    | DOUBLE_ARRAY { $$ = new_ast_type("double[]"); }
    | STRING_ARRAY { $$ = new_ast_type("String[]"); }
    ;

assignment:
        ID ASSIGN expression SEMICOLON { 
        printf("Asignación: %s\n", $1);
        // Verificar compatibilidad en asignaciones
        if (!verificar_asignacion($1, $3)) {
            /* report_semantic_error(yylineno, 0, "Incompatibilidad de tipos en la asignación", "Global"); */
           /* Dejar la validación/report desde semantic_analysis(AST) */
        }
        $$ = new_ast_assign($1, $3); 
        if ($$) $$->line = yylineno;
    }
    | array_access ASSIGN expression SEMICOLON {
            printf("Asignación a elemento de arreglo\n");
            /* $1 es ast_node* devuelto por array_access (new_ast_array_access) */
            if ($1 && $1->type == AST_ARRAY_ACCESS) {
                /* crear nodo específico de asignación a array (implementar en ast.c si falta) */
                $$ = new_ast_array_assignment($1->data.array_access.array_name, $1->data.array_access.index, $3);
                if ($$) $$->line = yylineno;
            } else {
                $$ = NULL;
            }
    }
    | ID PLUS_ASSIGN expression SEMICOLON { 
        // x += y se convierte en x = x + y
        ast_node* var = new_ast_variable($1);
        ast_node* add_expr = new_ast_binary_op(OP_PLUS, var, $3);
        $$ = new_ast_assign($1, add_expr);
    }
    | ID MINUS_ASSIGN expression SEMICOLON { 
        // x -= y se convierte en x = x - y
        ast_node* var = new_ast_variable($1);
        ast_node* sub_expr = new_ast_binary_op(OP_MINUS, var, $3);
        $$ = new_ast_assign($1, sub_expr);
    }
    | ID MULT_ASSIGN expression SEMICOLON {
        // x *= y se convierte en x = x * y
        ast_node* var = new_ast_variable($1);
        ast_node* mul_expr = new_ast_binary_op(OP_MULT, var, $3);
        $$ = new_ast_assign($1, mul_expr);
    }
    | ID DIV_ASSIGN expression SEMICOLON {
        // x /= y se convierte en x = x / y
        ast_node* var = new_ast_variable($1);
        ast_node* div_expr = new_ast_binary_op(OP_DIV, var, $3);
        $$ = new_ast_assign($1, div_expr);
    }
    ;

expression:
    literal { $$ = $1; }
    | array_initialization { $$ = $1; }   /* <-- permite { ... } como expresión (inicializadores anidados) */
    | ID { $$ = new_ast_variable($1); }
    /* permitir asignaciones como expresión (para init/step de for) */
   | ID ASSIGN expression {
        printf("Asignación (expr) en contexto: %s = ...\n", $1);
       $$ = new_ast_assign($1, $3);
       if ($$) $$->line = yylineno;
    }
    | array_access ASSIGN expression {
        printf("Asignación a elemento de arreglo (expr) en contexto\n");
        if ($1 && $1->type == AST_ARRAY_ACCESS) {
            $$ = new_ast_array_assignment($1->data.array_access.array_name, $1->data.array_access.index, $3);
            if ($$) $$->line = yylineno;
        } else $$ = NULL;
    }
   | ID PLUS_ASSIGN expression {
        ast_node* var = new_ast_variable($1);
        ast_node* add_expr = new_ast_binary_op(OP_PLUS, var, $3);
        $$ = new_ast_assign($1, add_expr);
        if ($$) $$->line = yylineno;
    }
   | ID MINUS_ASSIGN expression {
        ast_node* var = new_ast_variable($1);
        ast_node* sub_expr = new_ast_binary_op(OP_MINUS, var, $3);
        $$ = new_ast_assign($1, sub_expr);
        if ($$) $$->line = yylineno;
    }
   | ID MULT_ASSIGN expression {
        ast_node* var = new_ast_variable($1);
        ast_node* mul_expr = new_ast_binary_op(OP_MULT, var, $3);
        $$ = new_ast_assign($1, mul_expr);
        if ($$) $$->line = yylineno;
    }
    | ID DIV_ASSIGN expression {
        ast_node* var = new_ast_variable($1);
        ast_node* div_expr = new_ast_binary_op(OP_DIV, var, $3);
        $$ = new_ast_assign($1, div_expr);
        if ($$) $$->line = yylineno;
    }
    | expression PLUS expression { $$ = new_ast_binary_op(OP_PLUS, $1, $3); }
    | expression MINUS expression { $$ = new_ast_binary_op(OP_MINUS, $1, $3); }
    | expression MULT expression { $$ = new_ast_binary_op(OP_MULT, $1, $3); }
    | expression DIV expression { $$ = new_ast_binary_op(OP_DIV, $1, $3); }
    | expression MOD expression { $$ = new_ast_binary_op(OP_MOD, $1, $3); }
    | expression EQUALS expression { $$ = new_ast_binary_op(OP_EQUALS, $1, $3); }
    | expression NOT_EQUALS expression { $$ = new_ast_binary_op(OP_NOT_EQUALS, $1, $3); }
    | expression LESS expression { $$ = new_ast_binary_op(OP_LESS, $1, $3); }
    | expression GREATER expression { $$ = new_ast_binary_op(OP_GREATER, $1, $3); }
    | expression LESS_EQUALS expression { $$ = new_ast_binary_op(OP_LESS_EQUALS, $1, $3); }
    | expression GREATER_EQUALS expression { $$ = new_ast_binary_op(OP_GREATER_EQUALS, $1, $3); }
    | expression AND expression { $$ = new_ast_binary_op(OP_AND, $1, $3); }
    | expression OR expression { $$ = new_ast_binary_op(OP_OR, $1, $3); }
    | expression DOT EQUALS_METHOD LPAREN expression RPAREN {$$ = new_ast_string_equals($1, $5);}
    | expression DOT ID LPAREN expression RPAREN {
        printf("Method call parser: receiver . %s(...)\n", $3);
        $$ = new_ast_method_call($1, $3, $5);
        if ($$) $$->line = yylineno;
    }
    | expression DOT ID LPAREN RPAREN {
       printf("Method call (no-arg) parser: receiver . %s()\n", $3);
        $$ = new_ast_method_call($1, $3, NULL);
        if ($$) $$->line = yylineno;
    }
    | ID DOT ID LPAREN expression RPAREN {
        printf("Static method call parser: %s.%s(...)\n", $1, $3);
        ast_node *recv = new_ast_variable($1);
        $$ = new_ast_method_call(recv, $3, $5);
        if ($$) $$->line = yylineno;
    }
    | ID DOT ID LPAREN RPAREN {
        printf("Static method call (no-arg) parser: %s.%s()\n", $1, $3);
        ast_node *recv = new_ast_variable($1);
        $$ = new_ast_method_call(recv, $3, NULL);
        if ($$) $$->line = yylineno;
    }

    |ID LPAREN expression_list RPAREN {
        printf("Function call parser: %s(...)\n", $1);
        $$ = new_ast_method_call(NULL, $1, $3);
        if ($$) $$->line = yylineno;
    }
    | ID LPAREN RPAREN {
        printf("Function call (no-arg) parser: %s()\n", $1);
        $$ = new_ast_method_call(NULL, $1, NULL);
        if ($$) $$->line = yylineno;
    }
    | expression DOT ID {
        /* Si el receptor es una variable, construiremos "var.field" como nombre */
        if ($1 && $1->type == AST_VARIABLE && $1->data.var_name) {
            size_t len = strlen($1->data.var_name) + 1 + strlen($3) + 1;
            char *tmp = malloc(len);
            snprintf(tmp, len, "%s.%s", $1->data.var_name, $3);
            $$ = new_ast_variable(tmp);
            free(tmp);
        } else {
            /* Fallback: usar solo el campo como variable */
            $$ = new_ast_variable($3);
        }
        if ($$) $$->line = yylineno;
    }
   | ID DOT ID {
        /* Caso común: ID.ID -> crear variable "id.field" */
        size_t len = strlen($1) + 1 + strlen($3) + 1;
        char *tmp = malloc(len);
        snprintf(tmp, len, "%s.%s", $1, $3);
        $$ = new_ast_variable(tmp);
        free(tmp);
        if ($$) $$->line = yylineno;
    }

    | expression DOT ID LPAREN expression_list RPAREN {
        printf("Method call parser: receiver . %s(...)\n", $3);
        $$ = new_ast_method_call($1, $3, $5);
        if ($$) $$->line = yylineno;
    }
    | ID DOT ID LPAREN expression_list RPAREN {
        printf("Static method call parser: %s.%s(...)\n", $1, $3);
        ast_node *recv = new_ast_variable($1);
        $$ = new_ast_method_call(recv, $3, $5);
        if ($$) $$->line = yylineno;
    }
    | NEW ID LPAREN RPAREN {
        printf("Object creation parser: new %s()\n", $2);
        $$ = new_ast_new_object($2); /* implementar en ast.c */
        if ($$) $$->line = yylineno;
    }
    | NEW type LBRACKET expression RBRACKET {
        printf("Array creation parser: new <type>[expr]\n");
        $$ = new_ast_new_array($2, $4); /* implementar en ast.c */
        if ($$) $$->line = yylineno;
    }
    | NEW type LBRACKET RBRACKET LBRACE expression_list RBRACE {
        printf("Array creation con inicialización: new <type>[] { ... }\n");
        $$ = new_ast_new_array_with_init($2, $6); /* implementar en ast.c */
        if ($$) $$->line = yylineno;
    }
    | NEW INT_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("int[]"), $6);
        if ($$) $$->line = yylineno;
    }
    | NEW FLOAT_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("float[]"), $6);
        if ($$) $$->line = yylineno;
    }
    | NEW DOUBLE_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("double[]"), $6);
        if ($$) $$->line = yylineno;
    }
    | NEW STRING_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("String[]"), $6);
        if ($$) $$->line = yylineno;
    }
    | NEW BOOLEAN_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("boolean[]"), $6);
        if ($$) $$->line = yylineno;
    }
    | NEW CHAR_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("char[]"), $6);
        if ($$) $$->line = yylineno;
    }
    | NEW INT_ARRAY LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("int[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NEW INT_ARRAY LBRACKET expression RBRACKET {
        $$ = new_ast_new_array(new_ast_type("int[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NEW FLOAT_ARRAY LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("float[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NEW FLOAT_ARRAY LBRACKET expression RBRACKET {
        $$ = new_ast_new_array(new_ast_type("float[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NEW DOUBLE_ARRAY LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("double[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NEW DOUBLE_ARRAY LBRACKET expression RBRACKET {
        $$ = new_ast_new_array(new_ast_type("double[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NEW STRING_ARRAY LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("String[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NEW STRING_ARRAY LBRACKET expression RBRACKET {
        $$ = new_ast_new_array(new_ast_type("String[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NEW BOOLEAN_ARRAY LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("boolean[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NEW BOOLEAN_ARRAY LBRACKET expression RBRACKET {
        $$ = new_ast_new_array(new_ast_type("boolean[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NEW CHAR_ARRAY LBRACE expression_list RBRACE {
        $$ = new_ast_new_array_with_init(new_ast_type("char[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NEW CHAR_ARRAY LBRACKET expression RBRACKET {
        $$ = new_ast_new_array(new_ast_type("char[]"), $4);
        if ($$) $$->line = yylineno;
    }
    | NOT expression { $$ = new_ast_unary_op(OP_NOT, $2); }
    | MINUS expression %prec NOT { $$ = new_ast_unary_op(OP_UMINUS, $2); } // Operador unario negativo
    | INCREMENT ID { $$ = new_ast_unary_op(OP_INCREMENT, new_ast_variable($2)); } // ++x
    | ID INCREMENT { $$ = new_ast_unary_op(OP_POST_INCREMENT, new_ast_variable($1)); } // x++
    | DECREMENT ID { $$ = new_ast_unary_op(OP_DECREMENT, new_ast_variable($2)); } // --x
    | ID DECREMENT { $$ = new_ast_unary_op(OP_POST_DECREMENT, new_ast_variable($1)); } // x--
    | array_access { $$ = $1; }
    | array_access { $$ = $1; }
    | LPAREN expression RPAREN { $$ = $2; }
    ;

literal:
    INT_LITERAL { 
        printf("Literal int parser\n");
        $$ = new_ast_int_literal($1); 
        }
    | FLOAT_LITERAL { 
        printf("Literal float parser\n");
        $$ = new_ast_float_literal($1); 
        }

    | DOUBLE_LITERAL { 
        printf("Literal double parser\n");
        $$ = new_ast_double_literal($1); 
        }

    | STRING_LITERAL { 
        printf("Literal string parser\n");
        $$ = new_ast_string_literal($1); 
     }
    | CHAR_LITERAL { 
        printf("Literal char parser\n");
        char c = (strlen($1) >= 3) ? $1[1] : '\0';
        $$ = new_ast_char_literal(c); 
        }
    | TRUE_TOKEN { 
        printf("Literal bool true parser\n");
        $$ = new_ast_bool_literal(1); 
        }
    | FALSE_TOKEN { 
        printf("Literal bool false parser\n");
        $$ = new_ast_bool_literal(0); 
        }
    | NULL_TOKEN { 
        printf("Literal null parser\n");
        $$ = new_ast_null_literal(); 
        }
    ;

if_statement:
    IF LPAREN expression RPAREN statement {
        printf("If statement sin else\n");
        $$ = new_ast_if($3, $5, NULL);
        if ($$) $$->line = yylineno;
    }
    | IF LPAREN expression RPAREN statement ELSE statement {
        printf("If statement con else\n");
        $$ = new_ast_if($3, $5, $7);
        if ($$) $$->line = yylineno;
    }
    ;

while_statement:
    WHILE LPAREN expression RPAREN statement { 
        printf("While statement parser\n");
        $$ = new_ast_while($3, $5); 
        }
    | DO statement WHILE LPAREN expression RPAREN SEMICOLON {
        printf("Do-While statement parser\n");
        $$ = new_ast_do_while($5, $2); 
        }
    ;

for_statement:
    FOR LPAREN for_init SEMICOLON expression SEMICOLON expression RPAREN statement { 
        printf("For statement parser\n");
        $$ = new_ast_for($3, $5, $7, $9); 
    }
    | FOR LPAREN type ID COLON expression RPAREN statement {
        printf("Enhanced for parsed\n");
        /* $3 = type (ast_node*), $4 = var name, $6 = collection expr, $8 = body */
        $$ = new_ast_foreach($3, $4, $6, $8);
        if ($$) $$->line = yylineno;
    }
    ;

return_statement:
    RETURN SEMICOLON {
        printf("Return statement (void) parser\n");
        $$ = new_ast_return(NULL);
        if ($$) $$->line = yylineno;
    }
    | RETURN expression SEMICOLON {
        printf("Return statement parser\n");
        $$ = new_ast_return($2);
        if ($$) $$->line = yylineno;
    }
    ;

switch_statement:
    SWITCH LPAREN expression RPAREN  { /* guardar expresión del switch para las secciones */ g_switch_expr = $3; }
    LBRACE switch_sections RBRACE    { 
        /* limpiar la variable temporal y devolver un compound con las secciones transformadas */
        $$ = new_ast_compound_stmt($7, NULL);
        if ($$) $$->line = yylineno;
        g_switch_expr = NULL;
    }
    ;


switch_sections:
    /* empty */ {
        $$ = NULL;
    }
    | switch_sections switch_section {
        /* append switch_section into a single chain so default becomes else of previous if */
        $$ = append_switch_case($1, $2);
    }
    ;

/* Cada case genera un AST_IF; DEFAULT devuelve directamente el bloque de statements (no if) */
switch_section:
    CASE literal COLON statement_list_opt {
        printf("Switch case parsed (transforming to if)\n");
        if (g_switch_expr == NULL) {
            /* protección: si no hay expr, devolver body tal cual */
            $$ = $4;
        } else {
            ast_node *cmp = new_ast_binary_op(OP_EQUALS, g_switch_expr, $2);
            $$ = new_ast_if(cmp, $4, NULL);
            if ($$) $$->line = yylineno;
        }
    }
    | DEFAULT COLON statement_list_opt {
        printf("Switch default parsed (as else)\n");
        /* default -> devolver el bloque de statements directamente; será enlazado como else por append_switch_case */
        $$ = $3;
    }
    ;

statement_list_opt:
    statement_list { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

array_declaration:
    type ID LBRACKET INT_LITERAL RBRACKET {
        printf("Declaración de arreglo: %s[%d]\n", $2, $4); 
        ast_node *size_node = new_ast_int_literal($4);
        $$ = new_ast_array_declaration($1, $2, size_node);
    }
    | type ID LBRACKET INT_LITERAL RBRACKET ASSIGN array_initialization {
        printf("Declaración de arreglo con inicialización: %s\n", $2);
        ast_node *size_node = new_ast_int_literal($4);
        $$ = new_ast_array_declaration_with_init($1, $2, size_node, $7);
    }
    ;

array_initialization:
    LBRACE expression_list RBRACE {
        printf("Inicialización de arreglo con valores\n");
        $$ = new_ast_array_init($2);
    }
    ;

expression_list:
    expression { $$ = $1; }
    | expression_list COMMA expression {
        if ($1) {
            ast_node *current = $1;
            while (current->next) {
                current = current->next;
            }
            current->next = $3;
            $$ = $1;
        } else {
            $$ = $3;
        }
    }
    ;
array_access:
    ID LBRACKET expression RBRACKET {
        printf("Acceso a arreglo: %s[]\n", $1);
        $$ = new_ast_array_access($1, $3);
    }
    ;


%%

/********************** SECCIÓN DE CÓDIGO C **********************/

void yyerror(const char *s) {
    fprintf(stderr, "Error sintáctico en línea %d: %s\n", yylineno, s);
    fprintf(stderr, "Token inesperado: '%s'\n", yytext);
    
    // enviar este error a la GUI aquí
    report_syntax_error(yylineno, 0, s, yytext);
    reset_lexer();
}

// Función para reiniciar el estado del lexer
void reset_lexer(void) {
    // Limpia cualquier estado residual del lexer
    yyrestart(NULL);
    // Reinicia las variables de entrada desde memoria
    cleanup_lexer();
}

// Función para ejecutar el parser desde código externo
int parse_from_string(const char *input) {
    // Limpiar cualquier análisis anterior
    if (root) {
        // Liberar el AST anterior si existe
        free_ast(root);
        root = NULL;
    }
    
    // Configurar la entrada desde memoria
    set_input_string(input);
    
    // Reiniciar el estado del parser y lexer
    yyrestart(NULL);
    reset_lexer();
    
    // Ejecutar el análisis
    int result = yyparse();
    
    return result;
}

// Función para obtener el AST resultante
ast_node* get_ast_root(void) {
    return root;
}

// Función para limpiar completamente el parser
void cleanup_parser(void) {
    if (root) {
        free_ast(root);
        root = NULL;
    }
    cleanup_lexer();
}