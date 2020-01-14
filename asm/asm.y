%{
 
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

%}


%union
{
    double fvalue;
    long value;
    char *text;
    const dlx_instr_entry *instr;
    struct Node *node;
    struct Node *params[3];
    struct { int r, t; } reserve;
}

%token <text>   DATA_TYPE
%token <text>   IDENTIFIER 
%token <instr>  OP_CODE 
%token <value>  IMM_VALUE 
%token <value>  F_REG I_REG
%token <fvalue> IMM_FVALUE

%type <params> mem
%type <node>   immediate expr reg org equ data reservations reservation reservation_pre reservation_post

%token EQU ORG T_CR

%left '+' '-'
%left '*' '/'
%left NEG /* unary minus operation */


%%

program :
      instructions
    ;

instructions:
      instructions instruction
    | instruction
    ;
    
instruction:
      labels instr_asm  T_CR
    | labels      T_CR      
    | instr_asm   T_CR          
    | pseudo_code T_CR
    | T_CR      
    | error T_CR    {   yyerror_printf( yy_error_txt[ ERRCANTPARSELINE ] );  yyerrok; yyclearin; }
    ;

labels: 
      labels label 
    | label
    ;

label: 
      IDENTIFIER ':'          {   
                                Node *node = makeNode( A_LABEL );
                                node->identifier = $1;
                                asm_push_node( node ); 
                              }
    ;


