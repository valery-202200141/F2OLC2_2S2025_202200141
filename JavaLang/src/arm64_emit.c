// JavaLang/src/codegen/arm64_emit.c
#include "arm64_emit.h"
#include <string.h>

void emit_prologue(FILE *out, int frame_size){
    fprintf(out, "stp x29, x30, [sp, -16]!\n");
    fprintf(out, "mov x29, sp\n");
    if(frame_size>0) fprintf(out, "sub sp, sp, #%d\n", frame_size);
}
void emit_epilogue(FILE *out, int frame_size){
    if(frame_size>0) fprintf(out, "add sp, sp, #%d\n", frame_size);
    fprintf(out, "ldp x29, x30, [sp], #16\n");
    fprintf(out, "ret\n");
}
void emit_mov_imm64(FILE *out, const char *xdst, uint64_t v){
    unsigned w0=v&0xFFFF, w1=(v>>16)&0xFFFF, w2=(v>>32)&0xFFFF, w3=(v>>48)&0xFFFF;
    fprintf(out, "movz %s, #%u\n", xdst, w0);
    if(w1) fprintf(out, "movk %s, #%u, lsl #16\n", xdst, w1);
    if(w2) fprintf(out, "movk %s, #%u, lsl #32\n", xdst, w2);
    if(w3) fprintf(out, "movk %s, #%u, lsl #48\n", xdst, w3);
}
void emit_binop(FILE *out, const char *op){
    if(!strcmp(op,"+"))      fprintf(out,"add x0, x0, x1\n");
    else if(!strcmp(op,"-")) fprintf(out,"sub x0, x0, x1\n");
    else if(!strcmp(op,"*")) fprintf(out,"mul x0, x0, x1\n");
    else if(!strcmp(op,"/")) fprintf(out,"sdiv x0, x0, x1\n");
    else if(!strcmp(op,"%%")){ fprintf(out,"sdiv x2, x0, x1\n"); fprintf(out,"msub x0, x2, x1, x0\n"); }
}
void emit_cmp_to_bool(FILE *out, const char *rel){
    fprintf(out,"cmp x0, x1\n");
    if(!strcmp(rel,"=="))      fprintf(out,"cset w0, eq\n");
    else if(!strcmp(rel,"!=")) fprintf(out,"cset w0, ne\n");
    else if(!strcmp(rel,"<"))  fprintf(out,"cset w0, lt\n");
    else if(!strcmp(rel,"<=")) fprintf(out,"cset w0, le\n");
    else if(!strcmp(rel,">"))  fprintf(out,"cset w0, gt\n");
    else if(!strcmp(rel,">=")) fprintf(out,"cset w0, ge\n");
}
void emit_label(FILE *out, const char *label){
    fprintf(out, "%s:\n", label);
}
void emit_branch(FILE *out, const char *label){
    fprintf(out, "b %s\n", label);
}
void emit_branch_cond(FILE *out, const char *cond, const char *label){
    if(!strcmp(cond,"=="))      fprintf(out,"beq %s\n", label);
    else if(!strcmp(cond,"!=")) fprintf(out,"bne %s\n", label           
    );
    else if(!strcmp(cond,"<"))  fprintf(out,"blt %s\n", label);
    else if(!strcmp(cond,"<=")) fprintf(out,"ble %s\n", label);
    else if(!strcmp(cond,">"))  fprintf(out,"bgt %s\n", label);
    else if(!strcmp(cond,">=")) fprintf(out,"bge %s\n", label);
}