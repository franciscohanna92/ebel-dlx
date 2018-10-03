#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__

#include "asm.h"

typedef struct symbols_t {
  Node *list;
  Node *last;
} symbols_t;

symbols_t *symbols_create();
symbols_t *symbols_delete( symbols_t *s );
symbols_t *symbols_add( symbols_t *s, const char *name, Node *val );
Node *symbols_get( symbols_t *s, const char *name );
void symbols_printall( symbols_t *s );
void symbols_print( symbols_t *s, const char* name );
#endif
