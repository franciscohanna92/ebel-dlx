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
#include <stdlib.h>
#include "../lib/dlxdebug.h"
#include "../asm/dlxasm.h"
#include "../vm/dlxvm.h"
#include "../asm/gencode.h"
#include <readline/readline.h>
#include <readline/history.h>

#define true 1
#define false 0

void sim_version()
{
  printf("EBEL DLX Simulator 1.0\n");
}

void sim_init()
{
  /* Initialize the readline library */
  rl_initialize();
}

#define SIM_CMDUNKNOWN 0 /* Must be 0 */
#define SIM_CMDQUIT 1
#define SIM_CMDHELP 2
#define SIM_CMDLOAD 3
#define SIM_CMDSAVE 4
#define SIM_CMDSTEP 5
#define SIM_CMDRUN 6
#define SIM_CMDNEXT 7
#define SIM_CMDINSPECT 8
#define SIM_CMDDISASSEMBLE 9
#define SIM_CMDDUMP 10
#define SIM_CMDBREAK 11
#define SIM_CMDUNBREAK 12
#define SIM_CMDSYMBOLS 13
#define SIM_CMDTREE 14
#define SIM_CMDSETSLOTS 15
#define SIM_CMDTRACE 16
#define SIM_CMDUNTRACE 17
#define SIM_CMDRESET 18

#define streq(_a, _b) (!strcasecmp((_a), (_b)))
int sim_help(char *command)
{
  {
    printf("DLX Simulator General Help\n"
           "\n"
           "The following commands are available:\n"
           "load <filename>    - Loads and compile an assembler program\n"
           "run                - Runs the loaded program up to a TRAP\n"
           "step [<number>]    - Runs the specified number of instructions\n"
           "save <format> <filename> - Save the compiled program in\n"
           "                           the specified format\n"
           "inspect [register] - Inspects the value of all or specified reg\n"
           "disassemble [<start> [<length>]] - Disassemble the memory content for the\n"
           "                                   specified location and data length\n"
           "dump [<start> [<length>]]        - Dumps the memory content to the screen for\n"
           "                                   the specified location and data length\n"
           "break <symbol>     - Adds a breakpoint at the address of the symbol value\n"
           "unbreak <symbol>   - Removes a breakpoint at the address of the symbol value\n"
           "symbols [<symbol>] - Show symbol value/lists all symbols.\n"
           "set-slots <number> - Sets the number of branch delay slots to be used\n"
           "tree               - Shows the parse tree\n"
           "quit               - Quits the simulator\n"
           "trace              - Enables printing information on code being executed\n"
           "untrace            - Disables printing information on code being executed\n"
           "reset              - Resets the execution environment, just as if the program\n"
           "                     being executed had been loaded anew\n"
           "\n"
           "Available formats for save:\n"
           " * b - Binary\n"
           " * h - Hexadecimal array\n"
           " * v - VHDL array\n");
  }
}

int sim_save(char *mode_and_file)
{
  char *mode_token = strsep(&mode_and_file, "\t\n\v ");
  char *file_token = strsep(&mode_and_file, "\t\n\v ");
  FILE *dest;
  if (!mode_token)
  {
    printf("Mode not specified -- must be one of b, v, c or d");
    return 0;
  }
  else if (!file_token)
  {
    printf("Filename not specified");
    return 0;
  }

  dest = fopen(file_token, "wb");
  if (!dest)
  {
    perror("Can't open file for writing");
  }
  else
  {
    switch (mode_token[0])
    {
    case 'b':
    case 'B':
      asm_gencode_raw(dest);
      break;
    case 'v':
    case 'V':
      asm_gencode_vhdl(dest);
      break;
    case 'h':
    case 'H':
      asm_gencode_hex(dest);
      break;
    }
    fclose(dest);
  }
}

