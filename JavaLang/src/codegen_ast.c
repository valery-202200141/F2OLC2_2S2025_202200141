#include "../include/codegen_ast.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>


static void sanitize_name(const char *src, char *dst, size_t n);


// --------- Entorno de variables locales ----------
typedef enum { VT_INT=0, VT_BOOL=1, VT_FLOAT=2, VT_DOUBLE=3, VT_STRING=4 } VarType;

typedef struct { 
    char name[64]; 
    int  off;           // offset relativo a x29 (negativo)
    VarType vtype;      // tipo del local
} LocalVar;


typedef struct {
    LocalVar vars[256];
    int count;
    int local_bytes;     // bytes reservados en el frame (múltiplos de 16)
    int scope_mark[256]; // pila de marcas de scope
    int sp;              // puntero de pila de scopes
} VarEnv;

// Inicializa entorno (si no existe ya)
static void env_init(VarEnv *e){
    if (!e) return;
    e->count = 0;
    e->local_bytes = 0;
    e->sp = 0; // init stack de scopes
}

static void env_push_scope(VarEnv *e){
    if (e->sp < (int)(sizeof(e->scope_mark)/sizeof(e->scope_mark[0]))) {
        e->scope_mark[e->sp++] = e->count;
    }
}

static int env_pop_scope(VarEnv *e, CodegenARM64 *cg){
    (void)cg;
    if (e->sp > 0) {
        int from = e->scope_mark[--e->sp];
        e->count = from;
    }
    return 0;
}

// Declara int local y guarda nombre normalizado
static int env_decl_int(VarEnv *e, CodegenARM64 *cg, const char *raw_name){
    if (!e || e->count >= 256) return -1;
    char key[64]; sanitize_name(raw_name ? raw_name : "", key, sizeof key);

    e->local_bytes += 16;
    int off = -e->local_bytes; // offsets negativos relativos a x29
    strncpy(e->vars[e->count].name, key, sizeof(e->vars[e->count].name)-1);
    e->vars[e->count].name[sizeof(e->vars[e->count].name)-1] = '\0';
    e->vars[e->count].off = off;
    e->count++;

    fprintf(cg->out, "    // decl %s @ [x29,#%d]\n", key[0]?key:"(anon)", off);
    return off;
}


// Mapea el type_name del AST a VarType
static VarType map_ast_type(ast_node *type_node){
    if (!type_node || !type_node->data.type_name) return VT_INT;
    const char *t = type_node->data.type_name;
    if      (!strcmp(t,"int"))     return VT_INT;
    else if (!strcmp(t,"boolean")) return VT_BOOL;
    else if (!strcmp(t,"float"))   return VT_DOUBLE; // simplificación: tratar float como double
    else if (!strcmp(t,"double"))  return VT_DOUBLE;
    else if (!strcmp(t,"String"))  return VT_STRING;
    return VT_INT;
}
// Emite una literal de cadena y devuelve etiqueta
static void emit_cstr_asm_escaped(FILE *out, const char *s); // ya definida al final

static void emit_string_label(CodegenARM64 *cg, const char *raw, char out_label[32]){
    // quita comillas del literal del AST
    char buf[1024]; size_t j=0;
    for (size_t i=0; raw && raw[i] && j+1<sizeof(buf); ++i){
        if (raw[i] != '"') buf[j++] = raw[i];
    }
    buf[j]='\0';

    snprintf(out_label, 32, "slit_%u", ++cg->str_count);
    fprintf(cg->out, ".data\n");
    fprintf(cg->out, "%s: .asciz \"", out_label);
    emit_cstr_asm_escaped(cg->out, buf);
    fputs("\"\n", cg->out);
    fprintf(cg->out, ".text\n");
}

// Emite una constante double y devuelve etiqueta
static void emit_double_label(CodegenARM64 *cg, double v, char out_label[32]){
    snprintf(out_label, 32, "dcon_%u", ++cg->str_count);
    fprintf(cg->out, ".data\n");
    fprintf(cg->out, "%s: .double %.17g\n", out_label, v);
    fprintf(cg->out, ".text\n");
}
// Busca offset y tipo por nombre
static int env_find(VarEnv *e, const char *name);
static int env_offset_strict(VarEnv *e, CodegenARM64 *cg, const char *raw_name); // ya definida
static VarType env_type(VarEnv *e, const char *raw_name){
    if (!e || !raw_name) return VT_INT;
    char key[64]; sanitize_name(raw_name, key, sizeof key);
    for (int i=e->count-1;i>=0;--i){
        if (!strcmp(e->vars[i].name, key)) return e->vars[i].vtype;
    }
    return VT_INT;
}

// Declaración tipada (sigue reservando en bloques de 16 para simpleza)
static int env_decl_typed(VarEnv *e, CodegenARM64 *cg, const char *raw_name, VarType vt){
    if (!e || e->count >= 256) return -1;
    char key[64]; sanitize_name(raw_name ? raw_name : "", key, sizeof key);

    e->local_bytes += 16;
    int off = -e->local_bytes;

    LocalVar *lv = &e->vars[e->count++];
    strncpy(lv->name, key, sizeof(lv->name)-1);
    lv->name[sizeof(lv->name)-1] = '\0';
    lv->off = off;
    lv->vtype = vt;

    fprintf(cg->out, "    // decl %s @ [x29,#%d]\n", key[0]?key:"(anon)", off);
    return off;
}


// Convierte a consulta de tipo real
static int is_intish(VarEnv *env, ast_node *n){
    if (!n) return 0;
    switch(n->type){
        case AST_INT_LITERAL:
        case AST_BOOL_LITERAL:
            return 1;
        case AST_VARIABLE: {
            // No tratar String como int
            return env_type(env, n->data.var_name) != VT_STRING;
        }
        case AST_BINARY_OP:
            // Si es PLUS y cualquiera lado es String, no es int-ish
            if (n->data.op.op == OP_PLUS) {
                int Ls = (n->data.op.left  && n->data.op.left->type  == AST_VARIABLE && env_type(env, n->data.op.left->data.var_name)  == VT_STRING) ||
                         (n->data.op.left  && n->data.op.left->type  == AST_STRING_LITERAL);
                int Rs = (n->data.op.right && n->data.op.right->type == AST_VARIABLE && env_type(env, n->data.op.right->data.var_name) == VT_STRING) ||
                         (n->data.op.right && n->data.op.right->type == AST_STRING_LITERAL);
                return !(Ls || Rs);
            }
            return 1; // otros binarios: trátalos como numéricos/booleanos
        case AST_UNARY_OP:
            return 1;
        default: return 0;
    }
}

