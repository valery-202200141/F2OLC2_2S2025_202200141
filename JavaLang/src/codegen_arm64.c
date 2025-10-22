#include "../include/codegen_arm64.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Emite línea cruda
static void asmf(CodegenARM64 *cg, const char *s) {
    fputs(s, cg->out);
    if (s[0] && s[strlen(s)-1] != '\n') fputc('\n', cg->out);
}

static void ensure_text(CodegenARM64 *cg) {
    if (!cg->text_opened) {
        asmf(cg, ".text");
        cg->text_opened = true;
    }
}

static void ensure_data(CodegenARM64 *cg) {
    asmf(cg, ".data");
    cg->text_opened = false;
}

static void new_label(CodegenARM64 *cg, const char *base, char *buf, size_t n) {
    snprintf(buf, n, ".L%s_%u", base, ++cg->lbl_count);
}

int codegen_arm64_begin(CodegenARM64 *cg, const char *path) {
    memset(cg, 0, sizeof(*cg));
    cg->out = fopen(path ? path : "reports/out_arm64.s", "w");
    if (!cg->out) return -1;

    // Formatos
    ensure_data(cg);
    asmf(cg, "fmt_int:    .asciz \"%d\\n\"");
    asmf(cg, "fmt_dbl:    .asciz \"%f\\n\"");
    asmf(cg, "fmt_str:    .asciz \"%s\\n\"");

    // Prologue
    ensure_text(cg);
    asmf(cg, ".global main");
    asmf(cg, ".extern printf");
    asmf(cg, "main:");
    asmf(cg, "    stp x29, x30, [sp, #-16]!");
    asmf(cg, "    mov x29, sp");
    cg->prologue_emitted = true;
    return 0;
}

void codegen_arm64_emit_prologue(CodegenARM64 *cg) {
    if (cg->prologue_emitted) return;
    asmf(cg, ".global main\n");
    asmf(cg, ".extern printf\n");
    asmf(cg, "main:\n");
    asmf(cg, "    stp x29, x30, [sp, #-16]!\n");
    asmf(cg, "    mov x29, sp\n");
    cg->prologue_emitted = true;
}

void codegen_arm64_emit_epilogue(CodegenARM64 *cg) {
    if (cg->epilogue_emitted) return;
    ensure_text(cg);
    asmf(cg, "    mov w0, #0\n");
    asmf(cg, "    ldp x29, x30, [sp], #16\n");
    asmf(cg, "    ret\n");
    cg->epilogue_emitted = true;
}

void codegen_arm64_end(CodegenARM64 *cg) {
    if (!cg->out) return;
    codegen_arm64_emit_epilogue(cg);
    fclose(cg->out);
    cg->out = NULL;
}

// Helper: emite literal string y devuelve su etiqueta
static void emit_str_literal(CodegenARM64 *cg, const char *s, char label[32]) {
    snprintf(label, 32, "str_%u", ++cg->str_count);
    // CAMBIO: usa ensure_data/ensure_text para mantener el estado de sección
    ensure_data(cg);
    fprintf(cg->out, "%s: .asciz \"", label);
    for (const unsigned char *p = (const unsigned char*)s; *p; ++p) {
        unsigned char c = *p;
        if (c == '\"' || c == '\\') fprintf(cg->out, "\\%c", c);
        else if (c == '\n') fputs("\\n", cg->out);
        else if (c == '\r') fputs("\\r", cg->out);
        else if (c == '\t') fputs("\\t", cg->out);
        else if (c < 32 || c >= 127) fprintf(cg->out, "\\x%02X", c);
        else fputc(c, cg->out);
    }
    fputs("\"\n", cg->out);
    ensure_text(cg);
}

void codegen_arm64_println_int(CodegenARM64 *cg, long value) {
    ensure_text(cg);
    // x0 = &fmt_int ; w1 = value ; bl printf
    asmf(cg, "    adrp x0, fmt_int\n");
    asmf(cg, "    add  x0, x0, :lo12:fmt_int\n");
    fprintf(cg->out, "    ldr  w1, =%ld\n", value);
    asmf(cg, "    bl   printf\n");
}

void codegen_arm64_println_double(CodegenARM64 *cg, double value) {
    // CAMBIO: usa ensure_data/ensure_text
    char lab[32];
    snprintf(lab, 32, "dbl_%u", ++cg->str_count);
    ensure_data(cg);
    fprintf(cg->out, "%s: .double %.17g\n", lab, value);
    ensure_text(cg);

    asmf(cg, "    adrp x0, fmt_dbl");
    asmf(cg, "    add  x0, x0, :lo12:fmt_dbl");
    fprintf(cg->out, "    adrp x1, %s\n", lab);
    fprintf(cg->out, "    add  x1, x1, :lo12:%s\n", lab);
    asmf(cg, "    ldr  d0, [x1]");
    asmf(cg, "    bl   printf");
}

