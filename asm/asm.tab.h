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


extern YYSTYPE yylval;
