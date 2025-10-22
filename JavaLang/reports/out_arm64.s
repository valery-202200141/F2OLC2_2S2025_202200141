.data
fmt_int:    .asciz "%d\n"
fmt_dbl:    .asciz "%f\n"
fmt_str:    .asciz "%s\n"
.text
.global main
.extern printf
main:
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    sub sp, sp, #16
    // decl a @ [x29,#-16]
    sub sp, sp, #16
    // decl b @ [x29,#-32]
    sub sp, sp, #16
    // decl c @ [x29,#-48]
.data
str_1: .asciz "c="
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_1
    add  x1, x1, :lo12:str_1
    bl   printf
    // WARN: var not found 'c'
    mov w0, wzr
    adrp x0, fmt_int
    add  x0, x0, :lo12:fmt_int
    mov  w1, w0
    bl   printf
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #7
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_1
.data
str_2: .asciz "ge7"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_2
    add  x1, x1, :lo12:str_2
    bl   printf
    b .Lendif_2
.Lelse_1:
.data
str_3: .asciz "lt7"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_3
    add  x1, x1, :lo12:str_3
    bl   printf
.Lendif_2:
    sub sp, sp, #16
    // decl i @ [x29,#-64]
.Lwhile_cond_3:
    // WARN: var not found 'i'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lwhile_end_4
    // WARN: var not found 'i'
    mov w0, wzr
    adrp x0, fmt_int
    add  x0, x0, :lo12:fmt_int
    mov  w1, w0
    bl   printf
    sub sp, sp, #16
    // decl i @ [x29,#-80]
    // auto-decl i
    // WARN: var not found 'i'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #1
    ldr w1, [sp], #16
    sub w0, w1, w0
    str w0, [x29, #-80]
    add sp, sp, #16
    b .Lwhile_cond_3
.Lwhile_end_4:
    sub sp, sp, #16
    // decl j @ [x29,#-80]
.Lfor_cond_5:
    // WARN: var not found 'j'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #3
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, lt
    cbz w0, .Lfor_end_7
    // WARN: var not found 'j'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #1
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_8
    b .Lfor_step_6
.Lelse_8:
.Lendif_9:
    // WARN: var not found 'j'
    mov w0, wzr
    adrp x0, fmt_int
    add  x0, x0, :lo12:fmt_int
    mov  w1, w0
    bl   printf
    b .Lfor_step_6
.Lfor_step_6:
    sub sp, sp, #16
    // decl j @ [x29,#-96]
    // auto-decl j
    // WARN: var not found 'j'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #1
    ldr w1, [sp], #16
    add w0, w1, w0
    str w0, [x29, #-96]
    b .Lfor_cond_5
.Lfor_end_7:
    // WARN: var not found 'a'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #2
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, eq
    eor w0, w0, #1
    str w0, [sp, #-16]!
    // WARN: var not found 'b'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #3
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, lt
    str w0, [sp, #-16]!
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, gt
    ldr w1, [sp], #16
    mov w0, w1
    cbz w0, .Land_10
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, gt
    and w0, w0, #1
.Land_10:
    ldr w1, [sp], #16
    mov w0, w1
    cbnz w0, .Lor_true_11
    // WARN: var not found 'b'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #3
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, lt
    str w0, [sp, #-16]!
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, gt
    ldr w1, [sp], #16
    mov w0, w1
    cbz w0, .Land_12
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, gt
    and w0, w0, #1
.Land_12:
    and w0, w0, #1
    b .Lor_end_11
.Lor_true_11:
    mov w0, #1
.Lor_end_11:
    cbz w0, .Lelse_13
.data
str_4: .asciz "logic"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_4
    add  x1, x1, :lo12:str_4
    bl   printf
.Lelse_13:
.Lendif_14:
    add sp, sp, #96
    mov w0, #0
    ldp x29, x30, [sp], #16
    ret
