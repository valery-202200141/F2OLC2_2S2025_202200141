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
.data
str_1: .asciz "=== SISTEMA DE GESTION DE NOTAS INDIVIDUAL ==="
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_1
    add  x1, x1, :lo12:str_1
    bl   printf
.data
str_2: .asciz "Procesando 5 estudiantes individuales"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_2
    add  x1, x1, :lo12:str_2
    bl   printf
.data
str_3: .asciz "\n--- EVALUACION CON IF/ELSE ---"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_3
    add  x1, x1, :lo12:str_3
    bl   printf
.data
str_4: .asciz "Evaluando: Ana"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_4
    add  x1, x1, :lo12:str_4
    bl   printf
.data
str_5: .asciz "Clasificacion: NOTABLE"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_5
    add  x1, x1, :lo12:str_5
    bl   printf
.data
str_6: .asciz "Resultado: No apto para beca"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_6
    add  x1, x1, :lo12:str_6
    bl   printf
.data
str_7: .asciz "\nEvaluando: Luis"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_7
    add  x1, x1, :lo12:str_7
    bl   printf
.data
str_8: .asciz "Clasificacion: NOTABLE"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_8
    add  x1, x1, :lo12:str_8
    bl   printf
.data
str_9: .asciz "Resultado: Apto para beca"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_9
    add  x1, x1, :lo12:str_9
    bl   printf
.data
str_10: .asciz "\nEvaluando: Maria"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_10
    add  x1, x1, :lo12:str_10
    bl   printf
.data
str_11: .asciz "Clasificacion: BIEN"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_11
    add  x1, x1, :lo12:str_11
    bl   printf
.data
str_12: .asciz "\n--- PROCESAMIENTO CON WHILE ---"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_12
    add  x1, x1, :lo12:str_12
    bl   printf
.data
str_13: .asciz "Buscando estudiantes con nota >= 90:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_13
    add  x1, x1, :lo12:str_13
    bl   printf
.data
str_14: .asciz "Revisando estudiante 1: Ana"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_14
    add  x1, x1, :lo12:str_14
    bl   printf
.data
str_15: .asciz "Revisando estudiante 2: Luis"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_15
    add  x1, x1, :lo12:str_15
    bl   printf
.data
str_16: .asciz "Destacado encontrado: Luis con 92"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_16
    add  x1, x1, :lo12:str_16
    bl   printf
.data
str_17: .asciz "Revisando estudiante 3: Maria"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_17
    add  x1, x1, :lo12:str_17
    bl   printf
.data
str_18: .asciz "Revisando estudiante 4: Carlos"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_18
    add  x1, x1, :lo12:str_18
    bl   printf
.data
str_19: .asciz "Destacado encontrado: Carlos con 95"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_19
    add  x1, x1, :lo12:str_19
    bl   printf
.data
str_20: .asciz "Revisando estudiante 5: Sofia"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_20
    add  x1, x1, :lo12:str_20
    bl   printf
.data
str_21: .asciz "Total de estudiantes destacados: 2"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_21
    add  x1, x1, :lo12:str_21
    bl   printf
.data
str_22: .asciz "\nContador regresivo:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_22
    add  x1, x1, :lo12:str_22
    bl   printf
.data
str_23: .asciz "Quedan: 5 estudiantes por procesar"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_23
    add  x1, x1, :lo12:str_23
    bl   printf
.data
str_24: .asciz "Quedan: 4 estudiantes por procesar"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_24
    add  x1, x1, :lo12:str_24
    bl   printf
.data
str_25: .asciz "Quedan: 3 estudiantes por procesar"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_25
    add  x1, x1, :lo12:str_25
    bl   printf
.data
str_26: .asciz "Quedan: 2 estudiantes por procesar"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_26
    add  x1, x1, :lo12:str_26
    bl   printf
.data
str_27: .asciz "Quedan: 1 estudiantes por procesar"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_27
    add  x1, x1, :lo12:str_27
    bl   printf
.data
str_28: .asciz "\nBusqueda de estudiante joven con buena nota:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_28
    add  x1, x1, :lo12:str_28
    bl   printf
.data
str_29: .asciz "Estudiante joven destacado: Luis (Edad: 19, Nota: 92)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_29
    add  x1, x1, :lo12:str_29
    bl   printf
.data
str_30: .asciz "Estudiante joven destacado: Carlos (Edad: 20, Nota: 95)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_30
    add  x1, x1, :lo12:str_30
    bl   printf
.data
str_31: .asciz "\n--- PROCESAMIENTO CON FOR CLASICO ---"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_31
    add  x1, x1, :lo12:str_31
    bl   printf
.data
str_32: .asciz "Listado numerado:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_32
    add  x1, x1, :lo12:str_32
    bl   printf