// Sanea nombre: quita espacios/tab/newline
static void ident_norm(char *dst, size_t ndst, const char *src){
    size_t j = 0;
    for (size_t i=0; src && src[i] && j+1<ndst; ++i){
        unsigned char c = (unsigned char)src[i];
        if (!isspace(c)) dst[j++] = c;   // quita espacios/tab/newline ASCII
    }
    dst[j] = '\0';
}

// Busca índice por nombre, usando el mismo saneo con el que se almacena
static int env_find(VarEnv *e, const char *name){
    char key[64]; sanitize_name(name ? name : "", key, sizeof key);
    if (!key[0]) return -1;
    for (int i = e->count - 1; i >= 0; --i)
        if (strcmp(e->vars[i].name, key) == 0) return i;
    return -1;
}

static int count_decls_in_node(ast_node *n);
static int count_decls_in_list(ast_node *n){
    int c = 0;
    for (ast_node *cur=n; cur; cur=cur->next) c += count_decls_in_node(cur);
    return c;
}
static int count_decls_in_node(ast_node *n){
    if (!n) return 0;
    int c = 0;
    switch (n->type){
        case AST_DECLARATION: c += 1; break;
        case AST_COMPOUND_STMT:
            c += count_decls_in_list(n->data.compound.statement_list); break;
        case AST_IF:
            c += count_decls_in_node(n->data.if_stmt.condition);
            c += count_decls_in_node(n->data.if_stmt.then_branch);
            c += count_decls_in_node(n->data.if_stmt.else_branch);
            break;
        case AST_WHILE:
            c += count_decls_in_node(n->data.while_stmt.condition);
            c += count_decls_in_node(n->data.while_stmt.body);
            break;
        case AST_FOR:
            c += count_decls_in_node(n->data.for_stmt.init);
            c += count_decls_in_node(n->data.for_stmt.condition);
            c += count_decls_in_node(n->data.for_stmt.increment);
            c += count_decls_in_node(n->data.for_stmt.body);
            break;
        case AST_PROGRAM:
        case AST_MAIN_FUNCTION:
            c += count_decls_in_node(n->data.function_def.body);
            break;
        default: break;
    }
    return c;
}

static void dump_hex(const char *tag, const char *s){
    if(!s){ fprintf(stderr,"%s: <null>\n",tag); return; }
    fprintf(stderr,"%s: '", tag);
    for (const unsigned char *p=(const unsigned char*)s; *p; ++p) fputc(*p, stderr);
    fprintf(stderr,"'  [");
    for (const unsigned char *p=(const unsigned char*)s; *p; ++p){
        fprintf(stderr,"%s%02X", (p==(const unsigned char*)s)?"":" ", *p);
    }
    fprintf(stderr,"]\n");
}

static int env_offset(VarEnv *e, const char *name){ int i=env_find(e,name); return i>=0? e->vars[i].off : -1; }

// Añade un find/offset robusto
// Lookup robusto: normalizado primero, luego raw como fallback (por si algo quedó sin normalizar)
static int env_offset_strict(VarEnv *e, CodegenARM64 *cg, const char *raw_name){
    if (!e || !raw_name) return -1;
    char key[64]; sanitize_name(raw_name, key, sizeof key);

    for (int i = e->count - 1; i >= 0; --i){
        if (strcmp(e->vars[i].name, key) == 0) return e->vars[i].off;
    }
    for (int i = e->count - 1; i >= 0; --i){
        if (strcmp(e->vars[i].name, raw_name) == 0) return e->vars[i].off;
    }

    // Diagnóstico visible en el .s
    fprintf(cg->out, "    // LOOKUP FAIL raw='%s' san='%s' (count=%d)\n", raw_name, key, e->count);
    for (int i=0;i<e->count;++i){
        fprintf(cg->out, "    //   [%d] name='%s' off=%d\n", i, e->vars[i].name, e->vars[i].off);
    }
    return -1;
}


static inline int align16(int n){ return (n + 15) & ~15; }


static void env_dump(CodegenARM64 *cg, VarEnv *e, const char *tag){
    if (!cg || !e) return;
    fprintf(cg->out, "    // ENV DUMP [%s] count=%d local_bytes=%d\n",
            tag?tag:"", e->count, e->local_bytes);
    for (int i=0;i<e->count;i++){
        fprintf(cg->out, "    //   #%d name='%s' off=%d\n", i, e->vars[i].name, e->vars[i].off);
    }
}

static int env_index(VarEnv *e, const char *raw_name){
    if (!e || !raw_name) return -1;
    char key[64]; sanitize_name(raw_name, key, sizeof key);
    for (int i=e->count-1;i>=0;--i){
        if (!strcmp(e->vars[i].name, key)) return i;
    }
    return -1;
}

static void env_set_type(VarEnv *e, const char *raw_name, VarType vt){
    int idx = env_index(e, raw_name);
    if (idx >= 0) e->vars[idx].vtype = vt;
}

// Normaliza: quita espacios/control y deja [A-Za-z0-9_]
static void sanitize_name(const char *src, char *dst, size_t n){
    size_t j=0;
    if (!dst || n==0){ return; }
    if (!src){ dst[0]='\0'; return; }
    for (size_t i=0; src[i] && j+1<n; ++i){
        unsigned char c = (unsigned char)src[i];
        if (isspace(c)) continue;
        if ((c>='A' && c<='Z') || (c>='a' && c<='z') || (c>='0' && c<='9') || c=='_'){
            dst[j++] = (char)c;
        }
        // ignora otros
    }
    dst[j] = '\0';
}


static int is_print_like_call(ast_node *call){
    if (!call || call->type != AST_METHOD_CALL) return 0;
    const char *m = call->data.method_call.method_name;
    if (!m) return 0;
    return strcmp(m, "println") == 0 || strcmp(m, "print") == 0;
}


// Convención: expr int/bool deja resultado en w0
static void gen_expr(CodegenARM64 *cg, VarEnv *env, ast_node *n);

// Convención: stmt no deja nada
static void gen_stmt(CodegenARM64 *cg, VarEnv *env, ast_node *s);

