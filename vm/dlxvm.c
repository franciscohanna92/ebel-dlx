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

#include "../asm/asm.h"
#include "../asm/symbols.h"
#include "dlxvm.h"

DLX_vm dlx_vm;

void vm_set_branch_delay_slots(int nb)
{
  if (nb < 0)
    dlx_vm.branch_delay_slots = 0;
  else
    dlx_vm.branch_delay_slots = nb;
}

void vm_version()
{
  printf("EBEL DLX Virtual Machine 1.0\n");
}

void vm_init()
{
  debug_println("DLX Virtual Machine Initialisation...");
  debug_indent(2);
  vm_debug_println(1, "DLX VM structure reset.");
  debug_indent(-2);

  bzero(&dlx_vm, sizeof(DLX_vm));
  vm_set_branch_delay_slots(0);
  vm_jump(0);
  vm_untrace();
}

int vm_load(DLX_UBYTE *memory, int length, DLX_UBYTE *code, int code_length, DLX_UBYTE *data, int data_length, symbols_t *s)
{
  debug_println("DLX Virtual Machine loading code...");
  dlx_vm.memory = memory;
  dlx_vm.code = code;
  dlx_vm.code_length = code_length;
  dlx_vm.data = data;
  dlx_vm.data_length = data_length;
  dlx_vm.memory_length = length;
  dlx_vm.breakpoints = (DLX_UBYTE *)malloc(sizeof(DLX_UBYTE) * code_length);
  memset(dlx_vm.breakpoints, 0, dlx_vm.code_length);
  dlx_vm.symbols = s;
  return 1;
}

void vm_reset()
{
  int i;
  dlx_vm.registers.IAR = 0;
  dlx_vm.registers.PC = 0;
  dlx_vm.registers.NPC = 0;
  dlx_vm.registers.FPSR = 0;
  for (i = 0; i < 32; i++)
  {
    dlx_vm.registers.R[i] = 0;
    dlx_vm.registers.F[i] = 0.;
  }
}

void vm_trace()
{
  dlx_vm.trace = 1;
}

void vm_untrace()
{
  dlx_vm.trace = 0;
}

int vm_internal_breakpoint_value(const char *label)
{
  Node *n = symbols_get(dlx_vm.symbols, label);

  long i = -1;
  if (n != NULL)
  {
    if (n->type != A_VALUE)
      printf("Invalid label type.\n");
    else
      i = n->value;
  }
  else
  {
    char *test;
    i = strtol(label, &test, 0);

    if (test == label)
    {
      printf("Invalid or unknown label\n");
      return -1;
    }
  }

  if (i < 0)
    printf("Invalid label, must greater than 0\n");
  if (i > dlx_vm.code_length)
    printf("Invalid label, out of code segment.\n");

  return i;
}

void vm_set_breakpoint(const char *label)
{
  int i;
  if (label != NULL)
  {
    i = vm_internal_breakpoint_value(label);
    if (i >= 0)
      dlx_vm.breakpoints[i] = 1;
  }
  else
  {
    for (i = 0; i < dlx_vm.code_length; i++)
    {
      if (dlx_vm.breakpoints[i])
        printf("%08X\n", i);
    }
  }
}

void vm_unset_breakpoint(const char *label)
{
  if (label != NULL)
  {
    int i = vm_internal_breakpoint_value(label);
    if (i >= 0)
      dlx_vm.breakpoints[i] = 0;
  }
}

void vm_jump(int pc)
{
  dlx_vm.branch_delay_slots_count = 0;
  dlx_vm.registers.PC = pc;
  dlx_vm.registers.NPC = pc;
}

int vm_internal_fetch(DLX_UINT pc, dlx_instr_decode *instr)
{
  if (pc >= dlx_vm.code_length)
    return 1;
  instr->instr = LOAD_BYTE_TO_INT(&(dlx_vm.code[pc]));
  return 0;
}