void codegen_arm64_println_string(CodegenARM64 *cg, const char *utf8) {
    ensure_text(cg);
    char lab[32];
    emit_str_literal(cg, utf8 ? utf8 : "(null)", lab);

    asmf(cg, "    adrp x0, fmt_str\n");
    asmf(cg, "    add  x0, x0, :lo12:fmt_str\n");
    fprintf(cg->out, "    adrp x1, %s\n", lab);
    fprintf(cg->out, "    add  x1, x1, :lo12:%s\n", lab);
    asmf(cg, "    bl   printf\n");
}

// ===== Helpers de locales y control de flujo (pegar al final) =====
void cg_local_alloc(CodegenARM64 *cg, int bytes){ if(bytes>0){ ensure_text(cg); fprintf(cg->out,"    sub sp, sp, #%d\n",bytes); cg->stack_bytes+=bytes; } }
void cg_local_free (CodegenARM64 *cg, int bytes){ if(bytes>0){ ensure_text(cg); fprintf(cg->out,"    add sp, sp, #%d\n",bytes); cg->stack_bytes-=bytes; } }
void cg_store_local_w(CodegenARM64 *cg, int off, const char *wreg){
    ensure_text(cg);
    // locales estables: base FP (x29), offset NEGATIVO
    fprintf(cg->out, "    str %s, [x29, #%d]\n", wreg, off);
}

void cg_load_local_w(CodegenARM64 *cg, int off, const char *wreg){
    ensure_text(cg);
    fprintf(cg->out, "    ldr %s, [x29, #%d]\n", wreg, off);
}

void cg_cmp_int(CodegenARM64 *cg, const char *cond, const char *wa, const char *wb){
    ensure_text(cg);
    fprintf(cg->out,"    cmp %s, %s\n",wa,wb);
    const char *cc="eq";
    if(!strcmp(cond,"==")) cc="eq"; else if(!strcmp(cond,"!=")) cc="ne";
    else if(!strcmp(cond,"<")) cc="lt"; else if(!strcmp(cond,"<=")) cc="le";
    else if(!strcmp(cond,">")) cc="gt"; else if(!strcmp(cond,">=")) cc="ge";
    fprintf(cg->out,"    cset w0, %s\n",cc);
}

void cg_logical_not(CodegenARM64 *cg){ ensure_text(cg); asmf(cg,"    eor w0, w0, #1\n"); }

void cg_if_begin(CodegenARM64 *cg, char *Lelse, size_t nElse, char *Lend, size_t nEnd){
    new_label(cg,"else",Lelse,nElse); new_label(cg,"endif",Lend,nEnd);
    ensure_text(cg); fprintf(cg->out,"    cbz w0, %s\n",Lelse);
}
void cg_if_else(CodegenARM64 *cg, const char *Lelse, const char *Lend){
    ensure_text(cg); fprintf(cg->out,"    b %s\n%s:\n",Lend,Lelse);
}
void cg_if_end(CodegenARM64 *cg, const char *Lend){ ensure_text(cg); fprintf(cg->out,"%s:\n",Lend); }

void cg_while_begin(CodegenARM64 *cg, char *Lcond, size_t nCond, char *Lend, size_t nEnd){
    new_label(cg,"while_cond",Lcond,nCond); new_label(cg,"while_end",Lend,nEnd);
    ensure_text(cg); fprintf(cg->out,"%s:\n",Lcond); cg_loop_push(cg,Lend,Lcond);
}
void cg_while_check(CodegenARM64 *cg, const char *Lend){ ensure_text(cg); fprintf(cg->out,"    cbz w0, %s\n",Lend); }
void cg_while_end(CodegenARM64 *cg, const char *Lcond, const char *Lend){
    ensure_text(cg); fprintf(cg->out,"    b %s\n%s:\n",Lcond,Lend); cg_loop_pop(cg);
}

void cg_for_begin(CodegenARM64 *cg, char *Lcond, size_t nCond, char *Lstep, size_t nStep, char *Lend, size_t nEnd){
    new_label(cg,"for_cond",Lcond,nCond); new_label(cg,"for_step",Lstep,nStep); new_label(cg,"for_end",Lend,nEnd);
    ensure_text(cg); fprintf(cg->out,"%s:\n",Lcond); cg_loop_push(cg,Lend,Lstep);
}
void cg_for_goto_step(CodegenARM64 *cg, const char *Lstep, const char *Lcond){
    (void)Lcond;
    ensure_text(cg);
    fprintf(cg->out, "    b %s\n", Lstep);
}

