/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "../include/ast.h" 
#include "../include/lexer_utils.h"
#include "../include/parser_utils.h"
#include "../include/errores.h"
#include "../include/semantic.h"

// Declaraciones de funciones
int yylex(void);
void yyerror(const char *s);

// AGREGAR: Declaraciones externas del lexer
extern int yylineno;        // Número de línea actual
extern char *yytext;        // Texto del token actual
extern void yyrestart(FILE *input_file);  // Reiniciar lexer
extern data_type_t string_to_type(const char* type_str);
extern void add_symbol_to_table(const char* name, data_type_t type, const char* scope, int line);

// Variable global para la raíz del AST 
ast_node *root = NULL;
char* type_token_to_string(int token);

// Declaración externa 
extern symbol_table_t *global_symbol_table;
static ast_node *g_switch_expr = NULL;

static ast_node* append_switch_case(ast_node *chain, ast_node *new_case) {
    if (!chain) return new_case;
    ast_node *cur = chain;

    // Buscar la última IF en la cadena (siguiendo else_branch)
    ast_node *last_if = NULL;
    ast_node *walker = cur;
    while (walker) {
        if (walker->type == AST_IF) last_if = walker;
        // Preferir descender por else_branch cuando exista (cadena if-else-if)
        if (walker->type == AST_IF && walker->data.if_stmt.else_branch) {
            walker = walker->data.if_stmt.else_branch;
            continue;
        }
        // sino avanzar por next
        if (walker->next) { walker = walker->next; continue; }
        break;
    }

    if (last_if && last_if->data.if_stmt.else_branch == NULL) {
        // Si new_case es IF, enlazar como else_branch; si no, poner el bloque (default) como else
        last_if->data.if_stmt.else_branch = new_case;
        return chain;
    }

    // Fallback: anexar al final de la lista via next
    ast_node *last = chain;
    while (last->next) last = last->next;
    last->next = new_case;
    return chain;
}


