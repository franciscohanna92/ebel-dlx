#ifndef __DLXASM_H__
#define __DLXASM_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../lib/dlxinstset.h"
#include "../lib/dlxtypes.h"
#include "../lib/dlxdebug.h"
#include "asm.h"
#include "symbols.h"

typedef struct asm_info_t {
  int success;
  char *filename;
  symbols_t *symbols;
  Node *tree;
  DLX_BYTE *code, *data;
  int code_length, data_length;
} asm_info_t;



void asm_version();

asm_info_t *asm_create_asm_info();
void asm_destroy_asm_info( asm_info_t * );
void asm_compile_file( asm_info_t *, const char * );


#endif