static int gen_print_plus_str_int(CodegenARM64 *cg, VarEnv *env, ast_node *e);

//EVITAR DECLARACIONES IMPLÍCITAS
static int gen_print_concat(CodegenARM64 *cg, VarEnv *env, ast_node *e);
static int get_lit_text(ast_node *n, char *out, size_t nout);


static int is_intish_simple(ast_node *n){
    if (!n) return 0;
    switch(n->type){
        case AST_INT_LITERAL:
        case AST_BOOL_LITERAL:
        case AST_VARIABLE:
        case AST_BINARY_OP:
        case AST_UNARY_OP:
            return 1;
        default: return 0;
    }
}

static void gen_print_int(CodegenARM64 *cg){
    // printf("%d\n", w0)
    // 1) preserva el valor en w1 ANTES de clobber x0
    fprintf(cg->out, "    mov  w1, w0\n");
    // 2) ahora puedes cargar el formato en x0
    fprintf(cg->out, "    adrp x0, fmt_int\n");
    fprintf(cg->out, "    add  x0, x0, :lo12:fmt_int\n");
    fprintf(cg->out, "    bl   printf\n");
}

static void gen_print_cstr(CodegenARM64 *cg, const char *s){
    // usar literal + printf("%s\n")
    codegen_arm64_println_string(cg, s ? s : "");
}

// ...existing code...
static void gen_binop(CodegenARM64 *cg, VarEnv *env, ast_node *n){
    // Short-circuit primero: NO evalúes right por defecto
    if (n->data.op.op == OP_AND){
        // eval left -> w0 y normaliza
        gen_expr(cg, env, n->data.op.left);
        fprintf(cg->out, "    and w0, w0, #1\n");
        char Lend[32]; snprintf(Lend,sizeof Lend,".Land_%u", ++cg->lbl_count);
        fprintf(cg->out, "    cbz w0, %s\n", Lend);
        // solo si left true, eval right -> w0 y normaliza
        gen_expr(cg, env, n->data.op.right);
        fprintf(cg->out, "    and w0, w0, #1\n");
        fprintf(cg->out, "%s:\n", Lend);
        return;
    }
    if (n->data.op.op == OP_OR){
        // eval left -> w0 y normaliza
        gen_expr(cg, env, n->data.op.left);
        fprintf(cg->out, "    and w0, w0, #1\n");
        char Ltrue[32]; snprintf(Ltrue,sizeof Ltrue,".Lor_true_%u", ++cg->lbl_count);
        char Lend [32]; snprintf(Lend ,sizeof Lend ,".Lor_end_%u",  cg->lbl_count);
        fprintf(cg->out, "    cbnz w0, %s\n", Ltrue);
        // solo si left false, eval right -> w0 y normaliza
        gen_expr(cg, env, n->data.op.right);
        fprintf(cg->out, "    and w0, w0, #1\n");
        fprintf(cg->out, "    b %s\n", Lend);
        fprintf(cg->out, "%s:\n", Ltrue);
        fprintf(cg->out, "    mov w0, #1\n");
        fprintf(cg->out, "%s:\n", Lend);
        return;
    }

    // Resto de operadores: left -> w1 ; right -> w0 ; resultado en w0
    gen_expr(cg, env, n->data.op.left);           // -> w0
    fprintf(cg->out, "    mov w1, w0\n");         // w1 = left
    gen_expr(cg, env, n->data.op.right);          // -> w0 (right)

    switch(n->data.op.op){
        case OP_PLUS:   fprintf(cg->out, "    add w0, w1, w0\n"); break;
        case OP_MINUS:  fprintf(cg->out, "    sub w0, w1, w0\n"); break;
        case OP_MULT:   fprintf(cg->out, "    mul w0, w1, w0\n"); break;
        case OP_DIV:    fprintf(cg->out, "    sdiv w0, w1, w0\n"); break;
        case OP_MOD:
            fprintf(cg->out, "    sdiv w9, w1, w0\n");
            fprintf(cg->out, "    msub w0, w9, w0, w1\n");
            break;

        case OP_EQUALS:         cg_cmp_int(cg, "==", "w1", "w0"); break;
        case OP_NOT_EQUALS:     cg_cmp_int(cg, "!=", "w1", "w0"); break;
        case OP_LESS:           cg_cmp_int(cg, "<",  "w1", "w0"); break;
        case OP_LESS_EQUALS:    cg_cmp_int(cg, "<=", "w1", "w0"); break;
        case OP_GREATER:        cg_cmp_int(cg, ">",  "w1", "w0"); break;
        case OP_GREATER_EQUALS: cg_cmp_int(cg, ">=", "w1","w0"); break;

        default:
            fprintf(cg->out, "    mov w0, wzr\n");
    }
}



static void gen_expr(CodegenARM64 *cg, VarEnv *env, ast_node *n){
    if (!n){ fprintf(cg->out,"    mov w0, wzr\n"); return; }
        switch(n->type){
        case AST_INT_LITERAL:
            fprintf(cg->out, "    mov w0, #%d\n", n->data.int_value);
            break;
        case AST_BOOL_LITERAL:
            fprintf(cg->out, "    mov w0, #%d\n", n->data.bool_value ? 1 : 0);
            break;
        case AST_VARIABLE: {
            const char *raw = n->data.var_name ? n->data.var_name : "";
            char key[64]; sanitize_name(raw, key, sizeof key);
            fprintf(cg->out, "    // CG_VAR raw='%s' san='%s'\n", raw, key);  // <--- MARCA

            int off = env_offset_strict(env, cg, raw);
            if (off == -1){
                fprintf(cg->out,"    // WARN: var not found '%s'\n", raw);
                fprintf(cg->out,"    mov w0, wzr\n");
            } else {
                fprintf(cg->out,"    // load %s @ [x29,#%d]\n", raw, off);
                cg_load_local_w(cg, off, "w0");
            }
            break;
        }
        case AST_BINARY_OP:
            gen_binop(cg, env, n);
            break;
        case AST_UNARY_OP:
            if (n->data.op.op == OP_NOT){
                gen_expr(cg, env, n->data.op.left);
                cg_logical_not(cg);
            } else if (n->data.op.op == OP_UMINUS){
                gen_expr(cg, env, n->data.op.left);
                fprintf(cg->out, "    neg w0, w0\n");
            } else if (
                n->data.op.op == OP_INCREMENT       || n->data.op.op == OP_POST_INCREMENT ||
                n->data.op.op == OP_DECREMENT       || n->data.op.op == OP_POST_DECREMENT
            ){
                ast_node *v = n->data.op.left;
                if (v && v->type == AST_VARIABLE){
                    int off = env_offset_strict(env, cg, v->data.var_name);
                    if (off == -1){
                        fprintf(cg->out,"    // WARN: ++/-- var not found\n");
                        fprintf(cg->out,"    mov w0, wzr\n");
                        break;
                    }
                    // w9 = old value
                    cg_load_local_w(cg, off, "w9");
                    // w10 = updated
                    if (n->data.op.op == OP_INCREMENT || n->data.op.op == OP_POST_INCREMENT)
                        fprintf(cg->out, "    add w10, w9, #1\n");
                    else
                        fprintf(cg->out, "    sub w10, w9, #1\n");
                    cg_store_local_w(cg, off, "w10");
                    // valor de la expresión
                    if (n->data.op.op == OP_INCREMENT || n->data.op.op == OP_DECREMENT)
                        fprintf(cg->out, "    mov w0, w10\n");  // pre-: devuelve nuevo
                    else
                        fprintf(cg->out, "    mov w0, w9\n");   // post-: devuelve viejo
                } else {
                    gen_expr(cg, env, n->data.op.left);
                }
            } else {
                gen_expr(cg, env, n->data.op.left);
            }
            break;
        default:
            fprintf(cg->out,"    mov w0, wzr\n");
    }
}


