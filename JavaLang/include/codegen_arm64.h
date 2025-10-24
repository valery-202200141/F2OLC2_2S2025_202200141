#pragma once

#ifndef CODEGEN_ARM64_H
#define CODEGEN_ARM64_H

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    FILE *out;
    unsigned str_count;
    unsigned lbl_count;
    int stack_bytes;
    int loop_sp;
    char break_lbl[32][32];
    char cont_lbl[32][32];
    bool text_opened;
    bool prologue_emitted;
    bool epilogue_emitted;
} CodegenARM64;

int  codegen_arm64_begin(CodegenARM64 *cg, const char *path);
void codegen_arm64_emit_prologue(CodegenARM64 *cg);
void codegen_arm64_emit_epilogue(CodegenARM64 *cg);
void codegen_arm64_end(CodegenARM64 *cg);

// println
void codegen_arm64_println_int(CodegenARM64 *cg, long value);
void codegen_arm64_println_double(CodegenARM64 *cg, double value);
void codegen_arm64_println_string(CodegenARM64 *cg, const char *utf8);

// locals
void cg_local_alloc(CodegenARM64*, int bytes);
void cg_local_free (CodegenARM64*, int bytes);
void cg_store_local_w(CodegenARM64*, int off, const char *wreg);
void cg_load_local_w (CodegenARM64*, int off, const char *wreg);
void cg_store_local_x(CodegenARM64*, int off, const char *xreg);
void cg_load_local_x (CodegenARM64*, int off, const char *xreg);
void cg_store_local_d(CodegenARM64*, int off, const char *dreg);
void cg_load_local_d (CodegenARM64*, int off, const char *dreg);

// exprs/booleanos
void cg_binop_int(CodegenARM64*, const char *op, const char *wa, const char *wb, const char *wd);
void cg_cmp_int(CodegenARM64*, const char *cond, const char *wa, const char *wb);
void cg_cmp_double(CodegenARM64*, const char *cond);
void cg_logical_not(CodegenARM64*);

// control de flujo
void cg_if_begin(CodegenARM64*, char *Lelse, size_t, char *Lend, size_t);
void cg_if_else (CodegenARM64*, const char *Lelse, const char *Lend);
void cg_if_end  (CodegenARM64*, const char *Lend);

void cg_while_begin(CodegenARM64*, char *Lcond, size_t, char *Lend, size_t);
void cg_while_check(CodegenARM64*, const char *Lend);
void cg_while_end  (CodegenARM64*, const char *Lcond, const char *Lend);

void cg_for_begin     (CodegenARM64*, char *Lcond, size_t, char *Lstep, size_t, char *Lend, size_t);
void cg_for_goto_step (CodegenARM64*, const char *Lstep, const char *Lcond);
void cg_for_step_label(CodegenARM64*, const char *Lstep);
void cg_for_end       (CodegenARM64*, const char *Lcond, const char *Lend);

void cg_loop_push(CodegenARM64*, const char *Lbreak, const char *Lcont);
void cg_loop_pop (CodegenARM64*);
void cg_emit_break(CodegenARM64*);
void cg_emit_continue(CodegenARM64*);


// lógica corta (ya implementadas en .c)
void cg_logic_and_begin(CodegenARM64*, char *Lend, size_t nEnd);
void cg_logic_and_join (CodegenARM64*, const char *Lend);
void cg_logic_or_begin (CodegenARM64*, char *Lend, size_t nEnd);
void cg_logic_or_join  (CodegenARM64*, const char *Lend);

// funciones usuario
void cg_function_begin(CodegenARM64*, const char *name);
void cg_function_end  (CodegenARM64*);
void cg_return_void   (CodegenARM64*);

// switch
void cg_switch_begin(CodegenARM64*, char *Lend, size_t, char *Ldef, size_t);
void cg_switch_case_imm(CodegenARM64*, int imm, const char *Lcase);
void cg_switch_goto_end(CodegenARM64*, const char *Lend);

void cg_store_local_w(CodegenARM64*, int off, const char *wreg);
void cg_load_local_w (CodegenARM64*, int off, const char *wreg);

void cg_store_local_x(CodegenARM64*, int off, const char *xreg);
void cg_load_local_x (CodegenARM64*, int off, const char *xreg);

void cg_store_local_d(CodegenARM64*, int off, const char *dreg);
void cg_load_local_d (CodegenARM64*, int off, const char *dreg);



// helpers ASM
void cg_mov_w(CodegenARM64*, const char *wd, int imm);
void cg_mov_x(CodegenARM64*, const char *xd, long imm);
void cg_addi_w(CodegenARM64*, const char *wd, const char *ws, int imm);
void cg_addi_x(CodegenARM64*, const char *xd, const char *xs, long imm);
void cg_ldr_w(CodegenARM64*, const char *wd, const char *xn, int off);
void cg_str_w(CodegenARM64*, const char *ws, const char *xn, int off);
void cg_ldr_x(CodegenARM64*, const char *xd, const char *xn, int off);
void cg_str_x(CodegenARM64*, const char *xs, const char *xn, int off);
void cg_strb_w(CodegenARM64*, const char *ws, const char *xn);
void cg_push_w(CodegenARM64*, const char *ws);
void cg_pop_w (CodegenARM64*, const char *wd);
void cg_push_x(CodegenARM64*, const char *xs);
void cg_pop_x (CodegenARM64*, const char *xd);
void cg_push_d(CodegenARM64*, const char *ds);
void cg_pop_d (CodegenARM64*, const char *dd);
void cg_label (CodegenARM64*, const char *L);

#endif