int sim_inspect(char *reg)
{
  char *register_token = strsep(&reg, "\t\n\v ");
  if (!register_token)
  {
    /* Print out all registers */
    vm_print_registers();
  }
  else
  {
    int rlen = strlen(register_token);
    int rtype = 0;
    if (rlen > 4)
    {
      printf("Invalid register name '%s'\n", register_token);
    }
    else
    {
      switch (register_token[0])
      {
      case 'r':
      case 'R':
        rtype = 1;
        break;

      case 'f':
      case 'F':
        rtype = 2;
        break;

      case 'p':
      case 'P':
        rtype = 3;
        break;

      case 'i':
      case 'I':
        rtype = 4;
        break;
      }
      {
        int r_index = 0;
        DLX_INT i_val = 0;
        DLX_FLOAT f_val = 0;
        switch (rtype)
        {

        case 0:
          printf("Invalid register name '%s'\n", register_token);
          break;
        case 1:
        case 2:
          if (streq("fpsr", register_token))
          {
            i_val = dlx_vm.registers.PC;
            printf("FPSR = %u\n", i_val);
            return 0;
          }
          if ((register_token[1] >= '0' && register_token[1] <= '9') && ((register_token[2] >= '0' && register_token[2] <= '9' && register_token[3] == 0) || register_token[2] == 0))
          {
            r_index = register_token[1] - '0';
            if (register_token[2])
            {
              r_index = 10 * r_index + register_token[2] - '0';
            }
            if (r_index < 32)
            {
              if (rtype == 1)
              {
                i_val = dlx_vm.registers.R[r_index];
                printf("R%d = %d %u 0%o 0x%08x\n", r_index, i_val, i_val, i_val, i_val);
              }
              else
              {
                f_val = dlx_vm.registers.F[r_index];
                printf("F%d = %f %f 0%f 0x%08f\n", r_index, f_val, f_val, f_val, f_val);
              }
            }
            else
            {
              printf("Register out of range (%d)\n", r_index);
            }
          }
          else
          {
            printf("Invalid register name '%s'\n", register_token);
          }
          break;
        case 3:
          if (streq("pc", register_token))
          {
            i_val = dlx_vm.registers.PC;
            printf("PC = %i %u 0%o 0x%08x\n", i_val, i_val, i_val, i_val);
          }
          else
          {
            printf("Invalid register name\n");
          }
          break;
        case 4:
          if (streq("iar", register_token))
          {
            i_val = dlx_vm.registers.PC;
            printf("IAR = %u 0%o 0x%08x\n", i_val, i_val, i_val);
          }
          else
          {
            printf("Invalid register name '%s'\n", register_token);
          }
          break;
        }
      }
    }
  }
}

int sim_disasm_or_dump(char *start_and_length, int dump)
{
  char *start_token = strsep(&start_and_length, "\t\n\v ");
  char *length_token = strsep(&start_and_length, "\t\n\v ");
  DLX_UINT start = 0;
  DLX_INT length = -1;
  if (start_token)
  {
    char *endptr;
    start = strtol(start_token, &endptr, 0);
    if (endptr == start_token)
    {
      printf("Invalid start position\n");
      return 0;
    }
    else
    {
      if (length_token)
      {
        length = strtol(length_token, &endptr, 0);
        if (endptr == start_token)
        {
          printf("Invalid length\n");
          return 0;
        }
      }
    }
  }

  if (dump)
  {
    vm_print_memory(start, length);
  }
  else
  {
    vm_disassemble(start, length);
  }
}

int sim_command(char *command, char **remainder)
{
  char *token;
  if (!command)
    return SIM_CMDUNKNOWN;
  token = strsep(&command, "\t\n\v ");
  *remainder = command;
  if (streq(token, "quit"))
    return SIM_CMDQUIT;
  if (streq(token, "q"))
    return SIM_CMDQUIT;
  if (streq(token, "exit"))
    return SIM_CMDQUIT;
  if (streq(token, "help"))
    return SIM_CMDHELP;
  if (streq(token, "h"))
    return SIM_CMDHELP;
  if (streq(token, "?"))
    return SIM_CMDHELP;
  if (streq(token, "load"))
    return SIM_CMDLOAD;
  if (streq(token, "save"))
    return SIM_CMDSAVE;
  if (streq(token, "step"))
    return SIM_CMDSTEP;
  if (streq(token, "s"))
    return SIM_CMDSTEP;
  if (streq(token, "run"))
    return SIM_CMDRUN;
  if (streq(token, "r"))
    return SIM_CMDRUN;
  if (streq(token, "inspect"))
    return SIM_CMDINSPECT;
  if (streq(token, "i"))
    return SIM_CMDINSPECT;
  if (streq(token, "disassemble"))
    return SIM_CMDDISASSEMBLE;
  if (streq(token, "dasm"))
    return SIM_CMDDISASSEMBLE;
  if (streq(token, "dump"))
    return SIM_CMDDUMP;
  if (streq(token, "d"))
    return SIM_CMDDUMP;
  if (streq(token, "break"))
    return SIM_CMDBREAK;
  if (streq(token, "unbreak"))
    return SIM_CMDUNBREAK;
  if (streq(token, "symbols"))
    return SIM_CMDSYMBOLS;
  if (streq(token, "set-slots"))
    return SIM_CMDSETSLOTS;
  if (streq(token, "tree"))
    return SIM_CMDTREE;
  if (streq(token, "trace"))
    return SIM_CMDTRACE;
  if (streq(token, "untrace"))
    return SIM_CMDUNTRACE;
  if (streq(token, "reset"))
    return SIM_CMDRESET;
  return SIM_CMDUNKNOWN;
}

