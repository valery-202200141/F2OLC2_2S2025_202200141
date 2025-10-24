#include "../include/codegen_ast.h"
#include <string.h>
#include <stdio.h>


static void sanitize_name(const char *src, char *dst, size_t n);

// Entorno de variables locales (stack en [sp])
typedef struct { char name[64]; int off; } LocalVar;
typedef struct {
    LocalVar vars[256];
    int count;
    int scope_mark[64];
    int sp; // scope stack pointer
    int local_bytes; // ACUMULADO de frame (múltiplos de 16)
} VarEnv;

static int env_find(VarEnv *e, const char *name){
    // Busca usando nombre saneado contra el nombre almacenado (que ya está saneado)
    char key[64]; sanitize_name(name ? name : "", key, sizeof(key));
    if (!key[0]) return -1;
    for (int i = e->count - 1; i >= 0; --i){
        if (strcmp(e->vars[i].name, key) == 0) return i;
    }
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


static int env_offset(VarEnv *e, const char *name){ int i=env_find(e,name); return i>=0? e->vars[i].off : -1; }

// Añade un find/offset robusto
static int env_offset_strict(VarEnv *e, CodegenARM64 *cg, const char *raw_name){
    if (!raw_name) return -1;
    char nm[64]; sanitize_name(raw_name, nm, sizeof(nm));
    if (!nm[0]) return -1;

    // 1) match directo con nombre almacenado (ya saneado)
    for (int i = e->count - 1; i >= 0; --i){
        if (strcmp(e->vars[i].name, nm) == 0) return e->vars[i].off;
    }
    // 2) por si acaso, compara contra raw (por si el almacenado llegó sin saneo en algún caso)
    for (int i = e->count - 1; i >= 0; --i){
        if (strcmp(e->vars[i].name, raw_name) == 0) return e->vars[i].off;
    }

    // Diagnóstico
    fprintf(cg->out, "    // LOOKUP FAIL raw='%s' san='%s'. En entorno hay:\n", raw_name, nm);
    for (int i = 0; i < e->count; ++i) {
        fprintf(cg->out, "    //   [%d] name='%s' off=%d\n", i, e->vars[i].name, e->vars[i].off);
    }
    return -1;
}


static void env_push_scope(VarEnv *e){ e->scope_mark[e->sp++] = e->count; }

static inline int align16(int n){ return (n + 15) & ~15; }

static int  env_pop_scope(VarEnv *e, CodegenARM64 *cg){
    // Ya NO movemos SP; solo olvidamos nombres fuera de scope
    (void)cg;
    int from = e->scope_mark[--e->sp];
    e->count = from;
    return 0;
}

static void env_dump(CodegenARM64 *cg, VarEnv *e, const char *tag){
    if (!cg || !e) return;
    fprintf(cg->out, "    // ENV DUMP [%s] count=%d local_bytes=%d\n", tag, e->count, e->local_bytes);
    for (int i = 0; i < e->count; ++i){
        fprintf(cg->out, "    //   #%d name='%s' off=%d\n", i, e->vars[i].name, e->vars[i].off);
    }
}

static void sanitize_name(const char *src, char *dst, size_t n){
    size_t j=0;
    if (!dst || n==0){ return; }
    if (!src){ dst[0]='\0'; return; }
    for (size_t i=0; src[i] && j+1<n; ++i){
        unsigned char c = (unsigned char)src[i];
        if ((c>='A' && c<='Z') || (c>='a' && c<='z') || (c>='0' && c<='9') || c=='_'){
            dst[j++] = (char)c;
        }
        // ignora cualquier otro caracter (espacios, ;, NBSP, etc.)
    }
    dst[j] = '\0';
}

static int is_print_like_call(ast_node *call){
    if (!call || call->type != AST_METHOD_CALL) return 0;
    const char *m = call->data.method_call.method_name;
    if (!m) return 0;
    return strcmp(m, "println") == 0 || strcmp(m, "print") == 0;
}

static int env_decl_int(VarEnv *e, CodegenARM64 *cg, const char *name){
    if (e->count>=256) return -1;
    char nm[64]; sanitize_name(name ? name : "", nm, sizeof(nm));
    if (!nm[0]) {
        fprintf(cg->out, "    // ERROR: nombre de variable vacío en declaración, se omite\n");
        return -1;
    }
    e->local_bytes += 16;
    int off = -e->local_bytes;
    strncpy(e->vars[e->count].name, nm, sizeof(e->vars[e->count].name)-1);
    e->vars[e->count].name[sizeof(e->vars[e->count].name)-1]='\0';
    e->vars[e->count].off = off;
    e->count++;
    fprintf(cg->out, "    // decl %s @ [x29,#%d]\n", nm, off);
    env_dump(cg, e, "after-decl");
    return off;
}

// Convención: expr int/bool deja resultado en w0
static void gen_expr(CodegenARM64 *cg, VarEnv *env, ast_node *n);

// Convención: stmt no deja nada
static void gen_stmt(CodegenARM64 *cg, VarEnv *env, ast_node *s);


static int is_intish(ast_node *n){
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

static void gen_binop(CodegenARM64 *cg, VarEnv *env, ast_node *n){
    // left -> w0; push; right -> w0; pop w1; op w0 = w1 (op) w0
    gen_expr(cg, env, n->data.op.left);
    cg_push_w(cg, "w0");
    gen_expr(cg, env, n->data.op.right);
    cg_pop_w(cg, "w1");
    switch(n->data.op.op){
        case OP_PLUS:   fprintf(cg->out, "    add w0, w1, w0\n"); break;
        case OP_MINUS:  fprintf(cg->out, "    sub w0, w1, w0\n"); break;
        case OP_MULT:   fprintf(cg->out, "    mul w0, w1, w0\n"); break;
        case OP_DIV:    fprintf(cg->out, "    sdiv w0, w1, w0\n"); break;
        case OP_MOD:
            fprintf(cg->out, "    sdiv w9, w1, w0\n");
            fprintf(cg->out, "    msub w0, w9, w0, w1\n"); // w0 = w1 - (w1/w0)*w0
            break;
        case OP_EQUALS:         cg_cmp_int(cg, "==", "w1", "w0"); break;
        case OP_NOT_EQUALS:     cg_cmp_int(cg, "!=", "w1", "w0"); break;
        case OP_LESS:           cg_cmp_int(cg, "<",  "w1", "w0"); break;
        case OP_LESS_EQUALS:    cg_cmp_int(cg, "<=", "w1", "w0"); break;
        case OP_GREATER:        cg_cmp_int(cg, ">",  "w1", "w0"); break;
        case OP_GREATER_EQUALS: cg_cmp_int(cg, ">=","w1","w0"); break;
        case OP_AND: {
            fprintf(cg->out, "    mov w0, w1\n");
            char Lend[32]; snprintf(Lend,sizeof Lend,".Land_%u", ++cg->lbl_count);
            fprintf(cg->out, "    cbz w0, %s\n", Lend);
            gen_expr(cg, env, n->data.op.right);
            fprintf(cg->out, "    and w0, w0, #1\n");
            fprintf(cg->out, "%s:\n", Lend);
            break;
        }
        case OP_OR: {
            fprintf(cg->out, "    mov w0, w1\n");
            char Ltrue[32]; snprintf(Ltrue,sizeof Ltrue,".Lor_true_%u", ++cg->lbl_count);
            char Lend [32]; snprintf(Lend ,sizeof Lend ,".Lor_end_%u",  cg->lbl_count);
            fprintf(cg->out, "    cbnz w0, %s\n", Ltrue);
            gen_expr(cg, env, n->data.op.right);
            fprintf(cg->out, "    and w0, w0, #1\n");
            fprintf(cg->out, "    b %s\n", Lend);
            fprintf(cg->out, "%s:\n", Ltrue);
            fprintf(cg->out, "    mov w0, #1\n");
            fprintf(cg->out, "%s:\n", Lend);
            break;
        }
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
            env_dump(cg, env, "before-load");
            const char *raw = n->data.var_name ? n->data.var_name : "";
            int off = env_offset_strict(env, cg, raw);  // usar raw aquí
            if (off < 0){
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
            int off = env_decl_int(env, cg, s->data.declaration.var_name);
            // inicializa (0 si no hay valor)
            if (s->data.declaration.value){
                gen_expr(cg, env, s->data.declaration.value);
                cg_store_local_w(cg, off, "w0");
            } else {
                fprintf(cg->out, "    mov w0, wzr\n");
                cg_store_local_w(cg, off, "w0");
            }
            // dump opcional
            fprintf(cg->out, "    // ENV DUMP [after-decl-store] count=%d local_bytes=%d\n", env->count, env->local_bytes);
            for (int i=0;i<env->count;i++){
                fprintf(cg->out, "    //   #%d name='%s' off=%d\n", i, env->vars[i].name, env->vars[i].off);
            }
            break;
        }
        case AST_ASSIGNMENT: {
            env_dump(cg, env, "before-assign");
            const char *raw = s->data.assignment.var_name ? s->data.assignment.var_name : "";
            char nm[64]; sanitize_name(raw, nm, sizeof(nm));
            if (!nm[0]) {
                fprintf(cg->out,"    // ERROR: nombre de variable vacío en asignación\n");
                break;
            }
            int off = env_offset_strict(env, cg, raw); // usar raw aquí también
            if (off < 0){
                fprintf(cg->out,"    // ERROR: var not found for assign '%s' (no auto-decl)\n", nm);
                break;
            }
            fprintf(cg->out,"    // assign %s @ [x29,#%d]\n", nm, off);
            gen_expr(cg, env, s->data.assignment.value);
            cg_store_local_w(cg, off, "w0");
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
            gen_expr(cg, env, s->data.while_stmt.condition);
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
        case AST_BREAK:    cg_emit_break(cg); break;
        case AST_CONTINUE: cg_emit_continue(cg); break;
        case AST_RETURN:   cg_return_void(cg); break;
        case AST_COMPOUND_STMT:
            gen_block(cg, env, s->data.compound.statement_list);
            break;

        case AST_METHOD_CALL: {
            // Soporte directo: System.out.println(x) / println(x) -> printf
            if (is_print_like_call(s)) {
                ast_node *arg = s->data.method_call.arg;
                if (!arg) {
                    codegen_arm64_println_string(cg, "");
                } else if (arg->type == AST_STRING_LITERAL) {
                    gen_print_cstr(cg, arg->data.string_value);
                } else {
                    // por defecto: evaluar como entero
                    gen_expr(cg, env, arg);
                    gen_print_int(cg);
                }
            } else {
                // otros method_call como expr (no generan salida)
                // opcional: gen_expr(cg, env, s) si fuera útil
            }
            break;
        }
        case AST_PRINT_STMT: {
            ast_node *e = s->data.print_stmt.expression;
            if (!e) {
                codegen_arm64_println_string(cg, "");
            } else if (e && is_intish(e)){
                gen_expr(cg, env, e);
                gen_print_int(cg);
            } else if (e && e->type == AST_STRING_LITERAL){
                gen_print_cstr(cg, e->data.string_value);
            } else {
                // si no sabemos el tipo, imprime como entero
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