.data
str_33: .asciz "1. Ana - Nota: 85"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_33
    add  x1, x1, :lo12:str_33
    bl   printf
.data
str_34: .asciz "2. Luis - Nota: 92"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_34
    add  x1, x1, :lo12:str_34
    bl   printf
.data
str_35: .asciz "3. Maria - Nota: 78"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_35
    add  x1, x1, :lo12:str_35
    bl   printf
.data
str_36: .asciz "4. Carlos - Nota: 95"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_36
    add  x1, x1, :lo12:str_36
    bl   printf
.data
str_37: .asciz "5. Sofia - Nota: 88"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_37
    add  x1, x1, :lo12:str_37
    bl   printf
.data
str_38: .asciz "\nProceso inverso:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_38
    add  x1, x1, :lo12:str_38
    bl   printf
.data
str_39: .asciz "Procesando posicion: 5"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_39
    add  x1, x1, :lo12:str_39
    bl   printf
.data
str_40: .asciz "Procesando posicion: 4"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_40
    add  x1, x1, :lo12:str_40
    bl   printf
.data
str_41: .asciz "Procesando posicion: 3"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_41
    add  x1, x1, :lo12:str_41
    bl   printf
.data
str_42: .asciz "Procesando posicion: 2"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_42
    add  x1, x1, :lo12:str_42
    bl   printf
.data
str_43: .asciz "Procesando posicion: 1"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_43
    add  x1, x1, :lo12:str_43
    bl   printf
.data
str_44: .asciz "\nTabla de multiplicar (1-3 x 1-4):"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_44
    add  x1, x1, :lo12:str_44
    bl   printf
.data
str_45: .asciz "1 x 1 = 1"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_45
    add  x1, x1, :lo12:str_45
    bl   printf
.data
str_46: .asciz "1 x 2 = 2"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_46
    add  x1, x1, :lo12:str_46
    bl   printf
.data
str_47: .asciz "1 x 3 = 3"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_47
    add  x1, x1, :lo12:str_47
    bl   printf
.data
str_48: .asciz "1 x 4 = 4"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_48
    add  x1, x1, :lo12:str_48
    bl   printf
.data
str_49: .asciz "2 x 1 = 2"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_49
    add  x1, x1, :lo12:str_49
    bl   printf
.data
str_50: .asciz "2 x 2 = 4"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_50
    add  x1, x1, :lo12:str_50
    bl   printf
.data
str_51: .asciz "2 x 3 = 6"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_51
    add  x1, x1, :lo12:str_51
    bl   printf
.data
str_52: .asciz "2 x 4 = 8"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_52
    add  x1, x1, :lo12:str_52
    bl   printf
.data
str_53: .asciz "3 x 1 = 3"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_53
    add  x1, x1, :lo12:str_53
    bl   printf
.data
str_54: .asciz "3 x 2 = 6"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_54
    add  x1, x1, :lo12:str_54
    bl   printf
.data
str_55: .asciz "3 x 3 = 9"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_55
    add  x1, x1, :lo12:str_55
    bl   printf
.data
str_56: .asciz "3 x 4 = 12"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_56
    add  x1, x1, :lo12:str_56
    bl   printf
.data
str_57: .asciz "\n--- FOREACH CON ARRAY SIMPLE ---"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_57
    add  x1, x1, :lo12:str_57
    bl   printf
.data
str_58: .asciz "Procesando notas con forEach:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_58
    add  x1, x1, :lo12:str_58
    bl   printf
.data
str_59: .asciz "Nota 1: 85"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_59
    add  x1, x1, :lo12:str_59
    bl   printf
.data
str_60: .asciz "Nota 2: 92"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_60
    add  x1, x1, :lo12:str_60
    bl   printf
.data
str_61: .asciz "Nota 3: 78"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_61
    add  x1, x1, :lo12:str_61
    bl   printf
.data
str_62: .asciz "Nota 4: 95"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_62
    add  x1, x1, :lo12:str_62
    bl   printf
.data
str_63: .asciz "Nota 5: 88"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_63
    add  x1, x1, :lo12:str_63
    bl   printf
.data
str_64: .asciz "Promedio calculado con forEach: 87.600000"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_64
    add  x1, x1, :lo12:str_64
    bl   printf
.data
str_65: .asciz "\nConteo de categorias con forEach:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_65
    add  x1, x1, :lo12:str_65
    bl   printf
.data
str_66: .asciz "Nota alta encontrada: 92"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_66
    add  x1, x1, :lo12:str_66
    bl   printf
.data
str_67: .asciz "Nota baja encontrada: 78"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_67
    add  x1, x1, :lo12:str_67
    bl   printf
.data
str_68: .asciz "Nota alta encontrada: 95"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_68
    add  x1, x1, :lo12:str_68
    bl   printf
