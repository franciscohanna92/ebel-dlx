/************************************************************************
 *
 * EBEL DLX Simulator
 * Copyright (c) 2001 by
 * Etienne Bergeron <bergeret@iro.umontreal.ca>
 * and Eric Lesage <lesagee@iro.umontreal.ca>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (see file COPYING); if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 ************************************************************************/
                                                                              
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbols.h"


symbols_t *symbols_create() {
  symbols_t *s = (symbols_t*)malloc( sizeof( symbols_t ) );
  s->list = NULL;
  s->last = NULL;
  return s;
}

symbols_t *symbols_delete( symbols_t *s ) {
  if( s ) {
    if( s->list ) asm_delete_tree( s->list );
    free( s );
  }
}

symbols_t *symbols_add( symbols_t *s, const char *name, Node *val ) {
  if( name == NULL ) return NULL;
  else {
	Node *n = makeNode( val->type );

	n->fvalue = val->fvalue;
	n->value = val->value;
	n->identifier = strdup( name );
	n->next = s->list;
	s->list = n;
	return s;
  }
}

Node *symbols_get( symbols_t *s, const char *name ) {
  if( name == NULL ) return NULL;
  else {
	Node *tmp = s->list;

	while( tmp != NULL ) {
	  if( strcasecmp( name, tmp->identifier ) == 0) 
		return tmp;
	  tmp = tmp->next;
	}
	return NULL;
  }
}

void symbols_print( symbols_t *s, const char* name ) {
  Node *n = symbols_get( s, name );
  if( n == NULL ) {
    printf("Symbols not found.\n");
  }
  else {
    if( n->type == A_VALUE ) 
      printf("%10s = %08X  (%d)\n", n->identifier, n->value, n->value );
    else
      printf("%10s = %08X  (%f)\n", n->identifier, n->value, n->value );
  }
}

void symbols_printall( symbols_t *s ) {
  Node *tmp = s->list;
  while( tmp != NULL ) {
    if( tmp->type == A_VALUE )
      printf("%10s = %08X  (%d)\n", tmp->identifier, tmp->value, tmp->value );
    else
      printf("%10s = %08X  (%f)\n", tmp->identifier, tmp->fvalue, tmp->value );
    tmp = tmp->next;
  }
}
