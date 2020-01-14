/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "asm.y" /* yacc.c:339  */

 
#include <stdio.h>
#include <stdarg.h> 
#include <string.h>
#include <stdlib.h>
#include "../asm/asm.h"
#include "../lib/dlxinstset.h"

#define H(v) (((unsigned long)v)>>16)
#define L(v) (v&0xFFFFU)
#define IMM16(v) ((unsigned short)(((unsigned long) v) & 0xFFFFU))

  Node *makeNode( asm_node_type type );

  int asm_check_instr_param( Node *node, int check );
  int yyerror_printf( const char *s, ... );
  extern int yylineno;

#define OPOK              0

#define ERRCANTPARSELINE  1

#define OPUNDEFINE        2
#define OPNEEDNOPARAM     3
#define OPNEEDREGREGPARAM 4
#define OPNEEDREGIMMPARAM 5
#define OPNEEDIMMPARAM    6
#define OPNEEDREGPARAM    7
#define OPNEEDSPREGPARAM  8
#define OPNEEDFPREGPARAM  9

#define ERRINVALIDIDENTIFIER 10
#define ERRINVALIDORG 11

#define P_REG_REG_REG 1
#define P_REG_REG_IMM 2
#define P_REG_REG     3
#define P_REG_IMM     4
#define P_MEM_REG     5
#define P_REG_MEM     6
#define P_REG         7
#define P_IMM         8
#define P_NONE        9



  const char *yy_error_txt[] = {
    "OK",

    "Can't parse line (ignoring line)",

    "instruction %s not defined (ignoring line)",
    "too many parameters for instruction %s  (ignoring line)",
    "instruction %s needs reg-reg params (ignoring line)",
    "instruction %s needs reg-imm params (ignoring line)",
    "instruction %s needs imm params (ignoring line)",
    "instruction %s needs reg params (ignoring line)",
    "instruction %s needs general-purpose registers",
    "instruction %s needs floating-point registers",

    "%s invalid or unknown data type.\n",
    "%s invalid segment identifier.\n"
  };

extern FILE *yyin;


#line 135 "asm.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "asm.tab.h".  */
#ifndef YY_YY_ASM_TAB_H_INCLUDED
# define YY_YY_ASM_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DATA_TYPE = 258,
    IDENTIFIER = 259,
    OP_CODE = 260,
    IMM_VALUE = 261,
    F_REG = 262,
    I_REG = 263,
    IMM_FVALUE = 264,
    EQU = 265,
    ORG = 266,
    T_CR = 267,
    NEG = 268
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 72 "asm.y" /* yacc.c:355  */

    double fvalue;
    long value;
    char *text;
    const dlx_instr_entry *instr;
    struct Node *node;
    struct Node *params[3];
    struct { int r, t; } reserve;

#line 199 "asm.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ASM_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 216 "asm.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  42
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   105

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  24
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  89

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   268

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      20,    21,    15,    13,    19,    14,     2,    16,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    18,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    22,     2,    23,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    17
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   102,   102,   106,   107,   111,   112,   113,   114,   115,
     116,   120,   121,   125,   134,   150,   166,   192,   207,   221,
     246,   260,   276,   295,   296,   305,   309,   310,   318,   319,
     323,   326,   327,   328,   333,   334,   335,   336,   337,   338,
     344,   345,   346,   351,   355,   370,   387,   389,   393,   396,
     401,   406,   413,   417
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DATA_TYPE", "IDENTIFIER", "OP_CODE",
  "IMM_VALUE", "F_REG", "I_REG", "IMM_FVALUE", "EQU", "ORG", "T_CR", "'+'",
  "'-'", "'*'", "'/'", "NEG", "':'", "','", "'('", "')'", "'['", "']'",
  "$accept", "program", "instructions", "instruction", "labels", "label",
  "instr_asm", "pseudo_code", "mem", "reg", "immediate", "expr", "org",
  "equ", "data", "reservations", "reservation", "reservation_post",
  "reservation_pre", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,    43,    45,    42,    47,   268,    58,    44,
      40,    41,    91,    93
};
# endif