static void gen_block(CodegenARM64 *cg, VarEnv *env, ast_node *list){
    env_push_scope(env);
    for (ast_node *cur=list; cur; cur=cur->next){
        gen_stmt(cg, env, cur);
    }
    env_pop_scope(env, cg);
}

static void gen_stmt(CodegenARM64 *cg, VarEnv *env, ast_node *s){
    if (!s) return;
    switch(s->type){
        case AST_DECLARATION: {
            VarType vt = map_ast_type(s->data.declaration.var_type);
            int off = env_decl_typed(env, cg, s->data.declaration.var_name, vt);

            if (s->data.declaration.value){
                ast_node *v = s->data.declaration.value;
                if (vt == VT_STRING){
                    if (v->type == AST_STRING_LITERAL){
                        char lab[32]; emit_string_label(cg, v->data.string_value, lab);
                        fprintf(cg->out, "    adrp x0, %s\n    add  x0, x0, :lo12:%s\n", lab, lab);
                        cg_store_local_x(cg, off, "x0");
                    } else if (v->type == AST_VARIABLE && env_type(env, v->data.var_name)==VT_STRING){
                        int rhs_off = env_offset_strict(env, cg, v->data.var_name);
                        if (rhs_off != -1){ cg_load_local_x(cg, rhs_off, "x0"); cg_store_local_x(cg, off, "x0"); }
                    } else {
                        // default: empty string
                        char lab[32]; emit_string_label(cg, "\"\"", lab);
                        fprintf(cg->out, "    adrp x0, %s\n    add  x0, x0, :lo12:%s\n", lab, lab);
                        cg_store_local_x(cg, off, "x0");
                    }
                } else if (vt == VT_DOUBLE){
                    if (v->type == AST_DOUBLE_LITERAL || v->type == AST_FLOAT_LITERAL){
                        double dv = (v->type==AST_DOUBLE_LITERAL)? v->data.double_value : (double)v->data.float_value;
                        char dlab[32]; emit_double_label(cg, dv, dlab);
                        fprintf(cg->out, "    adrp x1, %s\n    add  x1, x1, :lo12:%s\n", dlab, dlab);
                        fprintf(cg->out, "    ldr  d0, [x1]\n");
                        cg_store_local_d(cg, off, "d0");
                    } else if (v->type == AST_VARIABLE && env_type(env, v->data.var_name)==VT_DOUBLE){
                        int rhs_off = env_offset_strict(env, cg, v->data.var_name);
                        if (rhs_off != -1){ cg_load_local_d(cg, rhs_off, "d0"); cg_store_local_d(cg, off, "d0"); }
                    } else {
                        // default 0.0
                        char dlab[32]; emit_double_label(cg, 0.0, dlab);
                        fprintf(cg->out, "    adrp x1, %s\n    add  x1, x1, :lo12:%s\n", dlab, dlab);
                        fprintf(cg->out, "    ldr  d0, [x1]\n");
                        cg_store_local_d(cg, off, "d0");
                    }
                } else { // int/bool por ahora usan enteros
                    gen_expr(cg, env, v);
                    cg_store_local_w(cg, off, "w0");
                }
            } else {
                // sin inicializador -> defaults
                if (vt == VT_STRING){
                    char lab[32]; emit_string_label(cg, "\"\"", lab);
                    fprintf(cg->out, "    adrp x0, %s\n    add  x0, x0, :lo12:%s\n", lab, lab);
                    cg_store_local_x(cg, off, "x0");
                } else if (vt == VT_DOUBLE){
                    char dlab[32]; emit_double_label(cg, 0.0, dlab);
                    fprintf(cg->out, "    adrp x1, %s\n    add  x1, x1, :lo12:%s\n", dlab, dlab);
                    fprintf(cg->out, "    ldr  d0, [x1]\n");
                    cg_store_local_d(cg, off, "d0");
                } else {
                    fprintf(cg->out, "    mov w0, wzr\n");
                    cg_store_local_w(cg, off, "w0");
                }
            }
            env_dump(cg, env, "after-decl-store");
            break;
        }
        case AST_ASSIGNMENT: {
            env_dump(cg, env, "before-assign");
            const char *lhs = s->data.assignment.var_name ? s->data.assignment.var_name : "";
            int offL = env_offset_strict(env, cg, lhs);
            if (offL == -1){ fprintf(cg->out, "    // ERROR: var not found for assign '%s'\n", lhs); break; }

            VarType vtL = env_type(env, lhs);
            ast_node *v = s->data.assignment.value;

            // PROMOCIÓN DINÁMICA A STRING
            if (v->type == AST_STRING_LITERAL) {
                char lab[32]; emit_string_label(cg, v->data.string_value, lab);
                fprintf(cg->out, "    adrp x0, %s\n    add  x0, x0, :lo12:%s\n", lab, lab);
                cg_store_local_x(cg, offL, "x0");
                env_set_type(env, lhs, VT_STRING);
                env_dump(cg, env, "after-assign (promoted STRING literal)");
                break;
            }
            if (v->type == AST_VARIABLE && env_type(env, v->data.var_name) == VT_STRING) {
                int offR = env_offset_strict(env, cg, v->data.var_name);
                if (offR != -1){ cg_load_local_x(cg, offR, "x0"); cg_store_local_x(cg, offL, "x0"); }
                env_set_type(env, lhs, VT_STRING);
                env_dump(cg, env, "after-assign (promoted STRING var)");
                break;
            }

            // PROMOCIÓN DINÁMICA A DOUBLE (incluye float)
            if (v->type == AST_DOUBLE_LITERAL || v->type == AST_FLOAT_LITERAL ||
                (v->type == AST_VARIABLE && env_type(env, v->data.var_name) == VT_DOUBLE)) {

                if (v->type == AST_VARIABLE) {
                    int offR = env_offset_strict(env, cg, v->data.var_name);
                    if (offR != -1){ cg_load_local_d(cg, offR, "d0"); }
                } else {
                    double dv = (v->type==AST_DOUBLE_LITERAL)? v->data.double_value : (double)v->data.float_value;
                    char dlab[32]; emit_double_label(cg, dv, dlab);
                    fprintf(cg->out, "    adrp x1, %s\n    add  x1, x1, :lo12:%s\n", dlab, dlab);
                    fprintf(cg->out, "    ldr  d0, [x1]\n");
                }
                cg_store_local_d(cg, offL, "d0");
                env_set_type(env, lhs, VT_DOUBLE);
                env_dump(cg, env, "after-assign (promoted DOUBLE)");
                break;
            }

            // Si el LHS ya es STRING/DOUBLE, mantener caminos existentes
            if (vtL == VT_STRING){
                if (v->type == AST_STRING_LITERAL){
                    char lab[32]; emit_string_label(cg, v->data.string_value, lab);
                    fprintf(cg->out, "    adrp x0, %s\n    add  x0, x0, :lo12:%s\n", lab, lab);
                    cg_store_local_x(cg, offL, "x0");
                } else if (v->type == AST_VARIABLE && env_type(env, v->data.var_name)==VT_STRING){
                    int offR = env_offset_strict(env, cg, v->data.var_name);
                    if (offR != -1){ cg_load_local_x(cg, offR, "x0"); cg_store_local_x(cg, offL, "x0"); }
                } else {
                    char lab[32]; emit_string_label(cg, "\"\"", lab);
                    fprintf(cg->out, "    adrp x0, %s\n    add  x0, x0, :lo12:%s\n", lab, lab);
                    cg_store_local_x(cg, offL, "x0");
                }
                env_dump(cg, env, "after-assign (STRING)");
                break;
            } else if (vtL == VT_DOUBLE){
                if (v->type == AST_VARIABLE && env_type(env, v->data.var_name)==VT_DOUBLE){
                    int offR = env_offset_strict(env, cg, v->data.var_name);
                    if (offR != -1){ cg_load_local_d(cg, offR, "d0"); cg_store_local_d(cg, offL, "d0"); }
                } else {
                    double dv = 0.0;
                    if (v->type == AST_DOUBLE_LITERAL) dv = v->data.double_value;
                    else if (v->type == AST_FLOAT_LITERAL) dv = (double)v->data.float_value;
                    char dlab[32]; emit_double_label(cg, dv, dlab);
                    fprintf(cg->out, "    adrp x1, %s\n    add  x1, x1, :lo12:%s\n", dlab, dlab);
                    fprintf(cg->out, "    ldr  d0, [x1]\n");
                    cg_store_local_d(cg, offL, "d0");
                }
                env_dump(cg, env, "after-assign (DOUBLE)");
                break;
            }

            // Default int/bool
            gen_expr(cg, env, v);
            cg_store_local_w(cg, offL, "w0");
            env_dump(cg, env, "after-assign");
            break;
        }

        case AST_IF: {
            gen_expr(cg, env, s->data.if_stmt.condition);
            char Lelse[32], Lend[32];
            cg_if_begin(cg, Lelse, sizeof Lelse, Lend, sizeof Lend);
            if (s->data.if_stmt.then_branch) gen_stmt(cg, env, s->data.if_stmt.then_branch);
            if (s->data.if_stmt.else_branch){
                cg_if_else(cg, Lelse, Lend);
                gen_stmt(cg, env, s->data.if_stmt.else_branch);
            } else {
                cg_label(cg, Lelse);
            }
            cg_if_end(cg, Lend);
            break;
        }
        case AST_WHILE: {
            char Lcond[32], Lend[32];
            cg_while_begin(cg, Lcond, sizeof Lcond, Lend, sizeof Lend);
            // PROTEGER: si no hay condición, fuerza false para no colgar
            if (s->data.while_stmt.condition) {
                gen_expr(cg, env, s->data.while_stmt.condition);
                // normaliza a 0/1
                fprintf(cg->out, "    and w0, w0, #1\n");
            } else {
                fprintf(cg->out, "    mov w0, #0\n");
            }
            cg_while_check(cg, Lend);
            if (s->data.while_stmt.body) gen_stmt(cg, env, s->data.while_stmt.body);
            cg_while_end(cg, Lcond, Lend);
            break;
        }
        case AST_FOR: {
            if (s->data.for_stmt.init) gen_stmt(cg, env, s->data.for_stmt.init);
            char Lcond[32], Lstep[32], Lend[32];
            cg_for_begin(cg, Lcond, sizeof Lcond, Lstep, sizeof Lstep, Lend, sizeof Lend);
            if (s->data.for_stmt.condition){
                gen_expr(cg, env, s->data.for_stmt.condition);
                cg_while_check(cg, Lend);
            }
            if (s->data.for_stmt.body) gen_stmt(cg, env, s->data.for_stmt.body);
            cg_for_goto_step(cg, Lstep, Lcond);
            cg_for_step_label(cg, Lstep);
            if (s->data.for_stmt.increment) gen_stmt(cg, env, s->data.for_stmt.increment);
            cg_for_end(cg, Lcond, Lend);
            break;
        }

        /*case AST_SWITCH: {
            // evalúa selector -> w0
            gen_expr(cg, env, s->data.switch_stmt.expr);

            char Lend[32], Ldef[32];
            cg_switch_begin(cg, Lend, sizeof Lend, Ldef, sizeof Ldef);

            // Emite comparaciones por cada case (no default)
            for (ast_node *c = s->data.switch_stmt.cases; c; c = c->next) {
                if (c->data.case_stmt.is_default) continue;
                // value inmediato (si es literal) o eval expr a w0 y usa registro temporal si tu helper lo requiere
                // Aquí asumimos literal entero:
                char Lcase[32]; snprintf(Lcase, sizeof Lcase, ".Lcase_%u", ++cg->lbl_count);
                cg_switch_case_imm(cg, evaluate_expression(c->data.case_stmt.value), Lcase);
                cg_label(cg, Lcase);
                if (c->data.case_stmt.body) gen_stmt(cg, env, c->data.case_stmt.body);
                // fall-through (no jump) hasta que un break emita salto a Lend
            }

            // default: si existe, etiquétalo; si no, usa label ya creado
            int has_default = 0;
            for (ast_node *c = s->data.switch_stmt.cases; c; c = c->next) {
                if (c->data.case_stmt.is_default) {
                    has_default = 1;
                    cg_label(cg, Ldef);
                    if (c->data.case_stmt.body) gen_stmt(cg, env, c->data.case_stmt.body);
                    break;
                }
            }
            if (!has_default) cg_label(cg, Ldef);

            cg_switch_goto_end(cg, Lend);
            cg_label(cg, Lend);
            break;
        }*/

        case AST_BREAK:    cg_emit_break(cg); break;
        case AST_CONTINUE: cg_emit_continue(cg); break;
        case AST_RETURN:   cg_return_void(cg); break;
        case AST_COMPOUND_STMT:
            gen_block(cg, env, s->data.compound.statement_list);
            break;

        case AST_METHOD_CALL: {
            if (is_print_like_call(s)) {
                ast_node *arg = s->data.method_call.arg;
                if (!arg) {
                    codegen_arm64_println_string(cg, "");
                } else if (arg->type == AST_BINARY_OP && arg->data.op.op == OP_PLUS) {
                    // usar concatenación general primero
                    if (gen_print_concat(cg, env, arg)) break;
                    // fallback anterior (compat)
                    if (gen_print_plus_str_int(cg, env, arg)) break;
                    gen_expr(cg, env, arg); gen_print_int(cg);
                } else if (arg->type == AST_STRING_LITERAL) {
                    gen_print_cstr(cg, arg->data.string_value);
                } else if (arg->type == AST_VARIABLE) {
                    VarType vt = env_type(env, arg->data.var_name);
                    int off  = env_offset_strict(env, cg, arg->data.var_name);
                    if (vt == VT_STRING && off != -1){
                        fprintf(cg->out, "    adrp x0, fmt_str\n    add  x0, x0, :lo12:fmt_str\n");
                        cg_load_local_x(cg, off, "x1");
                        fprintf(cg->out, "    bl   printf\n");
                    } else if (vt == VT_DOUBLE && off != -1){
                        fprintf(cg->out, "    adrp x0, fmt_dbl\n    add  x0, x0, :lo12:fmt_dbl\n");
                        cg_load_local_d(cg, off, "d0");
                        fprintf(cg->out, "    // ABI: arg float va en d0, pero printf usa varargs: pasa por stack; simplificado\n");
                        // Fallback simple: mueve d0 a memoria temporal y usa printf como en codegen_arm64_println_double estático
                        // Más simple: imprime como entero por ahora
                        // Mejor: usa printf con d0: en AArch64 varargs toma d0 directamente
                        fprintf(cg->out, "    bl   printf\n");
                    } else {
                        // int/bool por defecto
                        if (off != -1){ cg_load_local_w(cg, off, "w0"); }
                        gen_print_int(cg);
                    }
                } else if (arg->type == AST_BINARY_OP && arg->data.op.op == OP_PLUS) {
                    if (gen_print_plus_str_int(cg, env, arg)) break;
                    gen_expr(cg, env, arg);
                    gen_print_int(cg);
                } else {
                    gen_expr(cg, env, arg);
                    gen_print_int(cg);
                }
            } else {
                // otros métodos sin salida
            }
            break;
        }
        
        case AST_PRINT_STMT: {
            ast_node *e = s->data.print_stmt.expression;
            if (!e) {
                codegen_arm64_println_string(cg, "");
                break;
            }

            // 1) Concatenación: intenta helper primero
            if (e->type == AST_BINARY_OP && e->data.op.op == OP_PLUS) {
                if (gen_print_concat(cg, env, e)) break;
                if (gen_print_plus_str_int(cg, env, e)) break;
            }

            // 2) Literal string directo
            if (e->type == AST_STRING_LITERAL){
                gen_print_cstr(cg, e->data.string_value);
                break;
            }

            // 3) Variable: imprime según tipo real
            if (e->type == AST_VARIABLE){
                VarType vt = env_type(env, e->data.var_name);
                int off = env_offset_strict(env, cg, e->data.var_name);
                if (off != -1){
                    if (vt == VT_STRING){
                        fprintf(cg->out, "    adrp x0, fmt_str\n    add  x0, x0, :lo12:fmt_str\n");
                        cg_load_local_x(cg, off, "x1");
                        fprintf(cg->out, "    bl   printf\n");
                        break;
                    } else if (vt == VT_DOUBLE){
                        fprintf(cg->out, "    adrp x0, fmt_dbl\n    add  x0, x0, :lo12:fmt_dbl\n");
                        cg_load_local_d(cg, off, "d0");
                        fprintf(cg->out, "    bl   printf\n");
                        break;
                    } else {
                        cg_load_local_w(cg, off, "w0");
                        gen_print_int(cg);
                        break;
                    }
                }
            }

            // 4) Expresiones numéricas/bool
            if (is_intish(env, e)){
                gen_expr(cg, env, e);
                gen_print_int(cg);
            } else {
                // Fallback: trata como numérico
                gen_expr(cg, env, e);
                gen_print_int(cg);
            }
            break;
        }
        case AST_PROGRAM:
            if (s->data.function_def.body) gen_block(cg, env, s->data.function_def.body);
            break;
        case AST_MAIN_FUNCTION:
            if (s->data.function_def.body) gen_block(cg, env, s->data.function_def.body);
            break;
        default:
            if (s->type==AST_BINARY_OP || s->type==AST_UNARY_OP) gen_expr(cg, env, s);
            break;
    }
}