.data
str_69: .asciz "Total notas altas (>=90): 2"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_69
    add  x1, x1, :lo12:str_69
    bl   printf
.data
str_70: .asciz "Total notas bajas (<80): 1"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_70
    add  x1, x1, :lo12:str_70
    bl   printf
.data
str_71: .asciz "\n--- CLASIFICACION CON SWITCH/CASE ---"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_71
    add  x1, x1, :lo12:str_71
    bl   printf
.data
str_72: .asciz "Analizando: Ana (Nota: 85)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_72
    add  x1, x1, :lo12:str_72
    bl   printf
.data
str_73: .asciz "Categoria: MUY BUENO"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_73
    add  x1, x1, :lo12:str_73
    bl   printf
.data
str_74: .asciz "\nAnalizando: Luis (Nota: 92)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_74
    add  x1, x1, :lo12:str_74
    bl   printf
.data
str_75: .asciz "Categoria: EXCELENTE"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_75
    add  x1, x1, :lo12:str_75
    bl   printf
.data
str_76: .asciz "\nAnalisis por edad:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_76
    add  x1, x1, :lo12:str_76
    bl   printf
.data
str_77: .asciz "\n--- DEMOSTRACION DE BREAK ---"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_77
    add  x1, x1, :lo12:str_77
    bl   printf
.data
str_78: .asciz "Busqueda con break (primera nota > 90):"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_78
    add  x1, x1, :lo12:str_78
    bl   printf
.data
str_79: .asciz "Verificando: Ana - 85"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_79
    add  x1, x1, :lo12:str_79
    bl   printf
.data
str_80: .asciz "Verificando: Luis - 92"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_80
    add  x1, x1, :lo12:str_80
    bl   printf
.data
str_81: .asciz "Encontrado! Luis supera 90 puntos"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_81
    add  x1, x1, :lo12:str_81
    bl   printf
.data
str_82: .asciz "\nBusqueda limitada con while y break:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_82
    add  x1, x1, :lo12:str_82
    bl   printf
.data
str_83: .asciz "Procesando posicion: 1"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_83
    add  x1, x1, :lo12:str_83
    bl   printf
.data
str_84: .asciz "Procesando posicion: 2"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_84
    add  x1, x1, :lo12:str_84
    bl   printf
.data
str_85: .asciz "Procesando posicion: 3"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_85
    add  x1, x1, :lo12:str_85
    bl   printf
.data
str_86: .asciz "Limite alcanzado, usando break para salir"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_86
    add  x1, x1, :lo12:str_86
    bl   printf
.data
str_87: .asciz "\nBreak en for anidado:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_87
    add  x1, x1, :lo12:str_87
    bl   printf
.data
str_88: .asciz "Fila 1:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_88
    add  x1, x1, :lo12:str_88
    bl   printf
.data
str_89: .asciz "  Columna 1"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_89
    add  x1, x1, :lo12:str_89
    bl   printf
.data
str_90: .asciz "  Columna 2"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_90
    add  x1, x1, :lo12:str_90
    bl   printf
.data
str_91: .asciz "  Break en columna 3"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_91
    add  x1, x1, :lo12:str_91
    bl   printf
.data
str_92: .asciz "Fila 2:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_92
    add  x1, x1, :lo12:str_92
    bl   printf
.data
str_93: .asciz "  Columna 1"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_93
    add  x1, x1, :lo12:str_93
    bl   printf
.data
str_94: .asciz "  Columna 2"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_94
    add  x1, x1, :lo12:str_94
    bl   printf
.data
str_95: .asciz "  Break en columna 3"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_95
    add  x1, x1, :lo12:str_95
    bl   printf
.data
str_96: .asciz "Fila 3:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_96
    add  x1, x1, :lo12:str_96
    bl   printf
.data
str_97: .asciz "  Columna 1"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_97
    add  x1, x1, :lo12:str_97
    bl   printf
.data
str_98: .asciz "  Columna 2"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_98
    add  x1, x1, :lo12:str_98
    bl   printf
.data
str_99: .asciz "  Break en columna 3"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_99
    add  x1, x1, :lo12:str_99
    bl   printf
.data
str_100: .asciz "\n--- DEMOSTRACION DE CONTINUE ---"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_100
    add  x1, x1, :lo12:str_100
    bl   printf
.data
str_101: .asciz "Procesando solo notas pares (con continue):"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_101
    add  x1, x1, :lo12:str_101
    bl   printf
.data
str_102: .asciz "Saltando Ana (nota impar: 85)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_102
    add  x1, x1, :lo12:str_102
    bl   printf
.data
str_103: .asciz "Procesando Luis (nota par: 92)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_103
    add  x1, x1, :lo12:str_103
    bl   printf
.data
str_104: .asciz "Procesando Maria (nota par: 78)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_104
    add  x1, x1, :lo12:str_104
    bl   printf
