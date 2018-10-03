#ifndef __ASM_H__
#define __ASM_H__

#include <stdio.h>
#include "../lib/dlxinstset.h"

typedef enum { A_LABEL, A_IDENT, A_RREG, A_FREG, A_INSTR, A_VALUE, A_FVALUE, 
               A_OPADD, A_OPSUB, A_OPMUL, A_OPDIV, 
               A_CMDORG, A_CMDEQU, A_CMDDATA, A_CMDRES } asm_node_type;

typedef struct Node {
  asm_node_type type;
  char *identifier;
  long value;
  double fvalue;
  const dlx_instr_entry *instr;
  int line_no;
  struct Node *param[3];
  struct Node *next;
} Node;


Node *makeNode( asm_node_type type );
void asm_delete_tree( Node * );
void asm_parse_file( FILE *f );
void asm_print_tree( Node *tree );
void asm_push_node( Node *node );
int asm_data_type_length( const char *name );
int asm_data_type_fixnum( const char *name );
int asm_data_type_flonum( const char *name );
int yyerror_printf2( const char *s, int lineno, ... );
int yyerror( const char *s);
int yylex();

#endif