void vm_internal_decode(dlx_instr_decode *instr)
{
  instr->opcode = (instr->instr >> 26);
  instr->r1 = (instr->instr >> 21) & 0x1F;
  instr->r2 = (instr->instr >> 16) & 0x1F;
  instr->r3 = (instr->instr >> 11) & 0x1F;
  instr->fAlu = (instr->instr) & 0x3F;
  instr->fFpu = (instr->instr) & 0x1F;
  instr->name = ((instr->instr & 0x040000) ? 0xFFFFFC0000 : 0) | ((instr->instr) & 0x07FFFF);
  instr->imm = ((instr->instr & 0x008000) ? 0xFFFFFF8000 : 0) | ((instr->instr) & 0x00FFFF);
  instr->ent = ((instr->opcode == 0) ? DLX_INSTR_SP_TABLE + instr->fAlu : ((instr->opcode == 1) ? DLX_INSTR_FP_TABLE + instr->fFpu : (DLX_INSTR_TABLE + instr->opcode)));
  instr->rd = ((instr->ent->format == FORMAT_I) ? instr->r2 : instr->r3);
}

void vm_internal_print_registers()
{
  int i;
  printf("{\"PC\": \"%2.2X\", ", dlx_vm.registers.PC);
  printf("\"NPC\": \"%2.2X\", ", dlx_vm.registers.NPC);
  printf("\"IAR\": \"%2.2X\", ", dlx_vm.registers.IAR);
  printf("\"FPSR\": \"%2.2X\", ", dlx_vm.registers.FPSR);
  printf("\"R\": [");
  for (i = 0; i < 32; i++)
  {
    DLX_WORD regValue = dlx_vm.registers.R[i];
    if (i == 31)
    {
      printf("{ \"id\": %d, \"value\": \"%8.8x\" }], ", i, regValue);
    }
    else
    {
      printf("{ \"id\": %d, \"value\": \"%8.8x\" }, ", i, regValue);
    }
  }

  printf("\"F\": [");
  for (i = 0; i < 32; i++)
  {
    DLX_FLOAT regValue = dlx_vm.registers.F[i];
    if (i == 31)
    {
      printf("\"%8f\"], ", regValue);
    }
    else
    {
      printf("\"%8f\", ", regValue);
    }
  }

  printf("\"D\": [");
  for (i = 0; i < 16; i++)
  {
    double regValue = *((double *)&dlx_vm.registers.F[i * 2]);
    if (i == 15)
    {
      printf("\"%8f\"] ", regValue);
    }
    else
    {
      printf("\"%8f\", ", regValue);
    }

    // if (i % 8 == 0)
    //   printf("\n  ");
    // printf("%8f ", *((double *)&dlx_vm.registers.F[i * 2]));
  }
  printf("}");
  printf("\n");
}

void vm_print_registers()
{
  vm_internal_print_registers();
}

void vm_print_symbols(const char *label)
{
  if (label != NULL)
    symbols_print(dlx_vm.symbols, label);
  else
    symbols_printall(dlx_vm.symbols);
}