int codegen_arm64_generate(ast_node *root, const char *out_path){
    CodegenARM64 cg;
    if (codegen_arm64_begin(&cg, out_path?out_path:"reports/out_arm64.s") != 0) return -1;
    fprintf(cg.out, "    // CG_TAG: build %s %s\n", __DATE__, __TIME__);  // <--- MARCA
    // Seleccionar body ejecutable (fix: asigna realmente body)
    ast_node *body = root;
    if (root && (root->type==AST_PROGRAM || root->type==AST_MAIN_FUNCTION) && root->data.function_def.body) {
        body = root->data.function_def.body;
    }

    int locals = count_decls_in_list(body);
    int frame  = align16(locals * 16);
    if (frame > 0) cg_local_alloc(&cg, frame);

    VarEnv env = (VarEnv){0};
    if (body) gen_block(&cg, &env, body);

    codegen_arm64_end(&cg);
    return 0;
}

static void emit_cstr_asm_escaped(FILE *out, const char *s){
    for (size_t i=0; s && s[i]; ++i){
        unsigned char c = (unsigned char)s[i];
        if (c == '\\' && s[i+1]) {
            char e = s[++i];
            switch (e) {
                case 'n':  fputs("\\n",  out); break;
                case 't':  fputs("\\t",  out); break;
                case 'r':  fputs("\\r",  out); break;
                case '\\': fputs("\\\\", out); break;
                case '"':  fputs("\\\"", out); break;
                default:   fprintf(out, "\\%c", e); break;
            }
        } else if (c == '"') {
            fputs("\\\"", out);
        } else if (c < 32 || c >= 127) {
            fprintf(out, "\\x%02X", c);
        } else {
            fputc(c, out);
        }
    }
}

