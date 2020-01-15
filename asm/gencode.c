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
#include "../lib/dlxtypes.h"
#include "gencode.h"

#define SEGMENT_CODE 1
#define SEGMENT_DATA 2

DLX_BYTE *mem_code;
DLX_BYTE *mem_data;
int mem_code_length;
int mem_data_length;

void asm_gencode_allocate_memory(Node *node)
{
  Node *n;
  int segment = SEGMENT_CODE;
  int code_max_offset, data_max_offset;
  int offset = 0;
  int data_length;
  mem_code_length = 0;
  mem_data_length = 0;
  code_max_offset = data_max_offset = 0;

  while (node != NULL)
  {

    switch (node->type)
    {
    case A_CMDDATA:
      n = node->param[0];
      data_length = node->param[1]->value;
      while (n != NULL)
      {
        offset += data_length;
        n = n->next;
      }
      break;

    case A_CMDORG:
      if (strcasecmp(node->identifier, "code") == 0)
        segment = SEGMENT_CODE;
      else
        segment = SEGMENT_DATA;

      offset = node->param[0]->value;
      break;

    case A_INSTR:
      offset += 4;
      break;

    default:
      break;
    }

    if (segment == SEGMENT_CODE && code_max_offset < offset)
      code_max_offset = offset;
    if (segment == SEGMENT_DATA && data_max_offset < offset)
      data_max_offset = offset;

    node = node->next;
  }

  mem_code_length = code_max_offset;
  mem_data_length = data_max_offset;
  mem_code = (DLX_BYTE *)malloc(sizeof(DLX_BYTE) * (mem_code_length + mem_data_length));
  memset(mem_code, 0, mem_code_length + mem_data_length);

  if (mem_data_length > 0)
  {
    mem_data = mem_code + mem_code_length;
  }
  else
  {
    mem_data = mem_code;
    mem_data_length = mem_code_length;
  }
}

void asm_gencode_build_memory(Node *node)
{
  Node *n;
  DLX_BYTE *ptr = mem_code;
  int res;
  int data_length;

  ptr = mem_code;

  while (node != NULL)
  {
    switch (node->type)
    {
    case A_CMDDATA:
      n = node->param[0];
      data_length = node->param[1]->value;

      while (n != NULL)
      {
        if (n->type == A_VALUE)
          n->fvalue = n->value;
        if (n->type == A_FVALUE)
          n->value = n->fvalue;

        switch (asm_data_type_fixnum(node->param[1]->identifier))
        {
        case 1:
          STORE_BYTE_TO_BYTE(ptr, n->value);
          break;
        case 2:
          STORE_SHORT_TO_BYTE(ptr, n->value);
          break;
        case 4:
          STORE_INT_TO_BYTE(ptr, n->value);
          break;
        case 8:
          STORE_LONG_TO_BYTE(ptr, n->value);
          break;
        }
        switch (asm_data_type_flonum(node->param[1]->identifier))
        {
        case 4:
          STORE_FLOAT_TO_BYTE(ptr, n->fvalue);
          break;
        case 8:
          STORE_DOUBLE_TO_BYTE(ptr, n->fvalue);
          break;
        }
        ptr += data_length;
        n = n->next;
      }
      break;

    case A_CMDORG:
      if (strcasecmp(node->identifier, "code") == 0)
        ptr = mem_code + node->param[0]->value;
      else
        ptr = mem_data + node->param[0]->value;
      break;

    case A_INSTR:
      res = 0;

      res |= node->instr->opcode_value;

      switch (node->instr->format)
      {
      case FORMAT_R:
        if (node->param[0] != NULL)
          res |= ((node->param[0]->value) << 11);
        if (node->param[1] != NULL)
          res |= ((node->param[1]->value) << 21);
        if (node->param[2] != NULL)
          res |= ((node->param[2]->value) << 16);
        break;

      case FORMAT_J:
        if (node->param[2] != NULL)
          res |= (node->param[2]->value & 0x03FFFFFF);
        break;

      case FORMAT_I:
        if (node->param[0] != NULL)
          res |= (node->param[0]->value) << 16;
        if (node->param[1] != NULL)
          res |= (node->param[1]->value) << 21;
        if (node->param[2] != NULL)
          res |= ((node->param[2]->value) & 0xFFFF);
        break;
      }
      /*printf("res: %08X\n", res );*/
      STORE_INT_TO_BYTE(ptr, res);
      ptr += 4;
      break;
    }
    node = node->next;
  }
}

void asm_gencode_vhdl(FILE *dest)
{
  int i;
  fprintf(dest, "-- CODE\n");
  fprintf(dest, "( ");
  for (i = 0; i < mem_code_length; i += 4)
  {
    if (i != mem_code_length - 4)
      fprintf(dest, "X\"%08X\",\n", LOAD_BYTE_TO_INT(mem_code + i));
    else
      fprintf(dest, "X\"%08X\" )\n", LOAD_BYTE_TO_INT(mem_code + i));
  }

  if (mem_data != mem_code)
  {
    if (mem_data_length > 0)
    {
      fprintf(dest, "-- DATA\n");
      fprintf(dest, "( ");
      for (i = 0; i < mem_data_length; i++)
      {
        if (i != mem_data_length - 1)
          fprintf(dest, "X\"%08X\",\n", LOAD_BYTE_TO_INT(mem_data + i));
        else
          fprintf(dest, "X\"%08X\" )\n", LOAD_BYTE_TO_INT(mem_data + i));
      }
    }
  }
}

void asm_gencode_raw(FILE *dest)
{
  int i;
  for (i = 0; i < mem_code_length; i++)
    fprintf(dest, "%c", mem_code[i]);
  if (mem_data != mem_code)
    for (i = 0; i < mem_data_length; i++)
      fprintf(dest, "%c", mem_data[i]);
}

void asm_gencode_hex(FILE *dest)
{
  int i;
  for (i = 0; i < mem_code_length; i++)
    fprintf(dest, "%02X", mem_code[i] & 255);
  if (mem_data != mem_code)
    for (i = 0; i < mem_data_length; i++)
      fprintf(dest, "%02X", mem_data[i] & 255);
}

void asm_gencode_tree(asm_info_t *a, Node *node, GenType type)
{
  asm_gencode_allocate_memory(node);
  asm_gencode_build_memory(node);

  /*
  switch( type ) {
    case GEN_VHDL: asm_gencode_vhdl(stdout); break;
    case GEN_RAW:  asm_gencode_raw(stdout); break;
    case GEN_HEX:  asm_gencode_hex(stdout); break;
  }
  */

  a->code_length = mem_code_length;
  a->data_length = mem_data_length;
  a->code = mem_code;
  a->data = mem_data;
};
