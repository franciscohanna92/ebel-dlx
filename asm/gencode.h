#ifndef __GENCODE_H__
#define __GENCODE_H__

#include "dlxasm.h"
#include "asm.h"

typedef enum { GEN_VHDL, GEN_RAW, GEN_HEX, GEN_NONE, GEN_DETAIL } GenType;

void asm_gencode_tree( asm_info_t *a, Node *node, GenType type );
void asm_gencode_allocate_memory( Node *node );
void asm_gencode_build_memory( Node *node );
void asm_gencode_vhdl(FILE* dest);
void asm_gencode_raw(FILE* dest);
void asm_gencode_hex(FILE* dest);

#endif