#line 133 "src/parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INT_LITERAL = 4,                /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 5,              /* FLOAT_LITERAL  */
  YYSYMBOL_DOUBLE_LITERAL = 6,             /* DOUBLE_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 7,             /* STRING_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 8,               /* CHAR_LITERAL  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 11,                    /* DOUBLE  */
  YYSYMBOL_BOOLEAN = 12,                   /* BOOLEAN  */
  YYSYMBOL_CHAR = 13,                      /* CHAR  */
  YYSYMBOL_STRING_TYPE = 14,               /* STRING_TYPE  */
  YYSYMBOL_CLASS = 15,                     /* CLASS  */
  YYSYMBOL_PUBLIC = 16,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 17,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 18,                 /* PROTECTED  */
  YYSYMBOL_STATIC = 19,                    /* STATIC  */
  YYSYMBOL_FINAL = 20,                     /* FINAL  */
  YYSYMBOL_VOID = 21,                      /* VOID  */
  YYSYMBOL_SYSTEM = 22,                    /* SYSTEM  */
  YYSYMBOL_OUT = 23,                       /* OUT  */
  YYSYMBOL_PRINTLN = 24,                   /* PRINTLN  */
  YYSYMBOL_EQUALS_METHOD = 25,             /* EQUALS_METHOD  */
  YYSYMBOL_IF = 26,                        /* IF  */
  YYSYMBOL_ELSE = 27,                      /* ELSE  */
  YYSYMBOL_WHILE = 28,                     /* WHILE  */
  YYSYMBOL_FOR = 29,                       /* FOR  */
  YYSYMBOL_DO = 30,                        /* DO  */
  YYSYMBOL_SWITCH = 31,                    /* SWITCH  */
  YYSYMBOL_CASE = 32,                      /* CASE  */
  YYSYMBOL_DEFAULT = 33,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 34,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 35,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 36,                    /* RETURN  */
  YYSYMBOL_NEW = 37,                       /* NEW  */
  YYSYMBOL_THIS = 38,                      /* THIS  */
  YYSYMBOL_TRUE_TOKEN = 39,                /* TRUE_TOKEN  */
  YYSYMBOL_FALSE_TOKEN = 40,               /* FALSE_TOKEN  */
  YYSYMBOL_NULL_TOKEN = 41,                /* NULL_TOKEN  */
  YYSYMBOL_PLUS = 42,                      /* PLUS  */
  YYSYMBOL_MINUS = 43,                     /* MINUS  */
  YYSYMBOL_MULT = 44,                      /* MULT  */
  YYSYMBOL_DIV = 45,                       /* DIV  */
  YYSYMBOL_MOD = 46,                       /* MOD  */
  YYSYMBOL_INCREMENT = 47,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 48,                 /* DECREMENT  */
  YYSYMBOL_ASSIGN = 49,                    /* ASSIGN  */
  YYSYMBOL_PLUS_ASSIGN = 50,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 51,              /* MINUS_ASSIGN  */
  YYSYMBOL_MULT_ASSIGN = 52,               /* MULT_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 53,                /* DIV_ASSIGN  */
  YYSYMBOL_EQUALS = 54,                    /* EQUALS  */
  YYSYMBOL_NOT_EQUALS = 55,                /* NOT_EQUALS  */
  YYSYMBOL_LESS = 56,                      /* LESS  */
  YYSYMBOL_GREATER = 57,                   /* GREATER  */
  YYSYMBOL_LESS_EQUALS = 58,               /* LESS_EQUALS  */
  YYSYMBOL_GREATER_EQUALS = 59,            /* GREATER_EQUALS  */
  YYSYMBOL_AND = 60,                       /* AND  */
  YYSYMBOL_OR = 61,                        /* OR  */
  YYSYMBOL_NOT = 62,                       /* NOT  */
  YYSYMBOL_LPAREN = 63,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 64,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 65,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 66,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 67,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 68,                  /* RBRACKET  */
  YYSYMBOL_SEMICOLON = 69,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 70,                     /* COMMA  */
  YYSYMBOL_DOT = 71,                       /* DOT  */
  YYSYMBOL_COLON = 72,                     /* COLON  */
  YYSYMBOL_INT_ARRAY = 73,                 /* INT_ARRAY  */
  YYSYMBOL_FLOAT_ARRAY = 74,               /* FLOAT_ARRAY  */
  YYSYMBOL_DOUBLE_ARRAY = 75,              /* DOUBLE_ARRAY  */
  YYSYMBOL_STRING_ARRAY = 76,              /* STRING_ARRAY  */
  YYSYMBOL_BOOLEAN_ARRAY = 77,             /* BOOLEAN_ARRAY  */
  YYSYMBOL_CHAR_ARRAY = 78,                /* CHAR_ARRAY  */
  YYSYMBOL_ERROR = 79,                     /* ERROR  */
  YYSYMBOL_UMINUS = 80,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_program = 82,                   /* program  */
  YYSYMBOL_function_list = 83,             /* function_list  */
  YYSYMBOL_function_decl = 84,             /* function_decl  */
  YYSYMBOL_parameter = 85,                 /* parameter  */
  YYSYMBOL_parameter_list = 86,            /* parameter_list  */
  YYSYMBOL_main_function = 87,             /* main_function  */
  YYSYMBOL_function_body = 88,             /* function_body  */
  YYSYMBOL_statement_list = 89,            /* statement_list  */
  YYSYMBOL_statement = 90,                 /* statement  */
  YYSYMBOL_declaration = 91,               /* declaration  */
  YYSYMBOL_declaration_list = 92,          /* declaration_list  */
  YYSYMBOL_declaration_no_semicolon = 93,  /* declaration_no_semicolon  */
  YYSYMBOL_for_init = 94,                  /* for_init  */
  YYSYMBOL_type = 95,                      /* type  */
  YYSYMBOL_assignment = 96,                /* assignment  */
  YYSYMBOL_expression = 97,                /* expression  */
  YYSYMBOL_literal = 98,                   /* literal  */
  YYSYMBOL_if_statement = 99,              /* if_statement  */
  YYSYMBOL_while_statement = 100,          /* while_statement  */
  YYSYMBOL_for_statement = 101,            /* for_statement  */
  YYSYMBOL_return_statement = 102,         /* return_statement  */
  YYSYMBOL_switch_statement = 103,         /* switch_statement  */
  YYSYMBOL_104_1 = 104,                    /* $@1  */
  YYSYMBOL_switch_sections = 105,          /* switch_sections  */
  YYSYMBOL_switch_section = 106,           /* switch_section  */
  YYSYMBOL_statement_list_opt = 107,       /* statement_list_opt  */
  YYSYMBOL_array_declaration = 108,        /* array_declaration  */
  YYSYMBOL_array_initialization = 109,     /* array_initialization  */
  YYSYMBOL_expression_list = 110,          /* expression_list  */
  YYSYMBOL_array_access = 111              /* array_access  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  97
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1900

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  160
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  368

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   335


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   137,   137,   153,   161,   162,   171,   184,   190,   203,
     211,   212,   222,   229,   240,   241,   245,   249,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   282,   287,
     292,   297,   305,   310,   335,   371,   376,   390,   395,   411,
     416,   425,   426,   427,   431,   435,   439,   443,   447,   451,
     455,   459,   464,   468,   472,   476,   481,   488,   500,   501,
     502,   503,   507,   517,   528,   534,   540,   546,   555,   556,
     557,   559,   564,   571,   577,   583,   589,   595,   596,   597,
     598,   599,   600,   601,   602,   603,   604,   605,   606,   607,
     608,   609,   614,   619,   625,   632,   637,   642,   656,   666,
     671,   677,   682,   687,   692,   696,   700,   704,   708,   712,
     716,   720,   724,   728,   732,   736,   740,   744,   748,   752,
     756,   760,   764,   765,   766,   767,   768,   769,   770,   771,
     772,   776,   780,   785,   790,   794,   799,   803,   807,   814,
     819,   827,   831,   838,   842,   851,   856,   864,   864,   875,
     878,   886,   897,   905,   906,   910,   915,   923,   930,   931,
     945
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INT_LITERAL",
  "FLOAT_LITERAL", "DOUBLE_LITERAL", "STRING_LITERAL", "CHAR_LITERAL",
  "INT", "FLOAT", "DOUBLE", "BOOLEAN", "CHAR", "STRING_TYPE", "CLASS",
  "PUBLIC", "PRIVATE", "PROTECTED", "STATIC", "FINAL", "VOID", "SYSTEM",
  "OUT", "PRINTLN", "EQUALS_METHOD", "IF", "ELSE", "WHILE", "FOR", "DO",
  "SWITCH", "CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN", "NEW",
  "THIS", "TRUE_TOKEN", "FALSE_TOKEN", "NULL_TOKEN", "PLUS", "MINUS",
  "MULT", "DIV", "MOD", "INCREMENT", "DECREMENT", "ASSIGN", "PLUS_ASSIGN",
  "MINUS_ASSIGN", "MULT_ASSIGN", "DIV_ASSIGN", "EQUALS", "NOT_EQUALS",
  "LESS", "GREATER", "LESS_EQUALS", "GREATER_EQUALS", "AND", "OR", "NOT",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
  "SEMICOLON", "COMMA", "DOT", "COLON", "INT_ARRAY", "FLOAT_ARRAY",
  "DOUBLE_ARRAY", "STRING_ARRAY", "BOOLEAN_ARRAY", "CHAR_ARRAY", "ERROR",
  "UMINUS", "$accept", "program", "function_list", "function_decl",
  "parameter", "parameter_list", "main_function", "function_body",
  "statement_list", "statement", "declaration", "declaration_list",
  "declaration_no_semicolon", "for_init", "type", "assignment",
  "expression", "literal", "if_statement", "while_statement",
  "for_statement", "return_statement", "switch_statement", "$@1",
  "switch_sections", "switch_section", "statement_list_opt",
  "array_declaration", "array_initialization", "expression_list",
  "array_access", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-335)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     643,   215,  -335,  -335,  -335,  -335,  -335,   -64,   -55,   -25,
    -335,  -335,    -3,  -335,    15,    10,    12,    13,   643,    30,
      47,    56,   689,    14,  -335,  -335,  -335,  1287,   125,   130,
    1287,  1287,   643,  -335,  -335,  -335,  -335,    66,   132,   643,
    -335,  -335,     3,  -335,  1116,  -335,  -335,  -335,  -335,  -335,
    -335,  -335,  -335,    85,  -335,  -335,  1287,  1287,  1287,  1287,
    1287,  1103,   735,   147,    96,    97,   108,   116,   126,  1287,
    1287,   449,   163,  1287,  -335,  -335,   222,  1287,  -335,  1162,
     164,   -13,   -14,    92,   118,   154,   157,   162,   181,   184,
    -335,  -335,   184,  1208,   569,  1116,    -5,  -335,   237,  -335,
    -335,   643,     4,  -335,  -335,    36,   189,   -49,  1287,  1287,
    1287,  1287,  1287,  1287,  1287,  1287,  1287,  1287,  1287,  1287,
    1287,  -335,     8,  1287,  1254,  1299,  1319,  1339,  1359,  -335,
    1829,   -33,  -335,  1379,   195,  -335,  -335,  -335,  -335,   205,
    1399,  1422,   349,  -335,   191,     5,  1829,   214,  1445,  1287,
    1287,  1287,  1287,  1287,  1287,  -335,  1287,   216,   211,  1287,
     781,  1287,   827,  1287,   873,  1287,   919,  1287,   965,  1287,
    1011,  1057,  -335,  -335,  -335,  1287,   262,    63,  1287,   280,
    -335,  -335,  -335,   284,    37,    37,   184,   184,   184,   188,
     188,    53,    53,    53,    53,   656,   144,   225,   227,  1468,
    -335,  -335,  -335,  -335,  -335,  -335,  -335,  1149,   267,   643,
     643,  1287,   -36,  1287,  -335,  1829,  1829,  1829,  1829,  1829,
    1829,  -335,    34,   231,  1488,    48,   232,  1508,    61,   235,
    1528,    81,   236,  1548,    86,   241,  1568,   104,   242,  1588,
     244,  1608,  1829,   289,    46,  1628,   243,   256,  1195,  1287,
    -335,  -335,  1648,    -2,   247,   290,  -335,  1671,  1287,  1287,
    1691,   253,  -335,  1287,  -335,  -335,  1287,  -335,  -335,  1287,
    -335,  -335,  1287,  -335,  -335,  1287,  -335,  -335,  1287,  -335,
    1287,  -335,   257,   252,   258,  -335,    -1,     7,  -335,   273,
    1287,  -335,  1714,    59,  1737,  -335,  -335,  1241,   643,  1287,
    1829,  1760,   255,  -335,   111,   112,   146,   169,   170,   171,
     172,   -35,   643,   261,   240,  -335,   270,  1829,  -335,  -335,
    -335,   268,  1783,  -335,  1806,   643,  -335,   -18,  -335,  -335,
    -335,  -335,  -335,  -335,  -335,   271,   337,   281,   643,   643,
    -335,  -335,  -335,   277,   643,  -335,    39,   276,  -335,  -335,
     643,   287,  -335,   288,  -335,  -335,   283,   643,   292,   291,
    -335,   643,  -335,  -335,   643,  -335,   294,  -335
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    70,   131,   132,   133,   134,   135,    44,    45,    46,
      48,    49,    50,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   136,   137,   138,     0,     0,     0,
       0,     0,     0,    58,    59,    60,    61,     0,   154,     3,
      16,    18,     0,    19,     0,    68,    20,    21,    22,    23,
      24,    25,    69,   128,   125,   127,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    43,     0,     0,    27,    28,    70,     0,   145,     0,
     128,     0,     0,     0,     0,     0,     0,     0,     0,   123,
     124,   126,   122,     0,     0,   158,     0,     1,     0,     6,
       5,   153,     0,     2,    17,    37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,     0,     0,    71,    73,    74,    75,    76,    96,
     158,     0,    56,     0,    98,    52,    53,    54,    55,     0,
       0,     0,    70,    41,     0,     0,    42,     0,     0,     0,
       0,     0,     0,     0,     0,   146,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   130,    31,   157,     0,     0,    37,     0,     0,
      32,    57,    34,     0,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    97,     0,    72,
      62,    64,    65,    66,    67,    95,   160,     0,     0,     0,
       0,     0,    39,     0,   147,    71,    73,    74,    75,    76,
      72,   101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,     0,   159,     0,     0,    35,     0,    38,     0,     0,
      63,    94,   158,     0,     0,   139,   141,     0,     0,     0,
       0,     0,   110,     0,   111,   112,     0,   113,   114,     0,
     115,   116,     0,   117,   118,     0,   119,   120,     0,   121,
       0,   102,     0,    51,     0,    10,     0,     0,    33,   155,
       0,    92,   158,     0,     0,    93,   100,     0,     0,     0,
      40,     0,     0,   149,     0,     0,     0,     0,     0,     0,
       0,     0,    15,     0,     0,     9,     0,    36,    91,    99,
      90,     0,     0,   140,     0,     0,   142,     0,   104,   105,
     106,   107,   108,   109,   103,     0,     0,     0,    14,    15,
      11,   156,    30,     0,     0,   144,     0,     0,   148,   150,
      15,     0,     7,     0,    29,   143,     0,   154,     0,     0,
       8,   154,   152,    12,    15,   151,     0,    13
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -335,  -335,  -335,  -335,    51,  -335,  -335,  -334,     2,   -17,
    -335,  -335,  -335,  -335,   -19,  -335,   272,    16,  -335,  -335,
    -335,  -335,  -335,  -335,  -335,  -335,  -255,  -335,    50,   -52,
       0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    37,    38,    99,   285,   286,   100,   337,   338,    40,
      41,   107,   143,   144,    42,    43,    44,    45,    46,    47,
      48,    49,    50,   261,   327,   349,   103,    51,    52,    96,
      80
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,    72,    39,    64,    88,   353,   105,   177,   212,   131,
     315,   197,    65,   258,   346,   347,   358,    81,    53,   102,
     182,   183,   104,     7,     8,     9,    10,    11,    12,   335,
     366,   205,    53,   198,    94,    13,   259,   175,    53,    53,
     101,   336,    66,     2,     3,     4,     5,     6,   348,   283,
     157,   159,   145,   160,   158,     7,     8,     9,    10,    11,
      12,   174,   296,   313,    67,   175,    97,    13,   175,   314,
     106,   106,   106,    69,   106,    70,    71,   104,    24,    25,
      26,   110,   111,   112,   104,   178,    68,    82,    83,    84,
      85,    86,    87,    73,    53,   108,   109,   110,   111,   112,
     262,    53,   362,   179,   175,   180,   365,   222,   122,   225,
     284,   228,   178,   231,   265,   234,    74,   237,   175,    33,
      34,    35,    36,   319,   122,    75,   244,   268,    90,   175,
     179,   175,   180,    91,   123,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,   271,    98,   139,
     134,   175,   274,    13,    14,   253,   175,   161,    15,   162,
      16,    17,    18,    19,   135,   136,    20,    21,    22,    23,
     277,    24,    25,    26,   175,    27,   137,   328,   329,    28,
      29,   175,   175,   163,   138,   164,   108,   109,   110,   111,
     112,   147,   255,   256,    30,    31,   293,    32,   113,   114,
     115,   116,   117,   118,   119,    33,    34,    35,    36,    53,
      53,   304,   330,   156,   305,   122,   175,   306,   -51,   165,
     307,   166,   167,   308,   168,   287,   309,   169,   310,   170,
     108,   109,   110,   111,   112,   331,   332,   333,   334,   175,
     175,   175,   175,   283,   115,   116,   117,   118,   171,     7,
       8,     9,    10,    11,    12,   122,   176,   181,   207,   122,
     211,    13,    54,    55,    56,    57,    58,    59,    60,    54,
      55,   149,   150,   151,   152,   153,   208,   213,    61,   132,
     221,   323,    62,   243,   246,    61,    63,   247,   248,   154,
     249,   254,   282,    63,    79,   287,   263,   266,    53,    89,
     269,   272,    92,    93,    95,   290,   275,   278,   345,   280,
     297,   289,    53,    33,    34,    35,    36,   298,   303,   158,
     311,   104,   316,   312,   326,    53,   339,   355,   124,   125,
     126,   127,   128,   130,   133,    77,   350,   342,    53,    53,
     351,   140,   141,   146,    53,   148,   354,   352,   357,   130,
      53,   359,   -51,     0,   360,   361,   364,    53,   363,   101,
     367,    53,   356,   101,    53,   340,   341,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,     0,     0,   199,    54,    55,   149,   150,
     151,   152,   153,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,     0,     0,     0,    62,     0,     0,     0,
      63,   215,   216,   217,   218,   219,   133,     0,   220,     0,
       0,   130,   224,   130,   227,   130,   230,   130,   233,   130,
     236,   130,   239,   241,     0,     0,     0,   242,     0,     0,
     245,     0,   142,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,     0,     0,     0,     0,     0,     0,
      13,     0,     0,     0,     0,     0,     0,     0,     0,   252,
       0,     0,     0,   257,     0,   260,    23,     0,    24,    25,
      26,     0,    27,     0,     0,     0,    28,    29,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    30,    31,     0,    77,     0,     0,     0,     0,     0,
     292,   294,    33,    34,    35,    36,     0,     0,     0,     0,
     300,   301,     0,     0,     0,   130,     0,     0,   130,     0,
       0,   130,     0,     0,   130,     0,     0,   130,     0,     0,
     130,     0,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   317,     0,     0,     0,     0,     0,     0,   322,
       0,   324,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,     0,     0,     0,     0,     0,     0,
      13,    14,     0,     0,     0,    15,     0,    16,    17,    18,
      19,     0,     0,    20,    21,    22,    23,     0,    24,    25,
      26,     0,    27,     0,     0,     0,    28,    29,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    30,    31,     0,    32,   173,     0,     0,     0,     0,
       0,     0,    33,    34,    35,    36,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,     0,     0,
       0,     0,     0,     0,    13,    14,     0,     0,     0,    15,
       0,    16,    17,    18,    19,     0,     0,    20,    21,    22,
      23,     0,    24,    25,    26,     0,    27,     0,     0,     0,
      28,    29,    76,     2,     3,     4,     5,     6,   108,   109,
     110,   111,   112,     0,     0,    30,    31,     0,    32,     0,
     113,   114,   115,   116,   117,   118,    33,    34,    35,    36,
       0,     0,     0,     0,     0,     0,    23,   122,    24,    25,
      26,     0,    27,     0,     0,     0,    28,    29,    76,     2,
       3,     4,     5,     6,     0,     0,     0,     0,     0,     0,
       0,    30,    31,     0,    77,     0,     0,     0,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    23,     0,    24,    25,    26,     0,    27,     0,
       0,     0,    28,    29,    76,     2,     3,     4,     5,     6,
       0,     0,     0,     0,     0,     0,     0,    30,    31,     0,
      77,     0,     0,   132,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    23,     0,
      24,    25,    26,     0,    27,     0,     0,     0,    28,    29,
      76,     2,     3,     4,     5,     6,     0,     0,     0,     0,
       0,     0,     0,    30,    31,     0,    77,     0,     0,   223,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    23,     0,    24,    25,    26,     0,
      27,     0,     0,     0,    28,    29,    76,     2,     3,     4,
       5,     6,     0,     0,     0,     0,     0,     0,     0,    30,
      31,     0,    77,     0,     0,   226,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,     0,    24,    25,    26,     0,    27,     0,     0,     0,
      28,    29,    76,     2,     3,     4,     5,     6,     0,     0,
       0,     0,     0,     0,     0,    30,    31,     0,    77,     0,
       0,   229,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,     0,    24,    25,
      26,     0,    27,     0,     0,     0,    28,    29,    76,     2,
       3,     4,     5,     6,     0,     0,     0,     0,     0,     0,
       0,    30,    31,     0,    77,     0,     0,   232,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    23,     0,    24,    25,    26,     0,    27,     0,
       0,     0,    28,    29,    76,     2,     3,     4,     5,     6,
       0,     0,     0,     0,     0,     0,     0,    30,    31,     0,
      77,     0,     0,   235,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    23,     0,
      24,    25,    26,     0,    27,     0,     0,     0,    28,    29,
      76,     2,     3,     4,     5,     6,     0,     0,     0,     0,
       0,     0,     0,    30,    31,     0,    77,     0,     0,   238,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    23,     0,    24,    25,    26,     0,
      27,     0,     0,     0,    28,    29,    76,     2,     3,     4,
       5,     6,     0,     0,     0,     0,     0,     0,     0,    30,
      31,     0,    77,     0,     0,   240,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,     0,    24,    25,    26,     0,    27,     0,     0,     0,
      28,    29,    76,     2,     3,     4,     5,     6,   108,   109,
     110,   111,   112,     0,     0,    30,    31,   129,    77,     0,
     113,   114,   115,   116,   117,   118,   119,   120,     0,     0,
       0,     0,     0,     0,     0,   121,    23,   122,    24,    25,
      26,     0,    27,     0,     0,     0,    28,    29,    76,     2,
       3,     4,     5,     6,   108,   109,   110,   111,   112,     0,
       0,    30,    31,   251,    77,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,     0,     0,     0,     0,     0,
       0,   155,    23,   122,    24,    25,    26,     0,    27,     0,
       0,     0,    28,    29,    76,     2,     3,     4,     5,     6,
     108,   109,   110,   111,   112,     0,     0,    30,    31,   291,
      77,     0,   113,   114,   115,   116,   117,   118,   119,   120,
       0,     0,   172,     0,     0,     0,     0,     0,    23,   122,
      24,    25,    26,     0,    27,     0,     0,     0,    28,    29,
      76,     2,     3,     4,     5,     6,   108,   109,   110,   111,
     112,     0,     0,    30,    31,   321,    77,     0,   113,   114,
     115,   116,   117,   118,   119,   120,     0,     0,     0,     0,
       0,     0,     0,   200,    23,   122,    24,    25,    26,     0,
      27,     0,     0,     0,    28,    29,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,     0,     0,     0,    30,
      31,     0,    77,   113,   114,   115,   116,   117,   118,   119,
     120,   108,   109,   110,   111,   112,     0,     0,   201,     0,
     122,     0,     0,   113,   114,   115,   116,   117,   118,   119,
     120,   108,   109,   110,   111,   112,     0,     0,   202,     0,
     122,     0,     0,   113,   114,   115,   116,   117,   118,   119,
     120,   108,   109,   110,   111,   112,     0,     0,   203,     0,
     122,     0,     0,   113,   114,   115,   116,   117,   118,   119,
     120,   108,   109,   110,   111,   112,     0,     0,   204,     0,
     122,     0,     0,   113,   114,   115,   116,   117,   118,   119,
     120,   108,   109,   110,   111,   112,     0,   206,     0,     0,
     122,     0,     0,   113,   114,   115,   116,   117,   118,   119,
     120,     0,     0,   209,   108,   109,   110,   111,   112,     0,
     122,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,     0,   210,   108,   109,   110,
     111,   112,     0,   122,     0,     0,     0,     0,     0,   113,
     114,   115,   116,   117,   118,   119,   120,     0,     0,   214,
     108,   109,   110,   111,   112,     0,   122,     0,     0,     0,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     108,   109,   110,   111,   112,     0,     0,   250,     0,   122,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     108,   109,   110,   111,   112,     0,   264,     0,     0,   122,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     108,   109,   110,   111,   112,     0,   267,     0,     0,   122,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     108,   109,   110,   111,   112,     0,   270,     0,     0,   122,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     108,   109,   110,   111,   112,     0,   273,     0,     0,   122,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     108,   109,   110,   111,   112,     0,   276,     0,     0,   122,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     108,   109,   110,   111,   112,     0,   279,     0,     0,   122,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     108,   109,   110,   111,   112,     0,   281,     0,     0,   122,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
     108,   109,   110,   111,   112,     0,     0,   288,     0,   122,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
       0,     0,   295,   108,   109,   110,   111,   112,     0,   122,
       0,     0,     0,     0,     0,   113,   114,   115,   116,   117,
     118,   119,   120,   108,   109,   110,   111,   112,     0,     0,
     299,     0,   122,     0,     0,   113,   114,   115,   116,   117,
     118,   119,   120,     0,     0,   302,   108,   109,   110,   111,
     112,     0,   122,     0,     0,     0,     0,     0,   113,   114,
     115,   116,   117,   118,   119,   120,     0,     0,   318,   108,
     109,   110,   111,   112,     0,   122,     0,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,     0,
       0,   320,   108,   109,   110,   111,   112,     0,   122,     0,
       0,     0,     0,     0,   113,   114,   115,   116,   117,   118,
     119,   120,     0,     0,   325,   108,   109,   110,   111,   112,
       0,   122,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,     0,   343,   108,   109,
     110,   111,   112,     0,   122,     0,     0,     0,     0,     0,
     113,   114,   115,   116,   117,   118,   119,   120,     0,     0,
     344,   108,   109,   110,   111,   112,     0,   122,     0,     0,
       0,     0,     0,   113,   114,   115,   116,   117,   118,   119,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     122
};

static const yytype_int16 yycheck[] =
{
       0,    18,     0,    67,    23,   339,     3,     3,     3,    61,
       3,     3,    67,    49,    32,    33,   350,     3,    18,    38,
      69,    70,    39,     9,    10,    11,    12,    13,    14,    64,
     364,    64,    32,    25,    32,    21,    72,    70,    38,    39,
      38,    76,    67,     4,     5,     6,     7,     8,    66,     3,
      63,    65,    71,    67,    67,     9,    10,    11,    12,    13,
      14,    66,    64,    64,    67,    70,     0,    21,    70,    70,
      67,    67,    67,    63,    67,    63,    63,    94,    39,    40,
      41,    44,    45,    46,   101,    49,    71,    73,    74,    75,
      76,    77,    78,    63,    94,    42,    43,    44,    45,    46,
      66,   101,   357,    67,    70,    69,   361,   159,    71,   161,
      64,   163,    49,   165,    66,   167,    69,   169,    70,    73,
      74,    75,    76,    64,    71,    69,    63,    66,     3,    70,
      67,    70,    69,     3,    49,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    66,    16,    23,
       3,    70,    66,    21,    22,   207,    70,    65,    26,    67,
      28,    29,    30,    31,    68,    68,    34,    35,    36,    37,
      66,    39,    40,    41,    70,    43,    68,    66,    66,    47,
      48,    70,    70,    65,    68,    67,    42,    43,    44,    45,
      46,    28,   209,   210,    62,    63,   248,    65,    54,    55,
      56,    57,    58,    59,    60,    73,    74,    75,    76,   209,
     210,   263,    66,    49,   266,    71,    70,   269,     3,    65,
     272,    67,    65,   275,    67,   244,   278,    65,   280,    67,
      42,    43,    44,    45,    46,    66,    66,    66,    66,    70,
      70,    70,    70,     3,    56,    57,    58,    59,    67,     9,
      10,    11,    12,    13,    14,    71,    19,    68,    63,    71,
      69,    21,    47,    48,    49,    50,    51,    52,    53,    47,
      48,    49,    50,    51,    52,    53,    71,    63,    63,    68,
      64,   298,    67,    21,     4,    63,    71,     3,    63,    67,
      63,    24,     3,    71,    22,   314,    65,    65,   298,    27,
      65,    65,    30,    31,    32,    49,    65,    65,   325,    65,
      63,    68,   312,    73,    74,    75,    76,    27,    65,    67,
      63,   338,    49,    65,    69,   325,    65,   344,    56,    57,
      58,    59,    60,    61,    62,    65,    65,    69,   338,   339,
       3,    69,    70,    71,   344,    73,    69,    66,    72,    77,
     350,    64,     3,    -1,    66,    72,    65,   357,    66,   357,
      66,   361,   346,   361,   364,   314,   316,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,    -1,    -1,   123,    47,    48,    49,    50,
      51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    -1,    67,    -1,    -1,    -1,
      71,   149,   150,   151,   152,   153,   154,    -1,   156,    -1,
      -1,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,    -1,    -1,    -1,   175,    -1,    -1,
     178,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   207,
      -1,    -1,    -1,   211,    -1,   213,    37,    -1,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,
     248,   249,    73,    74,    75,    76,    -1,    -1,    -1,    -1,
     258,   259,    -1,    -1,    -1,   263,    -1,    -1,   266,    -1,
      -1,   269,    -1,    -1,   272,    -1,    -1,   275,    -1,    -1,
     278,    -1,   280,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   290,    -1,    -1,    -1,    -1,    -1,    -1,   297,
      -1,   299,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      21,    22,    -1,    -1,    -1,    26,    -1,    28,    29,    30,
      31,    -1,    -1,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    -1,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,    76,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    22,    -1,    -1,    -1,    26,
      -1,    28,    29,    30,    31,    -1,    -1,    34,    35,    36,
      37,    -1,    39,    40,    41,    -1,    43,    -1,    -1,    -1,
      47,    48,     3,     4,     5,     6,     7,     8,    42,    43,
      44,    45,    46,    -1,    -1,    62,    63,    -1,    65,    -1,
      54,    55,    56,    57,    58,    59,    73,    74,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    71,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    47,    48,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    39,    40,    41,    -1,    43,    -1,
      -1,    -1,    47,    48,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,
      65,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,
      39,    40,    41,    -1,    43,    -1,    -1,    -1,    47,    48,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    39,    40,    41,    -1,
      43,    -1,    -1,    -1,    47,    48,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    -1,    65,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    39,    40,    41,    -1,    43,    -1,    -1,    -1,
      47,    48,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    47,    48,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    -1,    65,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    39,    40,    41,    -1,    43,    -1,
      -1,    -1,    47,    48,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,
      65,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,
      39,    40,    41,    -1,    43,    -1,    -1,    -1,    47,    48,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    39,    40,    41,    -1,
      43,    -1,    -1,    -1,    47,    48,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    -1,    65,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    39,    40,    41,    -1,    43,    -1,    -1,    -1,
      47,    48,     3,     4,     5,     6,     7,     8,    42,    43,
      44,    45,    46,    -1,    -1,    62,    63,    64,    65,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    37,    71,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    47,    48,     3,     4,
       5,     6,     7,     8,    42,    43,    44,    45,    46,    -1,
      -1,    62,    63,    64,    65,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    37,    71,    39,    40,    41,    -1,    43,    -1,
      -1,    -1,    47,    48,     3,     4,     5,     6,     7,     8,
      42,    43,    44,    45,    46,    -1,    -1,    62,    63,    64,
      65,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    37,    71,
      39,    40,    41,    -1,    43,    -1,    -1,    -1,    47,    48,
       3,     4,     5,     6,     7,     8,    42,    43,    44,    45,
      46,    -1,    -1,    62,    63,    64,    65,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    37,    71,    39,    40,    41,    -1,
      43,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    42,    43,    44,    45,    46,    -1,    -1,    -1,    62,
      63,    -1,    65,    54,    55,    56,    57,    58,    59,    60,
      61,    42,    43,    44,    45,    46,    -1,    -1,    69,    -1,
      71,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    42,    43,    44,    45,    46,    -1,    -1,    69,    -1,
      71,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    42,    43,    44,    45,    46,    -1,    -1,    69,    -1,
      71,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    42,    43,    44,    45,    46,    -1,    -1,    69,    -1,
      71,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    42,    43,    44,    45,    46,    -1,    68,    -1,    -1,
      71,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    64,    42,    43,    44,    45,    46,    -1,
      71,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    -1,    64,    42,    43,    44,
      45,    46,    -1,    71,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    60,    61,    -1,    -1,    64,
      42,    43,    44,    45,    46,    -1,    71,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      42,    43,    44,    45,    46,    -1,    -1,    69,    -1,    71,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      42,    43,    44,    45,    46,    -1,    68,    -1,    -1,    71,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      42,    43,    44,    45,    46,    -1,    68,    -1,    -1,    71,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      42,    43,    44,    45,    46,    -1,    68,    -1,    -1,    71,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      42,    43,    44,    45,    46,    -1,    68,    -1,    -1,    71,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      42,    43,    44,    45,    46,    -1,    68,    -1,    -1,    71,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      42,    43,    44,    45,    46,    -1,    68,    -1,    -1,    71,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      42,    43,    44,    45,    46,    -1,    68,    -1,    -1,    71,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      42,    43,    44,    45,    46,    -1,    -1,    69,    -1,    71,
      -1,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      -1,    -1,    64,    42,    43,    44,    45,    46,    -1,    71,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    42,    43,    44,    45,    46,    -1,    -1,
      69,    -1,    71,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    -1,    -1,    64,    42,    43,    44,    45,
      46,    -1,    71,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    -1,    64,    42,
      43,    44,    45,    46,    -1,    71,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    64,    42,    43,    44,    45,    46,    -1,    71,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    -1,    64,    42,    43,    44,    45,    46,
      -1,    71,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    64,    42,    43,
      44,    45,    46,    -1,    71,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    -1,
      64,    42,    43,    44,    45,    46,    -1,    71,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    21,    22,    26,    28,    29,    30,    31,
      34,    35,    36,    37,    39,    40,    41,    43,    47,    48,
      62,    63,    65,    73,    74,    75,    76,    82,    83,    89,
      90,    91,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   108,   109,   111,    47,    48,    49,    50,    51,    52,
      53,    63,    67,    71,    67,    67,    67,    67,    71,    63,
      63,    63,    90,    63,    69,    69,     3,    65,    69,    97,
     111,     3,    73,    74,    75,    76,    77,    78,    95,    97,
       3,     3,    97,    97,    89,    97,   110,     0,    16,    84,
      87,    89,    95,   107,    90,     3,    67,    92,    42,    43,
      44,    45,    46,    54,    55,    56,    57,    58,    59,    60,
      61,    69,    71,    49,    97,    97,    97,    97,    97,    64,
      97,   110,    68,    97,     3,    68,    68,    68,    68,    23,
      97,    97,     3,    93,    94,    95,    97,    28,    97,    49,
      50,    51,    52,    53,    67,    69,    49,    63,    67,    65,
      67,    65,    67,    65,    67,    65,    67,    65,    67,    65,
      67,    67,    64,    66,    66,    70,    19,     3,    49,    67,
      69,    68,    69,    70,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,     3,    25,    97,
      69,    69,    69,    69,    69,    64,    68,    63,    71,    64,
      64,    69,     3,    63,    64,    97,    97,    97,    97,    97,
      97,    64,   110,    68,    97,   110,    68,    97,   110,    68,
      97,   110,    68,    97,   110,    68,    97,   110,    68,    97,
      68,    97,    97,    21,    63,    97,     4,     3,    63,    63,
      69,    64,    97,   110,    24,    90,    90,    97,    49,    72,
      97,   104,    66,    65,    68,    66,    65,    68,    66,    65,
      68,    66,    65,    68,    66,    65,    68,    66,    65,    68,
      65,    68,     3,     3,    64,    85,    86,    95,    69,    68,
      49,    64,    97,   110,    97,    64,    64,    63,    27,    69,
      97,    97,    64,    65,   110,   110,   110,   110,   110,   110,
     110,    63,    65,    64,    70,     3,    49,    97,    64,    64,
      64,    64,    97,    90,    97,    64,    69,   105,    66,    66,
      66,    66,    66,    66,    66,    64,    76,    88,    89,    65,
      85,   109,    69,    64,    64,    90,    32,    33,    66,   106,
      65,     3,    66,    88,    69,    90,    98,    72,    88,    64,
      66,    72,   107,    66,    65,   107,    88,    66
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    81,    82,    82,    83,    83,    83,    84,    84,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    91,    91,    91,    92,    92,    92,    92,    93,
      93,    94,    94,    94,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    96,    96,    96,    96,    96,    96,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    98,    98,    98,    98,    98,    98,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   104,   103,   105,
     105,   106,   106,   107,   107,   108,   108,   109,   110,   110,
     111
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     0,     2,     2,     7,     8,     2,
       1,     3,     9,    11,     1,     0,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     9,
       8,     3,     3,     5,     3,     3,     5,     1,     3,     2,
       4,     1,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     4,     4,     4,     4,     4,     4,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       6,     6,     5,     6,     5,     4,     3,     3,     3,     6,
       6,     4,     5,     7,     7,     7,     7,     7,     7,     7,
       5,     5,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,     2,     2,     2,     2,     2,     2,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       7,     5,     7,     9,     8,     2,     3,     0,     8,     0,
       2,     4,     3,     1,     0,     5,     7,     3,     1,     3,
       4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: function_list statement_list_opt  */