void cg_for_step_label(CodegenARM64 *cg, const char *Lstep){
    ensure_text(cg);
    fprintf(cg->out,"%s:\n", Lstep);
}
void cg_for_end(CodegenARM64 *cg, const char *Lcond, const char *Lend){
    ensure_text(cg);
    fprintf(cg->out,"    b %s\n%s:\n",Lcond,Lend);
    cg_loop_pop(cg);
}


void cg_loop_push(CodegenARM64 *cg, const char *Lbreak, const char *Lcont){
    snprintf(cg->break_lbl[cg->loop_sp], sizeof(cg->break_lbl[0]), "%s", Lbreak);
    if (Lcont) snprintf(cg->cont_lbl[cg->loop_sp],  sizeof(cg->cont_lbl[0]),  "%s", Lcont);
    else       cg->cont_lbl[cg->loop_sp][0] = '\0';
    cg->loop_sp++;
}

void cg_emit_continue(CodegenARM64 *cg){
    ensure_text(cg);
    if (cg->loop_sp>0 && cg->cont_lbl[cg->loop_sp-1][0])
        fprintf(cg->out,"    b %s\n",cg->cont_lbl[cg->loop_sp-1]);
}

void cg_loop_pop(CodegenARM64 *cg){ if(cg->loop_sp>0) cg->loop_sp--; }
void cg_emit_break(CodegenARM64 *cg){ ensure_text(cg); fprintf(cg->out,"    b %s\n",cg->break_lbl[cg->loop_sp-1]); }

// ...existing code...
void cg_binop_int(CodegenARM64 *cg, const char *op, const char *wa, const char *wb, const char *wd){
    ensure_text(cg);
    if(!strcmp(op,"+")) fprintf(cg->out,"    add %s, %s, %s\n",wd,wa,wb);
    else if(!strcmp(op,"-")) fprintf(cg->out,"    sub %s, %s, %s\n",wd,wa,wb);
    else if(!strcmp(op,"*")) fprintf(cg->out,"    mul %s, %s, %s\n",wd,wa,wb);
    else if(!strcmp(op,"/")) fprintf(cg->out,"    sdiv %s, %s, %s\n",wd,wa,wb);
    else if(!strcmp(op,"%%")){
    fprintf(cg->out,"    sdiv w9, %s, %s\n",wa,wb);
    fprintf(cg->out,"    msub %s, w9, %s, %s\n",wd,wb,wa); // wd = a - (a/b)*b
}
}

void cg_cmp_double(CodegenARM64 *cg, const char *cond){
    ensure_text(cg);
    asmf(cg,"    fcmp d0, d1\n");
    const char *cc="EQ";
    if(!strcmp(cond,"==")) cc="EQ"; else if(!strcmp(cond,"!=")) cc="NE";
    else if(!strcmp(cond,"<")) cc="LT"; else if(!strcmp(cond,"<=")) cc="LE";
    else if(!strcmp(cond,">")) cc="GT"; else if(!strcmp(cond,">=")) cc="GE";
    fprintf(cg->out,"    cset w0, %s\n",cc);
}

// Short-circuit AND: eval A -> w0; si 0 salta a Lend, sino continúa y al final etiqueta Lend
void cg_logic_and_begin(CodegenARM64 *cg, char *Lend, size_t nEnd){
    new_label(cg,"land_end",Lend,nEnd);
    ensure_text(cg); fprintf(cg->out,"    cbz w0, %s\n",Lend);
}
void cg_logic_and_join(CodegenARM64 *cg, const char *Lend){
    ensure_text(cg); fprintf(cg->out,"%s:\n",Lend);
}

// Short-circuit OR: eval A -> w0; si 1 salta a Lend (resultado true), sino eval B y unir
void cg_logic_or_begin(CodegenARM64 *cg, char *Lend, size_t nEnd){
    new_label(cg,"lor_end",Lend,nEnd);
    ensure_text(cg); fprintf(cg->out,"    cbnz w0, %s\n",Lend);
}
void cg_logic_or_join(CodegenARM64 *cg, const char *Lend){
    ensure_text(cg); fprintf(cg->out,"%s:\n",Lend);
}

