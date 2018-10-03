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
                                                                              
#ifndef __DLX_DEBUG_H__
#define __DLX_DEBUG_H__

#if defined( VM_DEBUG ) || defined( SIM_DEBUG ) || defined( ASM_DEBUG )
#ifndef DEBUG
#define DEBUG
#endif
#endif


#ifndef VM_DEBUG_LEVEL
#define VM_DEBUG_LEVEL 3
#endif

#ifndef ASM_DEBUG_LEVEL
#define ASM_DEBUG_LEVEL 3
#endif


#ifndef SIM_DEBUG_LEVEL
#define SIM_DEBUG_LEVEL 3
#endif




#ifdef DEBUG

extern int debug_indent_counter;

void debug_indent( int i );
void debug_indent_print();
void vm_debug_println( int level, char *txt, ... );
void sim_debug_println( int level, char *txt, ... );
void asm_debug_println( int level, char *txt, ... );
void debug_println( char *txt, ... );


#else


#define debug_indent //
#define debug_indent_print //
#define vm_debug_println //
#define sim_debug_println //
#define asm_debug_println //
#define debug_println //

#endif



#endif
