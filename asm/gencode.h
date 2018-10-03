#ifndef __GENCODE_H__
#define __GENCODE_H__

#include "dlxasm.h"
#include "asm.h"

typedef enum { GEN_VHDL, GEN_RAW, GEN_HEX, GEN_NONE, GEN_DETAIL } GenType;

void asm_gencode_tree( asm_info_t *a, Node *node, GenType type );

#endif