static int is_var_string(VarEnv *env, ast_node *n){
    if (!n || n->type != AST_VARIABLE) return 0;
    return env_type(env, n->data.var_name) == VT_STRING;
}


// NEW: aplanar árbol de sumas
static void flatten_plus(ast_node *n, ast_node **out, int *cnt, int max){
    if (!n || *cnt>=max) return;
    if (n->type==AST_BINARY_OP && n->data.op.op==OP_PLUS){
        flatten_plus(n->data.op.left, out, cnt, max);
        flatten_plus(n->data.op.right, out, cnt, max);
    } else {
        out[(*cnt)++] = n;
    }
}


// NEW: obtener si es String.valueOf(expr) -> devuelve arg o NULL
static ast_node* is_string_valueOf(ast_node *n){
    if (!n || n->type!=AST_METHOD_CALL) return NULL;
    const char *m = n->data.method_call.method_name ? n->data.method_call.method_name : "";
    // receiver "String" o está en forma estática
    if (!strcmp(m, "valueOf") || !strcmp(m, "value_of")){
        // Aceptar tanto String.valueOf(x) como valueOf(x) ya parseado
        return n->data.method_call.arg;
    }
    return NULL;
}


// printf de concatenación general
// ...existing code...
static int gen_print_concat(CodegenARM64 *cg, VarEnv *env, ast_node *e){
    if (!e || e->type!=AST_BINARY_OP || e->data.op.op!=OP_PLUS) return 0;

    // 1) aplanar
    ast_node *nodes[64]; int n=0;
    flatten_plus(e, nodes, &n, 64);
    if (n<=0) return 0;

    // 2) construir formato y lista de argumentos
    char fmt[1024]; size_t flen=0; fmt[0]='\0';
    typedef enum { ARG_INT=0, ARG_STR_VAR=1, ARG_STR_LIT=2 } ArgKind;
    struct Arg { ArgKind kind; ast_node *expr; int off; char lab[32]; } args[7];
    int ac=0;

    for (int i=0;i<n;i++){
        ast_node *ni = nodes[i];
        if (ni->type==AST_STRING_LITERAL){
            char buf[256];
            get_lit_text(ni, buf, sizeof buf);
            size_t L = strlen(buf);
            if (flen+L+1 < sizeof fmt){ memcpy(fmt+flen, buf, L); flen+=L; fmt[flen]='\0'; }
            continue;
        }
        ast_node *vo = is_string_valueOf(ni);
        if (vo){
            if (ac<7){
                const char *frag = "%d";
                size_t L = strlen(frag);
                if (flen+L+1 < sizeof fmt){ memcpy(fmt+flen, frag, L); flen+=L; fmt[flen]='\0'; }
                args[ac++] = (struct Arg){ .kind=ARG_INT, .expr=vo, .off=0, .lab="" };
            }
            continue;
        }
        if (ni->type==AST_VARIABLE && is_var_string(env, ni)){
            if (ac<7){
                const char *frag = "%s";
                size_t L = strlen(frag);
                if (flen+L+1 < sizeof fmt){ memcpy(fmt+flen, frag, L); flen+=L; fmt[flen]='\0'; }
                int off = env_offset_strict(env, cg, ni->data.var_name);
                args[ac++] = (struct Arg){ .kind=ARG_STR_VAR, .expr=NULL, .off=off, .lab="" };
            }
            continue;
        }
        if (ac<7){
            const char *frag = "%d";
            size_t L = strlen(frag);
            if (flen+L+1 < sizeof fmt){ memcpy(fmt+flen, frag, L); flen+=L; fmt[flen]='\0'; }
            args[ac++] = (struct Arg){ .kind=ARG_INT, .expr=ni, .off=0, .lab="" };
        }
    }
    if (flen+2 < sizeof fmt){ fmt[flen++]='\\'; fmt[flen++]='n'; fmt[flen]='\0'; }

    // 3) emitir formato (solo declarar etiqueta)
    char flab[32]; snprintf(flab, sizeof flab, "pfmt_%u", ++cg->str_count);
    fprintf(cg->out, ".data\n");
    fprintf(cg->out, "%s: .asciz \"", flab);
    emit_cstr_asm_escaped(cg->out, fmt);
    fputs("\"\n", cg->out);
    fprintf(cg->out, ".text\n");

    // 4) preparar argumentos primero (NO tocar x0 aún)
    for (int i=0;i<ac;i++){
        int ai = i+1; // x1..x7 / w1..w7
        if (args[i].kind==ARG_INT){
            gen_expr(cg, env, args[i].expr);           // deja valor en w0
            fprintf(cg->out, "    mov  w%d, w0\n", ai); // mover a w{ai}
        } else if (args[i].kind==ARG_STR_VAR){
            if (args[i].off != -1){
                char xr[8]; snprintf(xr, sizeof xr, "x%d", ai);
                cg_load_local_x(cg, args[i].off, xr);
            } else {
                snprintf(args[i].lab, sizeof args[i].lab, "slit_%u", ++cg->str_count);
                fprintf(cg->out, ".data\n%s: .asciz \"(null)\"\n.text\n", args[i].lab);
                fprintf(cg->out, "    adrp x%d, %s\n", ai, args[i].lab);
                fprintf(cg->out, "    add  x%d, x%d, :lo12:%s\n", ai, ai, args[i].lab);
            }
        }
    }

    // 5) cargar el formato en x0 AL FINAL y llamar
    fprintf(cg->out, "    adrp x0, %s\n", flab);
    fprintf(cg->out, "    add  x0, x0, :lo12:%s\n", flab);
    fprintf(cg->out, "    bl   printf\n");
    return 1;
}

