// JavaLang/src/codegen/arm64_emit.h
#pragma once
#include <stdint.h>
#include <stdio.h>

void emit_prologue(FILE *out, int frame_size);
void emit_epilogue(FILE *out, int frame_size);
void emit_mov_imm64(FILE *out, const char *xdst, uint64_t val);
void emit_binop(FILE *out, const char *op);           // x0 op x1 -> x0
void emit_cmp_to_bool(FILE *out, const char *rel);    // x0 ? x1 -> w0 in {0,1}