instr_asm:
      OP_CODE reg ',' reg ',' reg           
                              { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( $1->opname );
                                node->instr = $1;
                                node->param[0] = $2;
                                node->param[1] = $4;
                                node->param[2] = $6;

                                if( (check_error = asm_check_instr_param( node, P_REG_REG_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
     | OP_CODE reg ',' reg ',' immediate
                              { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( $1->opname );
                                node->instr = $1;
                                node->param[0] = $2;
                                node->param[1] = $4;
                                node->param[2] = $6;

                                if( (check_error = asm_check_instr_param( node, P_REG_REG_IMM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
     | OP_CODE reg ',' immediate    
                              { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( $1->opname );
                                node->instr = $1;
                                node->param[1] = $2;
                                if( $1->type == BRANCH ) {
                                  node->param[2] = makeNode( A_OPSUB );
                                  node->param[2]->param[0] = $4;
                                  node->param[2]->param[1] = makeNode( A_OPADD );
                                  node->param[2]->param[1]->param[0] = makeNode( A_IDENT );
                                  node->param[2]->param[1]->param[0]->identifier = strdup("%OFFSET");
                                  node->param[2]->param[1]->param[1] = makeNode( A_VALUE );
                                  node->param[2]->param[1]->param[1]->value = 4;                                  
                                }
                                else
                                  node->param[2] = $4;


                                if( (check_error = asm_check_instr_param( node, P_REG_IMM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
     | OP_CODE reg ',' reg    
                              { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( $1->opname );
                                node->instr = $1;
                                node->param[1] = $2;
                                node->param[2] = $4;

                                if( (check_error = asm_check_instr_param( node, P_REG_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
     | OP_CODE reg     
                              { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( $1->opname );
                                node->instr = $1;
                                node->param[1] = $2;

                                if( (check_error = asm_check_instr_param( node, P_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
     | OP_CODE immediate     
                              { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( $1->opname );
                                node->instr = $1;

                                if( $1->type == BRANCH ) {
                                  node->param[2] = makeNode( A_OPSUB );
                                  node->param[2]->param[0] = $2;
                                  node->param[2]->param[1] = makeNode( A_OPADD );
                                  node->param[2]->param[1]->param[0] = makeNode( A_IDENT );
                                  node->param[2]->param[1]->param[0]->identifier = strdup("%OFFSET");
                                  node->param[2]->param[1]->param[1] = makeNode( A_VALUE );
                                  node->param[2]->param[1]->param[1]->value = 4;                                  
                                }
                                else
                                  node->param[2] = $2;

                                if( (check_error = asm_check_instr_param( node, P_IMM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
     | OP_CODE      
                              { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( $1->opname );
                                node->instr = $1;

                                if( (check_error = asm_check_instr_param( node, P_NONE )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }

     | OP_CODE mem ',' reg     
                              { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( $1->opname );
                                node->instr = $1;
                                node->param[0] = $4;
                                node->param[1] = $2[0];
                                node->param[2] = $2[1];

                                if( (check_error = asm_check_instr_param( node, P_MEM_REG )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
     | OP_CODE reg ',' mem     
                              { int check_error;
                                Node *node = makeNode( A_INSTR );
                                node->identifier = strdup( $1->opname );
                                node->instr = $1;
                                node->param[0] = $2;
                                node->param[1] = $4[0];
                                node->param[2] = $4[1];

                                if( (check_error = asm_check_instr_param( node, P_REG_MEM )) == OPOK )
                                  asm_push_node( node );
                                else {
                                  yyerror_printf( yy_error_txt[ check_error ], node->instr->opname );
                                  asm_delete_tree( node );
                                }
                              }
    ;

pseudo_code:
      equ  { asm_push_node( $1 ); }
    | org  { 
        if( strcasecmp( $1->identifier, "data" ) == 0 ||
            strcasecmp( $1->identifier, "code" ) == 0 )
          asm_push_node( $1 );
        else {
          yyerror_printf( yy_error_txt[ ERRINVALIDORG ], $1->identifier );
          asm_delete_tree( $1 );
        }
    }
    | data { asm_push_node( $1 ); }                    
    ;

mem:
      immediate '(' reg ')' { $$[0] = $3; $$[1] = $1;  }
    | '(' reg ')'           {   
                              $$[0] = $2;
                              $$[1] = makeNode( A_VALUE );
                              $$[1]->value = 0;
                            }
    ;

reg:                
      I_REG         { $$ = makeNode( A_RREG ); $$->value = $1; }
    | F_REG         { $$ = makeNode( A_FREG ); $$->value = $1; }
    ;

immediate:
    expr    
    ;

expr: expr '+' expr { $$ = makeNode( A_OPADD ); $$->param[0] = $1; $$->param[1] = $3; }
    | expr '-' expr { $$ = makeNode( A_OPSUB ); $$->param[0] = $1; $$->param[1] = $3; }
    | '-' expr %prec NEG  { $$ = makeNode( A_OPSUB );
                            $$->param[0] = makeNode( A_VALUE );
                            $$->param[0]->value = 0;
                            $$->param[1] = $2; 
                          }
    | expr '*' expr { $$ = makeNode( A_OPMUL );  $$->param[0] = $1; $$->param[1] = $3; }
    | expr '/' expr { $$ = makeNode( A_OPDIV );  $$->param[0] = $1; $$->param[1] = $3; }
    | IMM_FVALUE    { $$ = makeNode( A_FVALUE ); $$->fvalue = $1; }
    | IMM_VALUE     { $$ = makeNode( A_VALUE );  $$->value = $1; }
    | IDENTIFIER    { $$ = makeNode( A_IDENT );  $$->identifier = $1; }
    | '(' expr ')'  { $$ = $2; }
    ;



org:
      ORG immediate             { $$ = makeNode( A_CMDORG ); $$->identifier = strdup("code"); $$->param[0] = $2;  }
    | IDENTIFIER ORG immediate  { $$ = makeNode( A_CMDORG ); $$->identifier = strdup($1);   $$->param[0] = $3;  }
    | IDENTIFIER ORG            { $$ = makeNode( A_CMDORG ); $$->identifier = strdup($1);   
                                  $$->param[0] = makeNode( A_VALUE ); $$->param[0]->value = 0;  }
    ;

equ:
    IDENTIFIER EQU immediate    { $$ = makeNode( A_CMDEQU ); $$->identifier = strdup($1);   $$->param[0] = $3;  }
   ;

data:
    IDENTIFIER DATA_TYPE reservations {  int id_length = asm_data_type_length( $2 );
                                         if( id_length > 0 ) {
                                           $$ = makeNode( A_CMDDATA );  
                                           $$->identifier = $1;
                                           $$->param[0] = $3; 
                                           $$->param[1] = makeNode( A_VALUE );
                                           $$->param[1]->value = asm_data_type_length( $2 );
                                           $$->param[1]->identifier = strdup( $2 );
                                         }
                                         else {
                                           $$ = NULL;
                                           yyerror_printf( yy_error_txt[ ERRINVALIDIDENTIFIER ], $2 );
                                         }
                                       }
    |
    DATA_TYPE reservations            {  int id_length = asm_data_type_length( $1 );
                                         if( id_length > 0 ) {
                                           $$ = makeNode( A_CMDDATA );  
                                           $$->identifier = NULL;
                                           $$->param[0] = $2; 
                                           $$->param[1] = makeNode( A_VALUE );
                                           $$->param[1]->value = asm_data_type_length( $1 );
                                           $$->param[1]->identifier = strdup( $1 );
                                         }
                                         else {
                                           $$ = NULL;
                                           yyerror_printf( yy_error_txt[ ERRINVALIDIDENTIFIER ], $1 );
                                         }
                                       }
    ;

reservations:
      reservation ',' reservations     { $$ = $1;
                                         $$->param[2] = $3; }
    | reservation                      { $$ = $1; }
    ;

reservation:
      reservation reservation_post          { $$ = makeNode( A_CMDRES ); 
                                              $$->param[0] = $1;
                                              $$->param[1] = $2;   }
    | '(' reservation ',' reservations ')'  { $$ = makeNode( A_CMDRES );
                                              $$->param[0] = $2;
                                              $$->param[1] = makeNode( A_VALUE );
                                              $$->param[1]->value = 1;
                                              $$->param[2] = $4;  }
    | reservation_pre                       { $$ = makeNode( A_CMDRES );  
                                              $$->param[0] = $1; 
                                              $$->param[1] = makeNode( A_VALUE );
                                              $$->param[1]->value = 1;
                                            } 
    | reservation_post                      { $$ = makeNode( A_CMDRES );  
                                              $$->param[1] = $1; 
                                              $$->param[0] = makeNode( A_VALUE );
                                              $$->param[0]->value = 0; }
    ;

reservation_post:
    '[' immediate ']'                  { $$ = $2; }
    ;

reservation_pre:
      immediate                        { $$ = $1; }
     ;

%%



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