void vm_internal_print_memory(DLX_UWORD start, DLX_WORD length)
{
  int i, j;
  int loop = length;

  if (length <= 0)
    length = dlx_vm.data_length;
  if (start + length > dlx_vm.data_length)
    length = dlx_vm.data_length - start;

  printf("start = %d  length = %d\n", start, length);

  for (i = start / 16; i < ((start + length) / 16) + 1; i++)
  {
    printf("%4.4X: ", i * 16);
    for (j = 0; j < 16; j++)
    {
      if (j == 8)
        printf("  ");
      if (i * 16 + j < start + length && i * 16 + j >= start)
        printf("%2.2X ", dlx_vm.data[i * 16 + j]);
      else
        printf("   ");
    }
    printf("  ");
    for (j = 0; j < 16; j++)
    {
      if (j == 8)
        printf(" ");
      if (i * 16 + j < start + length && i * 16 + j >= start)
        if (isprint(dlx_vm.data[i * 16 + j]))
          printf("%c", dlx_vm.data[i * 16 + j]);
        else
          printf(".");
      else
        printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

void vm_print_memory(DLX_UWORD start, DLX_WORD length)
{
  vm_internal_print_memory(start, length);
}

void vm_internal_print_instr(DLX_UINT pc, dlx_instr_decode *instr, int code_length, int length)
{
  printf("{ \"pc\": \"%4.4X\", \"instr\": \"%8.8X\", \"opname\": \"%s\", \"args\": [", pc, instr->instr, instr->ent->opname);

  switch (instr->ent->type)
  {
  case REG:
    if (instr->ent->property == (RD | RS1 | RS2))
    {
      if (instr->ent->reg_type == INSTR_FP)
        printf("\"f%d\", \"f%d\", \"f%d\"", instr->rd, instr->r1, instr->r2);
      else
        printf("\"r%d\", \"r%d\", \"r%d\"", instr->rd, instr->r1, instr->r2);
    }
    break;

  case IMM:
    if (instr->ent->property == (RD | RS1 | SIMM))
    {
      if (instr->ent->reg_type == INSTR_FP)
        printf("\"f%d\", \"f%d\", \"%d\"", instr->rd, instr->r1, instr->imm);
      else
        printf("\"r%d\", \"r%d\", \"%X\"", instr->rd, instr->r1, instr->imm & 0xFFFF);
    }
    else if (instr->ent->property == (RD | RS1 | UIMM))
    {
      if (instr->ent->reg_type == INSTR_FP)
        printf("\"f%d\", \"f%d\", \"%d\"", instr->rd, instr->r1, instr->imm);
      else
        printf("r%d, r%d, %X ", instr->rd, instr->r1, instr->imm & 0xFFFF);
    }
    break;

  case LOAD:
    if (instr->ent->reg_type == INSTR_FP)
      printf("\"f%d\", \"%X(r%d)\"", instr->rd, instr->imm & 0xFFFF, instr->r1);
    else
      printf("\"r%d\", \"%X(r%d)\"", instr->rd, instr->imm & 0xFFFF, instr->r1);

    break;

  case STORE:
    if (instr->ent->reg_type == INSTR_FP)
      printf("\"%X(r%d)\", \"f%d\"", instr->imm & 0xFFFF, instr->r1, instr->rd);
    else
      printf("\"%X(r%d)\", \"r%d\"", instr->imm & 0xFFFF, instr->r1, instr->rd);

    break;

  case BRANCH:
    if (instr->ent->property == RS1)
      printf("\"r%d\"", instr->r1);
    else if (instr->ent->property == NAME)
      printf("\"%X\"", instr->name);
    else if (instr->ent->property == (RS1 | NAME))
      printf("\"r%d\", \"%X\"", instr->r1, instr->name);
    break;

  case MOVE:
    printf("MOVE not implemented\n");
    break;

  case NONE:
    break;

  case SPECIAL:
    if (instr->ent->property == NAME)
      printf("\"%X\"", instr->name);
    break;
  };

  if (pc + 4 == code_length || length == 1)
  {
    printf("]}");
  }
  else
  {
    printf("]}, ");
  }

  if(length == 1) {
    printf("\n");
  }
}

int vm_memory_check(int offset, int length)
{
  if (offset < 0 || dlx_vm.data_length <= (offset + length - 1))
  {
    printf("Out-of-memory access trap on code segment (at %X).\n", offset);
    return 1;
  }
  return 0;
}

int vm_internal_execute(dlx_instr_decode *instr)
{
  switch (instr->opcode)
  {

  case FPARITH:
    switch (instr->fFpu)
    {
    case ADDF:
      dlx_vm.registers.F[instr->rd] =
          (DLX_FLOAT)((DLX_FLOAT)dlx_vm.registers.F[instr->r1] +
                      (DLX_FLOAT)dlx_vm.registers.F[instr->r2]);
      break;

    case SUBF:
      dlx_vm.registers.F[instr->rd] =
          (DLX_FLOAT)((DLX_FLOAT)dlx_vm.registers.F[instr->r1] -
                      (DLX_FLOAT)dlx_vm.registers.F[instr->r2]);
      break;

    case MULTF:
      dlx_vm.registers.F[instr->rd] =
          (DLX_FLOAT)((DLX_FLOAT)dlx_vm.registers.F[instr->r1] *
                      (DLX_FLOAT)dlx_vm.registers.F[instr->r2]);
      break;

    case DIVF:
      dlx_vm.registers.F[instr->rd] =
          (DLX_FLOAT)((DLX_FLOAT)dlx_vm.registers.F[instr->r1] /
                      (DLX_FLOAT)dlx_vm.registers.F[instr->r2]);
      break;

    case ADDD:
      *((DLX_DOUBLE *)dlx_vm.registers.F + instr->rd) =
          *((DLX_DOUBLE *)dlx_vm.registers.F + instr->r1) +
          *((DLX_DOUBLE *)dlx_vm.registers.F + instr->r2);
      break;

    case SUBD:
      *((DLX_DOUBLE *)dlx_vm.registers.F + instr->rd) =
          *((DLX_DOUBLE *)dlx_vm.registers.F + instr->r1) -
          *((DLX_DOUBLE *)dlx_vm.registers.F + instr->r2);
      break;

    case MULTD:
      *((DLX_DOUBLE *)dlx_vm.registers.F + instr->rd) =
          *((DLX_DOUBLE *)dlx_vm.registers.F + instr->r1) *
          *((DLX_DOUBLE *)dlx_vm.registers.F + instr->r2);
      break;

    case DIVD:
      *((DLX_DOUBLE *)dlx_vm.registers.F + instr->rd) =
          *((DLX_DOUBLE *)dlx_vm.registers.F + instr->r1) /
          *((DLX_DOUBLE *)dlx_vm.registers.F + instr->r2);
      break;

    case CVTF2D:
      break;

    case CVTF2I:
      break;

    case CVTD2F:
      break;

    case CVTD2I:
      break;

    case CVTI2F:
      break;

    case MULT:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] *
                     (DLX_WORD)dlx_vm.registers.R[instr->r2]);
      break;

    case DIV:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] /
                     (DLX_WORD)dlx_vm.registers.R[instr->r2]);
      break;

    case EQF:
      dlx_vm.registers.FPSR =
          ((DLX_FLOAT)dlx_vm.registers.F[instr->r1] ==
           (DLX_FLOAT)dlx_vm.registers.F[instr->r2])
              ? 1
              : 0;
      break;

    case NEF:
      dlx_vm.registers.FPSR =
          ((DLX_FLOAT)dlx_vm.registers.F[instr->r1] !=
           (DLX_FLOAT)dlx_vm.registers.F[instr->r2])
              ? 1
              : 0;
      break;

    case LTF:
      dlx_vm.registers.FPSR =
          ((DLX_FLOAT)dlx_vm.registers.F[instr->r1] <
           (DLX_FLOAT)dlx_vm.registers.F[instr->r2])
              ? 1
              : 0;
      break;

    case GTF:
      dlx_vm.registers.FPSR =
          ((DLX_FLOAT)dlx_vm.registers.F[instr->r1] >
           (DLX_FLOAT)dlx_vm.registers.F[instr->r2])
              ? 1
              : 0;
      break;

    case LEF:
      dlx_vm.registers.FPSR =
          ((DLX_FLOAT)dlx_vm.registers.F[instr->r1] <=
           (DLX_FLOAT)dlx_vm.registers.F[instr->r2])
              ? 1
              : 0;
      break;

    case GEF:
      dlx_vm.registers.FPSR =
          ((DLX_FLOAT)dlx_vm.registers.F[instr->r1] >=
           (DLX_FLOAT)dlx_vm.registers.F[instr->r2])
              ? 1
              : 0;
      break;

    case MULTU:
      dlx_vm.registers.R[instr->rd] =
          (DLX_UWORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] *
                      (DLX_UWORD)dlx_vm.registers.R[instr->r2]);
      break;

    case DIVU:
      dlx_vm.registers.R[instr->rd] =
          (DLX_UWORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] /
                      (DLX_UWORD)dlx_vm.registers.R[instr->r2]);
      break;

    case EQD:
      dlx_vm.registers.FPSR =
          (*((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)) ==
           *((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)))
              ? 1
              : 0;
      break;

    case NED:
      dlx_vm.registers.FPSR =
          (*((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)) !=
           *((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)))
              ? 1
              : 0;
      break;

    case LTD:
      dlx_vm.registers.FPSR =
          (*((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)) <
           *((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)))
              ? 1
              : 0;
      break;

    case GTD:
      dlx_vm.registers.FPSR =
          (*((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)) >
           *((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)))
              ? 1
              : 0;
      break;

    case LED:
      dlx_vm.registers.FPSR =
          (*((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)) <=
           *((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)))
              ? 1
              : 0;
      break;

    case GED:
      dlx_vm.registers.FPSR =
          (*((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)) >=
           *((DLX_DOUBLE *)(dlx_vm.registers.F + instr->r1)))
              ? 1
              : 0;
      break;
    }
    break; //-- FP Arithm --//

  case ISPECIAL:
    switch (instr->fAlu)
    {
    case NOP:
      break;

    case SLL:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] << (DLX_WORD)dlx_vm.registers.R[instr->r2]);
      break;

    case SRL:
      dlx_vm.registers.R[instr->rd] =
          (DLX_UWORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] >>
                      (DLX_UWORD)dlx_vm.registers.R[instr->r2]);
      break;

    case SRA:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] >>
                     (DLX_WORD)dlx_vm.registers.R[instr->r2]);
      break;

    case SEQU:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] ==
                     (DLX_UWORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case SNEU:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] !=
                     (DLX_UWORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case SLTU:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] <
                     (DLX_UWORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case SGTU:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] >
                     (DLX_UWORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case SLEU:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] <=
                     (DLX_UWORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case SGEU:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] >=
                     (DLX_UWORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case ADD:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                     (DLX_WORD)dlx_vm.registers.R[instr->r2]);
      break;

    case ADDU:
      dlx_vm.registers.R[instr->rd] =
          (DLX_UWORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] +
                      (DLX_UWORD)dlx_vm.registers.R[instr->r2]);
      break;

    case SUB:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] -
                     (DLX_WORD)dlx_vm.registers.R[instr->r2]);
      break;

    case SUBU:
      dlx_vm.registers.R[instr->rd] =
          (DLX_UWORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] -
                      (DLX_UWORD)dlx_vm.registers.R[instr->r2]);
      break;

    case AND:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] &
                     (DLX_WORD)dlx_vm.registers.R[instr->r2]);
      break;

    case OR:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] |
                     (DLX_WORD)dlx_vm.registers.R[instr->r2]);
      break;

    case XOR:
      dlx_vm.registers.R[instr->rd] =
          (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] ^
                     (DLX_WORD)dlx_vm.registers.R[instr->r2]);
      break;

    case SEQ:
      dlx_vm.registers.R[instr->rd] =
          ((DLX_WORD)dlx_vm.registers.R[instr->r1] ==
           (DLX_WORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case SNE:
      dlx_vm.registers.R[instr->rd] =
          ((DLX_WORD)dlx_vm.registers.R[instr->r1] !=
           (DLX_WORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case SLT:
      dlx_vm.registers.R[instr->rd] =
          ((DLX_WORD)dlx_vm.registers.R[instr->r1] <
           (DLX_WORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case SGT:
      dlx_vm.registers.R[instr->rd] =
          ((DLX_WORD)dlx_vm.registers.R[instr->r1] >
           (DLX_WORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case SLE:
      dlx_vm.registers.R[instr->rd] =
          ((DLX_WORD)dlx_vm.registers.R[instr->r1] <=
           (DLX_WORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case SGE:
      dlx_vm.registers.R[instr->rd] =
          ((DLX_WORD)dlx_vm.registers.R[instr->r1] >=
           (DLX_WORD)dlx_vm.registers.R[instr->r2])
              ? 1
              : 0;
      break;

    case MOVI2S:
      break;

    case MOVS2I:
      break;

    case MOVF:
      break;

    case MOVD:
      break;

    case MOVFP2I:
      break;

    case MOVI2FP:
      break;
    }
    break; //-- Special --//

  case J:
    dlx_vm.registers.NPC = dlx_vm.registers.PC + instr->imm;
    if ((dlx_vm.branch_delay_slots_count = dlx_vm.branch_delay_slots) == 0)
      dlx_vm.registers.PC = dlx_vm.registers.NPC;
    break;

  case JAL:
    dlx_vm.registers.R[31] = dlx_vm.registers.PC;
    dlx_vm.registers.NPC = dlx_vm.registers.PC + instr->imm;
    if ((dlx_vm.branch_delay_slots_count = dlx_vm.branch_delay_slots) == 0)
      dlx_vm.registers.PC = dlx_vm.registers.NPC;
    break;

  case BEQZ:
    if (dlx_vm.registers.R[instr->r1] == 0)
    {
      dlx_vm.registers.NPC = dlx_vm.registers.PC + instr->imm;
      if ((dlx_vm.branch_delay_slots_count = dlx_vm.branch_delay_slots) == 0)
        dlx_vm.registers.PC = dlx_vm.registers.NPC;
    }
    break;

  case BNEZ:
    if (dlx_vm.registers.R[instr->r1] != 0)
    {
      dlx_vm.registers.NPC = dlx_vm.registers.PC + instr->imm;
      if ((dlx_vm.branch_delay_slots_count = dlx_vm.branch_delay_slots) == 0)
        dlx_vm.registers.PC = dlx_vm.registers.NPC;
    }
    break;

  case BFPT:
    if (dlx_vm.registers.FPSR == 1)
    {
      dlx_vm.registers.NPC = dlx_vm.registers.PC + instr->imm;
      if ((dlx_vm.branch_delay_slots_count = dlx_vm.branch_delay_slots) == 0)
        dlx_vm.registers.PC = dlx_vm.registers.NPC;
    }
    break;

  case BFPF:
    if (dlx_vm.registers.FPSR == 0)
    {
      dlx_vm.registers.NPC = dlx_vm.registers.PC + instr->imm;
      if ((dlx_vm.branch_delay_slots_count = dlx_vm.branch_delay_slots) == 0)
        dlx_vm.registers.PC = dlx_vm.registers.NPC;
    }
    break;

  case ADDI:
    dlx_vm.registers.R[instr->rd] =
        (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                   (DLX_WORD)instr->imm);
    break;

  case ADDUI:
    dlx_vm.registers.R[instr->rd] =
        (DLX_UWORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] +
                    (DLX_UWORD)instr->imm);
    break;

  case SUBI:
    dlx_vm.registers.R[instr->rd] =
        (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] -
                   (DLX_WORD)instr->imm);
    break;

  case SUBUI:
    dlx_vm.registers.R[instr->rd] =
        (DLX_UWORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] -
                    (DLX_UWORD)instr->imm);
    break;

  case ANDI:
    dlx_vm.registers.R[instr->rd] =
        (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] &
                   (DLX_WORD)instr->imm);
    break;

  case ORI:
    dlx_vm.registers.R[instr->rd] =
        (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] |
                   (DLX_WORD)instr->imm);
    break;

  case XORI:
    dlx_vm.registers.R[instr->rd] =
        (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] ^
                   (DLX_WORD)instr->imm);
    break;

  case LHI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_WORD)instr->imm) << 16;
    break;

  case RFE:
    break;

  case TRAP:
    dlx_vm.registers.IAR = dlx_vm.registers.PC;
    dlx_vm.registers.PC = (DLX_WORD)instr->name;
    // printf("Program exited normally.\n");
    return 1;

  case JR:
    dlx_vm.registers.PC = dlx_vm.registers.R[instr->r1];
    break;

  case JALR:
    dlx_vm.registers.R[31] = dlx_vm.registers.PC;
    dlx_vm.registers.PC = dlx_vm.registers.R[instr->r1];
    break;

  case SLLI:
    dlx_vm.registers.R[instr->rd] =
        (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] << (DLX_WORD)instr->imm);
    break;

  case SRLI:
    dlx_vm.registers.R[instr->rd] =
        (DLX_UWORD)((DLX_UWORD)dlx_vm.registers.R[instr->r1] >>
                    (DLX_UWORD)instr->imm);
    break;

  case SRAI:
    dlx_vm.registers.R[instr->rd] =
        (DLX_WORD)((DLX_WORD)dlx_vm.registers.R[instr->r1] >>
                   (DLX_WORD)instr->imm);
    break;

  case SEQI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_WORD)dlx_vm.registers.R[instr->r1] ==
         (DLX_WORD)instr->imm)
            ? 1
            : 0;
    break;

  case SNEI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_WORD)dlx_vm.registers.R[instr->r1] !=
         (DLX_WORD)instr->imm)
            ? 1
            : 0;
    break;

  case SLTI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_WORD)dlx_vm.registers.R[instr->r1] <
         (DLX_WORD)instr->imm)
            ? 1
            : 0;
    break;

  case SGTI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_WORD)dlx_vm.registers.R[instr->r1] <
         (DLX_WORD)instr->imm)
            ? 1
            : 0;
    break;

  case SLEI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_WORD)dlx_vm.registers.R[instr->r1] <=
         (DLX_WORD)instr->imm)
            ? 1
            : 0;
    break;

  case SGEI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_WORD)dlx_vm.registers.R[instr->r1] >=
         (DLX_WORD)instr->imm)
            ? 1
            : 0;
    break;

  case LB:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        1))
      return 1;
    dlx_vm.registers.R[instr->rd] = (DLX_BYTE)
        LOAD_BYTE_TO_BYTE(dlx_vm.data +
                          (DLX_WORD)dlx_vm.registers.R[instr->r1] +
                          (DLX_WORD)instr->imm);
    break;

  case LH:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        2))
      return 1;

    dlx_vm.registers.R[instr->rd] = (DLX_HALFWORD)
        LOAD_BYTE_TO_SHORT(dlx_vm.data +
                           (DLX_WORD)dlx_vm.registers.R[instr->r1] +
                           (DLX_WORD)instr->imm);
    break;

  case LW:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        4))
      return 1;
    dlx_vm.registers.R[instr->rd] = (DLX_WORD)
        LOAD_BYTE_TO_WORD(dlx_vm.data +
                          (DLX_WORD)dlx_vm.registers.R[instr->r1] +
                          (DLX_WORD)instr->imm);
    break;

  case LBU:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        1))
      return 1;

    dlx_vm.registers.R[instr->rd] = (DLX_UBYTE)
        LOAD_BYTE_TO_BYTE(dlx_vm.data +
                          (DLX_WORD)dlx_vm.registers.R[instr->r1] +
                          (DLX_WORD)instr->imm);
    break;

  case LHU:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        2))
      return 1;

    dlx_vm.registers.R[instr->rd] = (DLX_USHORT)
        LOAD_BYTE_TO_SHORT(dlx_vm.data +
                           (DLX_WORD)dlx_vm.registers.R[instr->r1] +
                           (DLX_WORD)instr->imm);
    break;

  case LF:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        4))
      return 1;

    dlx_vm.registers.F[instr->rd] =
        (DLX_FLOAT) * ((DLX_FLOAT *)(dlx_vm.data +
                                     (DLX_WORD)dlx_vm.registers.R[instr->r1] +
                                     (DLX_WORD)instr->imm));
    break;

  case LD:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        8))
      return 1;

    *((DLX_DOUBLE *)dlx_vm.registers.F + instr->rd) =
        (DLX_DOUBLE) * ((DLX_DOUBLE *)(dlx_vm.data +
                                       (DLX_WORD)dlx_vm.registers.R[instr->r1] +
                                       (DLX_WORD)instr->imm));
    break;

  case SB:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        1))
      return 1;

    STORE_BYTE_TO_BYTE(dlx_vm.data + instr->imm +
                           dlx_vm.registers.R[instr->r1],
                       dlx_vm.registers.R[instr->rd]);
    break;

  case SH:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        2))
      return 1;

    STORE_SHORT_TO_BYTE(dlx_vm.data + instr->imm +
                            dlx_vm.registers.R[instr->r1],
                        dlx_vm.registers.R[instr->rd]);
    break;

  case SW:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        4))
      return 1;

    STORE_WORD_TO_BYTE(dlx_vm.data + instr->imm +
                           dlx_vm.registers.R[instr->r1],
                       dlx_vm.registers.R[instr->rd]);
    break;

  case SF:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        4))
      return 1;

    *((DLX_FLOAT *)(dlx_vm.data + instr->imm +
                    dlx_vm.registers.R[instr->r1])) =
        dlx_vm.registers.F[instr->rd];
    break;

  case SD:
    if (vm_memory_check((DLX_WORD)dlx_vm.registers.R[instr->r1] +
                            (DLX_WORD)instr->imm,
                        8))
      return 1;

    *((DLX_DOUBLE *)(dlx_vm.data + instr->imm +
                     dlx_vm.registers.R[instr->r1])) =
        *((DLX_DOUBLE *)(dlx_vm.registers.F + instr->rd));
    break;

  case SEQUI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_UWORD)dlx_vm.registers.R[instr->r1] ==
         (DLX_UWORD)instr->imm)
            ? 1
            : 0;
    break;

  case SNEUI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_UWORD)dlx_vm.registers.R[instr->r1] !=
         (DLX_UWORD)instr->imm)
            ? 1
            : 0;
    break;

  case SLTUI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_UWORD)dlx_vm.registers.R[instr->r1] <
         (DLX_UWORD)instr->imm)
            ? 1
            : 0;
    break;

  case SGTUI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_UWORD)dlx_vm.registers.R[instr->r1] >
         (DLX_UWORD)instr->imm)
            ? 1
            : 0;
    break;

  case SLEUI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_UWORD)dlx_vm.registers.R[instr->r1] <=
         (DLX_UWORD)instr->imm)
            ? 1
            : 0;
    break;

  case SGEUI:
    dlx_vm.registers.R[instr->rd] =
        ((DLX_UWORD)dlx_vm.registers.R[instr->r1] >=
         (DLX_UWORD)instr->imm)
            ? 1
            : 0;
    break;
  }

  return 0;
}