.data
str_105: .asciz "Saltando Carlos (nota impar: 95)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_105
    add  x1, x1, :lo12:str_105
    bl   printf
.data
str_106: .asciz "Procesando Sofia (nota par: 88)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_106
    add  x1, x1, :lo12:str_106
    bl   printf
.data
str_107: .asciz "\nConteo con continue (saltando multiplos de 3):"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_107
    add  x1, x1, :lo12:str_107
    bl   printf
.data
str_108: .asciz "Numero procesado: 1"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_108
    add  x1, x1, :lo12:str_108
    bl   printf
.data
str_109: .asciz "Numero procesado: 2"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_109
    add  x1, x1, :lo12:str_109
    bl   printf
.data
str_110: .asciz "Saltando multiplo de 3: 3"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_110
    add  x1, x1, :lo12:str_110
    bl   printf
.data
str_111: .asciz "Numero procesado: 4"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_111
    add  x1, x1, :lo12:str_111
    bl   printf
.data
str_112: .asciz "Numero procesado: 5"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_112
    add  x1, x1, :lo12:str_112
    bl   printf
.data
str_113: .asciz "Saltando multiplo de 3: 6"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_113
    add  x1, x1, :lo12:str_113
    bl   printf
.data
str_114: .asciz "Numero procesado: 7"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_114
    add  x1, x1, :lo12:str_114
    bl   printf
.data
str_115: .asciz "Numero procesado: 8"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_115
    add  x1, x1, :lo12:str_115
    bl   printf
.data
str_116: .asciz "Saltando multiplo de 3: 9"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_116
    add  x1, x1, :lo12:str_116
    bl   printf
.data
str_117: .asciz "Numero procesado: 10"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_117
    add  x1, x1, :lo12:str_117
    bl   printf
.data
str_118: .asciz "\nMatriz con continue anidado:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_118
    add  x1, x1, :lo12:str_118
    bl   printf
.data
str_119: .asciz "Celda [1,1]"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_119
    add  x1, x1, :lo12:str_119
    bl   printf
.data
str_120: .asciz "Celda [1,3]"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_120
    add  x1, x1, :lo12:str_120
    bl   printf
.data
str_121: .asciz "Celda [1,4]"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_121
    add  x1, x1, :lo12:str_121
    bl   printf
.data
str_122: .asciz "Celda [2,1]"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_122
    add  x1, x1, :lo12:str_122
    bl   printf
.data
str_123: .asciz "Celda [2,3]"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_123
    add  x1, x1, :lo12:str_123
    bl   printf
.data
str_124: .asciz "Celda [2,4]"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_124
    add  x1, x1, :lo12:str_124
    bl   printf
.data
str_125: .asciz "Celda [3,1]"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_125
    add  x1, x1, :lo12:str_125
    bl   printf
.data
str_126: .asciz "Celda [3,3]"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_126
    add  x1, x1, :lo12:str_126
    bl   printf
.data
str_127: .asciz "Celda [3,4]"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_127
    add  x1, x1, :lo12:str_127
    bl   printf
.data
str_128: .asciz "\nProcesamiento selectivo con continue:"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_128
    add  x1, x1, :lo12:str_128
    bl   printf
.data
str_129: .asciz "Procesando Ana (cumple criterios: nota=85, edad=20)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_129
    add  x1, x1, :lo12:str_129
    bl   printf
.data
str_130: .asciz "Procesando Luis (cumple criterios: nota=92, edad=19)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_130
    add  x1, x1, :lo12:str_130
    bl   printf
.data
str_131: .asciz "Saltando Maria (no cumple criterios)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_131
    add  x1, x1, :lo12:str_131
    bl   printf
.data
str_132: .asciz "Procesando Carlos (cumple criterios: nota=95, edad=20)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_132
    add  x1, x1, :lo12:str_132
    bl   printf
.data
str_133: .asciz "Saltando Sofia (no cumple criterios)"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_133
    add  x1, x1, :lo12:str_133
    bl   printf
.data
str_134: .asciz "\n--- RESUMEN FINAL ---"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_134
    add  x1, x1, :lo12:str_134
    bl   printf
.data
str_135: .asciz "Mejor estudiante: Carlos con 95"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_135
    add  x1, x1, :lo12:str_135
    bl   printf
.data
str_136: .asciz "Promedio general: 87.600000"
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_136
    add  x1, x1, :lo12:str_136
    bl   printf
.data
str_137: .asciz "\n=== PROCESAMIENTO COMPLETADO ==="
    adrp x0, fmt_str
    add  x0, x0, :lo12:fmt_str
    adrp x1, str_137
    add  x1, x1, :lo12:str_137
    bl   printf
    mov w0, #0
    ldp x29, x30, [sp], #16
    ret
