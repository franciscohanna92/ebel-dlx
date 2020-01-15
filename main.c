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

#include "asm/dlxasm.h"
#include "sim/dlxsim.h"
#include "vm/dlxvm.h"

void version()
{
  printf("\n== DLX System version 1.0.3 ==\n");
  vm_version();
  asm_version();
  sim_version();
  printf("by Etienne Bergeron and Eric Lesage\n\n");
}

int main(int argc, char **argv)
{
  version();
  vm_init();
  sim_init();
  sim_run();
  sim_done();

  return 0;
}