#define YYPACT_NINF -35

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-35)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      92,    -2,     3,    37,    45,    69,   -35,    20,    87,   -35,
      52,   -35,    12,    23,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,    69,     3,    69,   -35,    28,   -35,   -11,   -35,   -35,
       3,    69,    69,   -35,   -35,   -35,    62,    26,    39,    43,
      69,   -35,   -35,   -35,    49,   -35,   -35,    60,   -35,   -35,
     -35,     0,     7,    51,    69,    69,    69,    69,     3,   -35,
     -35,   -35,   -35,    56,     0,    53,    45,    53,   -35,   -35,
       3,   -35,    70,    70,   -35,   -35,   -35,   -35,   -35,   -35,
      65,    43,    58,    73,    62,   -35,   -35,   -35,   -35
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,    20,     0,     9,     0,     0,     4,
       0,    12,     0,     0,    24,    23,    25,    10,    38,    37,
      36,     0,     0,     0,    53,    30,    45,    47,    51,    50,
       0,     0,    42,    13,    29,    28,     0,     0,    18,    19,
       0,    40,     1,     3,     0,     6,    11,     0,     7,     8,
      33,    30,     0,     0,     0,     0,     0,     0,     0,    48,
      44,    43,    41,     0,     0,     0,     0,     0,     5,    39,
       0,    52,    31,    32,    34,    35,    46,    27,    21,    22,
      17,    16,     0,     0,     0,    26,    49,    14,    15
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,   -35,    93,   -35,    71,    90,   -35,    36,   -34,
      -4,   -18,   -35,   -35,   -35,   -24,    83,   -22,   -35
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    11,    12,    13,    37,    38,
      24,    25,    14,    15,    16,    26,    27,    28,    29
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      39,    41,    63,    50,    51,    59,    60,    18,    58,    19,
      17,    23,    20,    54,    55,    56,    57,    21,    64,    53,
      42,    69,    64,    22,    48,    23,    70,    61,    62,    23,
      59,    78,    80,    82,    76,    49,    72,    73,    74,    75,
      30,    54,    55,    56,    57,    65,    83,    31,    32,    18,
      87,    19,    34,    35,    20,    33,    44,     4,    66,    21,
      34,    35,    81,    67,    45,    36,    18,    33,    19,    34,
      35,    20,    68,    18,    71,    19,    21,    77,    20,    85,
      88,    46,    40,    21,    84,    56,    57,    -2,     1,    40,
       2,     3,     4,     1,    86,     2,     3,     4,     5,     6,
      47,    43,    79,     5,     6,    52
};

