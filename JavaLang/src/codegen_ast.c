#include "../include/codegen_ast.h"
#include <string.h>
#include <stdio.h>

// Entorno de variables locales (stack en [sp])
typedef struct { char name[64]; int off; } LocalVar;
typedef struct {
    LocalVar vars[256];
    int count;
    int scope_mark[64];
    int sp; // scope stack pointer
} VarEnv;

static int env_find(VarEnv *e, const char *name){
    for (int i=e->count-1;i>=0;--i) if (strcmp(e->vars[i].name,name)==0) return i;
    return -1;
}
static int env_offset(VarEnv *e, const char *name){ int i=env_find(e,name); return i>=0? e->vars[i].off : -1; }
static void env_push_scope(VarEnv *e){ e->scope_mark[e->sp++] = e->count; }
static int  env_pop_scope(VarEnv *e, CodegenARM64 *cg){
    int from = e->scope_mark[--e->sp], bytes=0;
    for (int i=e->count-1;i>=from;--i) bytes += 16; // 16B por var para mantener SP alineado
    if (bytes) cg_local_free(cg, bytes);
    e->count = from;
    return bytes;
}
static int env_decl_int(VarEnv *e, CodegenARM64 *cg, const char *name){
    if (e->count>=256) return -1;
    cg_local_alloc(cg, 16); // reserva 16B por variable (alineación)
    int off = 0; // la var más reciente vive en [sp,#0]
    for (int i=0;i<e->count;++i) e->vars[i].off += 16; // desplazar offsets existentes
    strncpy(e->vars[e->count].name, name, sizeof(e->vars[e->count].name)-1);
    e->vars[e->count].name[sizeof(e->vars[e->count].name)-1]='\0';
    e->vars[e->count].off = off;
    e->count++;
    return off;
}

// Convención: expr int/bool deja resultado en w0
static void gen_expr(CodegenARM64 *cg, VarEnv *env, ast_node *n);

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
    fprintf(cg->out, "    adrp x0, fmt_int\n");
    fprintf(cg->out, "    add  x0, x0, :lo12:fmt_int\n");
    fprintf(cg->out, "    mov  w1, w0\n");
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
            char Lend[32]; snprintf(Lend,sizeof Lend,".Lor_%u", ++cg->lbl_count);
            fprintf(cg->out, "    cbnz w0, %s\n", Lend);
            gen_expr(cg, env, n->data.op.right);
            fprintf(cg->out, "    and w0, w0, #1\n");
            fprintf(cg->out, "%s:\n", Lend);
            fprintf(cg->out, "    mov w0, #1\n");
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
            int off = env_offset(env, n->data.var_name);
            if (off < 0){ fprintf(cg->out,"    mov w0, wzr\n"); break; }
            fprintf(cg->out, "    ldr w0, [sp, #%d]\n", off);
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

static void gen_stmt(CodegenARM64 *cg, VarEnv *env, ast_node *s);

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
            if (s->data.declaration.value && off>=0){
                gen_expr(cg, env, s->data.declaration.value);
                fprintf(cg->out, "    str w0, [sp, #%d]\n", off);
            }
            break;
        }
        case AST_ASSIGNMENT: {
            int off = env_offset(env, s->data.assignment.var_name);
            if (off < 0){ off = env_decl_int(env, cg, s->data.assignment.var_name); }
            gen_expr(cg, env, s->data.assignment.value);
            fprintf(cg->out, "    str w0, [sp, #%d]\n", off);
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
        case AST_PRINT_STMT: {
            ast_node *e = s->data.print_stmt.expression;
            if (e && is_intish(e)){
                gen_expr(cg, env, e);
                gen_print_int(cg);
            } else if (e && e->type == AST_STRING_LITERAL){
                gen_print_cstr(cg, e->data.string_value);
            } else {
                gen_print_cstr(cg, "UNSUPPORTED");
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
    VarEnv env = (VarEnv){0};
    if (root){
        if (root->type == AST_PROGRAM && root->data.function_def.body)
            gen_block(&cg, &env, root->data.function_def.body);
        else
            gen_block(&cg, &env, root);
    }
    codegen_arm64_end(&cg);
    return 0;
}