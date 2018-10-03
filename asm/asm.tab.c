
/*  A Bison parser, made from asm.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define	DATA_TYPE	257
#define	IDENTIFIER	258
#define	OP_CODE	259
#define	IMM_VALUE	260
#define	F_REG	261
#define	I_REG	262
#define	IMM_FVALUE	263
#define	EQU	264
#define	ORG	265
#define	T_CR	266
#define	NEG	267

#line 1 "asm.y"

 
#include <stdio.h>
#include <stdarg.h> 
#include <string.h>
#include <stdlib.h>
#include "asm/asm.h"
#include "lib/dlxinstset.h"

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


#line 71 "asm.y"
typedef union
{
    double fvalue;
    long value;
    char *text;
    const dlx_instr_entry *instr;
    struct Node *node;
    struct Node *params[3];
    struct { int r, t; } reserve;
} YYSTYPE;
#ifndef YYDEBUG
#define YYDEBUG 1
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		89
#define	YYFLAG		-32768
#define	YYNTBASE	24

#define YYTRANSLATE(x) ((unsigned)(x) <= 267 ? yytranslate[x] : 42)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    20,
    21,    15,    13,    19,    14,     2,    16,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    18,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    22,     2,    23,     2,     2,     2,     2,     2,     2,     2,
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
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    17
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     7,    11,    14,    17,    20,    22,    25,
    28,    30,    33,    40,    47,    52,    57,    60,    63,    65,
    70,    75,    77,    79,    81,    86,    90,    92,    94,    96,
   100,   104,   107,   111,   115,   117,   119,   121,   125,   128,
   132,   135,   139,   143,   146,   150,   152,   155,   161,   163,
   165,   169
};

static const short yyrhs[] = {    25,
     0,    25,    26,     0,    26,     0,    27,    29,    12,     0,
    27,    12,     0,    29,    12,     0,    30,    12,     0,    12,
     0,     1,    12,     0,    27,    28,     0,    28,     0,     4,
    18,     0,     5,    32,    19,    32,    19,    32,     0,     5,
    32,    19,    32,    19,    33,     0,     5,    32,    19,    33,
     0,     5,    32,    19,    32,     0,     5,    32,     0,     5,
    33,     0,     5,     0,     5,    31,    19,    32,     0,     5,
    32,    19,    31,     0,    36,     0,    35,     0,    37,     0,
    33,    20,    32,    21,     0,    20,    32,    21,     0,     8,
     0,     7,     0,    34,     0,    34,    13,    34,     0,    34,
    14,    34,     0,    14,    34,     0,    34,    15,    34,     0,
    34,    16,    34,     0,     9,     0,     6,     0,     4,     0,
    20,    34,    21,     0,    11,    33,     0,     4,    11,    33,
     0,     4,    11,     0,     4,    10,    33,     0,     4,     3,
    38,     0,     3,    38,     0,    39,    19,    38,     0,    39,
     0,    39,    40,     0,    20,    39,    19,    38,    21,     0,
    41,     0,    40,     0,    22,    33,    23,     0,    33,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   101,   105,   107,   110,   112,   113,   114,   115,   116,   119,
   121,   124,   133,   150,   166,   192,   207,   221,   246,   260,
   276,   294,   296,   305,   308,   310,   317,   319,   322,   326,
   327,   328,   333,   334,   335,   336,   337,   338,   343,   345,
   346,   350,   354,   369,   386,   389,   392,   396,   401,   406,
   412,   416
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","DATA_TYPE",
"IDENTIFIER","OP_CODE","IMM_VALUE","F_REG","I_REG","IMM_FVALUE","EQU","ORG",
"T_CR","'+'","'-'","'*'","'/'","NEG","':'","','","'('","')'","'['","']'","program",
"instructions","instruction","labels","label","instr_asm","pseudo_code","mem",
"reg","immediate","expr","org","equ","data","reservations","reservation","reservation_post",
"reservation_pre", NULL
};
#endif

static const short yyr1[] = {     0,
    24,    25,    25,    26,    26,    26,    26,    26,    26,    27,
    27,    28,    29,    29,    29,    29,    29,    29,    29,    29,
    29,    30,    30,    30,    31,    31,    32,    32,    33,    34,
    34,    34,    34,    34,    34,    34,    34,    34,    35,    35,
    35,    36,    37,    37,    38,    38,    39,    39,    39,    39,
    40,    41
};

static const short yyr2[] = {     0,
     1,     2,     1,     3,     2,     2,     2,     1,     2,     2,
     1,     2,     6,     6,     4,     4,     2,     2,     1,     4,
     4,     1,     1,     1,     4,     3,     1,     1,     1,     3,
     3,     2,     3,     3,     1,     1,     1,     3,     2,     3,
     2,     3,     3,     2,     3,     1,     2,     5,     1,     1,
     3,     1
};

static const short yydefact[] = {     0,
     0,     0,     0,    19,     0,     8,     0,     3,     0,    11,
     0,     0,    23,    22,    24,     9,    37,    36,    35,     0,
     0,     0,    52,    29,    44,    46,    50,    49,     0,     0,
    41,    12,    28,    27,     0,     0,    17,    18,     0,    39,
     2,     0,     5,    10,     0,     6,     7,    32,    29,     0,
     0,     0,     0,     0,     0,     0,    47,    43,    42,    40,
     0,     0,     0,     0,     0,     4,    38,     0,    51,    30,
    31,    33,    34,    45,    26,    20,    21,    16,    15,     0,
     0,     0,    25,    48,    13,    14,     0,     0,     0
};

static const short yydefgoto[] = {    87,
     7,     8,     9,    10,    11,    12,    36,    37,    23,    24,
    13,    14,    15,    25,    26,    27,    28
};

static const short yypact[] = {    85,
    -9,    37,    64,     8,    38,-32768,    80,-32768,    50,-32768,
     1,    13,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    38,
    37,    38,-32768,    -6,-32768,     2,-32768,-32768,    37,    38,
    38,-32768,-32768,-32768,    57,    10,    15,     0,    38,-32768,
-32768,    22,-32768,-32768,    36,-32768,-32768,-32768,    86,    31,
    33,    38,    38,    38,    38,    37,-32768,-32768,-32768,-32768,
    49,    86,    61,     8,    61,-32768,-32768,    37,-32768,    78,
    78,-32768,-32768,-32768,-32768,-32768,-32768,    53,     0,    52,
    55,    57,-32768,-32768,-32768,-32768,    79,    87,-32768
};

static const short yypgoto[] = {-32768,
-32768,    88,-32768,    89,    94,-32768,    40,   -33,    -4,   -16,
-32768,-32768,-32768,   -23,    84,   -15,-32768
};


#define	YYLAST		107


static const short yytable[] = {    38,
    40,    61,    16,    48,    49,    58,    52,    53,    54,    55,
    57,    17,    46,    18,    33,    34,    19,    51,    62,    65,
    56,    20,    62,    22,    47,    59,    60,    35,    63,    76,
    78,    80,    74,    64,    57,    70,    71,    72,    73,    32,
    17,    17,    18,    18,    81,    19,    19,    66,    85,    68,
    20,    20,    22,    42,     4,    69,    21,    39,    22,    79,
    17,    43,    18,    33,    34,    19,    29,    33,    34,    75,
    20,    82,    83,    30,    31,    84,    39,    86,    88,    -1,
     1,    32,     2,     3,     4,     1,    89,     2,     3,     4,
     5,     6,    54,    55,    41,     5,     6,    44,    52,    53,
    54,    55,    45,    77,    50,     0,    67
};

static const short yycheck[] = {     4,
     5,    35,    12,    20,    21,    29,    13,    14,    15,    16,
    26,     4,    12,     6,     7,     8,     9,    22,    35,    20,
    19,    14,    39,    22,    12,    30,    31,    20,    19,    63,
    64,    65,    56,    19,    50,    52,    53,    54,    55,    18,
     4,     4,     6,     6,    68,     9,     9,    12,    82,    19,
    14,    14,    22,     4,     5,    23,    20,    20,    22,    64,
     4,    12,     6,     7,     8,     9,     3,     7,     8,    21,
    14,    19,    21,    10,    11,    21,    20,    82,     0,     0,
     1,    18,     3,     4,     5,     1,     0,     3,     4,     5,
    11,    12,    15,    16,     7,    11,    12,     9,    13,    14,
    15,    16,     9,    64,    21,    -1,    21
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/lib/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/lib/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 9:
#line 116 "asm.y"
{   yyerror_printf( yy_error_txt[ ERRCANTPARSELINE ] );  yyerrok; yyclearin; ;
    break;}
case 12:
#line 125 "asm.y"
{   
                                Node *node = makeNode( A_LABEL );
                                node->identifier = yyvsp[-1].text;
                                asm_push_node( node ); 
                              ;
    break;}
case 13:
#line 135 "asm.y"
{ int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( yyvsp[-5].instr->opname );
                                node->instr = yyvsp[-5].instr;
                                node->param[0] = yyvsp[-4].node;
                                node->param[1] = yyvsp[-2].node;
                                node->param[2] = yyvsp[0].node;

                                if( (check_error = asm_check_instr_param( node, P_REG_REG_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              ;
    break;}
case 14:
#line 151 "asm.y"
{ int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( yyvsp[-5].instr->opname );
                                node->instr = yyvsp[-5].instr;
                                node->param[0] = yyvsp[-4].node;
                                node->param[1] = yyvsp[-2].node;
                                node->param[2] = yyvsp[0].node;

                                if( (check_error = asm_check_instr_param( node, P_REG_REG_IMM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              ;
    break;}
case 15:
#line 167 "asm.y"
{ int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( yyvsp[-3].instr->opname );
                                node->instr = yyvsp[-3].instr;
                                node->param[1] = yyvsp[-2].node;
                                if( yyvsp[-3].instr->type == BRANCH ) {
                                  node->param[2] = makeNode( A_OPSUB );
                                  node->param[2]->param[0] = yyvsp[0].node;
                                  node->param[2]->param[1] = makeNode( A_OPADD );
                                  node->param[2]->param[1]->param[0] = makeNode( A_IDENT );
                                  node->param[2]->param[1]->param[0]->identifier = strdup("%OFFSET");
                                  node->param[2]->param[1]->param[1] = makeNode( A_VALUE );
                                  node->param[2]->param[1]->param[1]->value = 4;                                  
                                }
                                else
                                  node->param[2] = yyvsp[0].node;


                                if( (check_error = asm_check_instr_param( node, P_REG_IMM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              ;
    break;}
case 16:
#line 193 "asm.y"
{ int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( yyvsp[-3].instr->opname );
                                node->instr = yyvsp[-3].instr;
                                node->param[1] = yyvsp[-2].node;
                                node->param[2] = yyvsp[0].node;

                                if( (check_error = asm_check_instr_param( node, P_REG_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              ;
    break;}
case 17:
#line 208 "asm.y"
{ int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( yyvsp[-1].instr->opname );
                                node->instr = yyvsp[-1].instr;
                                node->param[1] = yyvsp[0].node;

                                if( (check_error = asm_check_instr_param( node, P_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              ;
    break;}
case 18:
#line 222 "asm.y"
{ int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( yyvsp[-1].instr->opname );
                                node->instr = yyvsp[-1].instr;

                                if( yyvsp[-1].instr->type == BRANCH ) {
                                  node->param[2] = makeNode( A_OPSUB );
                                  node->param[2]->param[0] = yyvsp[0].node;
                                  node->param[2]->param[1] = makeNode( A_OPADD );
                                  node->param[2]->param[1]->param[0] = makeNode( A_IDENT );
                                  node->param[2]->param[1]->param[0]->identifier = strdup("%OFFSET");
                                  node->param[2]->param[1]->param[1] = makeNode( A_VALUE );
                                  node->param[2]->param[1]->param[1]->value = 4;                                  
                                }
                                else
                                  node->param[2] = yyvsp[0].node;

                                if( (check_error = asm_check_instr_param( node, P_IMM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              ;
    break;}
case 19:
#line 247 "asm.y"
{ int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( yyvsp[0].instr->opname );
                                node->instr = yyvsp[0].instr;

                                if( (check_error = asm_check_instr_param( node, P_NONE )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              ;
    break;}
case 20:
#line 261 "asm.y"
{ int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( yyvsp[-3].instr->opname );
                                node->instr = yyvsp[-3].instr;
                                node->param[0] = yyvsp[0].node;
                                node->param[1] = yyvsp[-2].params[0];
                                node->param[2] = yyvsp[-2].params[1];

                                if( (check_error = asm_check_instr_param( node, P_MEM_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              ;
    break;}
case 21:
#line 277 "asm.y"
{ int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( yyvsp[-3].instr->opname );
                                node->instr = yyvsp[-3].instr;
                                node->param[0] = yyvsp[-2].node;
                                node->param[1] = yyvsp[0].params[0];
                                node->param[2] = yyvsp[0].params[1];

                                if( (check_error = asm_check_instr_param( node, P_REG_MEM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              ;
    break;}
case 22:
#line 295 "asm.y"
{ asm_push_node( yyvsp[0].node ); ;
    break;}
case 23:
#line 296 "asm.y"
{ 
        if( strcasecmp( yyvsp[0].node->identifier, "data" ) == 0 ||
            strcasecmp( yyvsp[0].node->identifier, "code" ) == 0 )
          asm_push_node( yyvsp[0].node );
        else {
          yyerror_printf( yy_error_txt[ ERRINVALIDORG ], yyvsp[0].node->identifier );
          asm_delete_tree( yyvsp[0].node );
        }
    ;
    break;}
case 24:
#line 305 "asm.y"
{ asm_push_node( yyvsp[0].node ); ;
    break;}
case 25:
#line 309 "asm.y"
{ yyval.params[0] = yyvsp[-1].node; yyval.params[1] = yyvsp[-3].node;  ;
    break;}
case 26:
#line 310 "asm.y"
{   
                              yyval.params[0] = yyvsp[-1].node;
                              yyval.params[1] = makeNode( A_VALUE );
                              yyval.params[1]->value = 0;
                            ;
    break;}
case 27:
#line 318 "asm.y"
{ yyval.node = makeNode( A_RREG ); yyval.node->value = yyvsp[0].value; ;
    break;}
case 28:
#line 319 "asm.y"
{ yyval.node = makeNode( A_FREG ); yyval.node->value = yyvsp[0].value; ;
    break;}
case 30:
#line 326 "asm.y"
{ yyval.node = makeNode( A_OPADD ); yyval.node->param[0] = yyvsp[-2].node; yyval.node->param[1] = yyvsp[0].node; ;
    break;}
case 31:
#line 327 "asm.y"
{ yyval.node = makeNode( A_OPSUB ); yyval.node->param[0] = yyvsp[-2].node; yyval.node->param[1] = yyvsp[0].node; ;
    break;}
case 32:
#line 328 "asm.y"
{ yyval.node = makeNode( A_OPSUB );
                            yyval.node->param[0] = makeNode( A_VALUE );
                            yyval.node->param[0]->value = 0;
                            yyval.node->param[1] = yyvsp[0].node; 
                          ;
    break;}
case 33:
#line 333 "asm.y"
{ yyval.node = makeNode( A_OPMUL );  yyval.node->param[0] = yyvsp[-2].node; yyval.node->param[1] = yyvsp[0].node; ;
    break;}
case 34:
#line 334 "asm.y"
{ yyval.node = makeNode( A_OPDIV );  yyval.node->param[0] = yyvsp[-2].node; yyval.node->param[1] = yyvsp[0].node; ;
    break;}
case 35:
#line 335 "asm.y"
{ yyval.node = makeNode( A_FVALUE ); yyval.node->fvalue = yyvsp[0].fvalue; ;
    break;}
case 36:
#line 336 "asm.y"
{ yyval.node = makeNode( A_VALUE );  yyval.node->value = yyvsp[0].value; ;
    break;}
case 37:
#line 337 "asm.y"
{ yyval.node = makeNode( A_IDENT );  yyval.node->identifier = yyvsp[0].text; ;
    break;}
case 38:
#line 338 "asm.y"
{ yyval.node = yyvsp[-1].node; ;
    break;}
case 39:
#line 344 "asm.y"
{ yyval.node = makeNode( A_CMDORG ); yyval.node->identifier = strdup("code"); yyval.node->param[0] = yyvsp[0].node;  ;
    break;}
case 40:
#line 345 "asm.y"
{ yyval.node = makeNode( A_CMDORG ); yyval.node->identifier = strdup(yyvsp[-2].text);   yyval.node->param[0] = yyvsp[0].node;  ;
    break;}
case 41:
#line 346 "asm.y"
{ yyval.node = makeNode( A_CMDORG ); yyval.node->identifier = strdup(yyvsp[-1].text);   
                                  yyval.node->param[0] = makeNode( A_VALUE ); yyval.node->param[0]->value = 0;  ;
    break;}
case 42:
#line 351 "asm.y"
{ yyval.node = makeNode( A_CMDEQU ); yyval.node->identifier = strdup(yyvsp[-2].text);   yyval.node->param[0] = yyvsp[0].node;  ;
    break;}
case 43:
#line 355 "asm.y"
{  int id_length = asm_data_type_length( yyvsp[-1].text );
                                         if( id_length > 0 ) {
                                           yyval.node = makeNode( A_CMDDATA );  
                                           yyval.node->identifier = yyvsp[-2].text;
                                           yyval.node->param[0] = yyvsp[0].node; 
                                           yyval.node->param[1] = makeNode( A_VALUE );
                                           yyval.node->param[1]->value = asm_data_type_length( yyvsp[-1].text );
                                           yyval.node->param[1]->identifier = strdup( yyvsp[-1].text );
                                         }
                                         else {
                                           yyval.node = NULL;
                                           yyerror_printf( yy_error_txt[ ERRINVALIDIDENTIFIER ], yyvsp[-1].text );
                                         }
                                       ;
    break;}
case 44:
#line 370 "asm.y"
{  int id_length = asm_data_type_length( yyvsp[-1].text );
                                         if( id_length > 0 ) {
                                           yyval.node = makeNode( A_CMDDATA );  
                                           yyval.node->identifier = NULL;
                                           yyval.node->param[0] = yyvsp[0].node; 
                                           yyval.node->param[1] = makeNode( A_VALUE );
                                           yyval.node->param[1]->value = asm_data_type_length( yyvsp[-1].text );
                                           yyval.node->param[1]->identifier = strdup( yyvsp[-1].text );
                                         }
                                         else {
                                           yyval.node = NULL;
                                           yyerror_printf( yy_error_txt[ ERRINVALIDIDENTIFIER ], yyvsp[-1].text );
                                         }
                                       ;
    break;}
case 45:
#line 387 "asm.y"
{ yyval.node = yyvsp[-2].node;
                                         yyval.node->param[2] = yyvsp[0].node; ;
    break;}
case 46:
#line 389 "asm.y"
{ yyval.node = yyvsp[0].node; ;
    break;}
case 47:
#line 393 "asm.y"
{ yyval.node = makeNode( A_CMDRES ); 
                                              yyval.node->param[0] = yyvsp[-1].node;
                                              yyval.node->param[1] = yyvsp[0].node;   ;
    break;}
case 48:
#line 396 "asm.y"
{ yyval.node = makeNode( A_CMDRES );
                                              yyval.node->param[0] = yyvsp[-3].node;
                                              yyval.node->param[1] = makeNode( A_VALUE );
                                              yyval.node->param[1]->value = 1;
                                              yyval.node->param[2] = yyvsp[-1].node;  ;
    break;}
case 49:
#line 401 "asm.y"
{ yyval.node = makeNode( A_CMDRES );  
                                              yyval.node->param[0] = yyvsp[0].node; 
                                              yyval.node->param[1] = makeNode( A_VALUE );
                                              yyval.node->param[1]->value = 1;
                                            ;
    break;}
case 50:
#line 406 "asm.y"
{ yyval.node = makeNode( A_CMDRES );  
                                              yyval.node->param[1] = yyvsp[0].node; 
                                              yyval.node->param[0] = makeNode( A_VALUE );
                                              yyval.node->param[0]->value = 0; ;
    break;}
case 51:
#line 413 "asm.y"
{ yyval.node = yyvsp[-1].node; ;
    break;}
case 52:
#line 417 "asm.y"
{ yyval.node = yyvsp[0].node; ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/lib/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 420 "asm.y"




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
    case A_VALUE:  printf("%X", n->value );      
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

