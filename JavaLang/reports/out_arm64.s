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
    // CG_TAG: build Oct 24 2025 12:58:31
    sub sp, sp, #944
.data
str_1: .asciz "=== SISTEMA DE GESTION DE NOTAS INDIVIDUAL ==="
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_1
    add  x1, x1, :lo12:str_1
    bl   printf
    // decl estudiante1 @ [x29,#-16]
.data
slit_2: .asciz "Ana"
.text
    adrp x0, slit_2
    add  x0, x0, :lo12:slit_2
    str x0, [x29, #-16]
    // ENV DUMP [after-decl-store] count=1 local_bytes=16
    //   #0 name='estudiante1' off=-16
    // decl estudiante2 @ [x29,#-32]
.data
slit_3: .asciz "Luis"
.text
    adrp x0, slit_3
    add  x0, x0, :lo12:slit_3
    str x0, [x29, #-32]
    // ENV DUMP [after-decl-store] count=2 local_bytes=32
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    // decl estudiante3 @ [x29,#-48]
.data
slit_4: .asciz "Maria"
.text
    adrp x0, slit_4
    add  x0, x0, :lo12:slit_4
    str x0, [x29, #-48]
    // ENV DUMP [after-decl-store] count=3 local_bytes=48
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    // decl estudiante4 @ [x29,#-64]
.data
slit_5: .asciz "Carlos"
.text
    adrp x0, slit_5
    add  x0, x0, :lo12:slit_5
    str x0, [x29, #-64]
    // ENV DUMP [after-decl-store] count=4 local_bytes=64
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    // decl estudiante5 @ [x29,#-80]
.data
slit_6: .asciz "Sofia"
.text
    adrp x0, slit_6
    add  x0, x0, :lo12:slit_6
    str x0, [x29, #-80]
    // ENV DUMP [after-decl-store] count=5 local_bytes=80
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    // decl nota1 @ [x29,#-96]
    mov w0, #85
    str w0, [x29, #-96]
    // ENV DUMP [after-decl-store] count=6 local_bytes=96
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    // decl nota2 @ [x29,#-112]
    mov w0, #92
    str w0, [x29, #-112]
    // ENV DUMP [after-decl-store] count=7 local_bytes=112
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    // decl nota3 @ [x29,#-128]
    mov w0, #78
    str w0, [x29, #-128]
    // ENV DUMP [after-decl-store] count=8 local_bytes=128
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    // decl nota4 @ [x29,#-144]
    mov w0, #95
    str w0, [x29, #-144]
    // ENV DUMP [after-decl-store] count=9 local_bytes=144
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    // decl nota5 @ [x29,#-160]
    mov w0, #88
    str w0, [x29, #-160]
    // ENV DUMP [after-decl-store] count=10 local_bytes=160
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    // decl edad1 @ [x29,#-176]
    mov w0, #20
    str w0, [x29, #-176]
    // ENV DUMP [after-decl-store] count=11 local_bytes=176
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    // decl edad2 @ [x29,#-192]
    mov w0, #19
    str w0, [x29, #-192]
    // ENV DUMP [after-decl-store] count=12 local_bytes=192
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    // decl edad3 @ [x29,#-208]
    mov w0, #21
    str w0, [x29, #-208]
    // ENV DUMP [after-decl-store] count=13 local_bytes=208
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    // decl edad4 @ [x29,#-224]
    mov w0, #20
    str w0, [x29, #-224]
    // ENV DUMP [after-decl-store] count=14 local_bytes=224
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    // decl edad5 @ [x29,#-240]
    mov w0, #22
    str w0, [x29, #-240]
    // ENV DUMP [after-decl-store] count=15 local_bytes=240
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
.data
str_7: .asciz "Procesando 5 estudiantes individuales"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_7
    add  x1, x1, :lo12:str_7
    bl   printf
.data
str_8: .asciz "\n--- EVALUACION CON IF/ELSE ---"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_8
    add  x1, x1, :lo12:str_8
    bl   printf
.data
pfmt_9: .asciz "Evaluando: %s\n"
.text
    ldr x1, [x29, #-16]
    adrp x0, pfmt_9
    add  x0, x0, :lo12:pfmt_9
    bl   printf
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    mov w1, w0
    mov w0, #95
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_1
.data
str_10: .asciz "Clasificacion: SOBRESALIENTE"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_10
    add  x1, x1, :lo12:str_10
    bl   printf
    b .Lendif_2
.Lelse_1:
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    mov w1, w0
    mov w0, #85
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_3
.data
str_11: .asciz "Clasificacion: NOTABLE"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_11
    add  x1, x1, :lo12:str_11
    bl   printf
    b .Lendif_4
.Lelse_3:
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    mov w1, w0
    mov w0, #75
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_5
.data
str_12: .asciz "Clasificacion: BIEN"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_12
    add  x1, x1, :lo12:str_12
    bl   printf
    b .Lendif_6
.Lelse_5:
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    mov w1, w0
    mov w0, #65
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_7
.data
str_13: .asciz "Clasificacion: SUFICIENTE"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_13
    add  x1, x1, :lo12:str_13
    bl   printf
    b .Lendif_8
.Lelse_7:
.data
str_14: .asciz "Clasificacion: INSUFICIENTE"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_14
    add  x1, x1, :lo12:str_14
    bl   printf
.Lendif_8:
.Lendif_6:
.Lendif_4:
.Lendif_2:
    // CG_VAR raw='edad1' san='edad1'
    // load edad1 @ [x29,#-176]
    ldr w0, [x29, #-176]
    mov w1, w0
    mov w0, #21
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_9
.data
str_15: .asciz "Estado: Mayor de edad completa"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_15
    add  x1, x1, :lo12:str_15
    bl   printf
.Lelse_9:
.Lendif_10:
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    mov w1, w0
    mov w0, #90
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_11
.data
str_16: .asciz "Resultado: Apto para beca"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_16
    add  x1, x1, :lo12:str_16
    bl   printf
    b .Lendif_12
.Lelse_11:
.data
str_17: .asciz "Resultado: No apto para beca"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_17
    add  x1, x1, :lo12:str_17
    bl   printf
.Lendif_12:
.data
pfmt_18: .asciz "\nEvaluando: %s\n"
.text
    ldr x1, [x29, #-32]
    adrp x0, pfmt_18
    add  x0, x0, :lo12:pfmt_18
    bl   printf
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    mov w1, w0
    mov w0, #95
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_13
.data
str_19: .asciz "Clasificacion: SOBRESALIENTE"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_19
    add  x1, x1, :lo12:str_19
    bl   printf
    b .Lendif_14
.Lelse_13:
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    mov w1, w0
    mov w0, #85
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_15
.data
str_20: .asciz "Clasificacion: NOTABLE"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_20
    add  x1, x1, :lo12:str_20
    bl   printf
    b .Lendif_16
.Lelse_15:
.data
str_21: .asciz "Clasificacion: REGULAR"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_21
    add  x1, x1, :lo12:str_21
    bl   printf
.Lendif_16:
.Lendif_14:
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    mov w1, w0
    mov w0, #90
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_17
.data
str_22: .asciz "Resultado: Apto para beca"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_22
    add  x1, x1, :lo12:str_22
    bl   printf
    b .Lendif_18
.Lelse_17:
.data
str_23: .asciz "Resultado: No apto para beca"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_23
    add  x1, x1, :lo12:str_23
    bl   printf
.Lendif_18:
.data
pfmt_24: .asciz "\nEvaluando: %s\n"
.text
    ldr x1, [x29, #-48]
    adrp x0, pfmt_24
    add  x0, x0, :lo12:pfmt_24
    bl   printf
    // CG_VAR raw='nota3' san='nota3'
    // load nota3 @ [x29,#-128]
    ldr w0, [x29, #-128]
    mov w1, w0
    mov w0, #85
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_19
.data
str_25: .asciz "Clasificacion: NOTABLE"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_25
    add  x1, x1, :lo12:str_25
    bl   printf
    b .Lendif_20
.Lelse_19:
    // CG_VAR raw='nota3' san='nota3'
    // load nota3 @ [x29,#-128]
    ldr w0, [x29, #-128]
    mov w1, w0
    mov w0, #75
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_21
.data
str_26: .asciz "Clasificacion: BIEN"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_26
    add  x1, x1, :lo12:str_26
    bl   printf
    b .Lendif_22
.Lelse_21:
.data
str_27: .asciz "Clasificacion: REGULAR"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_27
    add  x1, x1, :lo12:str_27
    bl   printf
.Lendif_22:
.Lendif_20:
.data
str_28: .asciz "\n--- PROCESAMIENTO CON WHILE ---"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_28
    add  x1, x1, :lo12:str_28
    bl   printf
    // decl estudianteActual @ [x29,#-256]
    mov w0, #1
    str w0, [x29, #-256]
    // ENV DUMP [after-decl-store] count=16 local_bytes=256
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    // decl estudiantesDestacados @ [x29,#-272]
    mov w0, #0
    sub x9, x29, #272
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=17 local_bytes=272
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
.data
str_29: .asciz "Buscando estudiantes con nota >= 90:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_29
    add  x1, x1, :lo12:str_29
    bl   printf
.Lwhile_cond_23:
    // CG_VAR raw='estudianteActual' san='estudianteActual'
    // load estudianteActual @ [x29,#-256]
    ldr w0, [x29, #-256]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, le
    and w0, w0, #1
    cbz w0, .Lwhile_end_24
    // decl nombreActual @ [x29,#-288]
.data
slit_30: .asciz ""
.text
    adrp x0, slit_30
    add  x0, x0, :lo12:slit_30
    sub x9, x29, #288
    str x0, [x9]
    // ENV DUMP [after-decl-store] count=18 local_bytes=288
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    // decl notaActual @ [x29,#-304]
    mov w0, #0
    sub x9, x29, #304
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    // CG_VAR raw='estudianteActual' san='estudianteActual'
    // load estudianteActual @ [x29,#-256]
    ldr w0, [x29, #-256]
    mov w1, w0
    mov w0, #1
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_25
    // ENV DUMP [before-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    ldr x0, [x29, #-16]
    sub x9, x29, #288
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    // ENV DUMP [before-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    sub x9, x29, #304
    str w0, [x9]
    // ENV DUMP [after-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    b .Lendif_26
.Lelse_25:
    // CG_VAR raw='estudianteActual' san='estudianteActual'
    // load estudianteActual @ [x29,#-256]
    ldr w0, [x29, #-256]
    mov w1, w0
    mov w0, #2
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_27
    // ENV DUMP [before-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    ldr x0, [x29, #-32]
    sub x9, x29, #288
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    // ENV DUMP [before-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    sub x9, x29, #304
    str w0, [x9]
    // ENV DUMP [after-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    b .Lendif_28
.Lelse_27:
    // CG_VAR raw='estudianteActual' san='estudianteActual'
    // load estudianteActual @ [x29,#-256]
    ldr w0, [x29, #-256]
    mov w1, w0
    mov w0, #3
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_29
    // ENV DUMP [before-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    ldr x0, [x29, #-48]
    sub x9, x29, #288
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    // ENV DUMP [before-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    // CG_VAR raw='nota3' san='nota3'
    // load nota3 @ [x29,#-128]
    ldr w0, [x29, #-128]
    sub x9, x29, #304
    str w0, [x9]
    // ENV DUMP [after-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    b .Lendif_30
.Lelse_29:
    // CG_VAR raw='estudianteActual' san='estudianteActual'
    // load estudianteActual @ [x29,#-256]
    ldr w0, [x29, #-256]
    mov w1, w0
    mov w0, #4
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_31
    // ENV DUMP [before-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    ldr x0, [x29, #-64]
    sub x9, x29, #288
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    // ENV DUMP [before-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    // CG_VAR raw='nota4' san='nota4'
    // load nota4 @ [x29,#-144]
    ldr w0, [x29, #-144]
    sub x9, x29, #304
    str w0, [x9]
    // ENV DUMP [after-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    b .Lendif_32
.Lelse_31:
    // CG_VAR raw='estudianteActual' san='estudianteActual'
    // load estudianteActual @ [x29,#-256]
    ldr w0, [x29, #-256]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_33
    // ENV DUMP [before-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    ldr x0, [x29, #-80]
    sub x9, x29, #288
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    // ENV DUMP [before-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
    // CG_VAR raw='nota5' san='nota5'
    // load nota5 @ [x29,#-160]
    ldr w0, [x29, #-160]
    sub x9, x29, #304
    str w0, [x9]
    // ENV DUMP [after-assign] count=19 local_bytes=304
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='nombreActual' off=-288
    //   #18 name='notaActual' off=-304
.Lelse_33:
.Lendif_34:
.Lendif_32:
.Lendif_30:
.Lendif_28:
.Lendif_26:
.data
pfmt_31: .asciz "Revisando estudiante %d: %s\n"
.text
    // CG_VAR raw='estudianteActual' san='estudianteActual'
    // load estudianteActual @ [x29,#-256]
    ldr w0, [x29, #-256]
    mov  w1, w0
    sub x9, x29, #288
    ldr x2, [x9]
    adrp x0, pfmt_31
    add  x0, x0, :lo12:pfmt_31
    bl   printf
    // CG_VAR raw='notaActual' san='notaActual'
    // load notaActual @ [x29,#-304]
    sub x9, x29, #304
    ldr w0, [x9]
    mov w1, w0
    mov w0, #90
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lelse_35
.data
pfmt_32: .asciz "Destacado encontrado: %s con %d\n"
.text
    sub x9, x29, #288
    ldr x1, [x9]
    // CG_VAR raw='notaActual' san='notaActual'
    // load notaActual @ [x29,#-304]
    sub x9, x29, #304
    ldr w0, [x9]
    mov  w2, w0
    adrp x0, pfmt_32
    add  x0, x0, :lo12:pfmt_32
    bl   printf
    sub x9, x29, #272
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #272
    str w10, [x9]
    mov w0, w9
.Lelse_35:
.Lendif_36:
    ldr w9, [x29, #-256]
    add w10, w9, #1
    str w10, [x29, #-256]
    mov w0, w9
    b .Lwhile_cond_23
.Lwhile_end_24:
.data
pfmt_33: .asciz "Total de estudiantes destacados: %d\n"
.text
    // CG_VAR raw='estudiantesDestacados' san='estudiantesDestacados'
    // load estudiantesDestacados @ [x29,#-272]
    sub x9, x29, #272
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_33
    add  x0, x0, :lo12:pfmt_33
    bl   printf
.data
str_34: .asciz "\nContador regresivo:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_34
    add  x1, x1, :lo12:str_34
    bl   printf
    // decl contador @ [x29,#-320]
    mov w0, #5
    sub x9, x29, #320
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=18 local_bytes=320
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
.Lwhile_cond_37:
    // CG_VAR raw='contador' san='contador'
    // load contador @ [x29,#-320]
    sub x9, x29, #320
    ldr w0, [x9]
    mov w1, w0
    mov w0, #0
    cmp w1, w0
    cset w0, gt
    and w0, w0, #1
    cbz w0, .Lwhile_end_38
.data
pfmt_35: .asciz "Quedan: %d estudiantes por procesar\n"
.text
    // CG_VAR raw='contador' san='contador'
    // load contador @ [x29,#-320]
    sub x9, x29, #320
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_35
    add  x0, x0, :lo12:pfmt_35
    bl   printf
    sub x9, x29, #320
    ldr w9, [x9]
    sub w10, w9, #1
    sub x9, x29, #320
    str w10, [x9]
    mov w0, w9
    b .Lwhile_cond_37
.Lwhile_end_38:
.data
str_36: .asciz "\nBusqueda de estudiante joven con buena nota:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_36
    add  x1, x1, :lo12:str_36
    bl   printf
    // decl indice @ [x29,#-336]
    mov w0, #1
    sub x9, x29, #336
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=19 local_bytes=336
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
.Lwhile_cond_39:
    // CG_VAR raw='indice' san='indice'
    // load indice @ [x29,#-336]
    sub x9, x29, #336
    ldr w0, [x9]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, le
    and w0, w0, #1
    cbz w0, .Land_41
    // CG_VAR raw='estudiantesDestacados' san='estudiantesDestacados'
    // load estudiantesDestacados @ [x29,#-272]
    sub x9, x29, #272
    ldr w0, [x9]
    mov w1, w0
    mov w0, #0
    cmp w1, w0
    cset w0, gt
    and w0, w0, #1
.Land_41:
    and w0, w0, #1
    cbz w0, .Lwhile_end_40
    // decl nombre @ [x29,#-352]
.data
slit_37: .asciz ""
.text
    adrp x0, slit_37
    add  x0, x0, :lo12:slit_37
    sub x9, x29, #352
    str x0, [x9]
    // ENV DUMP [after-decl-store] count=20 local_bytes=352
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    // decl nota @ [x29,#-368]
    mov w0, #0
    sub x9, x29, #368
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=21 local_bytes=368
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    // decl edad @ [x29,#-384]
    mov w0, #0
    sub x9, x29, #384
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // CG_VAR raw='indice' san='indice'
    // load indice @ [x29,#-336]
    sub x9, x29, #336
    ldr w0, [x9]
    mov w1, w0
    mov w0, #1
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_42
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    ldr x0, [x29, #-16]
    sub x9, x29, #352
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    sub x9, x29, #368
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // CG_VAR raw='edad1' san='edad1'
    // load edad1 @ [x29,#-176]
    ldr w0, [x29, #-176]
    sub x9, x29, #384
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    b .Lendif_43
.Lelse_42:
    // CG_VAR raw='indice' san='indice'
    // load indice @ [x29,#-336]
    sub x9, x29, #336
    ldr w0, [x9]
    mov w1, w0
    mov w0, #2
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_44
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    ldr x0, [x29, #-32]
    sub x9, x29, #352
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    sub x9, x29, #368
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // CG_VAR raw='edad2' san='edad2'
    // load edad2 @ [x29,#-192]
    ldr w0, [x29, #-192]
    sub x9, x29, #384
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    b .Lendif_45
.Lelse_44:
    // CG_VAR raw='indice' san='indice'
    // load indice @ [x29,#-336]
    sub x9, x29, #336
    ldr w0, [x9]
    mov w1, w0
    mov w0, #3
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_46
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    ldr x0, [x29, #-48]
    sub x9, x29, #352
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // CG_VAR raw='nota3' san='nota3'
    // load nota3 @ [x29,#-128]
    ldr w0, [x29, #-128]
    sub x9, x29, #368
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // CG_VAR raw='edad3' san='edad3'
    // load edad3 @ [x29,#-208]
    ldr w0, [x29, #-208]
    sub x9, x29, #384
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    b .Lendif_47
.Lelse_46:
    // CG_VAR raw='indice' san='indice'
    // load indice @ [x29,#-336]
    sub x9, x29, #336
    ldr w0, [x9]
    mov w1, w0
    mov w0, #4
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_48
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    ldr x0, [x29, #-64]
    sub x9, x29, #352
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // CG_VAR raw='nota4' san='nota4'
    // load nota4 @ [x29,#-144]
    ldr w0, [x29, #-144]
    sub x9, x29, #368
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // CG_VAR raw='edad4' san='edad4'
    // load edad4 @ [x29,#-224]
    ldr w0, [x29, #-224]
    sub x9, x29, #384
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    b .Lendif_49
.Lelse_48:
    // CG_VAR raw='indice' san='indice'
    // load indice @ [x29,#-336]
    sub x9, x29, #336
    ldr w0, [x9]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_50
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    ldr x0, [x29, #-80]
    sub x9, x29, #352
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // CG_VAR raw='nota5' san='nota5'
    // load nota5 @ [x29,#-160]
    ldr w0, [x29, #-160]
    sub x9, x29, #368
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // ENV DUMP [before-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
    // CG_VAR raw='edad5' san='edad5'
    // load edad5 @ [x29,#-240]
    ldr w0, [x29, #-240]
    sub x9, x29, #384
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=384
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='nombre' off=-352
    //   #20 name='nota' off=-368
    //   #21 name='edad' off=-384
.Lelse_50:
.Lendif_51:
.Lendif_49:
.Lendif_47:
.Lendif_45:
.Lendif_43:
    // CG_VAR raw='nota' san='nota'
    // load nota @ [x29,#-368]
    sub x9, x29, #368
    ldr w0, [x9]
    mov w1, w0
    mov w0, #90
    cmp w1, w0
    cset w0, ge
    and w0, w0, #1
    cbz w0, .Land_52
    // CG_VAR raw='edad' san='edad'
    // load edad @ [x29,#-384]
    sub x9, x29, #384
    ldr w0, [x9]
    mov w1, w0
    mov w0, #20
    cmp w1, w0
    cset w0, le
    and w0, w0, #1
.Land_52:
    cbz w0, .Lelse_53
.data
pfmt_38: .asciz "Estudiante joven destacado: %s (Edad: %d, Nota: %d)\n"
.text
    sub x9, x29, #352
    ldr x1, [x9]
    // CG_VAR raw='edad' san='edad'
    // load edad @ [x29,#-384]
    sub x9, x29, #384
    ldr w0, [x9]
    mov  w2, w0
    // CG_VAR raw='nota' san='nota'
    // load nota @ [x29,#-368]
    sub x9, x29, #368
    ldr w0, [x9]
    mov  w3, w0
    adrp x0, pfmt_38
    add  x0, x0, :lo12:pfmt_38
    bl   printf
.Lelse_53:
.Lendif_54:
    sub x9, x29, #336
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #336
    str w10, [x9]
    mov w0, w9
    b .Lwhile_cond_39
.Lwhile_end_40:
.data
str_39: .asciz "\n--- PROCESAMIENTO CON FOR CLASICO ---"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_39
    add  x1, x1, :lo12:str_39
    bl   printf
.data
str_40: .asciz "Listado numerado:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_40
    add  x1, x1, :lo12:str_40
    bl   printf
    // decl i @ [x29,#-400]
    mov w0, #1
    sub x9, x29, #400
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=20 local_bytes=400
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
.Lfor_cond_55:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-400]
    sub x9, x29, #400
    ldr w0, [x9]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, le
    cbz w0, .Lfor_end_57
    // decl nombre @ [x29,#-416]
.data
slit_41: .asciz ""
.text
    adrp x0, slit_41
    add  x0, x0, :lo12:slit_41
    sub x9, x29, #416
    str x0, [x9]
    // ENV DUMP [after-decl-store] count=21 local_bytes=416
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    // decl nota @ [x29,#-432]
    mov w0, #0
    sub x9, x29, #432
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-400]
    sub x9, x29, #400
    ldr w0, [x9]
    mov w1, w0
    mov w0, #1
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_58
    // ENV DUMP [before-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    ldr x0, [x29, #-16]
    sub x9, x29, #416
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    // ENV DUMP [before-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    sub x9, x29, #432
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    b .Lendif_59
.Lelse_58:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-400]
    sub x9, x29, #400
    ldr w0, [x9]
    mov w1, w0
    mov w0, #2
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_60
    // ENV DUMP [before-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    ldr x0, [x29, #-32]
    sub x9, x29, #416
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    // ENV DUMP [before-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    sub x9, x29, #432
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    b .Lendif_61
.Lelse_60:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-400]
    sub x9, x29, #400
    ldr w0, [x9]
    mov w1, w0
    mov w0, #3
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_62
    // ENV DUMP [before-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    ldr x0, [x29, #-48]
    sub x9, x29, #416
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    // ENV DUMP [before-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    // CG_VAR raw='nota3' san='nota3'
    // load nota3 @ [x29,#-128]
    ldr w0, [x29, #-128]
    sub x9, x29, #432
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    b .Lendif_63
.Lelse_62:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-400]
    sub x9, x29, #400
    ldr w0, [x9]
    mov w1, w0
    mov w0, #4
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_64
    // ENV DUMP [before-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    ldr x0, [x29, #-64]
    sub x9, x29, #416
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    // ENV DUMP [before-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    // CG_VAR raw='nota4' san='nota4'
    // load nota4 @ [x29,#-144]
    ldr w0, [x29, #-144]
    sub x9, x29, #432
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    b .Lendif_65
.Lelse_64:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-400]
    sub x9, x29, #400
    ldr w0, [x9]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_66
    // ENV DUMP [before-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    ldr x0, [x29, #-80]
    sub x9, x29, #416
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    // ENV DUMP [before-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
    // CG_VAR raw='nota5' san='nota5'
    // load nota5 @ [x29,#-160]
    ldr w0, [x29, #-160]
    sub x9, x29, #432
    str w0, [x9]
    // ENV DUMP [after-assign] count=22 local_bytes=432
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='nombre' off=-416
    //   #21 name='nota' off=-432
.Lelse_66:
.Lendif_67:
.Lendif_65:
.Lendif_63:
.Lendif_61:
.Lendif_59:
.data
pfmt_42: .asciz "%d. %s - Nota: %d\n"
.text
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-400]
    sub x9, x29, #400
    ldr w0, [x9]
    mov  w1, w0
    sub x9, x29, #416
    ldr x2, [x9]
    // CG_VAR raw='nota' san='nota'
    // load nota @ [x29,#-432]
    sub x9, x29, #432
    ldr w0, [x9]
    mov  w3, w0
    adrp x0, pfmt_42
    add  x0, x0, :lo12:pfmt_42
    bl   printf
    b .Lfor_step_56
.Lfor_step_56:
    sub x9, x29, #400
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #400
    str w10, [x9]
    mov w0, w9
    b .Lfor_cond_55
.Lfor_end_57:
.data
str_43: .asciz "\nProceso inverso:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_43
    add  x1, x1, :lo12:str_43
    bl   printf
    // decl i @ [x29,#-448]
    mov w0, #5
    sub x9, x29, #448
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=21 local_bytes=448
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
.Lfor_cond_68:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-448]
    sub x9, x29, #448
    ldr w0, [x9]
    mov w1, w0
    mov w0, #1
    cmp w1, w0
    cset w0, ge
    cbz w0, .Lfor_end_70
.data
pfmt_44: .asciz "Procesando posicion: %d\n"
.text
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-448]
    sub x9, x29, #448
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_44
    add  x0, x0, :lo12:pfmt_44
    bl   printf
    b .Lfor_step_69
.Lfor_step_69:
    sub x9, x29, #448
    ldr w9, [x9]
    sub w10, w9, #1
    sub x9, x29, #448
    str w10, [x9]
    mov w0, w9
    b .Lfor_cond_68
.Lfor_end_70:
.data
str_45: .asciz "\nTabla de multiplicar (1-3 x 1-4):"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_45
    add  x1, x1, :lo12:str_45
    bl   printf
    // decl i @ [x29,#-464]
    mov w0, #1
    sub x9, x29, #464
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=22 local_bytes=464
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
.Lfor_cond_71:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-464]
    sub x9, x29, #464
    ldr w0, [x9]
    mov w1, w0
    mov w0, #3
    cmp w1, w0
    cset w0, le
    cbz w0, .Lfor_end_73
    // decl j @ [x29,#-480]
    mov w0, #1
    sub x9, x29, #480
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=23 local_bytes=480
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='j' off=-480
.Lfor_cond_74:
    // CG_VAR raw='j' san='j'
    // load j @ [x29,#-480]
    sub x9, x29, #480
    ldr w0, [x9]
    mov w1, w0
    mov w0, #4
    cmp w1, w0
    cset w0, le
    cbz w0, .Lfor_end_76
    // decl resultado @ [x29,#-496]
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-464]
    sub x9, x29, #464
    ldr w0, [x9]
    mov w1, w0
    // CG_VAR raw='j' san='j'
    // load j @ [x29,#-480]
    sub x9, x29, #480
    ldr w0, [x9]
    mul w0, w1, w0
    sub x9, x29, #496
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=24 local_bytes=496
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='j' off=-480
    //   #23 name='resultado' off=-496
.data
pfmt_46: .asciz "%d x %d = %d\n"
.text
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-464]
    sub x9, x29, #464
    ldr w0, [x9]
    mov  w1, w0
    // CG_VAR raw='j' san='j'
    // load j @ [x29,#-480]
    sub x9, x29, #480
    ldr w0, [x9]
    mov  w2, w0
    // CG_VAR raw='resultado' san='resultado'
    // load resultado @ [x29,#-496]
    sub x9, x29, #496
    ldr w0, [x9]
    mov  w3, w0
    adrp x0, pfmt_46
    add  x0, x0, :lo12:pfmt_46
    bl   printf
    b .Lfor_step_75
.Lfor_step_75:
    sub x9, x29, #480
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #480
    str w10, [x9]
    mov w0, w9
    b .Lfor_cond_74
.Lfor_end_76:
    b .Lfor_step_72
.Lfor_step_72:
    sub x9, x29, #464
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #464
    str w10, [x9]
    mov w0, w9
    b .Lfor_cond_71
.Lfor_end_73:
.data
str_47: .asciz "\n--- FOREACH CON ARRAY SIMPLE ---"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_47
    add  x1, x1, :lo12:str_47
    bl   printf
    // decl notasParaForeach @ [x29,#-512]
    mov w0, wzr
    sub x9, x29, #512
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=23 local_bytes=512
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
.data
str_48: .asciz "Procesando notas con forEach:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_48
    add  x1, x1, :lo12:str_48
    bl   printf
    // decl suma @ [x29,#-528]
    mov w0, #0
    sub x9, x29, #528
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=24 local_bytes=528
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    // decl contadorNotas @ [x29,#-544]
    mov w0, #0
    sub x9, x29, #544
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=25 local_bytes=544
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    // decl promedio @ [x29,#-560]
.data
dcon_49: .double 0
.text
    adrp x1, dcon_49
    add  x1, x1, :lo12:dcon_49
    ldr  d0, [x1]
    sub x9, x29, #560
    str d0, [x9]
    // ENV DUMP [after-decl-store] count=26 local_bytes=560
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
.data
pfmt_50: .asciz "Promedio calculado con forEach: %d\n"
.text
    // CG_VAR raw='promedio' san='promedio'
    // load promedio @ [x29,#-560]
    sub x9, x29, #560
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_50
    add  x0, x0, :lo12:pfmt_50
    bl   printf
.data
str_51: .asciz "\nConteo de categorias con forEach:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_51
    add  x1, x1, :lo12:str_51
    bl   printf
    // decl notasAltas @ [x29,#-576]
    mov w0, #0
    sub x9, x29, #576
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=27 local_bytes=576
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    // decl notasBajas @ [x29,#-592]
    mov w0, #0
    sub x9, x29, #592
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=28 local_bytes=592
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
.data
pfmt_52: .asciz "Total notas altas (>=90): %d\n"
.text
    // CG_VAR raw='notasAltas' san='notasAltas'
    // load notasAltas @ [x29,#-576]
    sub x9, x29, #576
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_52
    add  x0, x0, :lo12:pfmt_52
    bl   printf
.data
pfmt_53: .asciz "Total notas bajas (<80): %d\n"
.text
    // CG_VAR raw='notasBajas' san='notasBajas'
    // load notasBajas @ [x29,#-592]
    sub x9, x29, #592
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_53
    add  x0, x0, :lo12:pfmt_53
    bl   printf
.data
str_54: .asciz "\n--- CLASIFICACION CON SWITCH/CASE ---"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_54
    add  x1, x1, :lo12:str_54
    bl   printf
.data
pfmt_55: .asciz "Analizando: %s (Nota: %d)\n"
.text
    ldr x1, [x29, #-16]
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    mov  w2, w0
    adrp x0, pfmt_55
    add  x0, x0, :lo12:pfmt_55
    bl   printf
    // decl categoria1 @ [x29,#-608]
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    mov w1, w0
    mov w0, #10
    sdiv w0, w1, w0
    sub x9, x29, #608
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=29 local_bytes=608
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    // CG_VAR raw='categoria1' san='categoria1'
    // load categoria1 @ [x29,#-608]
    sub x9, x29, #608
    ldr w0, [x9]
    mov w1, w0
    mov w0, #10
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_77
    b .Lendif_78
.Lelse_77:
    // CG_VAR raw='categoria1' san='categoria1'
    // load categoria1 @ [x29,#-608]
    sub x9, x29, #608
    ldr w0, [x9]
    mov w1, w0
    mov w0, #9
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_79
.data
str_56: .asciz "Categoria: EXCELENTE"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_56
    add  x1, x1, :lo12:str_56
    bl   printf
    b .Lendif_80
.Lelse_79:
    // CG_VAR raw='categoria1' san='categoria1'
    // load categoria1 @ [x29,#-608]
    sub x9, x29, #608
    ldr w0, [x9]
    mov w1, w0
    mov w0, #8
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_81
.data
str_57: .asciz "Categoria: MUY BUENO"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_57
    add  x1, x1, :lo12:str_57
    bl   printf
    b .Lendif_82
.Lelse_81:
    // CG_VAR raw='categoria1' san='categoria1'
    // load categoria1 @ [x29,#-608]
    sub x9, x29, #608
    ldr w0, [x9]
    mov w1, w0
    mov w0, #7
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_83
.data
str_58: .asciz "Categoria: BUENO"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_58
    add  x1, x1, :lo12:str_58
    bl   printf
    b .Lendif_84
.Lelse_83:
    // CG_VAR raw='categoria1' san='categoria1'
    // load categoria1 @ [x29,#-608]
    sub x9, x29, #608
    ldr w0, [x9]
    mov w1, w0
    mov w0, #6
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_85
.data
str_59: .asciz "Categoria: SUFICIENTE"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_59
    add  x1, x1, :lo12:str_59
    bl   printf
    b .Lendif_86
.Lelse_85:
.data
str_60: .asciz "Categoria: INSUFICIENTE"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_60
    add  x1, x1, :lo12:str_60
    bl   printf
.Lendif_86:
.Lendif_84:
.Lendif_82:
.Lendif_80:
.Lendif_78:
.data
pfmt_61: .asciz "\nAnalizando: %s (Nota: %d)\n"
.text
    ldr x1, [x29, #-32]
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    mov  w2, w0
    adrp x0, pfmt_61
    add  x0, x0, :lo12:pfmt_61
    bl   printf
    // decl categoria2 @ [x29,#-624]
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    mov w1, w0
    mov w0, #10
    sdiv w0, w1, w0
    sub x9, x29, #624
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=30 local_bytes=624
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    // CG_VAR raw='categoria2' san='categoria2'
    // load categoria2 @ [x29,#-624]
    sub x9, x29, #624
    ldr w0, [x9]
    mov w1, w0
    mov w0, #10
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_87
    b .Lendif_88
.Lelse_87:
    // CG_VAR raw='categoria2' san='categoria2'
    // load categoria2 @ [x29,#-624]
    sub x9, x29, #624
    ldr w0, [x9]
    mov w1, w0
    mov w0, #9
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_89
.data
str_62: .asciz "Categoria: EXCELENTE"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_62
    add  x1, x1, :lo12:str_62
    bl   printf
    b .Lendif_90
.Lelse_89:
    // CG_VAR raw='categoria2' san='categoria2'
    // load categoria2 @ [x29,#-624]
    sub x9, x29, #624
    ldr w0, [x9]
    mov w1, w0
    mov w0, #8
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_91
.data
str_63: .asciz "Categoria: MUY BUENO"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_63
    add  x1, x1, :lo12:str_63
    bl   printf
    b .Lendif_92
.Lelse_91:
    // CG_VAR raw='categoria2' san='categoria2'
    // load categoria2 @ [x29,#-624]
    sub x9, x29, #624
    ldr w0, [x9]
    mov w1, w0
    mov w0, #7
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_93
.data
str_64: .asciz "Categoria: BUENO"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_64
    add  x1, x1, :lo12:str_64
    bl   printf
    b .Lendif_94
.Lelse_93:
.data
str_65: .asciz "Categoria: REGULAR"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_65
    add  x1, x1, :lo12:str_65
    bl   printf
.Lendif_94:
.Lendif_92:
.Lendif_90:
.Lendif_88:
.data
str_66: .asciz "\nAnalisis por edad:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_66
    add  x1, x1, :lo12:str_66
    bl   printf
    // CG_VAR raw='edad1' san='edad1'
    // load edad1 @ [x29,#-176]
    ldr w0, [x29, #-176]
    mov w1, w0
    mov w0, #18
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_95
    b .Lendif_96
.Lelse_95:
    // CG_VAR raw='edad1' san='edad1'
    // load edad1 @ [x29,#-176]
    ldr w0, [x29, #-176]
    mov w1, w0
    mov w0, #19
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_97
.data
pfmt_67: .asciz "%s - Categoria: Muy joven\n"
.text
    ldr x1, [x29, #-16]
    adrp x0, pfmt_67
    add  x0, x0, :lo12:pfmt_67
    bl   printf
    b .Lendif_98
.Lelse_97:
    // CG_VAR raw='edad1' san='edad1'
    // load edad1 @ [x29,#-176]
    ldr w0, [x29, #-176]
    mov w1, w0
    mov w0, #20
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_99
    b .Lendif_100
.Lelse_99:
    // CG_VAR raw='edad1' san='edad1'
    // load edad1 @ [x29,#-176]
    ldr w0, [x29, #-176]
    mov w1, w0
    mov w0, #21
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_101
.data
pfmt_68: .asciz "%s - Categoria: Joven adulto\n"
.text
    ldr x1, [x29, #-16]
    adrp x0, pfmt_68
    add  x0, x0, :lo12:pfmt_68
    bl   printf
    b .Lendif_102
.Lelse_101:
    // CG_VAR raw='edad1' san='edad1'
    // load edad1 @ [x29,#-176]
    ldr w0, [x29, #-176]
    mov w1, w0
    mov w0, #22
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_103
    b .Lendif_104
.Lelse_103:
    // CG_VAR raw='edad1' san='edad1'
    // load edad1 @ [x29,#-176]
    ldr w0, [x29, #-176]
    mov w1, w0
    mov w0, #23
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_105
.data
pfmt_69: .asciz "%s - Categoria: Adulto joven\n"
.text
    ldr x1, [x29, #-16]
    adrp x0, pfmt_69
    add  x0, x0, :lo12:pfmt_69
    bl   printf
    b .Lendif_106
.Lelse_105:
.data
pfmt_70: .asciz "%s - Categoria: Adulto\n"
.text
    ldr x1, [x29, #-16]
    adrp x0, pfmt_70
    add  x0, x0, :lo12:pfmt_70
    bl   printf
.Lendif_106:
.Lendif_104:
.Lendif_102:
.Lendif_100:
.Lendif_98:
.Lendif_96:
.data
str_71: .asciz "\n--- DEMOSTRACION DE BREAK ---"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_71
    add  x1, x1, :lo12:str_71
    bl   printf
.data
str_72: .asciz "Busqueda con break (primera nota > 90):"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_72
    add  x1, x1, :lo12:str_72
    bl   printf
    // decl i @ [x29,#-640]
    mov w0, #1
    sub x9, x29, #640
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=31 local_bytes=640
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
.Lfor_cond_107:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-640]
    sub x9, x29, #640
    ldr w0, [x9]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, le
    cbz w0, .Lfor_end_109
    // decl notaActual @ [x29,#-656]
    mov w0, #0
    sub x9, x29, #656
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=32 local_bytes=656
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    // decl nombreActual @ [x29,#-672]
.data
slit_73: .asciz ""
.text
    adrp x0, slit_73
    add  x0, x0, :lo12:slit_73
    sub x9, x29, #672
    str x0, [x9]
    // ENV DUMP [after-decl-store] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-640]
    sub x9, x29, #640
    ldr w0, [x9]
    mov w1, w0
    mov w0, #1
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_110
    // ENV DUMP [before-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    sub x9, x29, #656
    str w0, [x9]
    // ENV DUMP [after-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    // ENV DUMP [before-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    ldr x0, [x29, #-16]
    sub x9, x29, #672
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    b .Lendif_111
.Lelse_110:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-640]
    sub x9, x29, #640
    ldr w0, [x9]
    mov w1, w0
    mov w0, #2
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_112
    // ENV DUMP [before-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    sub x9, x29, #656
    str w0, [x9]
    // ENV DUMP [after-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    // ENV DUMP [before-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    ldr x0, [x29, #-32]
    sub x9, x29, #672
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    b .Lendif_113
.Lelse_112:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-640]
    sub x9, x29, #640
    ldr w0, [x9]
    mov w1, w0
    mov w0, #3
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_114
    // ENV DUMP [before-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    // CG_VAR raw='nota3' san='nota3'
    // load nota3 @ [x29,#-128]
    ldr w0, [x29, #-128]
    sub x9, x29, #656
    str w0, [x9]
    // ENV DUMP [after-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    // ENV DUMP [before-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    ldr x0, [x29, #-48]
    sub x9, x29, #672
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    b .Lendif_115
.Lelse_114:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-640]
    sub x9, x29, #640
    ldr w0, [x9]
    mov w1, w0
    mov w0, #4
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_116
    // ENV DUMP [before-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    // CG_VAR raw='nota4' san='nota4'
    // load nota4 @ [x29,#-144]
    ldr w0, [x29, #-144]
    sub x9, x29, #656
    str w0, [x9]
    // ENV DUMP [after-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    // ENV DUMP [before-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    ldr x0, [x29, #-64]
    sub x9, x29, #672
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    b .Lendif_117
.Lelse_116:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-640]
    sub x9, x29, #640
    ldr w0, [x9]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_118
    // ENV DUMP [before-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    // CG_VAR raw='nota5' san='nota5'
    // load nota5 @ [x29,#-160]
    ldr w0, [x29, #-160]
    sub x9, x29, #656
    str w0, [x9]
    // ENV DUMP [after-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    // ENV DUMP [before-assign] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
    ldr x0, [x29, #-80]
    sub x9, x29, #672
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=33 local_bytes=672
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='notaActual' off=-656
    //   #32 name='nombreActual' off=-672
.Lelse_118:
.Lendif_119:
.Lendif_117:
.Lendif_115:
.Lendif_113:
.Lendif_111:
.data
pfmt_74: .asciz "Verificando: %s - %d\n"
.text
    sub x9, x29, #672
    ldr x1, [x9]
    // CG_VAR raw='notaActual' san='notaActual'
    // load notaActual @ [x29,#-656]
    sub x9, x29, #656
    ldr w0, [x9]
    mov  w2, w0
    adrp x0, pfmt_74
    add  x0, x0, :lo12:pfmt_74
    bl   printf
    // CG_VAR raw='notaActual' san='notaActual'
    // load notaActual @ [x29,#-656]
    sub x9, x29, #656
    ldr w0, [x9]
    mov w1, w0
    mov w0, #90
    cmp w1, w0
    cset w0, gt
    cbz w0, .Lelse_120
.data
pfmt_75: .asciz "Encontrado! %s supera 90 puntos\n"
.text
    sub x9, x29, #672
    ldr x1, [x9]
    adrp x0, pfmt_75
    add  x0, x0, :lo12:pfmt_75
    bl   printf
    b .Lfor_end_109
.Lelse_120:
.Lendif_121:
    b .Lfor_step_108
.Lfor_step_108:
    sub x9, x29, #640
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #640
    str w10, [x9]
    mov w0, w9
    b .Lfor_cond_107
.Lfor_end_109:
.data
str_76: .asciz "\nBusqueda limitada con while y break:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_76
    add  x1, x1, :lo12:str_76
    bl   printf
    // decl posicion @ [x29,#-688]
    mov w0, #1
    sub x9, x29, #688
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=32 local_bytes=688
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
.Lwhile_cond_122:
    mov w0, #1
    and w0, w0, #1
    cbz w0, .Lwhile_end_123
    // CG_VAR raw='posicion' san='posicion'
    // load posicion @ [x29,#-688]
    sub x9, x29, #688
    ldr w0, [x9]
    mov w1, w0
    mov w0, #3
    cmp w1, w0
    cset w0, gt
    cbz w0, .Lelse_124
.data
str_77: .asciz "Limite alcanzado, usando break para salir"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_77
    add  x1, x1, :lo12:str_77
    bl   printf
    b .Lwhile_end_123
.Lelse_124:
.Lendif_125:
.data
pfmt_78: .asciz "Procesando posicion: %d\n"
.text
    // CG_VAR raw='posicion' san='posicion'
    // load posicion @ [x29,#-688]
    sub x9, x29, #688
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_78
    add  x0, x0, :lo12:pfmt_78
    bl   printf
    sub x9, x29, #688
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #688
    str w10, [x9]
    mov w0, w9
    b .Lwhile_cond_122
.Lwhile_end_123:
.data
str_79: .asciz "\nBreak en for anidado:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_79
    add  x1, x1, :lo12:str_79
    bl   printf
    // decl i @ [x29,#-704]
    mov w0, #1
    sub x9, x29, #704
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=33 local_bytes=704
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
.Lfor_cond_126:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-704]
    sub x9, x29, #704
    ldr w0, [x9]
    mov w1, w0
    mov w0, #3
    cmp w1, w0
    cset w0, le
    cbz w0, .Lfor_end_128
.data
pfmt_80: .asciz "Fila %d:\n"
.text
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-704]
    sub x9, x29, #704
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_80
    add  x0, x0, :lo12:pfmt_80
    bl   printf
    // decl j @ [x29,#-720]
    mov w0, #1
    sub x9, x29, #720
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=34 local_bytes=720
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='j' off=-720
.Lfor_cond_129:
    // CG_VAR raw='j' san='j'
    // load j @ [x29,#-720]
    sub x9, x29, #720
    ldr w0, [x9]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, le
    cbz w0, .Lfor_end_131
    // CG_VAR raw='j' san='j'
    // load j @ [x29,#-720]
    sub x9, x29, #720
    ldr w0, [x9]
    mov w1, w0
    mov w0, #3
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_132
.data
str_81: .asciz "  Break en columna 3"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_81
    add  x1, x1, :lo12:str_81
    bl   printf
    b .Lfor_end_131
.Lelse_132:
.Lendif_133:
.data
pfmt_82: .asciz "  Columna %d\n"
.text
    // CG_VAR raw='j' san='j'
    // load j @ [x29,#-720]
    sub x9, x29, #720
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_82
    add  x0, x0, :lo12:pfmt_82
    bl   printf
    b .Lfor_step_130
.Lfor_step_130:
    sub x9, x29, #720
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #720
    str w10, [x9]
    mov w0, w9
    b .Lfor_cond_129
.Lfor_end_131:
    b .Lfor_step_127
.Lfor_step_127:
    sub x9, x29, #704
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #704
    str w10, [x9]
    mov w0, w9
    b .Lfor_cond_126
.Lfor_end_128:
.data
str_83: .asciz "\n--- DEMOSTRACION DE CONTINUE ---"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_83
    add  x1, x1, :lo12:str_83
    bl   printf
.data
str_84: .asciz "Procesando solo notas pares (con continue):"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_84
    add  x1, x1, :lo12:str_84
    bl   printf
    // decl i @ [x29,#-736]
    mov w0, #1
    sub x9, x29, #736
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=34 local_bytes=736
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
.Lfor_cond_134:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-736]
    sub x9, x29, #736
    ldr w0, [x9]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, le
    cbz w0, .Lfor_end_136
    // decl notaActual @ [x29,#-752]
    mov w0, #0
    sub x9, x29, #752
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=35 local_bytes=752
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    // decl nombreActual @ [x29,#-768]
.data
slit_85: .asciz ""
.text
    adrp x0, slit_85
    add  x0, x0, :lo12:slit_85
    sub x9, x29, #768
    str x0, [x9]
    // ENV DUMP [after-decl-store] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-736]
    sub x9, x29, #736
    ldr w0, [x9]
    mov w1, w0
    mov w0, #1
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_137
    // ENV DUMP [before-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    sub x9, x29, #752
    str w0, [x9]
    // ENV DUMP [after-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    // ENV DUMP [before-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    ldr x0, [x29, #-16]
    sub x9, x29, #768
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    b .Lendif_138
.Lelse_137:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-736]
    sub x9, x29, #736
    ldr w0, [x9]
    mov w1, w0
    mov w0, #2
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_139
    // ENV DUMP [before-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    sub x9, x29, #752
    str w0, [x9]
    // ENV DUMP [after-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    // ENV DUMP [before-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    ldr x0, [x29, #-32]
    sub x9, x29, #768
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    b .Lendif_140
.Lelse_139:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-736]
    sub x9, x29, #736
    ldr w0, [x9]
    mov w1, w0
    mov w0, #3
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_141
    // ENV DUMP [before-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    // CG_VAR raw='nota3' san='nota3'
    // load nota3 @ [x29,#-128]
    ldr w0, [x29, #-128]
    sub x9, x29, #752
    str w0, [x9]
    // ENV DUMP [after-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    // ENV DUMP [before-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    ldr x0, [x29, #-48]
    sub x9, x29, #768
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    b .Lendif_142
.Lelse_141:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-736]
    sub x9, x29, #736
    ldr w0, [x9]
    mov w1, w0
    mov w0, #4
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_143
    // ENV DUMP [before-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    // CG_VAR raw='nota4' san='nota4'
    // load nota4 @ [x29,#-144]
    ldr w0, [x29, #-144]
    sub x9, x29, #752
    str w0, [x9]
    // ENV DUMP [after-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    // ENV DUMP [before-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    ldr x0, [x29, #-64]
    sub x9, x29, #768
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    b .Lendif_144
.Lelse_143:
    // CG_VAR raw='i' san='i'
    // load i @ [x29,#-736]
    sub x9, x29, #736
    ldr w0, [x9]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_145
    // ENV DUMP [before-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    // CG_VAR raw='nota5' san='nota5'
    // load nota5 @ [x29,#-160]
    ldr w0, [x29, #-160]
    sub x9, x29, #752
    str w0, [x9]
    // ENV DUMP [after-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    // ENV DUMP [before-assign] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
    ldr x0, [x29, #-80]
    sub x9, x29, #768
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=36 local_bytes=768
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='notaActual' off=-752
    //   #35 name='nombreActual' off=-768
.Lelse_145:
.Lendif_146:
.Lendif_144:
.Lendif_142:
.Lendif_140:
.Lendif_138:
    // CG_VAR raw='notaActual' san='notaActual'
    // load notaActual @ [x29,#-752]
    sub x9, x29, #752
    ldr w0, [x9]
    mov w1, w0
    mov w0, #2
    sdiv w9, w1, w0
    msub w0, w9, w0, w1
    mov w1, w0
    mov w0, #0
    cmp w1, w0
    cset w0, ne
    cbz w0, .Lelse_147
.data
pfmt_86: .asciz "Saltando %s (nota impar: %d)\n"
.text
    sub x9, x29, #768
    ldr x1, [x9]
    // CG_VAR raw='notaActual' san='notaActual'
    // load notaActual @ [x29,#-752]
    sub x9, x29, #752
    ldr w0, [x9]
    mov  w2, w0
    adrp x0, pfmt_86
    add  x0, x0, :lo12:pfmt_86
    bl   printf
    b .Lfor_step_135
.Lelse_147:
.Lendif_148:
.data
pfmt_87: .asciz "Procesando %s (nota par: %d)\n"
.text
    sub x9, x29, #768
    ldr x1, [x9]
    // CG_VAR raw='notaActual' san='notaActual'
    // load notaActual @ [x29,#-752]
    sub x9, x29, #752
    ldr w0, [x9]
    mov  w2, w0
    adrp x0, pfmt_87
    add  x0, x0, :lo12:pfmt_87
    bl   printf
    b .Lfor_step_135
.Lfor_step_135:
    sub x9, x29, #736
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #736
    str w10, [x9]
    mov w0, w9
    b .Lfor_cond_134
.Lfor_end_136:
.data
str_88: .asciz "\nConteo con continue (saltando multiplos de 3):"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_88
    add  x1, x1, :lo12:str_88
    bl   printf
    // decl numero @ [x29,#-784]
    mov w0, #0
    sub x9, x29, #784
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=35 local_bytes=784
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
.Lwhile_cond_149:
    // CG_VAR raw='numero' san='numero'
    // load numero @ [x29,#-784]
    sub x9, x29, #784
    ldr w0, [x9]
    mov w1, w0
    mov w0, #10
    cmp w1, w0
    cset w0, lt
    and w0, w0, #1
    cbz w0, .Lwhile_end_150
    sub x9, x29, #784
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #784
    str w10, [x9]
    mov w0, w9
    // CG_VAR raw='numero' san='numero'
    // load numero @ [x29,#-784]
    sub x9, x29, #784
    ldr w0, [x9]
    mov w1, w0
    mov w0, #3
    sdiv w9, w1, w0
    msub w0, w9, w0, w1
    mov w1, w0
    mov w0, #0
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_151
.data
pfmt_89: .asciz "Saltando multiplo de 3: %d\n"
.text
    // CG_VAR raw='numero' san='numero'
    // load numero @ [x29,#-784]
    sub x9, x29, #784
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_89
    add  x0, x0, :lo12:pfmt_89
    bl   printf
    b .Lwhile_cond_149
.Lelse_151:
.Lendif_152:
.data
pfmt_90: .asciz "Numero procesado: %d\n"
.text
    // CG_VAR raw='numero' san='numero'
    // load numero @ [x29,#-784]
    sub x9, x29, #784
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_90
    add  x0, x0, :lo12:pfmt_90
    bl   printf
    b .Lwhile_cond_149
.Lwhile_end_150:
.data
str_91: .asciz "\nMatriz con continue anidado:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_91
    add  x1, x1, :lo12:str_91
    bl   printf
    // decl fila @ [x29,#-800]
    mov w0, #1
    sub x9, x29, #800
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=36 local_bytes=800
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
.Lfor_cond_153:
    // CG_VAR raw='fila' san='fila'
    // load fila @ [x29,#-800]
    sub x9, x29, #800
    ldr w0, [x9]
    mov w1, w0
    mov w0, #3
    cmp w1, w0
    cset w0, le
    cbz w0, .Lfor_end_155
    // decl columna @ [x29,#-816]
    mov w0, #1
    sub x9, x29, #816
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=37 local_bytes=816
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='columna' off=-816
.Lfor_cond_156:
    // CG_VAR raw='columna' san='columna'
    // load columna @ [x29,#-816]
    sub x9, x29, #816
    ldr w0, [x9]
    mov w1, w0
    mov w0, #4
    cmp w1, w0
    cset w0, le
    cbz w0, .Lfor_end_158
    // CG_VAR raw='columna' san='columna'
    // load columna @ [x29,#-816]
    sub x9, x29, #816
    ldr w0, [x9]
    mov w1, w0
    mov w0, #2
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_159
    b .Lfor_step_157
.Lelse_159:
.Lendif_160:
.data
pfmt_92: .asciz "Celda [%d,%d]\n"
.text
    // CG_VAR raw='fila' san='fila'
    // load fila @ [x29,#-800]
    sub x9, x29, #800
    ldr w0, [x9]
    mov  w1, w0
    // CG_VAR raw='columna' san='columna'
    // load columna @ [x29,#-816]
    sub x9, x29, #816
    ldr w0, [x9]
    mov  w2, w0
    adrp x0, pfmt_92
    add  x0, x0, :lo12:pfmt_92
    bl   printf
    b .Lfor_step_157
.Lfor_step_157:
    sub x9, x29, #816
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #816
    str w10, [x9]
    mov w0, w9
    b .Lfor_cond_156
.Lfor_end_158:
    b .Lfor_step_154
.Lfor_step_154:
    sub x9, x29, #800
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #800
    str w10, [x9]
    mov w0, w9
    b .Lfor_cond_153
.Lfor_end_155:
.data
str_93: .asciz "\nProcesamiento selectivo con continue:"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_93
    add  x1, x1, :lo12:str_93
    bl   printf
    // decl pos @ [x29,#-832]
    mov w0, #1
    sub x9, x29, #832
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=37 local_bytes=832
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
.Lfor_cond_161:
    // CG_VAR raw='pos' san='pos'
    // load pos @ [x29,#-832]
    sub x9, x29, #832
    ldr w0, [x9]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, le
    cbz w0, .Lfor_end_163
    // decl notaPos @ [x29,#-848]
    mov w0, #0
    sub x9, x29, #848
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=38 local_bytes=848
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    // decl edadPos @ [x29,#-864]
    mov w0, #0
    sub x9, x29, #864
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=39 local_bytes=864
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    // decl nombrePos @ [x29,#-880]
.data
slit_94: .asciz ""
.text
    adrp x0, slit_94
    add  x0, x0, :lo12:slit_94
    sub x9, x29, #880
    str x0, [x9]
    // ENV DUMP [after-decl-store] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // CG_VAR raw='pos' san='pos'
    // load pos @ [x29,#-832]
    sub x9, x29, #832
    ldr w0, [x9]
    mov w1, w0
    mov w0, #1
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_164
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    sub x9, x29, #848
    str w0, [x9]
    // ENV DUMP [after-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // CG_VAR raw='edad1' san='edad1'
    // load edad1 @ [x29,#-176]
    ldr w0, [x29, #-176]
    sub x9, x29, #864
    str w0, [x9]
    // ENV DUMP [after-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    ldr x0, [x29, #-16]
    sub x9, x29, #880
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    b .Lendif_165
.Lelse_164:
    // CG_VAR raw='pos' san='pos'
    // load pos @ [x29,#-832]
    sub x9, x29, #832
    ldr w0, [x9]
    mov w1, w0
    mov w0, #2
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_166
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    sub x9, x29, #848
    str w0, [x9]
    // ENV DUMP [after-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // CG_VAR raw='edad2' san='edad2'
    // load edad2 @ [x29,#-192]
    ldr w0, [x29, #-192]
    sub x9, x29, #864
    str w0, [x9]
    // ENV DUMP [after-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    ldr x0, [x29, #-32]
    sub x9, x29, #880
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    b .Lendif_167
.Lelse_166:
    // CG_VAR raw='pos' san='pos'
    // load pos @ [x29,#-832]
    sub x9, x29, #832
    ldr w0, [x9]
    mov w1, w0
    mov w0, #3
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_168
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // CG_VAR raw='nota3' san='nota3'
    // load nota3 @ [x29,#-128]
    ldr w0, [x29, #-128]
    sub x9, x29, #848
    str w0, [x9]
    // ENV DUMP [after-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // CG_VAR raw='edad3' san='edad3'
    // load edad3 @ [x29,#-208]
    ldr w0, [x29, #-208]
    sub x9, x29, #864
    str w0, [x9]
    // ENV DUMP [after-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    ldr x0, [x29, #-48]
    sub x9, x29, #880
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    b .Lendif_169
.Lelse_168:
    // CG_VAR raw='pos' san='pos'
    // load pos @ [x29,#-832]
    sub x9, x29, #832
    ldr w0, [x9]
    mov w1, w0
    mov w0, #4
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_170
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // CG_VAR raw='nota4' san='nota4'
    // load nota4 @ [x29,#-144]
    ldr w0, [x29, #-144]
    sub x9, x29, #848
    str w0, [x9]
    // ENV DUMP [after-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // CG_VAR raw='edad4' san='edad4'
    // load edad4 @ [x29,#-224]
    ldr w0, [x29, #-224]
    sub x9, x29, #864
    str w0, [x9]
    // ENV DUMP [after-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    ldr x0, [x29, #-64]
    sub x9, x29, #880
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    b .Lendif_171
.Lelse_170:
    // CG_VAR raw='pos' san='pos'
    // load pos @ [x29,#-832]
    sub x9, x29, #832
    ldr w0, [x9]
    mov w1, w0
    mov w0, #5
    cmp w1, w0
    cset w0, eq
    cbz w0, .Lelse_172
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // CG_VAR raw='nota5' san='nota5'
    // load nota5 @ [x29,#-160]
    ldr w0, [x29, #-160]
    sub x9, x29, #848
    str w0, [x9]
    // ENV DUMP [after-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // CG_VAR raw='edad5' san='edad5'
    // load edad5 @ [x29,#-240]
    ldr w0, [x29, #-240]
    sub x9, x29, #864
    str w0, [x9]
    // ENV DUMP [after-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    // ENV DUMP [before-assign] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
    ldr x0, [x29, #-80]
    sub x9, x29, #880
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=40 local_bytes=880
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaPos' off=-848
    //   #38 name='edadPos' off=-864
    //   #39 name='nombrePos' off=-880
.Lelse_172:
.Lendif_173:
.Lendif_171:
.Lendif_169:
.Lendif_167:
.Lendif_165:
    // CG_VAR raw='notaPos' san='notaPos'
    // load notaPos @ [x29,#-848]
    sub x9, x29, #848
    ldr w0, [x9]
    mov w1, w0
    mov w0, #80
    cmp w1, w0
    cset w0, lt
    and w0, w0, #1
    cbnz w0, .Lor_true_174
    // CG_VAR raw='edadPos' san='edadPos'
    // load edadPos @ [x29,#-864]
    sub x9, x29, #864
    ldr w0, [x9]
    mov w1, w0
    mov w0, #21
    cmp w1, w0
    cset w0, gt
    and w0, w0, #1
    b .Lor_end_174
.Lor_true_174:
    mov w0, #1
.Lor_end_174:
    cbz w0, .Lelse_175
.data
pfmt_95: .asciz "Saltando %s (no cumple criterios)\n"
.text
    sub x9, x29, #880
    ldr x1, [x9]
    adrp x0, pfmt_95
    add  x0, x0, :lo12:pfmt_95
    bl   printf
    b .Lfor_step_162
.Lelse_175:
.Lendif_176:
.data
pfmt_96: .asciz "Procesando %s (cumple criterios: nota=%d, edad=%d)\n"
.text
    sub x9, x29, #880
    ldr x1, [x9]
    // CG_VAR raw='notaPos' san='notaPos'
    // load notaPos @ [x29,#-848]
    sub x9, x29, #848
    ldr w0, [x9]
    mov  w2, w0
    // CG_VAR raw='edadPos' san='edadPos'
    // load edadPos @ [x29,#-864]
    sub x9, x29, #864
    ldr w0, [x9]
    mov  w3, w0
    adrp x0, pfmt_96
    add  x0, x0, :lo12:pfmt_96
    bl   printf
    b .Lfor_step_162
.Lfor_step_162:
    sub x9, x29, #832
    ldr w9, [x9]
    add w10, w9, #1
    sub x9, x29, #832
    str w10, [x9]
    mov w0, w9
    b .Lfor_cond_161
.Lfor_end_163:
.data
str_97: .asciz "\n--- RESUMEN FINAL ---"
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_97
    add  x1, x1, :lo12:str_97
    bl   printf
    // decl notaMaxima @ [x29,#-896]
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    sub x9, x29, #896
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=38 local_bytes=896
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    // decl estudianteMejor @ [x29,#-912]
    ldr x0, [x29, #-16]
    sub x9, x29, #912
    str x0, [x9]
    // ENV DUMP [after-decl-store] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    mov w1, w0
    // CG_VAR raw='notaMaxima' san='notaMaxima'
    // load notaMaxima @ [x29,#-896]
    sub x9, x29, #896
    ldr w0, [x9]
    cmp w1, w0
    cset w0, gt
    cbz w0, .Lelse_177
    // ENV DUMP [before-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    sub x9, x29, #896
    str w0, [x9]
    // ENV DUMP [after-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    // ENV DUMP [before-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    ldr x0, [x29, #-32]
    sub x9, x29, #912
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
.Lelse_177:
.Lendif_178:
    // CG_VAR raw='nota3' san='nota3'
    // load nota3 @ [x29,#-128]
    ldr w0, [x29, #-128]
    mov w1, w0
    // CG_VAR raw='notaMaxima' san='notaMaxima'
    // load notaMaxima @ [x29,#-896]
    sub x9, x29, #896
    ldr w0, [x9]
    cmp w1, w0
    cset w0, gt
    cbz w0, .Lelse_179
    // ENV DUMP [before-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    // CG_VAR raw='nota3' san='nota3'
    // load nota3 @ [x29,#-128]
    ldr w0, [x29, #-128]
    sub x9, x29, #896
    str w0, [x9]
    // ENV DUMP [after-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    // ENV DUMP [before-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    ldr x0, [x29, #-48]
    sub x9, x29, #912
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
.Lelse_179:
.Lendif_180:
    // CG_VAR raw='nota4' san='nota4'
    // load nota4 @ [x29,#-144]
    ldr w0, [x29, #-144]
    mov w1, w0
    // CG_VAR raw='notaMaxima' san='notaMaxima'
    // load notaMaxima @ [x29,#-896]
    sub x9, x29, #896
    ldr w0, [x9]
    cmp w1, w0
    cset w0, gt
    cbz w0, .Lelse_181
    // ENV DUMP [before-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    // CG_VAR raw='nota4' san='nota4'
    // load nota4 @ [x29,#-144]
    ldr w0, [x29, #-144]
    sub x9, x29, #896
    str w0, [x9]
    // ENV DUMP [after-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    // ENV DUMP [before-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    ldr x0, [x29, #-64]
    sub x9, x29, #912
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
.Lelse_181:
.Lendif_182:
    // CG_VAR raw='nota5' san='nota5'
    // load nota5 @ [x29,#-160]
    ldr w0, [x29, #-160]
    mov w1, w0
    // CG_VAR raw='notaMaxima' san='notaMaxima'
    // load notaMaxima @ [x29,#-896]
    sub x9, x29, #896
    ldr w0, [x9]
    cmp w1, w0
    cset w0, gt
    cbz w0, .Lelse_183
    // ENV DUMP [before-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    // CG_VAR raw='nota5' san='nota5'
    // load nota5 @ [x29,#-160]
    ldr w0, [x29, #-160]
    sub x9, x29, #896
    str w0, [x9]
    // ENV DUMP [after-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    // ENV DUMP [before-assign] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    ldr x0, [x29, #-80]
    sub x9, x29, #912
    str x0, [x9]
    // ENV DUMP [after-assign (promoted STRING var)] count=39 local_bytes=912
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
.Lelse_183:
.Lendif_184:
    // decl sumaTotal @ [x29,#-928]
    // CG_VAR raw='nota1' san='nota1'
    // load nota1 @ [x29,#-96]
    ldr w0, [x29, #-96]
    mov w1, w0
    // CG_VAR raw='nota2' san='nota2'
    // load nota2 @ [x29,#-112]
    ldr w0, [x29, #-112]
    add w0, w1, w0
    mov w1, w0
    // CG_VAR raw='nota3' san='nota3'
    // load nota3 @ [x29,#-128]
    ldr w0, [x29, #-128]
    add w0, w1, w0
    mov w1, w0
    // CG_VAR raw='nota4' san='nota4'
    // load nota4 @ [x29,#-144]
    ldr w0, [x29, #-144]
    add w0, w1, w0
    mov w1, w0
    // CG_VAR raw='nota5' san='nota5'
    // load nota5 @ [x29,#-160]
    ldr w0, [x29, #-160]
    add w0, w1, w0
    sub x9, x29, #928
    str w0, [x9]
    // ENV DUMP [after-decl-store] count=40 local_bytes=928
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    //   #39 name='sumaTotal' off=-928
    // decl promedioFinal @ [x29,#-944]
.data
dcon_98: .double 0
.text
    adrp x1, dcon_98
    add  x1, x1, :lo12:dcon_98
    ldr  d0, [x1]
    sub x9, x29, #944
    str d0, [x9]
    // ENV DUMP [after-decl-store] count=41 local_bytes=944
    //   #0 name='estudiante1' off=-16
    //   #1 name='estudiante2' off=-32
    //   #2 name='estudiante3' off=-48
    //   #3 name='estudiante4' off=-64
    //   #4 name='estudiante5' off=-80
    //   #5 name='nota1' off=-96
    //   #6 name='nota2' off=-112
    //   #7 name='nota3' off=-128
    //   #8 name='nota4' off=-144
    //   #9 name='nota5' off=-160
    //   #10 name='edad1' off=-176
    //   #11 name='edad2' off=-192
    //   #12 name='edad3' off=-208
    //   #13 name='edad4' off=-224
    //   #14 name='edad5' off=-240
    //   #15 name='estudianteActual' off=-256
    //   #16 name='estudiantesDestacados' off=-272
    //   #17 name='contador' off=-320
    //   #18 name='indice' off=-336
    //   #19 name='i' off=-400
    //   #20 name='i' off=-448
    //   #21 name='i' off=-464
    //   #22 name='notasParaForeach' off=-512
    //   #23 name='suma' off=-528
    //   #24 name='contadorNotas' off=-544
    //   #25 name='promedio' off=-560
    //   #26 name='notasAltas' off=-576
    //   #27 name='notasBajas' off=-592
    //   #28 name='categoria1' off=-608
    //   #29 name='categoria2' off=-624
    //   #30 name='i' off=-640
    //   #31 name='posicion' off=-688
    //   #32 name='i' off=-704
    //   #33 name='i' off=-736
    //   #34 name='numero' off=-784
    //   #35 name='fila' off=-800
    //   #36 name='pos' off=-832
    //   #37 name='notaMaxima' off=-896
    //   #38 name='estudianteMejor' off=-912
    //   #39 name='sumaTotal' off=-928
    //   #40 name='promedioFinal' off=-944
.data
pfmt_99: .asciz "Mejor estudiante: %s con %d\n"
.text
    sub x9, x29, #912
    ldr x1, [x9]
    // CG_VAR raw='notaMaxima' san='notaMaxima'
    // load notaMaxima @ [x29,#-896]
    sub x9, x29, #896
    ldr w0, [x9]
    mov  w2, w0
    adrp x0, pfmt_99
    add  x0, x0, :lo12:pfmt_99
    bl   printf
.data
pfmt_100: .asciz "Promedio general: %d\n"
.text
    // CG_VAR raw='promedioFinal' san='promedioFinal'
    // load promedioFinal @ [x29,#-944]
    sub x9, x29, #944
    ldr w0, [x9]
    mov  w1, w0
    adrp x0, pfmt_100
    add  x0, x0, :lo12:pfmt_100
    bl   printf
.data
str_101: .asciz "\n=== PROCESAMIENTO COMPLETADO ==="
.text
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_101
    add  x1, x1, :lo12:str_101
    bl   printf
    add sp, sp, #944
    mov w0, #0
    ldp x29, x30, [sp], #16
    ret