#line 137 "src/parser.y"
                                     {
        printf("Programa con lista de funciones/decls parseado correctamente\n");
        /* Si hay funciones y statements, encadenarlas:
           las funciones quedan al inicio de la lista de nodos */
        if ((yyvsp[-1].astNode) && (yyvsp[0].astNode)) {
            ast_node *cur = (yyvsp[-1].astNode);
            while (cur->next) cur = cur->next;
            cur->next = (yyvsp[0].astNode);
            root = (yyvsp[-1].astNode);
        } else if ((yyvsp[-1].astNode)) {
            root = (yyvsp[-1].astNode);
        } else {
            root = (yyvsp[0].astNode);
        }
        (yyval.astNode) = root;
    }
#line 1802 "src/parser.c"
    break;

  case 3: /* program: statement_list  */
#line 153 "src/parser.y"
                     {
        printf("Programa (solo statements) parseado correctamente\n");
        root = (yyvsp[0].astNode);
        (yyval.astNode) = root;
    }
#line 1812 "src/parser.c"
    break;

  case 4: /* function_list: %empty  */
#line 161 "src/parser.y"
                { (yyval.astNode) = NULL; }
#line 1818 "src/parser.c"
    break;

  case 5: /* function_list: function_list main_function  */
#line 162 "src/parser.y"
                                  {
        if (!(yyvsp[-1].astNode)) (yyval.astNode) = (yyvsp[0].astNode);
        else {
            ast_node *cur = (yyvsp[-1].astNode);
            while (cur->next) cur = cur->next;
            cur->next = (yyvsp[0].astNode);
            (yyval.astNode) = (yyvsp[-1].astNode);
        }
    }
