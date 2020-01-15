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

#include "dlxdebug.h"
#include <stdarg.h>
#include <stdio.h>

#ifdef DEBUG

int debug_indent_counter = 0;

void debug_indent(int i)
{
#ifndef NODEBUGINDENT
  debug_indent_counter += i;
#endif
}

void debug_indent_print()
{
  int i;
  for (i = 0; i < debug_indent_counter; i++)
    printf(" ");
}

void vm_debug_println(int level, char *txt, ...)
{
#ifdef VM_DEBUG
  va_list ap;
  va_start(ap, txt);

  if (level < VM_DEBUG_LEVEL)
  {
    debug_indent_print();
    printf("DVM:");
    vprintf(txt, ap);
    printf("\n");
  }

  va_end(ap);
#endif
}

void sim_debug_println(int level, char *txt, ...)
{
#ifdef SIM_DEBUG
  va_list ap;
  va_start(ap, txt);

  if (level < SIM_DEBUG_LEVEL)
  {
    debug_indent_print();
    printf("SIM:");
    vprintf(txt, ap);
    printf("\n");
  }

  va_end(ap);
#endif
}

void asm_debug_println(int level, char *txt, ...)
{
#ifdef ASM_DEBUG
  va_list ap;
  va_start(ap, txt);

  if (level < ASM_DEBUG_LEVEL)
  {
    debug_indent_print();
    printf("ASM:");
    vprintf(txt, ap);
    printf("\n");
  }
  va_end(ap);
#endif
}

void debug_println(char *txt, ...)
{
  va_list ap;
  va_start(ap, txt);

  debug_indent_print();
  printf("DBG:");
  vprintf(txt, ap);
  printf("\n");

  va_end(ap);
}

#endif