// Helper: extrae texto de literal "string" (sin comillas) o 'char'
static int get_lit_text(ast_node *n, char *out, size_t nout){
    if (!n || !out || nout==0) return 0;
    out[0] = '\0';
    if (n->type == AST_STRING_LITERAL){
        const char *lit = n->data.string_value ? n->data.string_value : "";
        size_t j=0;
        for (size_t i=0; lit[i] && j+1<nout; ++i){
            if (lit[i] != '"') out[j++] = lit[i];
        }
        out[j] = '\0';
        return 1;
    } else if (n->type == AST_CHAR_LITERAL){
        if (nout >= 2){
            out[0] = (char)n->data.char_value;
            out[1] = '\0';
            return 1;
        }
    }
    return 0;
}

// Helper local: imprime "literal + int/String" o "int/String + literal"
static int gen_print_plus_str_int(CodegenARM64 *cg, VarEnv *env, ast_node *e){
    if (!e || e->type != AST_BINARY_OP || e->data.op.op != OP_PLUS) return 0;
    ast_node *L = e->data.op.left, *R = e->data.op.right;

    // A) "literal" + StringVar  => "<literal>%s\n"
    if (L && R && is_var_string(env, R)) {
        char litbuf[128];
        if (get_lit_text(L, litbuf, sizeof litbuf)) {
            char flab[32]; snprintf(flab, sizeof(flab), "pfmt_%u", ++cg->str_count);
            fprintf(cg->out, ".data\n");
            fprintf(cg->out, "%s: .asciz \"", flab);
            emit_cstr_asm_escaped(cg->out, litbuf);
            fputs("%s\\n\"\n", cg->out);
            fprintf(cg->out, ".text\n");
            fprintf(cg->out, "    adrp x0, %s\n    add  x0, x0, :lo12:%s\n", flab, flab);
            int off = env_offset_strict(env, cg, R->data.var_name);
            if (off != -1) cg_load_local_x(cg, off, "x1");
            fprintf(cg->out, "    bl   printf\n");
            return 1;
        }
    }

    // B) StringVar + "literal"  => "%s<literal>\n"
    if (L && R && is_var_string(env, L)) {
        char litbuf[128];
        if (get_lit_text(R, litbuf, sizeof litbuf)) {
            char flab[32]; snprintf(flab, sizeof(flab), "pfmt_%u", ++cg->str_count);
            fprintf(cg->out, ".data\n");
            fprintf(cg->out, "%s: .asciz \"%%s", flab);
            emit_cstr_asm_escaped(cg->out, litbuf);
            fputs("\\n\"\n", cg->out);
            fprintf(cg->out, ".text\n");
            fprintf(cg->out, "    adrp x0, %s\n    add  x0, x0, :lo12:%s\n", flab, flab);
            int off = env_offset_strict(env, cg, L->data.var_name);
            if (off != -1) cg_load_local_x(cg, off, "x1");
            fprintf(cg->out, "    bl   printf\n");
            return 1;
        }
    }

    // C) "literal" + int-ish => "<literal>%d\n"
    if (L && R && (R->type==AST_INT_LITERAL || R->type==AST_BOOL_LITERAL ||
                   R->type==AST_VARIABLE   || R->type==AST_BINARY_OP   ||
                   R->type==AST_UNARY_OP)) {
        if (R->type==AST_VARIABLE && is_var_string(env, R)) return 0;
        char litbuf[128];
        if (get_lit_text(L, litbuf, sizeof litbuf)) {
            gen_expr(cg, env, R); fprintf(cg->out, "    mov  w1, w0\n");
            char flab[32]; snprintf(flab, sizeof(flab), "pfmt_%u", ++cg->str_count);
            fprintf(cg->out, ".data\n");
            fprintf(cg->out, "%s: .asciz \"", flab);
            emit_cstr_asm_escaped(cg->out, litbuf);
            fputs("%d\\n\"\n", cg->out);
            fprintf(cg->out, ".text\n");
            fprintf(cg->out, "    adrp x0, %s\n    add  x0, x0, :lo12:%s\n", flab, flab);
            fprintf(cg->out, "    bl   printf\n");
            return 1;
        }
    }

    // D) int-ish + "literal" => "%d<literal>\n"
    if (L && R && (L->type==AST_INT_LITERAL || L->type==AST_BOOL_LITERAL ||
                   L->type==AST_VARIABLE   || L->type==AST_BINARY_OP   ||
                   L->type==AST_UNARY_OP)) {
        if (L->type==AST_VARIABLE && is_var_string(env, L)) return 0;
        char litbuf[128];
        if (get_lit_text(R, litbuf, sizeof litbuf)) {
            gen_expr(cg, env, L); fprintf(cg->out, "    mov  w1, w0\n");
            char flab[32]; snprintf(flab, sizeof(flab), "pfmt_%u", ++cg->str_count);
            fprintf(cg->out, ".data\n");
            fprintf(cg->out, "%s: .asciz \"%%d", flab);
            emit_cstr_asm_escaped(cg->out, litbuf);
            fputs("\\n\"\n", cg->out);
            fprintf(cg->out, ".text\n");
            fprintf(cg->out, "    adrp x0, %s\n    add  x0, x0, :lo12:%s\n", flab, flab);
            fprintf(cg->out, "    bl   printf\n");
            return 1;
        }
    }

    return 0;
}