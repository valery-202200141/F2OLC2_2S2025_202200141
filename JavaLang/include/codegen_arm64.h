#ifndef CODEGEN_ARM64_H
#define CODEGEN_ARM64_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    FILE *out;
    bool text_opened;
    bool prologue_emitted;
    bool epilogue_emitted;
    unsigned str_count;
} CodegenARM64;

int codegen_arm64_begin(CodegenARM64 *cg, const char *path);
void codegen_arm64_end(CodegenARM64 *cg);

// println de tipos básicos
void codegen_arm64_println_int(CodegenARM64 *cg, long value);
void codegen_arm64_println_double(CodegenARM64 *cg, double value);
void codegen_arm64_println_string(CodegenARM64 *cg, const char *utf8);

// util: asegura secciones/prólogo/epílogo
void codegen_arm64_emit_prologue(CodegenARM64 *cg);
void codegen_arm64_emit_epilogue(CodegenARM64 *cg);

#endif