int vm_internal_run(int length)
{
  unsigned int i;
  int loop = length;
  int res;
  int bypass_breakpoint = 1;

  dlx_instr_decode instr;
  debug_println("DLX Virtual Machine run code...");
  debug_indent(2);

  if (dlx_vm.breakpoints[dlx_vm.registers.PC])
    bypass_breakpoint = 1;

  if (dlx_vm.trace && (length > 1 || length == -1))
  {
    printf("[");
  }
  for (i = 0; i < length || loop == -1; i++)
  {

    //-- Fetch --//
    vm_debug_println(3, "run fetch");
    if (vm_internal_fetch(dlx_vm.registers.PC, &instr))
    {
      printf("Memory trap on code segment. (at %X)\n", dlx_vm.registers.PC);
      break;
    }

    //-- Decode --//
    vm_debug_println(3, "run decode.");
    vm_internal_decode(&instr);

    //-- Print --//
    vm_debug_println(3, "run print.");
    if (dlx_vm.trace)
    {
      vm_internal_print_instr(dlx_vm.registers.PC, &instr, dlx_vm.code_length, length);
    }

    //-- Breakpoint check --//
    if (dlx_vm.breakpoints[dlx_vm.registers.PC] && bypass_breakpoint == 0)
    {
      printf("Breakpoint at %04X\n", dlx_vm.registers.PC);
      break;
    }
    else
      bypass_breakpoint = 0;

    dlx_vm.registers.PC = dlx_vm.registers.PC + 4;

    //-- Execute --//
    if (dlx_vm.branch_delay_slots_count == 0)
    {
      res = vm_internal_execute(&instr);
      if (res)
        break;
    }
    else
    {
      res = vm_internal_execute(&instr);
      if ((--dlx_vm.branch_delay_slots_count) == 0)
        dlx_vm.registers.PC = dlx_vm.registers.NPC;
      if (res)
        break;
    }
  }
  debug_indent(-2);
  if (dlx_vm.trace && (length > 1 || length == -1))
  {
    printf("]\n");
  }
  return 1;
}

int vm_disassemble(DLX_UWORD start, DLX_WORD length)
{
  unsigned int i;
  int loop = length;
  dlx_instr_decode instr;

  debug_println("DLX Virtual Machine disassemble code...");
  debug_indent(2);

  printf("[");
  for (i = 0; i < length || loop < 0; i++)
  {
    if (start + i * 4 >= dlx_vm.code_length)
      break;
    //-- Fetch --//
    vm_debug_println(3, "disassemble fetch.");
    vm_internal_fetch((i * 4) + start, &instr);

    //-- Decode --//
    vm_debug_println(3, "disassemble decode.");
    vm_internal_decode(&instr);

    //-- Print --//
    vm_debug_println(3, "disassemble print.");
    if (dlx_vm.breakpoints[(i * 4) + start])
      printf("<!>");
    vm_internal_print_instr(i * 4 + start, &instr, dlx_vm.code_length, __INT_MAX__);
  }
  printf("]\n");
  debug_indent(-2);
  return 1;
}

int vm_step()
{
  vm_debug_println(1, "Step");
  vm_internal_run(1);
  return 1;
}

int vm_run(int length)
{
  vm_debug_println(1, "run");
  vm_internal_run(length);
  return 1;
}