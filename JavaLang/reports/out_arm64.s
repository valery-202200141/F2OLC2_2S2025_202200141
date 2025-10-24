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
    sub sp, sp, #80
    // decl a @ [x29,#-16]
    // ENV DUMP [after-decl] count=1 local_bytes=16
    //   #0 name='a' off=-16
    mov w0, #2
    str w0, [x29, #-16]
    // ENV DUMP [after-decl-store] count=1 local_bytes=16
    //   #0 name='a' off=-16
    // decl b @ [x29,#-32]
    // ENV DUMP [after-decl] count=2 local_bytes=32
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    mov w0, #3
    str w0, [x29, #-32]
    // ENV DUMP [after-decl-store] count=2 local_bytes=32
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    // decl c @ [x29,#-48]
    // ENV DUMP [after-decl] count=3 local_bytes=48
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    // ENV DUMP [before-load] count=3 local_bytes=48
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    // WARN: var not found 'a'
    mov w0, wzr
    str w0, [sp, #-16]!
    // ENV DUMP [before-load] count=3 local_bytes=48
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    // WARN: var not found 'b'
    mov w0, wzr
    ldr w1, [sp], #16
    mul w0, w1, w0
    str w0, [sp, #-16]!
    mov w0, #1
    ldr w1, [sp], #16
    add w0, w1, w0
    str w0, [x29, #-48]
    // ENV DUMP [after-decl-store] count=3 local_bytes=48
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
.data
str_1: .asciz "c="
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_1
    add  x1, x1, :lo12:str_1
    bl   printf
    // ENV DUMP [before-load] count=3 local_bytes=48
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    // WARN: var not found 'c'
    mov w0, wzr
    mov  w1, w0
    adrp x0, fmt_int
    add  x0, x0, :lo12:fmt_int
    bl   printf
    // ENV DUMP [before-load] count=3 local_bytes=48
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
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
    // decl i @ [x29,#-64]
    // ENV DUMP [after-decl] count=4 local_bytes=64
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    mov w0, #3
    str w0, [x29, #-64]
    // ENV DUMP [after-decl-store] count=4 local_bytes=64
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
.Lwhile_cond_3:
    // ENV DUMP [before-load] count=4 local_bytes=64
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    // WARN: var not found 'i'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lwhile_end_4
    // ENV DUMP [before-load] count=4 local_bytes=64
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    // WARN: var not found 'i'
    mov w0, wzr
    mov  w1, w0
    adrp x0, fmt_int
    add  x0, x0, :lo12:fmt_int
    bl   printf
    // ENV DUMP [before-assign] count=4 local_bytes=64
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    // ERROR: var not found for assign 'i' (no auto-decl)
    b .Lwhile_cond_3
.Lwhile_end_4:
    // decl j @ [x29,#-80]
    // ENV DUMP [after-decl] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    mov w0, #0
    str w0, [x29, #-80]
    // ENV DUMP [after-decl-store] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
.Lfor_cond_5:
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'j'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #3
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, lt
    cbz w0, .Lfor_end_7
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'j'
    mov w0, wzr
    mov  w1, w0
    adrp x0, fmt_int
    add  x0, x0, :lo12:fmt_int
    bl   printf
    b .Lfor_step_6
.Lfor_step_6:
    // ENV DUMP [before-assign] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // ERROR: var not found for assign 'j' (no auto-decl)
    b .Lfor_cond_5
.Lfor_end_7:
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'a'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #1
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, eq
    eor w0, w0, #1
    str w0, [sp, #-16]!
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'b'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #3
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, lt
    str w0, [sp, #-16]!
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, gt
    ldr w1, [sp], #16
    mov w0, w1
    cbz w0, .Land_8
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, gt
    and w0, w0, #1
.Land_8:
    ldr w1, [sp], #16
    mov w0, w1
    cbnz w0, .Lor_true_9
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'b'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #3
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, lt
    str w0, [sp, #-16]!
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
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
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, gt
    and w0, w0, #1
.Land_10:
    and w0, w0, #1
    b .Lor_end_9
.Lor_true_9:
    mov w0, #1
.Lor_end_9:
    str w0, [sp, #-16]!
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'b'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #3
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, lt
    str w0, [sp, #-16]!
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, gt
    ldr w1, [sp], #16
    mov w0, w1
    cbz w0, .Land_11
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, gt
    and w0, w0, #1
.Land_11:
    ldr w1, [sp], #16
    mov w0, w1
    cbnz w0, .Lor_true_12
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'b'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #3
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, lt
    str w0, [sp, #-16]!
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, gt
    ldr w1, [sp], #16
    mov w0, w1
    cbz w0, .Land_13
    // ENV DUMP [before-load] count=5 local_bytes=80
    //   #0 name='a' off=-16
    //   #1 name='b' off=-32
    //   #2 name='c' off=-48
    //   #3 name='i' off=-64
    //   #4 name='j' off=-80
    // WARN: var not found 'c'
    mov w0, wzr
    str w0, [sp, #-16]!
    mov w0, #0
    ldr w1, [sp], #16
    cmp w1, w0
    cset w0, gt
    and w0, w0, #1
.Land_13:
    and w0, w0, #1
    b .Lor_end_12
.Lor_true_12:
    mov w0, #1
.Lor_end_12:
    cbz w0, .Lelse_14
.data
str_4: .asciz "logic"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_4
    add  x1, x1, :lo12:str_4
    bl   printf
.Lelse_14:
.Lendif_15:
    add sp, sp, #80
    mov w0, #0
    ldp x29, x30, [sp], #16
    ret
