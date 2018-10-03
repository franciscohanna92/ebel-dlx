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
                                                                              
#include <stdlib.h>
#include "dlxasm.h"
#include "asm.h"
#include "analyse.h"
#include "gencode.h"
#include "symbols.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

Node *asm_head;
Node *asm_last;

void asm_init() {
  asm_head = NULL;
  asm_last = NULL;
}

void asm_push_node( Node *node ) {
  node->next = NULL;
  if( asm_head == NULL ) {
    asm_head = node;
    asm_last = node;
  }
  else {
    asm_last->next = node;
    asm_last = node;
  }
}


void asm_delete_tree( Node *node ) {
  if( node == NULL ) return;
  asm_delete_tree( node->param[0] );
  asm_delete_tree( node->param[1] );
  asm_delete_tree( node->param[2] );
  asm_delete_tree( node->next );
  if( node->identifier != NULL ) 
    free( node->identifier );
  
  free( node );
};


void asm_version() {
  printf("EBEL DLX Assembler 1.0\n");
}


asm_info_t *asm_create_asm_info() {
  
  asm_info_t *a;
  asm_debug_println( 2, "DLX ASM create asm info.");  
  a = (asm_info_t*)malloc( sizeof( asm_info_t ) );
  a->filename = NULL;
  a->tree = NULL;
  a->symbols = NULL;
  a->code = NULL;
  a->data = NULL;
  return a;
}


void asm_destroy_asm_info( asm_info_t *a ) {
  asm_debug_println( 2, "DLX ASM delete asm info.");
  if( a->filename != NULL ) free( a->filename );
  asm_delete_tree( a->tree );
  symbols_delete( a->symbols );
  if( a->code ) free( a->code );
}


void asm_internal_compile_file( asm_info_t *a, FILE *f ) {
  symbols_t *s;

  asm_debug_println( 2, "DLX ASM internal compile file ");

  s = symbols_create();
  a->symbols = s;

  asm_init();
  asm_parse_file( f );


  /*
  printf("----------------------------------- TREE ----------------------------------\n"); 
  asm_print_tree( asm_head );
  printf("---------------------------------------------------------------------------\n"); 
  */

  asm_head = asm_analyse_tree( asm_head, s );

  /*
  printf("----------------------------------- TREE ----------------------------------\n"); 
  asm_print_tree( asm_head );
  printf("---------------------------------------------------------------------------\n"); 
  */

  asm_gencode_tree( a, asm_head, GEN_NONE );
  //asm_delete_tree( asm_head ); //-- let asm_info delete him
  a->tree = asm_head;
  asm_head = NULL;
}

void asm_compile_file( asm_info_t *a, const char *filename ) {
  FILE *f;
  char *ptr;
  struct stat statbuf;
  asm_debug_println( 1, "DLX ASM compile file (%s)", filename );
  
  a->filename = strdup( filename );
  ptr = a->filename + strlen( a->filename ) -1;
  while( *ptr == ' ' && ptr != a->filename ) ptr--;
  *(ptr+1) = '\0';
  a->success = 0;

  f = fopen( a->filename, "r" );
  if( f == NULL ) return;

  fstat(fileno(f), &statbuf);
  if (S_ISDIR(statbuf.st_mode)) {
    printf("Can't open a directory!\n");
    fclose(f);
    return;
  }
  
  asm_internal_compile_file( a, f );
  fclose( f );
  a->success = 1;
}





