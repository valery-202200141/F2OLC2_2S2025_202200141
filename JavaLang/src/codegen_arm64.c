#include "../include/codegen_arm64.h"
#include <string.h>

// Emite líneas crudas
static void asmf(CodegenARM64 *cg, const char *s) {
    fputs(s, cg->out);
}

static void ensure_text(CodegenARM64 *cg) {
    if (!cg->text_opened) {
        asmf(cg, ".text\n");
        cg->text_opened = true;
    }
}

int codegen_arm64_begin(CodegenARM64 *cg, const char *path) {
    memset(cg, 0, sizeof(*cg));
    cg->out = fopen(path, "w");
    if (!cg->out) return -1;

    // Formatos comunes
    asmf(cg, ".data\n");
    asmf(cg, "fmt_int:    .asciz \"%d\\n\"\n");
    asmf(cg, "fmt_dbl:    .asciz \"%f\\n\"\n");
    asmf(cg, "fmt_str:    .asciz \"%s\\n\"\n");
    asmf(cg, ".text\n");
    cg->text_opened = true;

    codegen_arm64_emit_prologue(cg);
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
    asmf(cg, ".data\n");
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
    ensure_text(cg);
    // Colocamos el double en literal pool y lo cargamos en d0
    char lab[32];
    snprintf(lab, 32, "dbl_%u", ++cg->str_count);
    asmf(cg, ".data\n");
    fprintf(cg->out, "%s: .double %.17g\n", lab, value);
    ensure_text(cg);

    asmf(cg, "    adrp x0, fmt_dbl\n");
    asmf(cg, "    add  x0, x0, :lo12:fmt_dbl\n");
    fprintf(cg->out, "    adrp x1, %s\n", lab);
    fprintf(cg->out, "    add  x1, x1, :lo12:%s\n", lab);
    asmf(cg, "    ldr  d0, [x1]\n"); // primer arg en x0 (fmt), flotante en d0
    asmf(cg, "    bl   printf\n");
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