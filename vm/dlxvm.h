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

#ifndef __DLXVM_H__
#define __DLXVM_H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../asm/symbols.h"
#include "../lib/dlxinstset.h"
#include "../lib/dlxtypes.h"
#include "../lib/dlxdebug.h"

typedef struct
{
  DLX_WORD R[32];  //-- General-Purpose registers.
  DLX_FLOAT F[32]; //-- Floating-Point registers.
  DLX_WORD PC;     //-- Program counter.
  DLX_WORD NPC;    //-- Next Program counter.
  DLX_WORD IAR;    //-- Interrupt Adress Register.
  DLX_WORD FPSR;   //-- Floating-Point Status Register.
} registers_t;

typedef struct DLX_vm
{
  /** VM Variables **/
  registers_t registers;
  DLX_UBYTE *code;
  DLX_UBYTE *data;
  DLX_UBYTE *memory;
  DLX_UBYTE *breakpoints;

  int memory_length;
  int code_length;
  int data_length;

  symbols_t *symbols;
  //** VM Options **//
  int branch_delay_slots_count;
  int branch_delay_slots;
  int trace;
} DLX_vm;

typedef struct dlx_instr_decode
{
  unsigned int instr;
  unsigned int opcode;
  int name;
  DLX_WORD imm;
  unsigned int r1, r2, r3;
  unsigned int fAlu, fFpu;
  const dlx_instr_entry *ent;
  unsigned int rd;
} dlx_instr_decode;

extern DLX_vm dlx_vm;

void vm_set_branch_delay_slots(int nb);
void vm_version();
void vm_init();
int vm_load(DLX_UBYTE *memory, int length, DLX_UBYTE *code, int code_length,
            DLX_UBYTE *data, int data_length, symbols_t *s);
void vm_print_registers();
void vm_print_memory(DLX_UINT start, DLX_WORD length);
void vm_print_symbols(const char *);
int vm_disassemble(DLX_UINT start, DLX_WORD length);
int vm_step();
int vm_run(int length);
void vm_set_breakpoint(const char *label);
void vm_unset_breakpoint(const char *label);
void vm_trace();
void vm_untrace();
void vm_jump(int);
void vm_reset();

#endif