// Funciones de usuario
void cg_function_begin(CodegenARM64 *cg, const char *name){
    ensure_text(cg);
    fprintf(cg->out,".global %s\n%s:\n",name,name);
    asmf(cg,"    stp x29, x30, [sp, #-16]!\n");
    asmf(cg,"    mov x29, sp\n");
    cg->stack_bytes = 0;
}
void cg_function_end(CodegenARM64 *cg){ cg_return_void(cg); }
void cg_return_void(CodegenARM64 *cg){
    ensure_text(cg);
    if(cg->stack_bytes>0) fprintf(cg->out,"    add sp, sp, #%d\n",cg->stack_bytes);
    asmf(cg,"    ldp x29, x30, [sp], #16\n");
    asmf(cg,"    ret\n");
}

// Switch/case simple por comparación lineal
void cg_switch_begin(CodegenARM64 *cg, char *Lend, size_t nEnd, char *Ldef, size_t nDef){
    new_label(cg,"switch_end",Lend,nEnd);
    new_label(cg,"switch_def",Ldef,nDef);
    cg_loop_push(cg,Lend,NULL);
}
void cg_switch_case_imm(CodegenARM64 *cg, int imm, const char *Lcase){
    ensure_text(cg);
    fprintf(cg->out,"    mov w9, #%d\n",imm);
    asmf(cg,"    cmp w0, w9\n");
    fprintf(cg->out,"    beq %s\n",Lcase);
}
void cg_switch_goto_end(CodegenARM64 *cg, const char *Lend){
    ensure_text(cg); fprintf(cg->out,"    b %s\n",Lend);
}


void cg_mov_w(CodegenARM64 *cg, const char *wd, int imm){ ensure_text(cg); fprintf(cg->out,"    mov %s, #%d\n", wd, imm); }
void cg_mov_x(CodegenARM64 *cg, const char *xd, long imm){ ensure_text(cg); fprintf(cg->out,"    mov %s, #%ld\n", xd, imm); }
void cg_addi_w(CodegenARM64 *cg, const char *wd, const char *ws, int imm){ ensure_text(cg); fprintf(cg->out,"    add %s, %s, #%d\n", wd, ws, imm); }
void cg_addi_x(CodegenARM64 *cg, const char *xd, const char *xs, long imm){ ensure_text(cg); fprintf(cg->out,"    add %s, %s, #%ld\n", xd, xs, imm); }
void cg_ldr_w(CodegenARM64 *cg, const char *wd, const char *xn, int off){ ensure_text(cg); fprintf(cg->out,"    ldr %s, [%s, #%d]\n", wd, xn, off); }
void cg_str_w(CodegenARM64 *cg, const char *ws, const char *xn, int off){ ensure_text(cg); fprintf(cg->out,"    str %s, [%s, #%d]\n", ws, xn, off); }
void cg_ldr_x(CodegenARM64 *cg, const char *xd, const char *xn, int off){ ensure_text(cg); fprintf(cg->out,"    ldr %s, [%s, #%d]\n", xd, xn, off); }
void cg_str_x(CodegenARM64 *cg, const char *xs, const char *xn, int off){ ensure_text(cg); fprintf(cg->out,"    str %s, [%s, #%d]\n", xs, xn, off); }
void cg_strb_w(CodegenARM64 *cg, const char *ws, const char *xn){ ensure_text(cg); fprintf(cg->out,"    strb %s, [%s]\n", ws, xn); }

void cg_push_w(CodegenARM64 *cg, const char *ws){ ensure_text(cg); fprintf(cg->out,"    str %s, [sp, #-16]!\n", ws); }
void cg_pop_w (CodegenARM64 *cg, const char *wd){ ensure_text(cg); fprintf(cg->out,"    ldr %s, [sp], #16\n", wd); }
void cg_push_x(CodegenARM64 *cg, const char *xs){ ensure_text(cg); fprintf(cg->out,"    str %s, [sp, #-16]!\n", xs); }
void cg_pop_x (CodegenARM64 *cg, const char *xd){ ensure_text(cg); fprintf(cg->out,"    ldr %s, [sp], #16\n", xd); }
void cg_push_d(CodegenARM64 *cg, const char *ds){ ensure_text(cg); fprintf(cg->out,"    str %s, [sp, #-16]!\n", ds); }
void cg_pop_d (CodegenARM64 *cg, const char *dd){ ensure_text(cg); fprintf(cg->out,"    ldr %s, [sp], #16\n", dd); }
void cg_label  (CodegenARM64 *cg, const char *L){ ensure_text(cg); fprintf(cg->out,"%s:\n", L); }