#line 1832 "src/parser.c"
    break;

  case 6: /* function_list: function_list function_decl  */
#line 171 "src/parser.y"
                                  {
        if (!(yyvsp[-1].astNode)) (yyval.astNode) = (yyvsp[0].astNode);
        else {
            ast_node *cur = (yyvsp[-1].astNode);
            while (cur->next) cur = cur->next;
            cur->next = (yyvsp[0].astNode);
            (yyval.astNode) = (yyvsp[-1].astNode);
        }
    }
#line 1846 "src/parser.c"
    break;

  case 7: /* function_decl: type ID LPAREN RPAREN LBRACE function_body RBRACE  */
#line 184 "src/parser.y"
                                                      {
        printf("Función encontrada: %s\n", (yyvsp[-5].string_val));
        (yyval.astNode) = new_ast_function((yyvsp[-5].string_val), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 1856 "src/parser.c"
    break;

  case 8: /* function_decl: type ID LPAREN parameter_list RPAREN LBRACE function_body RBRACE  */
#line 190 "src/parser.y"
                                                                       {
        printf("Función con parámetros encontrada: %s\n", (yyvsp[-6].string_val));
        (yyval.astNode) = new_ast_function((yyvsp[-6].string_val), (yyvsp[-1].astNode));
        if ((yyval.astNode)) {
            /* almacenar la lista de parámetros en el nodo (new_ast_function crea nodo compatible) */
            (yyval.astNode)->data.function_def.parameters = (yyvsp[-4].astNode);
            (yyval.astNode)->line = yylineno;
        }
    }
#line 1870 "src/parser.c"
    break;

  case 9: /* parameter: type ID  */
#line 203 "src/parser.y"
            {
        /* representamos un parámetro como una declaración sin valor */
        (yyval.astNode) = new_ast_declaration((yyvsp[-1].astNode), (yyvsp[0].string_val), NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 1880 "src/parser.c"
    break;

  case 10: /* parameter_list: parameter  */
#line 211 "src/parser.y"
              { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1886 "src/parser.c"
    break;

  case 11: /* parameter_list: parameter_list COMMA parameter  */
#line 212 "src/parser.y"
                                     {
        ast_node *cur = (yyvsp[-2].astNode);
        while (cur->next) cur = cur->next;
        cur->next = (yyvsp[0].astNode);
        (yyval.astNode) = (yyvsp[-2].astNode);
    }
#line 1897 "src/parser.c"
    break;

  case 12: /* main_function: PUBLIC STATIC VOID ID LPAREN RPAREN LBRACE function_body RBRACE  */
#line 222 "src/parser.y"
                                                                    {
        printf("Función pública encontrada: %s\n", (yyvsp[-5].string_val));
        (yyval.astNode) = new_ast_main_function((yyvsp[-5].string_val), (yyvsp[-1].astNode));
        if ((yyval.astNode)) {
            (yyval.astNode)->line = yylineno;
        }
    }
#line 1909 "src/parser.c"
    break;

  case 13: /* main_function: PUBLIC STATIC VOID ID LPAREN STRING_ARRAY ID RPAREN LBRACE function_body RBRACE  */
#line 229 "src/parser.y"
                                                                                      {
        // Aceptar main(String[] args)
        printf("Función pública (con params) encontrada: %s\n", (yyvsp[-7].string_val));
        (yyval.astNode) = new_ast_main_function((yyvsp[-7].string_val), (yyvsp[-1].astNode));
        if ((yyval.astNode)) {
            (yyval.astNode)->line = yylineno;
        }
    }
#line 1922 "src/parser.c"
    break;

  case 14: /* function_body: statement_list  */
#line 240 "src/parser.y"
                   { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1928 "src/parser.c"
    break;

  case 15: /* function_body: %empty  */
#line 241 "src/parser.y"
                  { (yyval.astNode) = NULL; }
#line 1934 "src/parser.c"
    break;

  case 16: /* statement_list: statement  */
#line 245 "src/parser.y"
              { 
        printf("📝 Primera declaración en lista\n");
        (yyval.astNode) = (yyvsp[0].astNode); 
    }
#line 1943 "src/parser.c"
    break;

  case 17: /* statement_list: statement_list statement  */
#line 249 "src/parser.y"
                               { 
        printf("📝 Agregando declaración a lista\n");
        if ((yyvsp[-1].astNode) && (yyvsp[0].astNode)) {
            // Buscar el final de la lista y agregar
            ast_node *current = (yyvsp[-1].astNode);
            while (current->next) {
                current = current->next;
            }
            current->next = (yyvsp[0].astNode);
            (yyval.astNode) = (yyvsp[-1].astNode);
        } else if ((yyvsp[0].astNode)) {
            (yyval.astNode) = (yyvsp[0].astNode);
        } else {
            (yyval.astNode) = (yyvsp[-1].astNode);
        }
    }
#line 1964 "src/parser.c"
    break;

  case 18: /* statement: declaration  */
#line 268 "src/parser.y"
                { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1970 "src/parser.c"
    break;

  case 19: /* statement: assignment  */
#line 269 "src/parser.y"
                 { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1976 "src/parser.c"
    break;

  case 20: /* statement: if_statement  */
#line 270 "src/parser.y"
                   { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1982 "src/parser.c"
    break;

  case 21: /* statement: while_statement  */
#line 271 "src/parser.y"
                      { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1988 "src/parser.c"
    break;

  case 22: /* statement: for_statement  */
#line 272 "src/parser.y"
                    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1994 "src/parser.c"
    break;

  case 23: /* statement: return_statement  */
#line 273 "src/parser.y"
                       { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2000 "src/parser.c"
    break;

  case 24: /* statement: switch_statement  */
#line 274 "src/parser.y"
                       { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2006 "src/parser.c"
    break;

  case 25: /* statement: array_declaration  */
#line 275 "src/parser.y"
                        { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2012 "src/parser.c"
    break;

  case 26: /* statement: expression SEMICOLON  */
#line 276 "src/parser.y"
                           { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 2018 "src/parser.c"
    break;

  case 27: /* statement: BREAK SEMICOLON  */
#line 277 "src/parser.y"
                      {
        printf("Break statement\n");
        (yyval.astNode) = new_ast_break();
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2028 "src/parser.c"
    break;

  case 28: /* statement: CONTINUE SEMICOLON  */
#line 282 "src/parser.y"
                         {
        printf("Continue statement\n");
        (yyval.astNode) = new_ast_continue();
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2038 "src/parser.c"
    break;

  case 29: /* statement: SYSTEM DOT OUT DOT PRINTLN LPAREN expression RPAREN SEMICOLON  */
#line 287 "src/parser.y"
                                                                    {
        printf("System.out.println encontrado\n");
        (yyval.astNode) = new_ast_print_stmt((yyvsp[-2].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2048 "src/parser.c"
    break;

  case 30: /* statement: SYSTEM DOT OUT DOT PRINTLN LPAREN RPAREN SEMICOLON  */
#line 292 "src/parser.y"
                                                         {
        printf("System.out.println vacío\n");
        (yyval.astNode) = new_ast_print_stmt(NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2058 "src/parser.c"
    break;

  case 31: /* statement: LBRACE statement_list RBRACE  */
#line 297 "src/parser.y"
                                   {
        printf("Bloque de statements\n");
        (yyval.astNode) = new_ast_compound_stmt((yyvsp[-1].astNode), NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2068 "src/parser.c"
    break;

  case 32: /* declaration: type ID SEMICOLON  */
#line 305 "src/parser.y"
                      {
        printf("Declaracion simple: %s\n", (yyvsp[-1].string_val));
        (yyval.astNode) = new_ast_declaration((yyvsp[-2].astNode), (yyvsp[-1].string_val), NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2078 "src/parser.c"
    break;

  case 33: /* declaration: type ID ASSIGN expression SEMICOLON  */
#line 310 "src/parser.y"
                                          {
        printf("Declaracion con inicialización: %s\n", (yyvsp[-3].string_val));
        
        // ============= CORREGIR AQUÍ =============
        // Verificar y promover float a double automáticamente
        if ((yyvsp[-4].astNode) && (yyvsp[-1].astNode) && (yyvsp[-4].astNode)->data.type_name && 
            strcmp((yyvsp[-4].astNode)->data.type_name, "double") == 0 && 
            (yyvsp[-1].astNode)->type == AST_FLOAT_LITERAL) {
            printf("🔄 Promoción automática: float -> double\n");
            // Convertir el nodo literal float a double
            double promoted_value = (double)(yyvsp[-1].astNode)->data.float_value;
            // Crear nuevo nodo double
            ast_node* double_node = new_ast_double_literal(promoted_value);
            if (double_node) {
                double_node->line = (yyvsp[-1].astNode)->line;
                // Liberar el nodo float anterior
                free((yyvsp[-1].astNode));
                (yyvsp[-1].astNode) = double_node;
            }
        }
        // =========================================
        
        (yyval.astNode) = new_ast_declaration((yyvsp[-4].astNode), (yyvsp[-3].string_val), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2108 "src/parser.c"
    break;

  case 34: /* declaration: type declaration_list SEMICOLON  */
#line 335 "src/parser.y"
                                      {
        printf("Declaraciones múltiples\n");
        // Establecer el tipo para todas las declaraciones en la lista
        ast_node *current = (yyvsp[-1].astNode);
        while (current) {
            if (current->type == AST_DECLARATION && !current->data.declaration.var_type) {
                current->data.declaration.var_type = (yyvsp[-2].astNode);
                
                // ============= CORREGIR AQUÍ TAMBIÉN =============
                // Promoción para declaraciones múltiples
                if (current->data.declaration.value && 
                    (yyvsp[-2].astNode)->data.type_name &&
                    strcmp((yyvsp[-2].astNode)->data.type_name, "double") == 0 && 
                    current->data.declaration.value->type == AST_FLOAT_LITERAL) {
                    printf("🔄 Promoción automática en declaración múltiple: float -> double\n");
                    double promoted_value = (double)current->data.declaration.value->data.float_value;
                    ast_node* double_node = new_ast_double_literal(promoted_value);
                    if (double_node) {
                        double_node->line = current->data.declaration.value->line;
                        free(current->data.declaration.value);
                        current->data.declaration.value = double_node;
                    }
                }
                // ==============================================
            }
            if (current->next && current->next->type == AST_DECLARATION) {
                current = current->next;
            } else {
                break;
            }
        }
        (yyval.astNode) = (yyvsp[-1].astNode);
    }
#line 2146 "src/parser.c"
    break;

  case 35: /* declaration_list: ID ASSIGN expression  */
#line 371 "src/parser.y"
                         {
        printf("Primera declaración múltiple: %s\n", (yyvsp[-2].string_val));
        (yyval.astNode) = new_ast_declaration(NULL, (yyvsp[-2].string_val), (yyvsp[0].astNode)); // tipo se asigna después
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2156 "src/parser.c"
    break;

  case 36: /* declaration_list: declaration_list COMMA ID ASSIGN expression  */
#line 376 "src/parser.y"
                                                  {
        printf("Declaración múltiple adicional: %s\n", (yyvsp[-2].string_val));
        ast_node *new_decl = new_ast_declaration(NULL, (yyvsp[-2].string_val), (yyvsp[0].astNode));
        if (new_decl) {
            new_decl->line = yylineno;
            // Encontrar el final de la lista y agregar
            ast_node *current = (yyvsp[-4].astNode);
            while (current->next) {
                current = current->next;
            }
            current->next = new_decl;
        }
        (yyval.astNode) = (yyvsp[-4].astNode);
    }
#line 2175 "src/parser.c"
    break;

  case 37: /* declaration_list: ID  */
#line 390 "src/parser.y"
         {
        printf("Declaración múltiple simple: %s\n", (yyvsp[0].string_val));
        (yyval.astNode) = new_ast_declaration(NULL, (yyvsp[0].string_val), NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2185 "src/parser.c"
    break;

  case 38: /* declaration_list: declaration_list COMMA ID  */
#line 395 "src/parser.y"
                                {
        printf("Declaración múltiple simple adicional: %s\n", (yyvsp[0].string_val));
        ast_node *new_decl = new_ast_declaration(NULL, (yyvsp[0].string_val), NULL);
        if (new_decl) {
            new_decl->line = yylineno;
            ast_node *current = (yyvsp[-2].astNode);
            while (current->next) {
                current = current->next;
            }
            current->next = new_decl;
        }
        (yyval.astNode) = (yyvsp[-2].astNode);
    }
#line 2203 "src/parser.c"
    break;

  case 39: /* declaration_no_semicolon: type ID  */
#line 411 "src/parser.y"
            {
        printf("Declaracion (for init) simple: %s\n", (yyvsp[0].string_val));
        (yyval.astNode) = new_ast_declaration((yyvsp[-1].astNode), (yyvsp[0].string_val), NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2213 "src/parser.c"
    break;

  case 40: /* declaration_no_semicolon: type ID ASSIGN expression  */
#line 416 "src/parser.y"
                                {
        printf("Declaracion (for init) con inicializacion: %s\n", (yyvsp[-2].string_val));
        (yyval.astNode) = new_ast_declaration((yyvsp[-3].astNode), (yyvsp[-2].string_val), (yyvsp[0].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2223 "src/parser.c"
    break;

  case 41: /* for_init: declaration_no_semicolon  */
#line 425 "src/parser.y"
                             { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2229 "src/parser.c"
    break;

  case 42: /* for_init: expression  */
#line 426 "src/parser.y"
                 { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2235 "src/parser.c"
    break;

  case 43: /* for_init: %empty  */
#line 427 "src/parser.y"
                  { (yyval.astNode) = NULL; }
#line 2241 "src/parser.c"
    break;

  case 44: /* type: INT  */
#line 431 "src/parser.y"
        { 
        printf("Tipo int parser\n");
        (yyval.astNode) = new_ast_type("int"); 
        }
#line 2250 "src/parser.c"
    break;

  case 45: /* type: FLOAT  */
#line 435 "src/parser.y"
            { 
        printf("Tipo float parser\n");
        (yyval.astNode) = new_ast_type("float"); 
        }
#line 2259 "src/parser.c"
    break;

  case 46: /* type: DOUBLE  */
#line 439 "src/parser.y"
             { 
        printf("Tipo double parser\n");
        (yyval.astNode) = new_ast_type("double");
        }
#line 2268 "src/parser.c"
    break;

  case 47: /* type: VOID  */
#line 443 "src/parser.y"
           { 
        printf("Tipo void parser\n");
        (yyval.astNode) = new_ast_type("void"); 
        }
#line 2277 "src/parser.c"
    break;

  case 48: /* type: BOOLEAN  */
#line 447 "src/parser.y"
              { 
        printf("Tipo boolean parser\n");
        (yyval.astNode) = new_ast_type("boolean"); 
        }
#line 2286 "src/parser.c"
    break;

  case 49: /* type: CHAR  */
#line 451 "src/parser.y"
           { 
        printf("Tipo char parser\n");
        (yyval.astNode) = new_ast_type("char"); 
        }
#line 2295 "src/parser.c"
    break;

  case 50: /* type: STRING_TYPE  */
#line 455 "src/parser.y"
                  { 
        printf("Tipo String parser\n"); 
         (yyval.astNode) = new_ast_type("String");
        }
#line 2304 "src/parser.c"
    break;

  case 51: /* type: ID  */
#line 459 "src/parser.y"
         { 
        /* Soportar tipos de usuario / clases como StringBuilder */
        printf("Tipo (identificador) parser: %s\n", (yyvsp[0].string_val));
        (yyval.astNode) = new_ast_type((yyvsp[0].string_val));
        }
#line 2314 "src/parser.c"
    break;

  case 52: /* type: INT LBRACKET RBRACKET  */
#line 464 "src/parser.y"
                            {
        printf("Tipo int[] parser\n");
        (yyval.astNode) = new_ast_type("int[]");
    }
#line 2323 "src/parser.c"
    break;

  case 53: /* type: FLOAT LBRACKET RBRACKET  */
#line 468 "src/parser.y"
                              {
        printf("Tipo float[] parser\n");
        (yyval.astNode) = new_ast_type("float[]");
    }
#line 2332 "src/parser.c"
    break;

  case 54: /* type: DOUBLE LBRACKET RBRACKET  */
#line 472 "src/parser.y"
                               {
        printf("Tipo double[] parser\n");
        (yyval.astNode) = new_ast_type("double[]");
    }
#line 2341 "src/parser.c"
    break;

  case 55: /* type: STRING_TYPE LBRACKET RBRACKET  */
#line 476 "src/parser.y"
                                    {
        printf("Tipo String[] parser\n");
        (yyval.astNode) = new_ast_type("String[]");
    }
#line 2350 "src/parser.c"
    break;

  case 56: /* type: ID LBRACKET RBRACKET  */
#line 481 "src/parser.y"
                           {
        char *tmp = malloc(strlen((yyvsp[-2].string_val)) + 3);
        snprintf(tmp, strlen((yyvsp[-2].string_val)) + 3, "%s[]", (yyvsp[-2].string_val));
        printf("Tipo (identificador) array parser: %s\n", tmp);
        (yyval.astNode) = new_ast_type(tmp);
        free(tmp);
    }
#line 2362 "src/parser.c"
    break;

  case 57: /* type: type LBRACKET RBRACKET  */
#line 488 "src/parser.y"
                             {
        if ((yyvsp[-2].astNode) && (yyvsp[-2].astNode)->data.type_name) {
            size_t len = strlen((yyvsp[-2].astNode)->data.type_name) + 3;
            char *tmp = malloc(len);
            snprintf(tmp, len, "%s[]", (yyvsp[-2].astNode)->data.type_name);
            printf("Tipo multi-dimensional parser: %s\n", tmp);
            (yyval.astNode) = new_ast_type(tmp);
            free(tmp);
        } else {
            (yyval.astNode) = NULL;
        }
    }
#line 2379 "src/parser.c"
    break;

  case 58: /* type: INT_ARRAY  */
#line 500 "src/parser.y"
                { (yyval.astNode) = new_ast_type("int[]"); }
#line 2385 "src/parser.c"
    break;

  case 59: /* type: FLOAT_ARRAY  */
#line 501 "src/parser.y"
                  { (yyval.astNode) = new_ast_type("float[]"); }
#line 2391 "src/parser.c"
    break;

  case 60: /* type: DOUBLE_ARRAY  */
#line 502 "src/parser.y"
                   { (yyval.astNode) = new_ast_type("double[]"); }
#line 2397 "src/parser.c"
    break;

  case 61: /* type: STRING_ARRAY  */
#line 503 "src/parser.y"
                   { (yyval.astNode) = new_ast_type("String[]"); }
#line 2403 "src/parser.c"
    break;

  case 62: /* assignment: ID ASSIGN expression SEMICOLON  */
#line 507 "src/parser.y"
                                       { 
        printf("Asignación: %s\n", (yyvsp[-3].string_val));
        // Verificar compatibilidad en asignaciones
        if (!verificar_asignacion((yyvsp[-3].string_val), (yyvsp[-1].astNode))) {
            /* report_semantic_error(yylineno, 0, "Incompatibilidad de tipos en la asignación", "Global"); */
           /* Dejar la validación/report desde semantic_analysis(AST) */
        }
        (yyval.astNode) = new_ast_assign((yyvsp[-3].string_val), (yyvsp[-1].astNode)); 
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2418 "src/parser.c"
    break;

  case 63: /* assignment: array_access ASSIGN expression SEMICOLON  */
#line 517 "src/parser.y"
                                               {
            printf("Asignación a elemento de arreglo\n");
            /* $1 es ast_node* devuelto por array_access (new_ast_array_access) */
            if ((yyvsp[-3].astNode) && (yyvsp[-3].astNode)->type == AST_ARRAY_ACCESS) {
                /* crear nodo específico de asignación a array (implementar en ast.c si falta) */
                (yyval.astNode) = new_ast_array_assignment((yyvsp[-3].astNode)->data.array_access.array_name, (yyvsp[-3].astNode)->data.array_access.index, (yyvsp[-1].astNode));
                if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
            } else {
                (yyval.astNode) = NULL;
            }
    }
#line 2434 "src/parser.c"
    break;

  case 64: /* assignment: ID PLUS_ASSIGN expression SEMICOLON  */
#line 528 "src/parser.y"
                                          { 
        // x += y se convierte en x = x + y
        ast_node* var = new_ast_variable((yyvsp[-3].string_val));
        ast_node* add_expr = new_ast_binary_op(OP_PLUS, var, (yyvsp[-1].astNode));
        (yyval.astNode) = new_ast_assign((yyvsp[-3].string_val), add_expr);
    }
#line 2445 "src/parser.c"
    break;

  case 65: /* assignment: ID MINUS_ASSIGN expression SEMICOLON  */
#line 534 "src/parser.y"
                                           { 
        // x -= y se convierte en x = x - y
        ast_node* var = new_ast_variable((yyvsp[-3].string_val));
        ast_node* sub_expr = new_ast_binary_op(OP_MINUS, var, (yyvsp[-1].astNode));
        (yyval.astNode) = new_ast_assign((yyvsp[-3].string_val), sub_expr);
    }
#line 2456 "src/parser.c"
    break;

  case 66: /* assignment: ID MULT_ASSIGN expression SEMICOLON  */
#line 540 "src/parser.y"
                                          {
        // x *= y se convierte en x = x * y
        ast_node* var = new_ast_variable((yyvsp[-3].string_val));
        ast_node* mul_expr = new_ast_binary_op(OP_MULT, var, (yyvsp[-1].astNode));
        (yyval.astNode) = new_ast_assign((yyvsp[-3].string_val), mul_expr);
    }
#line 2467 "src/parser.c"
    break;

  case 67: /* assignment: ID DIV_ASSIGN expression SEMICOLON  */
#line 546 "src/parser.y"
                                         {
        // x /= y se convierte en x = x / y
        ast_node* var = new_ast_variable((yyvsp[-3].string_val));
        ast_node* div_expr = new_ast_binary_op(OP_DIV, var, (yyvsp[-1].astNode));
        (yyval.astNode) = new_ast_assign((yyvsp[-3].string_val), div_expr);
    }
#line 2478 "src/parser.c"
    break;

  case 68: /* expression: literal  */
#line 555 "src/parser.y"
            { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2484 "src/parser.c"
    break;

  case 69: /* expression: array_initialization  */
#line 556 "src/parser.y"
                           { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2490 "src/parser.c"
    break;

  case 70: /* expression: ID  */
#line 557 "src/parser.y"
         { (yyval.astNode) = new_ast_variable((yyvsp[0].string_val)); }
#line 2496 "src/parser.c"
    break;

  case 71: /* expression: ID ASSIGN expression  */
#line 559 "src/parser.y"
                          {
        printf("Asignación (expr) en contexto: %s = ...\n", (yyvsp[-2].string_val));
       (yyval.astNode) = new_ast_assign((yyvsp[-2].string_val), (yyvsp[0].astNode));
       if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2506 "src/parser.c"
    break;

  case 72: /* expression: array_access ASSIGN expression  */
#line 564 "src/parser.y"
                                     {
        printf("Asignación a elemento de arreglo (expr) en contexto\n");
        if ((yyvsp[-2].astNode) && (yyvsp[-2].astNode)->type == AST_ARRAY_ACCESS) {
            (yyval.astNode) = new_ast_array_assignment((yyvsp[-2].astNode)->data.array_access.array_name, (yyvsp[-2].astNode)->data.array_access.index, (yyvsp[0].astNode));
            if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
        } else (yyval.astNode) = NULL;
    }
#line 2518 "src/parser.c"
    break;

  case 73: /* expression: ID PLUS_ASSIGN expression  */
#line 571 "src/parser.y"
                               {
        ast_node* var = new_ast_variable((yyvsp[-2].string_val));
        ast_node* add_expr = new_ast_binary_op(OP_PLUS, var, (yyvsp[0].astNode));
        (yyval.astNode) = new_ast_assign((yyvsp[-2].string_val), add_expr);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2529 "src/parser.c"
    break;

  case 74: /* expression: ID MINUS_ASSIGN expression  */
#line 577 "src/parser.y"
                                {
        ast_node* var = new_ast_variable((yyvsp[-2].string_val));
        ast_node* sub_expr = new_ast_binary_op(OP_MINUS, var, (yyvsp[0].astNode));
        (yyval.astNode) = new_ast_assign((yyvsp[-2].string_val), sub_expr);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2540 "src/parser.c"
    break;

  case 75: /* expression: ID MULT_ASSIGN expression  */
#line 583 "src/parser.y"
                               {
        ast_node* var = new_ast_variable((yyvsp[-2].string_val));
        ast_node* mul_expr = new_ast_binary_op(OP_MULT, var, (yyvsp[0].astNode));
        (yyval.astNode) = new_ast_assign((yyvsp[-2].string_val), mul_expr);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2551 "src/parser.c"
    break;

  case 76: /* expression: ID DIV_ASSIGN expression  */
#line 589 "src/parser.y"
                               {
        ast_node* var = new_ast_variable((yyvsp[-2].string_val));
        ast_node* div_expr = new_ast_binary_op(OP_DIV, var, (yyvsp[0].astNode));
        (yyval.astNode) = new_ast_assign((yyvsp[-2].string_val), div_expr);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2562 "src/parser.c"
    break;

  case 77: /* expression: expression PLUS expression  */
#line 595 "src/parser.y"
                                 { (yyval.astNode) = new_ast_binary_op(OP_PLUS, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2568 "src/parser.c"
    break;

  case 78: /* expression: expression MINUS expression  */
#line 596 "src/parser.y"
                                  { (yyval.astNode) = new_ast_binary_op(OP_MINUS, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2574 "src/parser.c"
    break;

  case 79: /* expression: expression MULT expression  */
#line 597 "src/parser.y"
                                 { (yyval.astNode) = new_ast_binary_op(OP_MULT, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2580 "src/parser.c"
    break;

  case 80: /* expression: expression DIV expression  */
#line 598 "src/parser.y"
                                { (yyval.astNode) = new_ast_binary_op(OP_DIV, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2586 "src/parser.c"
    break;

  case 81: /* expression: expression MOD expression  */
#line 599 "src/parser.y"
                                { (yyval.astNode) = new_ast_binary_op(OP_MOD, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2592 "src/parser.c"
    break;

  case 82: /* expression: expression EQUALS expression  */
#line 600 "src/parser.y"
                                   { (yyval.astNode) = new_ast_binary_op(OP_EQUALS, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2598 "src/parser.c"
    break;

  case 83: /* expression: expression NOT_EQUALS expression  */
#line 601 "src/parser.y"
                                       { (yyval.astNode) = new_ast_binary_op(OP_NOT_EQUALS, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2604 "src/parser.c"
    break;

  case 84: /* expression: expression LESS expression  */
#line 602 "src/parser.y"
                                 { (yyval.astNode) = new_ast_binary_op(OP_LESS, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2610 "src/parser.c"
    break;

  case 85: /* expression: expression GREATER expression  */
#line 603 "src/parser.y"
                                    { (yyval.astNode) = new_ast_binary_op(OP_GREATER, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2616 "src/parser.c"
    break;

  case 86: /* expression: expression LESS_EQUALS expression  */
#line 604 "src/parser.y"
                                        { (yyval.astNode) = new_ast_binary_op(OP_LESS_EQUALS, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2622 "src/parser.c"
    break;

  case 87: /* expression: expression GREATER_EQUALS expression  */
#line 605 "src/parser.y"
                                           { (yyval.astNode) = new_ast_binary_op(OP_GREATER_EQUALS, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2628 "src/parser.c"
    break;

  case 88: /* expression: expression AND expression  */
#line 606 "src/parser.y"
                                { (yyval.astNode) = new_ast_binary_op(OP_AND, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2634 "src/parser.c"
    break;

  case 89: /* expression: expression OR expression  */
#line 607 "src/parser.y"
                               { (yyval.astNode) = new_ast_binary_op(OP_OR, (yyvsp[-2].astNode), (yyvsp[0].astNode)); }
#line 2640 "src/parser.c"
    break;

  case 90: /* expression: expression DOT EQUALS_METHOD LPAREN expression RPAREN  */
#line 608 "src/parser.y"
                                                            {(yyval.astNode) = new_ast_string_equals((yyvsp[-5].astNode), (yyvsp[-1].astNode));}
#line 2646 "src/parser.c"
    break;

  case 91: /* expression: expression DOT ID LPAREN expression RPAREN  */
#line 609 "src/parser.y"
                                                 {
        printf("Method call parser: receiver . %s(...)\n", (yyvsp[-3].string_val));
        (yyval.astNode) = new_ast_method_call((yyvsp[-5].astNode), (yyvsp[-3].string_val), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2656 "src/parser.c"
    break;

  case 92: /* expression: expression DOT ID LPAREN RPAREN  */
#line 614 "src/parser.y"
                                      {
       printf("Method call (no-arg) parser: receiver . %s()\n", (yyvsp[-2].string_val));
        (yyval.astNode) = new_ast_method_call((yyvsp[-4].astNode), (yyvsp[-2].string_val), NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2666 "src/parser.c"
    break;

  case 93: /* expression: ID DOT ID LPAREN expression RPAREN  */
#line 619 "src/parser.y"
                                         {
        printf("Static method call parser: %s.%s(...)\n", (yyvsp[-5].string_val), (yyvsp[-3].string_val));
        ast_node *recv = new_ast_variable((yyvsp[-5].string_val));
        (yyval.astNode) = new_ast_method_call(recv, (yyvsp[-3].string_val), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2677 "src/parser.c"
    break;

  case 94: /* expression: ID DOT ID LPAREN RPAREN  */
#line 625 "src/parser.y"
                              {
        printf("Static method call (no-arg) parser: %s.%s()\n", (yyvsp[-4].string_val), (yyvsp[-2].string_val));
        ast_node *recv = new_ast_variable((yyvsp[-4].string_val));
        (yyval.astNode) = new_ast_method_call(recv, (yyvsp[-2].string_val), NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2688 "src/parser.c"
    break;

  case 95: /* expression: ID LPAREN expression_list RPAREN  */
#line 632 "src/parser.y"
                                      {
        printf("Function call parser: %s(...)\n", (yyvsp[-3].string_val));
        (yyval.astNode) = new_ast_method_call(NULL, (yyvsp[-3].string_val), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2698 "src/parser.c"
    break;

  case 96: /* expression: ID LPAREN RPAREN  */
#line 637 "src/parser.y"
                       {
        printf("Function call (no-arg) parser: %s()\n", (yyvsp[-2].string_val));
        (yyval.astNode) = new_ast_method_call(NULL, (yyvsp[-2].string_val), NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2708 "src/parser.c"
    break;

  case 97: /* expression: expression DOT ID  */
#line 642 "src/parser.y"
                        {
        /* Si el receptor es una variable, construiremos "var.field" como nombre */
        if ((yyvsp[-2].astNode) && (yyvsp[-2].astNode)->type == AST_VARIABLE && (yyvsp[-2].astNode)->data.var_name) {
            size_t len = strlen((yyvsp[-2].astNode)->data.var_name) + 1 + strlen((yyvsp[0].string_val)) + 1;
            char *tmp = malloc(len);
            snprintf(tmp, len, "%s.%s", (yyvsp[-2].astNode)->data.var_name, (yyvsp[0].string_val));
            (yyval.astNode) = new_ast_variable(tmp);
            free(tmp);
        } else {
            /* Fallback: usar solo el campo como variable */
            (yyval.astNode) = new_ast_variable((yyvsp[0].string_val));
        }
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2727 "src/parser.c"
    break;

  case 98: /* expression: ID DOT ID  */
#line 656 "src/parser.y"
               {
        /* Caso común: ID.ID -> crear variable "id.field" */
        size_t len = strlen((yyvsp[-2].string_val)) + 1 + strlen((yyvsp[0].string_val)) + 1;
        char *tmp = malloc(len);
        snprintf(tmp, len, "%s.%s", (yyvsp[-2].string_val), (yyvsp[0].string_val));
        (yyval.astNode) = new_ast_variable(tmp);
        free(tmp);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2741 "src/parser.c"
    break;

  case 99: /* expression: expression DOT ID LPAREN expression_list RPAREN  */
#line 666 "src/parser.y"
                                                      {
        printf("Method call parser: receiver . %s(...)\n", (yyvsp[-3].string_val));
        (yyval.astNode) = new_ast_method_call((yyvsp[-5].astNode), (yyvsp[-3].string_val), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2751 "src/parser.c"
    break;

  case 100: /* expression: ID DOT ID LPAREN expression_list RPAREN  */
#line 671 "src/parser.y"
                                              {
        printf("Static method call parser: %s.%s(...)\n", (yyvsp[-5].string_val), (yyvsp[-3].string_val));
        ast_node *recv = new_ast_variable((yyvsp[-5].string_val));
        (yyval.astNode) = new_ast_method_call(recv, (yyvsp[-3].string_val), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2762 "src/parser.c"
    break;

  case 101: /* expression: NEW ID LPAREN RPAREN  */
#line 677 "src/parser.y"
                           {
        printf("Object creation parser: new %s()\n", (yyvsp[-2].string_val));
        (yyval.astNode) = new_ast_new_object((yyvsp[-2].string_val)); /* implementar en ast.c */
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2772 "src/parser.c"
    break;

  case 102: /* expression: NEW type LBRACKET expression RBRACKET  */
#line 682 "src/parser.y"
                                            {
        printf("Array creation parser: new <type>[expr]\n");
        (yyval.astNode) = new_ast_new_array((yyvsp[-3].astNode), (yyvsp[-1].astNode)); /* implementar en ast.c */
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2782 "src/parser.c"
    break;

  case 103: /* expression: NEW type LBRACKET RBRACKET LBRACE expression_list RBRACE  */
#line 687 "src/parser.y"
                                                               {
        printf("Array creation con inicialización: new <type>[] { ... }\n");
        (yyval.astNode) = new_ast_new_array_with_init((yyvsp[-5].astNode), (yyvsp[-1].astNode)); /* implementar en ast.c */
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2792 "src/parser.c"
    break;

  case 104: /* expression: NEW INT_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE  */
#line 692 "src/parser.y"
                                                                    {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("int[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2801 "src/parser.c"
    break;

  case 105: /* expression: NEW FLOAT_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE  */
#line 696 "src/parser.y"
                                                                      {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("float[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2810 "src/parser.c"
    break;

  case 106: /* expression: NEW DOUBLE_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE  */
#line 700 "src/parser.y"
                                                                       {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("double[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2819 "src/parser.c"
    break;

  case 107: /* expression: NEW STRING_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE  */
#line 704 "src/parser.y"
                                                                       {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("String[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2828 "src/parser.c"
    break;

  case 108: /* expression: NEW BOOLEAN_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE  */
#line 708 "src/parser.y"
                                                                        {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("boolean[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2837 "src/parser.c"
    break;

  case 109: /* expression: NEW CHAR_ARRAY LBRACKET RBRACKET LBRACE expression_list RBRACE  */
#line 712 "src/parser.y"
                                                                     {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("char[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2846 "src/parser.c"
    break;

  case 110: /* expression: NEW INT_ARRAY LBRACE expression_list RBRACE  */
#line 716 "src/parser.y"
                                                  {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("int[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2855 "src/parser.c"
    break;

  case 111: /* expression: NEW INT_ARRAY LBRACKET expression RBRACKET  */
#line 720 "src/parser.y"
                                                 {
        (yyval.astNode) = new_ast_new_array(new_ast_type("int[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2864 "src/parser.c"
    break;

  case 112: /* expression: NEW FLOAT_ARRAY LBRACE expression_list RBRACE  */
#line 724 "src/parser.y"
                                                    {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("float[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2873 "src/parser.c"
    break;

  case 113: /* expression: NEW FLOAT_ARRAY LBRACKET expression RBRACKET  */
#line 728 "src/parser.y"
                                                   {
        (yyval.astNode) = new_ast_new_array(new_ast_type("float[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2882 "src/parser.c"
    break;

  case 114: /* expression: NEW DOUBLE_ARRAY LBRACE expression_list RBRACE  */
#line 732 "src/parser.y"
                                                     {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("double[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2891 "src/parser.c"
    break;

  case 115: /* expression: NEW DOUBLE_ARRAY LBRACKET expression RBRACKET  */
#line 736 "src/parser.y"
                                                    {
        (yyval.astNode) = new_ast_new_array(new_ast_type("double[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2900 "src/parser.c"
    break;

  case 116: /* expression: NEW STRING_ARRAY LBRACE expression_list RBRACE  */
#line 740 "src/parser.y"
                                                     {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("String[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2909 "src/parser.c"
    break;

  case 117: /* expression: NEW STRING_ARRAY LBRACKET expression RBRACKET  */
#line 744 "src/parser.y"
                                                    {
        (yyval.astNode) = new_ast_new_array(new_ast_type("String[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2918 "src/parser.c"
    break;

  case 118: /* expression: NEW BOOLEAN_ARRAY LBRACE expression_list RBRACE  */
#line 748 "src/parser.y"
                                                      {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("boolean[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2927 "src/parser.c"
    break;

  case 119: /* expression: NEW BOOLEAN_ARRAY LBRACKET expression RBRACKET  */
#line 752 "src/parser.y"
                                                     {
        (yyval.astNode) = new_ast_new_array(new_ast_type("boolean[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2936 "src/parser.c"
    break;

  case 120: /* expression: NEW CHAR_ARRAY LBRACE expression_list RBRACE  */
#line 756 "src/parser.y"
                                                   {
        (yyval.astNode) = new_ast_new_array_with_init(new_ast_type("char[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2945 "src/parser.c"
    break;

  case 121: /* expression: NEW CHAR_ARRAY LBRACKET expression RBRACKET  */
#line 760 "src/parser.y"
                                                  {
        (yyval.astNode) = new_ast_new_array(new_ast_type("char[]"), (yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 2954 "src/parser.c"
    break;

  case 122: /* expression: NOT expression  */
#line 764 "src/parser.y"
                     { (yyval.astNode) = new_ast_unary_op(OP_NOT, (yyvsp[0].astNode)); }
#line 2960 "src/parser.c"
    break;

  case 123: /* expression: MINUS expression  */
#line 765 "src/parser.y"
                                 { (yyval.astNode) = new_ast_unary_op(OP_UMINUS, (yyvsp[0].astNode)); }
#line 2966 "src/parser.c"
    break;

  case 124: /* expression: INCREMENT ID  */
#line 766 "src/parser.y"
                   { (yyval.astNode) = new_ast_unary_op(OP_INCREMENT, new_ast_variable((yyvsp[0].string_val))); }
#line 2972 "src/parser.c"
    break;

  case 125: /* expression: ID INCREMENT  */
#line 767 "src/parser.y"
                   { (yyval.astNode) = new_ast_unary_op(OP_POST_INCREMENT, new_ast_variable((yyvsp[-1].string_val))); }
#line 2978 "src/parser.c"
    break;

  case 126: /* expression: DECREMENT ID  */
#line 768 "src/parser.y"
                   { (yyval.astNode) = new_ast_unary_op(OP_DECREMENT, new_ast_variable((yyvsp[0].string_val))); }
#line 2984 "src/parser.c"
    break;

  case 127: /* expression: ID DECREMENT  */
#line 769 "src/parser.y"
                   { (yyval.astNode) = new_ast_unary_op(OP_POST_DECREMENT, new_ast_variable((yyvsp[-1].string_val))); }
#line 2990 "src/parser.c"
    break;

  case 128: /* expression: array_access  */
#line 770 "src/parser.y"
                   { (yyval.astNode) = (yyvsp[0].astNode); }
#line 2996 "src/parser.c"
    break;

  case 129: /* expression: array_access  */
#line 771 "src/parser.y"
                   { (yyval.astNode) = (yyvsp[0].astNode); }
#line 3002 "src/parser.c"
    break;

  case 130: /* expression: LPAREN expression RPAREN  */
#line 772 "src/parser.y"
                               { (yyval.astNode) = (yyvsp[-1].astNode); }
#line 3008 "src/parser.c"
    break;

  case 131: /* literal: INT_LITERAL  */
#line 776 "src/parser.y"
                { 
        printf("Literal int parser\n");
        (yyval.astNode) = new_ast_int_literal((yyvsp[0].int_val)); 
        }
#line 3017 "src/parser.c"
    break;

  case 132: /* literal: FLOAT_LITERAL  */
#line 780 "src/parser.y"
                    { 
        printf("Literal float parser\n");
        (yyval.astNode) = new_ast_float_literal((yyvsp[0].float_val)); 
        }
#line 3026 "src/parser.c"
    break;

  case 133: /* literal: DOUBLE_LITERAL  */
#line 785 "src/parser.y"
                     { 
        printf("Literal double parser\n");
        (yyval.astNode) = new_ast_double_literal((yyvsp[0].double_val)); 
        }
#line 3035 "src/parser.c"
    break;

  case 134: /* literal: STRING_LITERAL  */
#line 790 "src/parser.y"
                     { 
        printf("Literal string parser\n");
        (yyval.astNode) = new_ast_string_literal((yyvsp[0].string_val)); 
     }
#line 3044 "src/parser.c"
    break;

  case 135: /* literal: CHAR_LITERAL  */
#line 794 "src/parser.y"
                   { 
        printf("Literal char parser\n");
        char c = (strlen((yyvsp[0].string_val)) >= 3) ? (yyvsp[0].string_val)[1] : '\0';
        (yyval.astNode) = new_ast_char_literal(c); 
        }
#line 3054 "src/parser.c"
    break;

  case 136: /* literal: TRUE_TOKEN  */
#line 799 "src/parser.y"
                 { 
        printf("Literal bool true parser\n");
        (yyval.astNode) = new_ast_bool_literal(1); 
        }
#line 3063 "src/parser.c"
    break;

  case 137: /* literal: FALSE_TOKEN  */
#line 803 "src/parser.y"
                  { 
        printf("Literal bool false parser\n");
        (yyval.astNode) = new_ast_bool_literal(0); 
        }
#line 3072 "src/parser.c"
    break;

  case 138: /* literal: NULL_TOKEN  */
#line 807 "src/parser.y"
                 { 
        printf("Literal null parser\n");
        (yyval.astNode) = new_ast_null_literal(); 
        }
#line 3081 "src/parser.c"
    break;

  case 139: /* if_statement: IF LPAREN expression RPAREN statement  */
#line 814 "src/parser.y"
                                          {
        printf("If statement sin else\n");
        (yyval.astNode) = new_ast_if((yyvsp[-2].astNode), (yyvsp[0].astNode), NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 3091 "src/parser.c"
    break;

  case 140: /* if_statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 819 "src/parser.y"
                                                           {
        printf("If statement con else\n");
        (yyval.astNode) = new_ast_if((yyvsp[-4].astNode), (yyvsp[-2].astNode), (yyvsp[0].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 3101 "src/parser.c"
    break;

  case 141: /* while_statement: WHILE LPAREN expression RPAREN statement  */
#line 827 "src/parser.y"
                                             { 
        printf("While statement parser\n");
        (yyval.astNode) = new_ast_while((yyvsp[-2].astNode), (yyvsp[0].astNode)); 
        }
#line 3110 "src/parser.c"
    break;

  case 142: /* while_statement: DO statement WHILE LPAREN expression RPAREN SEMICOLON  */
#line 831 "src/parser.y"
                                                            {
        printf("Do-While statement parser\n");
        (yyval.astNode) = new_ast_do_while((yyvsp[-2].astNode), (yyvsp[-5].astNode)); 
        }
#line 3119 "src/parser.c"
    break;

  case 143: /* for_statement: FOR LPAREN for_init SEMICOLON expression SEMICOLON expression RPAREN statement  */
#line 838 "src/parser.y"
                                                                                   { 
        printf("For statement parser\n");
        (yyval.astNode) = new_ast_for((yyvsp[-6].astNode), (yyvsp[-4].astNode), (yyvsp[-2].astNode), (yyvsp[0].astNode)); 
    }
#line 3128 "src/parser.c"
    break;

  case 144: /* for_statement: FOR LPAREN type ID COLON expression RPAREN statement  */
#line 842 "src/parser.y"
                                                           {
        printf("Enhanced for parsed\n");
        /* $3 = type (ast_node*), $4 = var name, $6 = collection expr, $8 = body */
        (yyval.astNode) = new_ast_foreach((yyvsp[-5].astNode), (yyvsp[-4].string_val), (yyvsp[-2].astNode), (yyvsp[0].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 3139 "src/parser.c"
    break;

  case 145: /* return_statement: RETURN SEMICOLON  */
#line 851 "src/parser.y"
                     {
        printf("Return statement (void) parser\n");
        (yyval.astNode) = new_ast_return(NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 3149 "src/parser.c"
    break;

  case 146: /* return_statement: RETURN expression SEMICOLON  */
#line 856 "src/parser.y"
                                  {
        printf("Return statement parser\n");
        (yyval.astNode) = new_ast_return((yyvsp[-1].astNode));
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
    }
#line 3159 "src/parser.c"
    break;

  case 147: /* $@1: %empty  */
#line 864 "src/parser.y"
                                     { /* guardar expresión del switch para las secciones */ g_switch_expr = (yyvsp[-1].astNode); }
#line 3165 "src/parser.c"
    break;

  case 148: /* switch_statement: SWITCH LPAREN expression RPAREN $@1 LBRACE switch_sections RBRACE  */
#line 865 "src/parser.y"
                                     { 
        /* limpiar la variable temporal y devolver un compound con las secciones transformadas */
        (yyval.astNode) = new_ast_compound_stmt((yyvsp[-1].astNode), NULL);
        if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
        g_switch_expr = NULL;
    }
#line 3176 "src/parser.c"
    break;

  case 149: /* switch_sections: %empty  */
#line 875 "src/parser.y"
                {
        (yyval.astNode) = NULL;
    }
#line 3184 "src/parser.c"
    break;

  case 150: /* switch_sections: switch_sections switch_section  */
#line 878 "src/parser.y"
                                     {
        /* append switch_section into a single chain so default becomes else of previous if */
        (yyval.astNode) = append_switch_case((yyvsp[-1].astNode), (yyvsp[0].astNode));
    }
#line 3193 "src/parser.c"
    break;

  case 151: /* switch_section: CASE literal COLON statement_list_opt  */
#line 886 "src/parser.y"
                                          {
        printf("Switch case parsed (transforming to if)\n");
        if (g_switch_expr == NULL) {
            /* protección: si no hay expr, devolver body tal cual */
            (yyval.astNode) = (yyvsp[0].astNode);
        } else {
            ast_node *cmp = new_ast_binary_op(OP_EQUALS, g_switch_expr, (yyvsp[-2].astNode));
            (yyval.astNode) = new_ast_if(cmp, (yyvsp[0].astNode), NULL);
            if ((yyval.astNode)) (yyval.astNode)->line = yylineno;
        }
    }
#line 3209 "src/parser.c"
    break;

  case 152: /* switch_section: DEFAULT COLON statement_list_opt  */
#line 897 "src/parser.y"
                                       {
        printf("Switch default parsed (as else)\n");
        /* default -> devolver el bloque de statements directamente; será enlazado como else por append_switch_case */
        (yyval.astNode) = (yyvsp[0].astNode);
    }
#line 3219 "src/parser.c"
    break;

  case 153: /* statement_list_opt: statement_list  */
#line 905 "src/parser.y"
                   { (yyval.astNode) = (yyvsp[0].astNode); }
#line 3225 "src/parser.c"
    break;

  case 154: /* statement_list_opt: %empty  */
#line 906 "src/parser.y"
                  { (yyval.astNode) = NULL; }
#line 3231 "src/parser.c"
    break;

  case 155: /* array_declaration: type ID LBRACKET INT_LITERAL RBRACKET  */
#line 910 "src/parser.y"
                                          {
        printf("Declaración de arreglo: %s[%d]\n", (yyvsp[-3].string_val), (yyvsp[-1].int_val)); 
        ast_node *size_node = new_ast_int_literal((yyvsp[-1].int_val));
        (yyval.astNode) = new_ast_array_declaration((yyvsp[-4].astNode), (yyvsp[-3].string_val), size_node);
    }
#line 3241 "src/parser.c"
    break;

  case 156: /* array_declaration: type ID LBRACKET INT_LITERAL RBRACKET ASSIGN array_initialization  */
#line 915 "src/parser.y"
                                                                        {
        printf("Declaración de arreglo con inicialización: %s\n", (yyvsp[-5].string_val));
        ast_node *size_node = new_ast_int_literal((yyvsp[-3].int_val));
        (yyval.astNode) = new_ast_array_declaration_with_init((yyvsp[-6].astNode), (yyvsp[-5].string_val), size_node, (yyvsp[0].astNode));
    }
#line 3251 "src/parser.c"
    break;

  case 157: /* array_initialization: LBRACE expression_list RBRACE  */
#line 923 "src/parser.y"
                                  {
        printf("Inicialización de arreglo con valores\n");
        (yyval.astNode) = new_ast_array_init((yyvsp[-1].astNode));
    }
#line 3260 "src/parser.c"
    break;

  case 158: /* expression_list: expression  */
#line 930 "src/parser.y"
               { (yyval.astNode) = (yyvsp[0].astNode); }
#line 3266 "src/parser.c"
    break;

  case 159: /* expression_list: expression_list COMMA expression  */
#line 931 "src/parser.y"
                                       {
        if ((yyvsp[-2].astNode)) {
            ast_node *current = (yyvsp[-2].astNode);
            while (current->next) {
                current = current->next;
            }
            current->next = (yyvsp[0].astNode);
            (yyval.astNode) = (yyvsp[-2].astNode);
        } else {
            (yyval.astNode) = (yyvsp[0].astNode);
        }
    }
#line 3283 "src/parser.c"
    break;

  case 160: /* array_access: ID LBRACKET expression RBRACKET  */
#line 945 "src/parser.y"
                                    {
        printf("Acceso a arreglo: %s[]\n", (yyvsp[-3].string_val));
        (yyval.astNode) = new_ast_array_access((yyvsp[-3].string_val), (yyvsp[-1].astNode));
    }
#line 3292 "src/parser.c"
    break;


#line 3296 "src/parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 952 "src/parser.y"


/********************** SECCIÓN DE CÓDIGO C **********************/

void yyerror(const char *s) {
    fprintf(stderr, "Error sintáctico en línea %d: %s\n", yylineno, s);
    fprintf(stderr, "Token inesperado: '%s'\n", yytext);
    
    // enviar este error a la GUI aquí
    report_syntax_error(yylineno, 0, s, yytext);
    reset_lexer();
}

// Función para reiniciar el estado del lexer
void reset_lexer(void) {
    // Limpia cualquier estado residual del lexer
    yyrestart(NULL);
    // Reinicia las variables de entrada desde memoria
    cleanup_lexer();
}

// Función para ejecutar el parser desde código externo
int parse_from_string(const char *input) {
    // Limpiar cualquier análisis anterior
    if (root) {
        // Liberar el AST anterior si existe
        free_ast(root);
        root = NULL;
    }
    
    // Configurar la entrada desde memoria
    set_input_string(input);
    
    // Reiniciar el estado del parser y lexer
    yyrestart(NULL);
    reset_lexer();
    
    // Ejecutar el análisis
    int result = yyparse();
    
    return result;
}

// Función para obtener el AST resultante
ast_node* get_ast_root(void) {
    return root;
}

// Función para limpiar completamente el parser
void cleanup_parser(void) {
    if (root) {
        free_ast(root);
        root = NULL;
    }
    cleanup_lexer();
}