void sim_run()
{
  int quit = 0; /* Quit now? */
  int in_fd = -1;
  int code_loaded = 0; /* Is there code loaded? */
  asm_info_t *asm_result = NULL;
  char *in;
  while (!quit && (in = readline("DLX>")))
  {
    int command_code = 0;
    char *out;
    char *histbuff = strdup(in);
    if (command_code = sim_command(in, &out))
    {
      add_history(histbuff);

      switch (command_code)
      {
      case SIM_CMDQUIT:
        quit = 1;
        break;
      case SIM_CMDHELP:
        sim_help(out);
        break;

      case SIM_CMDLOAD:
        if (asm_result)
          asm_destroy_asm_info(asm_result);
        asm_result = asm_create_asm_info();
        asm_compile_file(asm_result, out);
        if (!asm_result->success)
        {
          printf("Trying to compile %s\n", out);
          /* Error treatment */
          printf("Error loading file %s\n", out);
        }
        else
        {
          code_loaded = true;
          vm_reset();
          vm_load(asm_result->code,
                  asm_result->code_length + asm_result->data_length,
                  asm_result->code,
                  asm_result->code_length,
                  asm_result->data,
                  asm_result->data_length,
                  asm_result->symbols);
          /* Print out some information about the compilation */
          printf("Code length: %d; Data length: %d\n",
                 asm_result->code_length, asm_result->data_length);
        }

        break;

      /* Save the binary code */
      case SIM_CMDSAVE:
        if (code_loaded)
        {
          if (out)
          {
            printf("Saving in %s...\n", out);
            sim_save(out);
          }
          else
          {
            printf("Target filename not specified\n");
          }
        }
        else
        {
          printf("Can't save, no code loaded\n");
        }
        break;

      case SIM_CMDSTEP:
        if (code_loaded)
        {
          char *endptr = NULL;
          if (!out)
          {
            vm_step();
          }
          else
          {
            long steps = strtol(out, &endptr, 0);
            if (endptr && endptr != out && steps > 0)
            {
              vm_run(steps);
            }
            else
            {
              printf("Invalid step length\n");
            }
          }
        }
        else
        {
          printf("Can't step, no code loaded\n");
        }
        break;

      case SIM_CMDRUN:
        if (code_loaded)
        {
          vm_run(-1);
        }
        else
        {
          printf("Can't run, no code loaded\n");
        }
        break;

      case SIM_CMDINSPECT:
        if (code_loaded)
        {
          sim_inspect(out);
        }
        else
        {
          printf("Can't inspect, no code loaded\n");
        }
        break;
      case SIM_CMDDISASSEMBLE:
        if (code_loaded)
        {
          sim_disasm_or_dump(out, 0);
        }
        else
        {
          printf("Can't dump memory, no code loaded\n");
        }
        break;
      case SIM_CMDDUMP:
        if (code_loaded)
        {
          sim_disasm_or_dump(out, 1);
        }
        else
        {
          printf("Can't disassemble, no code loaded\n");
        }
        break;
      case SIM_CMDBREAK:
        if (code_loaded)
        {
          vm_set_breakpoint(out);
        }
        else
        {
          printf("Can't set breakpoint, no code loaded\n");
        }
        break;
      case SIM_CMDUNBREAK:
        if (code_loaded)
        {
          vm_unset_breakpoint(out);
        }
        else
        {
          printf("Can't unset breakpoint, no code loaded\n");
        }
        break;
      case SIM_CMDSYMBOLS:
        if (code_loaded)
        {
          vm_print_symbols(out);
        }
        else
        {
          printf("Can't print symbols, no code loaded\n");
        }
        break;
      case SIM_CMDTREE:
        if (code_loaded)
        {
          asm_print_tree(asm_result->tree);
        }
        else
        {
          printf("Can't print syntax tree, no code loaded\n");
        }
        break;
      case SIM_CMDSETSLOTS:
      {
        char *endptr = NULL;
        if (!out)
        {
          printf("Number of slots not specified\n");
        }
        else
        {
          long slots = strtol(out, &endptr, 0);
          if (endptr && endptr != out && slots >= 0)
          {
            vm_set_branch_delay_slots(slots);
          }
          else
          {
            printf("Invalid number of slots\n");
          }
        }
      }
      break;
      case SIM_CMDTRACE:
        vm_trace();
        break;
      case SIM_CMDUNTRACE:
        vm_untrace();
        break;
      case SIM_CMDRESET:
        vm_reset();
        break;
      }
    }
    else
    {
      free(histbuff);
      if (in[0])
      {
        printf("Unrecognized command\n");
      }
    }

    // FREE(in, __LINE__, __FILE__);
  }
  if (asm_result)
    asm_destroy_asm_info(asm_result);
}

void sim_done()
{
}