static const yytype_uint8 yycheck[] =
{
       4,     5,    36,    21,    22,    27,    30,     4,    19,     6,
      12,    22,     9,    13,    14,    15,    16,    14,    36,    23,
       0,    21,    40,    20,    12,    22,    19,    31,    32,    22,
      52,    65,    66,    67,    58,    12,    54,    55,    56,    57,
       3,    13,    14,    15,    16,    19,    70,    10,    11,     4,
      84,     6,     7,     8,     9,    18,     4,     5,    19,    14,
       7,     8,    66,    20,    12,    20,     4,    18,     6,     7,
       8,     9,    12,     4,    23,     6,    14,    21,     9,    21,
      84,    10,    20,    14,    19,    15,    16,     0,     1,    20,
       3,     4,     5,     1,    21,     3,     4,     5,    11,    12,
      10,     8,    66,    11,    12,    22
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,    11,    12,    25,    26,    27,
      28,    29,    30,    31,    36,    37,    38,    12,     4,     6,
       9,    14,    20,    22,    34,    35,    39,    40,    41,    42,
       3,    10,    11,    18,     7,     8,    20,    32,    33,    34,
      20,    34,     0,    27,     4,    12,    29,    30,    12,    12,
      35,    35,    40,    34,    13,    14,    15,    16,    19,    41,
      39,    34,    34,    33,    35,    19,    19,    20,    12,    21,
      19,    23,    35,    35,    35,    35,    39,    21,    33,    32,
      33,    34,    33,    39,    19,    21,    21,    33,    34
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    24,    25,    26,    26,    27,    27,    27,    27,    27,
      27,    28,    28,    29,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    31,    31,    31,    32,    32,    33,    33,
      34,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      36,    36,    36,    37,    38,    38,    39,    39,    40,    40,
      40,    40,    41,    42
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     3,     2,     2,     2,     1,
       2,     2,     1,     2,     6,     6,     4,     4,     2,     2,
       1,     4,     4,     1,     1,     1,     4,     3,     1,     1,
       1,     3,     3,     2,     3,     3,     1,     1,     1,     3,
       2,     3,     2,     3,     3,     2,     3,     1,     2,     5,
       1,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 10:
#line 116 "asm.y" /* yacc.c:1646  */
    {   yyerror_printf( yy_error_txt[ ERRCANTPARSELINE ] );  yyerrok; yyclearin; }
#line 1350 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 125 "asm.y" /* yacc.c:1646  */
    {   
                                Node *node = makeNode( A_LABEL );
                                node->identifier = (yyvsp[-1].text);
                                asm_push_node( node ); 
                              }
#line 1360 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 135 "asm.y" /* yacc.c:1646  */
    { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( (yyvsp[-5].instr)->opname );
                                node->instr = (yyvsp[-5].instr);
                                node->param[0] = (yyvsp[-4].node);
                                node->param[1] = (yyvsp[-2].node);
                                node->param[2] = (yyvsp[0].node);

                                if( (check_error = asm_check_instr_param( node, P_REG_REG_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
#line 1380 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 151 "asm.y" /* yacc.c:1646  */
    { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( (yyvsp[-5].instr)->opname );
                                node->instr = (yyvsp[-5].instr);
                                node->param[0] = (yyvsp[-4].node);
                                node->param[1] = (yyvsp[-2].node);
                                node->param[2] = (yyvsp[0].node);

                                if( (check_error = asm_check_instr_param( node, P_REG_REG_IMM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
#line 1400 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 167 "asm.y" /* yacc.c:1646  */
    { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( (yyvsp[-3].instr)->opname );
                                node->instr = (yyvsp[-3].instr);
                                node->param[1] = (yyvsp[-2].node);
                                if( (yyvsp[-3].instr)->type == BRANCH ) {
                                  node->param[2] = makeNode( A_OPSUB );
                                  node->param[2]->param[0] = (yyvsp[0].node);
                                  node->param[2]->param[1] = makeNode( A_OPADD );
                                  node->param[2]->param[1]->param[0] = makeNode( A_IDENT );
                                  node->param[2]->param[1]->param[0]->identifier = strdup("%OFFSET");
                                  node->param[2]->param[1]->param[1] = makeNode( A_VALUE );
                                  node->param[2]->param[1]->param[1]->value = 4;                                  
                                }
                                else
                                  node->param[2] = (yyvsp[0].node);


                                if( (check_error = asm_check_instr_param( node, P_REG_IMM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
#line 1430 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 193 "asm.y" /* yacc.c:1646  */
    { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( (yyvsp[-3].instr)->opname );
                                node->instr = (yyvsp[-3].instr);
                                node->param[1] = (yyvsp[-2].node);
                                node->param[2] = (yyvsp[0].node);

                                if( (check_error = asm_check_instr_param( node, P_REG_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
#line 1449 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 208 "asm.y" /* yacc.c:1646  */
    { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( (yyvsp[-1].instr)->opname );
                                node->instr = (yyvsp[-1].instr);
                                node->param[1] = (yyvsp[0].node);

                                if( (check_error = asm_check_instr_param( node, P_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
#line 1467 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 222 "asm.y" /* yacc.c:1646  */
    { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( (yyvsp[-1].instr)->opname );
                                node->instr = (yyvsp[-1].instr);

                                if( (yyvsp[-1].instr)->type == BRANCH ) {
                                  node->param[2] = makeNode( A_OPSUB );
                                  node->param[2]->param[0] = (yyvsp[0].node);
                                  node->param[2]->param[1] = makeNode( A_OPADD );
                                  node->param[2]->param[1]->param[0] = makeNode( A_IDENT );
                                  node->param[2]->param[1]->param[0]->identifier = strdup("%OFFSET");
                                  node->param[2]->param[1]->param[1] = makeNode( A_VALUE );
                                  node->param[2]->param[1]->param[1]->value = 4;                                  
                                }
                                else
                                  node->param[2] = (yyvsp[0].node);

                                if( (check_error = asm_check_instr_param( node, P_IMM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
#line 1496 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 247 "asm.y" /* yacc.c:1646  */
    { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( (yyvsp[0].instr)->opname );
                                node->instr = (yyvsp[0].instr);

                                if( (check_error = asm_check_instr_param( node, P_NONE )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
#line 1513 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 261 "asm.y" /* yacc.c:1646  */
    { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( (yyvsp[-3].instr)->opname );
                                node->instr = (yyvsp[-3].instr);
                                node->param[0] = (yyvsp[0].node);
                                node->param[1] = (yyvsp[-2].params)[0];
                                node->param[2] = (yyvsp[-2].params)[1];

                                if( (check_error = asm_check_instr_param( node, P_MEM_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
#line 1533 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 277 "asm.y" /* yacc.c:1646  */
    { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( (yyvsp[-3].instr)->opname );
                                node->instr = (yyvsp[-3].instr);
                                node->param[0] = (yyvsp[-2].node);
                                node->param[1] = (yyvsp[0].params)[0];
                                node->param[2] = (yyvsp[0].params)[1];

                                if( (check_error = asm_check_instr_param( node, P_REG_MEM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
#line 1553 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 295 "asm.y" /* yacc.c:1646  */
    { asm_push_node( (yyvsp[0].node) ); }
#line 1559 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 296 "asm.y" /* yacc.c:1646  */
    { 
        if( strcasecmp( (yyvsp[0].node)->identifier, "data" ) == 0 ||
            strcasecmp( (yyvsp[0].node)->identifier, "code" ) == 0 )
          asm_push_node( (yyvsp[0].node) );
        else {
          yyerror_printf( yy_error_txt[ ERRINVALIDORG ], (yyvsp[0].node)->identifier );
          asm_delete_tree( (yyvsp[0].node) );
        }
    }
#line 1573 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 305 "asm.y" /* yacc.c:1646  */
    { asm_push_node( (yyvsp[0].node) ); }
#line 1579 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 309 "asm.y" /* yacc.c:1646  */
    { (yyval.params)[0] = (yyvsp[-1].node); (yyval.params)[1] = (yyvsp[-3].node);  }
#line 1585 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 310 "asm.y" /* yacc.c:1646  */
    {   
                              (yyval.params)[0] = (yyvsp[-1].node);
                              (yyval.params)[1] = makeNode( A_VALUE );
                              (yyval.params)[1]->value = 0;
                            }
#line 1595 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 318 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_RREG ); (yyval.node)->value = (yyvsp[0].value); }
#line 1601 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 319 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_FREG ); (yyval.node)->value = (yyvsp[0].value); }
#line 1607 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 326 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_OPADD ); (yyval.node)->param[0] = (yyvsp[-2].node); (yyval.node)->param[1] = (yyvsp[0].node); }
#line 1613 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 327 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_OPSUB ); (yyval.node)->param[0] = (yyvsp[-2].node); (yyval.node)->param[1] = (yyvsp[0].node); }
#line 1619 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 328 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_OPSUB );
                            (yyval.node)->param[0] = makeNode( A_VALUE );
                            (yyval.node)->param[0]->value = 0;
                            (yyval.node)->param[1] = (yyvsp[0].node); 
                          }
#line 1629 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 333 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_OPMUL );  (yyval.node)->param[0] = (yyvsp[-2].node); (yyval.node)->param[1] = (yyvsp[0].node); }
#line 1635 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 334 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_OPDIV );  (yyval.node)->param[0] = (yyvsp[-2].node); (yyval.node)->param[1] = (yyvsp[0].node); }
#line 1641 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 335 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_FVALUE ); (yyval.node)->fvalue = (yyvsp[0].fvalue); }
#line 1647 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 336 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_VALUE );  (yyval.node)->value = (yyvsp[0].value); }
#line 1653 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 337 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_IDENT );  (yyval.node)->identifier = (yyvsp[0].text); }
#line 1659 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 338 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1665 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 344 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_CMDORG ); (yyval.node)->identifier = strdup("code"); (yyval.node)->param[0] = (yyvsp[0].node);  }
#line 1671 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 345 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_CMDORG ); (yyval.node)->identifier = strdup((yyvsp[-2].text));   (yyval.node)->param[0] = (yyvsp[0].node);  }
#line 1677 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 346 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_CMDORG ); (yyval.node)->identifier = strdup((yyvsp[-1].text));   
                                  (yyval.node)->param[0] = makeNode( A_VALUE ); (yyval.node)->param[0]->value = 0;  }
#line 1684 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 351 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_CMDEQU ); (yyval.node)->identifier = strdup((yyvsp[-2].text));   (yyval.node)->param[0] = (yyvsp[0].node);  }
#line 1690 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 355 "asm.y" /* yacc.c:1646  */
    {  int id_length = asm_data_type_length( (yyvsp[-1].text) );
                                         if( id_length > 0 ) {
                                           (yyval.node) = makeNode( A_CMDDATA );  
                                           (yyval.node)->identifier = (yyvsp[-2].text);
                                           (yyval.node)->param[0] = (yyvsp[0].node); 
                                           (yyval.node)->param[1] = makeNode( A_VALUE );
                                           (yyval.node)->param[1]->value = asm_data_type_length( (yyvsp[-1].text) );
                                           (yyval.node)->param[1]->identifier = strdup( (yyvsp[-1].text) );
                                         }
                                         else {
                                           (yyval.node) = NULL;
                                           yyerror_printf( yy_error_txt[ ERRINVALIDIDENTIFIER ], (yyvsp[-1].text) );
                                         }
                                       }
#line 1709 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 370 "asm.y" /* yacc.c:1646  */
    {  int id_length = asm_data_type_length( (yyvsp[-1].text) );
                                         if( id_length > 0 ) {
                                           (yyval.node) = makeNode( A_CMDDATA );  
                                           (yyval.node)->identifier = NULL;
                                           (yyval.node)->param[0] = (yyvsp[0].node); 
                                           (yyval.node)->param[1] = makeNode( A_VALUE );
                                           (yyval.node)->param[1]->value = asm_data_type_length( (yyvsp[-1].text) );
                                           (yyval.node)->param[1]->identifier = strdup( (yyvsp[-1].text) );
                                         }
                                         else {
                                           (yyval.node) = NULL;
                                           yyerror_printf( yy_error_txt[ ERRINVALIDIDENTIFIER ], (yyvsp[-1].text) );
                                         }
                                       }
#line 1728 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 387 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-2].node);
                                         (yyval.node)->param[2] = (yyvsp[0].node); }
#line 1735 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 389 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1741 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 393 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_CMDRES ); 
                                              (yyval.node)->param[0] = (yyvsp[-1].node);
                                              (yyval.node)->param[1] = (yyvsp[0].node);   }
#line 1749 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 396 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_CMDRES );
                                              (yyval.node)->param[0] = (yyvsp[-3].node);
                                              (yyval.node)->param[1] = makeNode( A_VALUE );
                                              (yyval.node)->param[1]->value = 1;
                                              (yyval.node)->param[2] = (yyvsp[-1].node);  }
#line 1759 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 401 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_CMDRES );  
                                              (yyval.node)->param[0] = (yyvsp[0].node); 
                                              (yyval.node)->param[1] = makeNode( A_VALUE );
                                              (yyval.node)->param[1]->value = 1;
                                            }
#line 1769 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 406 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = makeNode( A_CMDRES );  
                                              (yyval.node)->param[1] = (yyvsp[0].node); 
                                              (yyval.node)->param[0] = makeNode( A_VALUE );
                                              (yyval.node)->param[0]->value = 0; }
#line 1778 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 413 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1784 "asm.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 417 "asm.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1790 "asm.tab.c" /* yacc.c:1646  */
    break;


#line 1794 "asm.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 420 "asm.y" /* yacc.c:1906  */




void asm_parse_file( FILE *f ) {
  yyin = f;
  yylineno = 0;
  yyparse();
}



int yyerror_printf2( const char *s, int lineno, ... ) {
  va_list ap;
  va_start(ap, lineno );
  printf("Error at line %d: ", lineno );
  vprintf( s, ap );
  va_end( ap );

  printf("\n");
  return 0;
}

int yyerror_printf( const char *s, ... ) {
  va_list ap;
  va_start(ap, s);
  printf("Error at line %d: ", yylineno );
  vprintf( s, ap );
  va_end( ap );

  printf("\n");
  return 0;
}

int yyerror( const char *s) {
}



void asm_print_tree( Node *n ) {
  while( n ) {
    switch( n->type ) {
    case A_CMDRES:  printf("{");
                    asm_print_tree( n->param[0] );
                    if( n->param[1] ) {
                      printf("[");
                      asm_print_tree( n->param[1] );
                      printf("]");
                    }
                    printf("}");
                    if( n->param[2] ) {
                      printf(",");
                      asm_print_tree( n->param[2] );
                    }
                    break;
    case A_CMDDATA: printf("<%s>:", n->identifier );
                    asm_print_tree( n->param[0] );
                    printf("\n");
                    break; 

    case A_CMDEQU: if( n->identifier != NULL ) printf("%s", n->identifier );
                   printf(" equ ");
                   asm_print_tree( n->param[0] );
                   printf("\n");
                   break;
    case A_CMDORG: if( n->identifier != NULL ) printf("%s", n->identifier );
                   printf(" org ");
                   asm_print_tree( n->param[0] );
                   printf("\n");
                   break;
    case A_OPADD:  printf("(");
                   asm_print_tree( n->param[0] );
                   printf("+");
                   asm_print_tree( n->param[1] );
                   printf(")");
                   break;
    case A_OPSUB:  printf("(");
                   asm_print_tree( n->param[0] );
                   printf("-");
                   asm_print_tree( n->param[1] );
                   printf(")");
                   break;
    case A_OPMUL:  printf("(");
                   asm_print_tree( n->param[0] );
                   printf("*");
                   asm_print_tree( n->param[1] );
                   printf(")");
                   break;
    case A_OPDIV:  printf("(");
                   asm_print_tree( n->param[0] );
                   printf("/");
                   asm_print_tree( n->param[1] );
                   printf(")");
                   break;
    case A_LABEL:  printf("%s:\n", n->identifier ); break;
    case A_RREG:   printf("R%d", (int)n->value );      break;
    case A_FREG:   printf("F%d", (int)n->value );      break;
    case A_FVALUE: printf("(%f)", n->fvalue );      
                   if( n->next != NULL ) 
                     printf(",");
                   break;
    case A_VALUE:  printf("%ld", n->value );      
                   if( n->next != NULL ) 
                     printf(",");
                   break;
    case A_IDENT:  printf("<%s>", n->identifier );  break;
    case A_INSTR:  printf("%s ", n->identifier ); 
                   asm_print_tree( n->param[0] );
                   printf(" ");
                   asm_print_tree( n->param[1] );
                   printf(" ");
                   asm_print_tree( n->param[2] );
                   printf("\n");
                   break;
    default: printf("print-tree: Unknown\n");
    }
    n = n->next;
  }
}


Node *makeNode( asm_node_type type ) {
  Node *n = (Node*)malloc( sizeof( Node ) );
  n->identifier = NULL;
  n->type = type;
  n->next = NULL;
  n->param[0] = NULL;
  n->param[1] = NULL;
  n->param[2] = NULL;
  n->line_no = yylineno;
  return n;
}

int asm_check_instr_param( Node *node, int check ) {
  if( node->type == A_INSTR ) {
    
    switch( node->instr->type ) {
    case REG: 
      if( check != P_REG_REG_REG ) 
        return OPNEEDREGREGPARAM;

      if( node->instr->reg_type != INSTR_FP &&
          ( node->param[0]->type != A_RREG ||
            node->param[1]->type != A_RREG ||
            node->param[2]->type != A_RREG ))
        return OPNEEDSPREGPARAM;

      if( node->instr->reg_type == INSTR_FP &&
          ( node->param[0]->type != A_FREG ||
            node->param[1]->type != A_FREG ||
            node->param[2]->type != A_FREG ))
        return OPNEEDFPREGPARAM;

      return OPOK;
      



    case STORE:
      if( check != P_MEM_REG ) 
        return OPNEEDREGIMMPARAM;

      if( node->param[1]->type != A_RREG )
        return OPNEEDSPREGPARAM;

      if( node->instr->reg_type != INSTR_FP &&
          ( node->param[0]->type != A_RREG ))
        return OPNEEDSPREGPARAM;

      if( node->instr->reg_type == INSTR_FP &&
          node->param[0]->type != A_FREG )
        return OPNEEDFPREGPARAM;
      return OPOK;



    case LOAD:
      if( check != P_REG_MEM ) 
        return OPNEEDREGIMMPARAM;

      if( node->param[1]->type != A_RREG )
        return OPNEEDSPREGPARAM;

      if( node->instr->reg_type != INSTR_FP &&
          ( node->param[0]->type != A_RREG ))
        return OPNEEDSPREGPARAM;

      if( node->instr->reg_type == INSTR_FP &&
          node->param[0]->type != A_FREG )
        return OPNEEDFPREGPARAM;

      return OPOK;



    case IMM:
      if( check != P_REG_REG_IMM ) 
        return OPNEEDREGIMMPARAM;

      if( node->instr->reg_type != INSTR_FP &&
          ( node->param[0]->type != A_RREG ||
            node->param[1]->type != A_RREG ))
        return OPNEEDSPREGPARAM;

      if( node->instr->reg_type == INSTR_FP &&
          ( node->param[0]->type != A_FREG ||
            node->param[1]->type != A_FREG ))
        return OPNEEDFPREGPARAM;

      return OPOK;

    case NONE:
      if( check != P_NONE )  
        return OPNEEDNOPARAM;
      return OPOK;

    case BRANCH:
      if( node->instr->property == 0 ) {
        if( check != P_NONE )  
          return OPNEEDNOPARAM;
        return OPOK;
      }

      if( node->instr->property == NAME ) {
        if( check != P_IMM )
          return OPNEEDIMMPARAM;
        return OPOK;
      }

      if( node->instr->property == RS1 ) {
        if( check != P_REG )
          return OPNEEDREGPARAM;
        if( node->param[1]->type != A_RREG )
          return OPNEEDSPREGPARAM;
        return OPOK;
      }

      if( node->instr->property == (RS1 | NAME) ) {
        if( check != P_REG_IMM )
          return OPNEEDREGIMMPARAM;
        if( node->param[1]->type != A_RREG )
          return OPNEEDSPREGPARAM;
        return OPOK;
      }

    case MOVE:    break;

    case SPECIAL: 
      if( node->instr->property == NAME ) {
        if( check != P_IMM )
          return OPNEEDIMMPARAM;
        return OPOK;
      }
      break;
      
    }


  }
  
  return OPUNDEFINE;
}

int asm_data_type_length( const char *name ) {
  if( *name == '_' || *name == '.' ) name++;

  if( strcasecmp( name, "byte" ) == 0 )  return 1;
  if( strcasecmp( name, "short" ) == 0 ) return 2;
  if( strcasecmp( name, "word" ) == 0 )  return 4;
  if( strcasecmp( name, "int" ) == 0 )   return 4;
  if( strcasecmp( name, "dword" ) == 0 ) return 8;
  if( strcasecmp( name, "long" ) == 0 )  return 8;

  if( strcasecmp( name, "float" ) == 0 ) return 4;
  if( strcasecmp( name, "double" ) == 0 ) return 8;

  return -1;
}

int asm_data_type_fixnum( const char *name ) {
  if( *name == '_' || *name == '.' ) name++;

  if( strcasecmp( name, "byte" ) == 0 )  return 1;
  if( strcasecmp( name, "short" ) == 0 ) return 2;
  if( strcasecmp( name, "word" ) == 0 )  return 4;
  if( strcasecmp( name, "int" ) == 0 )   return 4;
  if( strcasecmp( name, "dword" ) == 0 ) return 8;
  if( strcasecmp( name, "long" ) == 0 )  return 8;

  if( strcasecmp( name, "float" ) == 0 ) return 0;
  if( strcasecmp( name, "double" ) == 0 ) return 0;

  return -1;
}

int asm_data_type_flonum( const char *name ) {
  if( *name == '_' || *name == '.' ) name++;

  if( strcasecmp( name, "byte" ) == 0 )  return 0;
  if( strcasecmp( name, "short" ) == 0 ) return 0;
  if( strcasecmp( name, "word" ) == 0 )  return 0;
  if( strcasecmp( name, "int" ) == 0 )   return 0;
  if( strcasecmp( name, "dword" ) == 0 ) return 0;
  if( strcasecmp( name, "long" ) == 0 )  return 0;

  if( strcasecmp( name, "float" ) == 0 ) return 4;
  if( strcasecmp( name, "double" ) == 0 ) return 8;

  return -1;
}

