%{
#include <string.h>
#include <ctype.h>
#include "../lib/dlxinstset.h"
#include "../asm/asm.h"
#include "../asm/asm.tab.h"


#ifdef DEBUG_LEX
YYSTYPE yylval;
#endif

%}

%option yylineno

HEX         [0-9a-fA-F]
hexa    {HEX}(_?{HEX})*
deci    [0-9](_?[0-9])*
flo         {deci}*\.{deci}|{deci}\.{deci}*
flonum      {flo}|{flo}[eE]{deci}
fixnum      ([xX]\"{hexa}\")|{deci}|0[xX]{hexa}
reg_number  (0?[0-9]|[12][0-9]|3[01])
i_reg   [rR]{reg_number}
f_reg   [fF]{reg_number}
s_reg   iar|fpsr
identifier  [a-zA-Z_.][a-zA-Z_0-9.]*
immediate {fixnum}
fimmediate  {flonum}
blank   [\t ]
newline   [\r\n]

%%

";".*   ;
{blank}   ;
{newline}   { return T_CR; }

{i_reg}   { 
              yylval.value = atoi(yytext+1); 
          return I_REG; 
            }

{f_reg}   { 
              yylval.value = atoi(yytext+1); 
            return F_REG; 
            }
{immediate} { 
          if(yytext[0] == 'X' || yytext[0] == 'x') 
           sscanf(yytext+2, "%lX", &yylval.value);
          else
          if( yytext[0] == '0' && (yytext[1] == 'X' || yytext[1] == 'x')) 
           sscanf(yytext+2, "%lX", &yylval.value);
          else 
           yylval.value = atoi(yytext);

          return IMM_VALUE;
        }

{fimmediate} {
           sscanf(yytext, "%lf\"", &yylval.fvalue);
               return IMM_FVALUE;
             }

{identifier} {
               const dlx_instr_entry *instr;
               if( strcasecmp( yytext, "ORG" ) == 0 )   return ORG;
               if( strcasecmp( yytext, "EQU" ) == 0 )   return EQU;
               if( (instr = dlx_get_instr_by_opcode( yytext )) != NULL ) {
                 yylval.instr = instr;
                 return OP_CODE;
               }

               if( asm_data_type_length( yytext ) >= 0 ) {
                 yylval.text = strdup( yytext );
                 return DATA_TYPE;
               }

               yylval.text = strdup( yytext );
               return IDENTIFIER;
             }



.   {
          return *yytext;
        }
%%


#ifdef DEBUG_LEX

int main (int argc, char *argv[])
{
int r;
  while(r = yylex())
  {
    switch(r)
    {
    case DATA_TYPE:
      printf(" type: %s\n", yylval.text );
      break;
    case IDENTIFIER:
      printf(" id: %s\n", yylval.text );
      break;
    case IMM_VALUE:
      printf(" im: %ld\n", yylval.value );
      break;
    case F_REG:
      printf(" f_reg: %ld\n", yylval.value );
      break;
    case I_REG:
      printf(" i_reg: %ld\n", yylval.value );
      break;
    case OP_CODE:
      printf(" code: %s\n", yylval.text);
      break;
    case EQU:
      printf(" EQU: %s\n", yylval.text);
      break;
    case ORG:
      printf(" ORG: %s\n", yylval.text);
      break;
        case T_CR:
             printf("<newline>");
            break;
    default:
            printf(" char : (%d) '%c'\n", r, (char)r );
      break;
    }
  
  }
}

#endif


int yywrap()
{
  return 1;
}

