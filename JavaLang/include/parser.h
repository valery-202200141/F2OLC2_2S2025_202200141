/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INCLUDE_PARSER_H_INCLUDED
# define YY_YY_INCLUDE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    INT_LITERAL = 259,             /* INT_LITERAL  */
    FLOAT_LITERAL = 260,           /* FLOAT_LITERAL  */
    DOUBLE_LITERAL = 261,          /* DOUBLE_LITERAL  */
    STRING_LITERAL = 262,          /* STRING_LITERAL  */
    CHAR_LITERAL = 263,            /* CHAR_LITERAL  */
    INT = 264,                     /* INT  */
    FLOAT = 265,                   /* FLOAT  */
    DOUBLE = 266,                  /* DOUBLE  */
    BOOLEAN = 267,                 /* BOOLEAN  */
    CHAR = 268,                    /* CHAR  */
    STRING_TYPE = 269,             /* STRING_TYPE  */
    CLASS = 270,                   /* CLASS  */
    PUBLIC = 271,                  /* PUBLIC  */
    PRIVATE = 272,                 /* PRIVATE  */
    PROTECTED = 273,               /* PROTECTED  */
    STATIC = 274,                  /* STATIC  */
    FINAL = 275,                   /* FINAL  */
    VOID = 276,                    /* VOID  */
    SYSTEM = 277,                  /* SYSTEM  */
    OUT = 278,                     /* OUT  */
    PRINTLN = 279,                 /* PRINTLN  */
    EQUALS_METHOD = 280,           /* EQUALS_METHOD  */
    IF = 281,                      /* IF  */
    ELSE = 282,                    /* ELSE  */
    WHILE = 283,                   /* WHILE  */
    FOR = 284,                     /* FOR  */
    DO = 285,                      /* DO  */
    SWITCH = 286,                  /* SWITCH  */
    CASE = 287,                    /* CASE  */
    DEFAULT = 288,                 /* DEFAULT  */
    BREAK = 289,                   /* BREAK  */
    CONTINUE = 290,                /* CONTINUE  */
    RETURN = 291,                  /* RETURN  */
    NEW = 292,                     /* NEW  */
    THIS = 293,                    /* THIS  */
    TRUE_TOKEN = 294,              /* TRUE_TOKEN  */
    FALSE_TOKEN = 295,             /* FALSE_TOKEN  */
    NULL_TOKEN = 296,              /* NULL_TOKEN  */
    PLUS = 297,                    /* PLUS  */
    MINUS = 298,                   /* MINUS  */
    MULT = 299,                    /* MULT  */
    DIV = 300,                     /* DIV  */
    MOD = 301,                     /* MOD  */
    INCREMENT = 302,               /* INCREMENT  */
    DECREMENT = 303,               /* DECREMENT  */
    ASSIGN = 304,                  /* ASSIGN  */
    PLUS_ASSIGN = 305,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 306,            /* MINUS_ASSIGN  */
    MULT_ASSIGN = 307,             /* MULT_ASSIGN  */
    DIV_ASSIGN = 308,              /* DIV_ASSIGN  */
    EQUALS = 309,                  /* EQUALS  */
    NOT_EQUALS = 310,              /* NOT_EQUALS  */
    LESS = 311,                    /* LESS  */
    GREATER = 312,                 /* GREATER  */
    LESS_EQUALS = 313,             /* LESS_EQUALS  */
    GREATER_EQUALS = 314,          /* GREATER_EQUALS  */
    AND = 315,                     /* AND  */
    OR = 316,                      /* OR  */
    NOT = 317,                     /* NOT  */
    LPAREN = 318,                  /* LPAREN  */
    RPAREN = 319,                  /* RPAREN  */
    LBRACE = 320,                  /* LBRACE  */
    RBRACE = 321,                  /* RBRACE  */
    LBRACKET = 322,                /* LBRACKET  */
    RBRACKET = 323,                /* RBRACKET  */
    SEMICOLON = 324,               /* SEMICOLON  */
    COMMA = 325,                   /* COMMA  */
    DOT = 326,                     /* DOT  */
    COLON = 327,                   /* COLON  */
    INT_ARRAY = 328,               /* INT_ARRAY  */
    FLOAT_ARRAY = 329,             /* FLOAT_ARRAY  */
    DOUBLE_ARRAY = 330,            /* DOUBLE_ARRAY  */
    STRING_ARRAY = 331,            /* STRING_ARRAY  */
    BOOLEAN_ARRAY = 332,           /* BOOLEAN_ARRAY  */
    CHAR_ARRAY = 333,              /* CHAR_ARRAY  */
    ERROR = 334,                   /* ERROR  */
    UMINUS = 335                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 66 "src/parser.y"

    ast_node* astNode;   // Puntero a un nodo del AST
    int int_val;         // Para valores enteros
    float float_val;     // Para valores flotantes
    double double_val;   // Para valores double
    char* string_val;    // Para strings e identificadores

#line 152 "include/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_PARSER_H_INCLUDED  */
