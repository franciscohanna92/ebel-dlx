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
#include <string.h>
#include "dlxinstset.h"

#define SOP( x ) ((x)<<26)
#define SSP( x ) (x)
#define SFP( x ) ((x)|(1<<26))

const dlx_instr_entry DLX_INSTR_TABLE[] = {
  //--   instr_name,  format,     inst_type,  property--//
  {  "special",         FORMAT_J,   SPECIAL,   0                  , INSTR_NORM, SOP( 0x00 ) },
  {  "fparith",         FORMAT_J,   SPECIAL,   0                  , INSTR_NORM, SOP( 0x01 ) },
  {  "j",               FORMAT_J,   BRANCH,    ( NAME )           , INSTR_NORM, SOP( 0x02 ) },
  {  "jal",             FORMAT_J,   BRANCH,    ( NAME )           , INSTR_NORM, SOP( 0x03 ) },
  {  "beqz",            FORMAT_I,   BRANCH,    ( RS1 | NAME )     , INSTR_NORM, SOP( 0x04 ) },
  {  "bnez",            FORMAT_I,   BRANCH,    ( RS1 | NAME )     , INSTR_NORM, SOP( 0x05 ) },
  {  "bfpt",            FORMAT_I,   BRANCH,    ( NAME )           , INSTR_NORM, SOP( 0x06 ) },
  {  "bfpf",            FORMAT_I,   BRANCH,    ( NAME )           , INSTR_NORM, SOP( 0x07 ) },
  {  "addi",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x08 ) },
  {  "addui",           FORMAT_I,   IMM,       (RD | RS1 | UIMM)  , INSTR_NORM, SOP( 0x09 ) },
  {  "subi",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x0A ) },
  {  "subui",           FORMAT_I,   IMM,       (RD | RS1 | UIMM)  , INSTR_NORM, SOP( 0x0B ) },
  {  "andi",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x0C ) },
  {  "ori",             FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x0D ) },
  {  "xori",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x0E ) },
  {  "lhi",             FORMAT_I,   LOAD,      (RD | IMM )        , INSTR_NORM, SOP( 0x0F ) },
  
  {  "rfe",             FORMAT_J,   BRANCH,    0                  , INSTR_NORM, SOP( 0x10 ) },
  {  "trap",            FORMAT_J,   SPECIAL,   ( NAME )           , INSTR_NORM, SOP( 0x11 ) },
  {  "jr",              FORMAT_I,   BRANCH,    ( RS1 )            , INSTR_NORM, SOP( 0x12 ) },
  {  "jalr",            FORMAT_I,   BRANCH,    ( RS1 )            , INSTR_NORM, SOP( 0x13 ) },
  {  "slli",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x14 ) },
  {  "op_undef_15",     FORMAT_J,   NONE,      0                  , INSTR_NORM, SOP( 0x15 ) },
  {  "srli",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x16 ) },
  {  "srai",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x17 ) },
  {  "seqi",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x18 ) },
  {  "snei",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x19 ) },
  {  "slti",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x1A ) },
  {  "sgti",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x1B ) },
  {  "slei",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x1C ) },
  {  "sgei",            FORMAT_I,   IMM,       (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x1D ) },
  {  "op_undef_1E",     FORMAT_J,   NONE,      0                  , INSTR_NORM, SOP( 0x1E ) },
  {  "op_undef_1F",     FORMAT_J,   NONE,      0                  , INSTR_NORM, SOP( 0x1F ) },
  
  {  "lb",              FORMAT_I,   LOAD,      (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x20 ) },
  {  "lh",              FORMAT_I,   LOAD,      (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x21 ) },
  {  "op_undef_22",     FORMAT_J,   NONE,      0                  , INSTR_NORM, SOP( 0x22 ) },
  {  "lw",              FORMAT_I,   LOAD,      (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x23 ) },
  {  "lbu",             FORMAT_I,   LOAD,      (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x24 ) },
  {  "lhu",             FORMAT_I,   LOAD,      (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x25 ) },
  {  "lf",              FORMAT_I,   LOAD,      (RD | RS1 | SIMM)  , INSTR_FP,   SOP( 0x26 ) },
  {  "ld",              FORMAT_I,   LOAD,      (RD | RS1 | SIMM)  , INSTR_FP,   SOP( 0x27 ) },
  {  "sb",              FORMAT_I,   STORE,     (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x28 ) },
  {  "sh",              FORMAT_I,   STORE,     (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x29 ) },
  {  "op_undef_2A",     FORMAT_J,   NONE,      0                  , INSTR_NORM, SOP( 0x2A ) },
  {  "sw",              FORMAT_I,   STORE,     (RD | RS1 | SIMM)  , INSTR_NORM, SOP( 0x2B ) },
  {  "op_undef_2C",     FORMAT_J,   NONE,      0                  , INSTR_NORM, SOP( 0x2C ) },
  {  "op_undef_2D",     FORMAT_J,   NONE,      0                  , INSTR_NORM, SOP( 0x2D ) },
  {  "sf",              FORMAT_I,   STORE,     (RD | RS1 | SIMM)  , INSTR_FP,   SOP( 0x2E ) },
  {  "sd",              FORMAT_I,   STORE,     (RD | RS1 | SIMM)  , INSTR_FP,   SOP( 0x2F ) },
  
  {  "sequi",           FORMAT_I,   IMM,       (RD | RS1 | UIMM) , INSTR_NORM, SOP( 0x30 ) },
  {  "sneui",           FORMAT_I,   IMM,       (RD | RS1 | UIMM) , INSTR_NORM, SOP( 0x31 ) },
  {  "sltui",           FORMAT_I,   IMM,       (RD | RS1 | UIMM) , INSTR_NORM, SOP( 0x32 ) },
  {  "sgtui",           FORMAT_I,   IMM,       (RD | RS1 | UIMM) , INSTR_NORM, SOP( 0x33 ) },
  {  "sleui",           FORMAT_I,   IMM,       (RD | RS1 | UIMM) , INSTR_NORM, SOP( 0x34 ) },
  {  "sgeui",           FORMAT_I,   IMM,       (RD | RS1 | UIMM) , INSTR_NORM, SOP( 0x35 ) },
  {  "op_undef_36",     FORMAT_J,   NONE,      0                 , INSTR_NORM, SOP( 0x36 ) },
  {  "op_undef_37",     FORMAT_J,   NONE,      0                 , INSTR_NORM, SOP( 0x37 ) },
  {  "op_undef_38",     FORMAT_J,   NONE,      0                 , INSTR_NORM, SOP( 0x38 ) },
  {  "op_undef_39",     FORMAT_J,   NONE,      0                 , INSTR_NORM, SOP( 0x39 ) },
  {  "op_undef_3A",     FORMAT_J,   NONE,      0                 , INSTR_NORM, SOP( 0x3A ) },
  {  "op_undef_3B",     FORMAT_J,   NONE,      0                 , INSTR_NORM, SOP( 0x3B ) },
  {  "op_undef_3C",     FORMAT_J,   NONE,      0                 , INSTR_NORM, SOP( 0x3C ) },
  {  "op_undef_3D",     FORMAT_J,   NONE,      0                 , INSTR_NORM, SOP( 0x3D ) },
  {  "op_undef_3E",     FORMAT_J,   NONE,      0                 , INSTR_NORM, SOP( 0x3E ) },
  {  "op_undef_3F",     FORMAT_J,   NONE,      0                 , INSTR_NORM, SOP( 0x3F ) }
};



const dlx_instr_entry DLX_INSTR_SP_TABLE[] = {
  {  "nop",              FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x00 ) },
  {  "sp_func_undef_01", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x01 ) },
  {  "sp_func_undef_02", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x02 ) },
  {  "sp_func_undef_03", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x03 ) },
  {  "sll",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x04 ) },
  {  "sp_func_undef_05", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x05 ) },
  {  "srl",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x06 ) },
  {  "sra",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x07 ) },
  {  "sp_func_undef_08", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x08 ) },
  {  "sp_func_undef_09", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x09 ) },
  {  "sp_func_undef_0A", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x0A ) },
  {  "sp_func_undef_0B", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x0B ) },
  {  "sp_func_undef_0C", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x0C ) },
  {  "sp_func_undef_0D", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x0D ) },
  {  "sp_func_undef_0E", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x0E ) },
  {  "sp_func_undef_0F", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x0F ) },
  
  {  "sequ",             FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x10 ) }, 
  {  "sneu",             FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x11 ) }, 
  {  "sltu",             FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x12 ) }, 
  {  "sgtu",             FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x13 ) }, 
  {  "sleu",             FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x14 ) }, 
  {  "sgeu",             FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x15 ) }, 
  {  "sp_func_undef_16", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x16 ) },
  {  "sp_func_undef_17", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x17 ) },
  {  "sp_func_undef_18", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x18 ) },
  {  "sp_func_undef_19", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x19 ) },
  {  "sp_func_undef_1A", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x1A ) },
  {  "sp_func_undef_1B", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x1B ) },
  {  "sp_func_undef_1C", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x1C ) },
  {  "sp_func_undef_1D", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x1D ) },
  {  "sp_func_undef_1E", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x1E ) },
  {  "sp_func_undef_1F", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x1F ) },
  
  {  "add",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x20 ) },
  {  "addu",             FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x21 ) },
  {  "sub",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x22 ) },
  {  "subu",             FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x23 ) },
  {  "and",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x24 ) },
  {  "or",               FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x25 ) },
  {  "xor",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x26 ) },
  {  "sp_func_undef_27", FORMAT_J,  NONE,     0,                 INSTR_SP, SSP( 0x27 ) },
  {  "seq",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x28 ) },
  {  "sne",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x29 ) },
  {  "slt",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x2A ) },
  {  "sgt",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x2B ) },
  {  "sle",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x2C ) },
  {  "sge",              FORMAT_R,  REG,      (RD | RS1 | RS2) , INSTR_SP, SSP( 0x2D ) },
  {  "sp_func_undef_2E", FORMAT_J,  NONE,     0                , INSTR_SP, SSP( 0x2E ) },
  {  "sp_func_undef_2F", FORMAT_R,  NONE,     0                , INSTR_SP, SSP( 0x2F ) },
  
  {  "movi2s",           FORMAT_R,  MOVE,      (RD | RS1)      , INSTR_SP, SSP( 0x30 ) },
  {  "movs2i",           FORMAT_R,  MOVE,      (RD | RS1)      , INSTR_SP, SSP( 0x31 ) },
  {  "movf",             FORMAT_R,  MOVE,      (RD | RS1)      , INSTR_SP, SSP( 0x32 ) },
  {  "movd",             FORMAT_R,  MOVE,      (RD | RS1)      , INSTR_SP, SSP( 0x33 ) },
  {  "movfp2i",          FORMAT_R,  MOVE,      (RD | RS1)      , INSTR_SP, SSP( 0x34 ) },
  {  "movi2fp",          FORMAT_R,  MOVE,      (RD | RS1)      , INSTR_SP, SSP( 0x35 ) },
  {  "sp_func_undef_36", FORMAT_J,  NONE,      0               , INSTR_SP, SSP( 0x36 ) },
  {  "sp_func_undef_37", FORMAT_J,  NONE,      0               , INSTR_SP, SSP( 0x37 ) },
  {  "sp_func_undef_38", FORMAT_J,  NONE,      0               , INSTR_SP, SSP( 0x38 ) },
  {  "sp_func_undef_39", FORMAT_J,  NONE,      0               , INSTR_SP, SSP( 0x39 ) },
  {  "sp_func_undef_3A", FORMAT_J,  NONE,      0               , INSTR_SP, SSP( 0x3A ) },
  {  "sp_func_undef_3B", FORMAT_J,  NONE,      0               , INSTR_SP, SSP( 0x3B ) },
  {  "sp_func_undef_3C", FORMAT_J,  NONE,      0               , INSTR_SP, SSP( 0x3C ) },
  {  "sp_func_undef_3D", FORMAT_J,  NONE,      0               , INSTR_SP, SSP( 0x3D ) },
  {  "sp_func_undef_3E", FORMAT_J,  NONE,      0               , INSTR_SP, SSP( 0x3E ) },
  {  "sp_func_undef_3F", FORMAT_J,  NONE,      0               , INSTR_SP, SSP( 0x3F ) }
};

const dlx_instr_entry DLX_INSTR_FP_TABLE[] = {
  {  "--patch--",       FORMAT_R,  NONE,     0,                INSTR_FP, SFP( 0x00 ) },  
  {  "addf",            FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x01 ) }, 
  {  "subf",            FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x02 ) }, 
  {  "multf",           FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x03 ) },
  {  "divf",            FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x04 ) },  
  {  "addd",            FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x05 ) },  
  {  "subd",            FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x06 ) },  
  {  "multd",           FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x07 ) },  
  {  "divd",            FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x08 ) },  
  {  "cvtf2d",          FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x09 ) },  
  {  "cvtf2i",          FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x0A ) },  
  {  "cvtd2f",          FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x0B ) },  
  {  "cvtd2i",          FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x0C ) },  
  {  "cvti2f",          FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x0D ) },  
  {  "mult",            FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_SP, SFP( 0x0E ) },  
  {  "div",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_SP, SFP( 0x0F ) },  
   
  {  "eqf",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x10 ) },  
  {  "nef",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x11 ) },   
  {  "ltf",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x12 ) },   
  {  "gtf",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x13 ) },   
  {  "lef",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x14 ) },   
  {  "gef",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x15 ) },   
  {  "multu",           FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x16 ) },   
  {  "divu",            FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x17 ) },   
  {  "eqd",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x18 ) },   
  {  "ned",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x19 ) },   
  {  "ltd",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x1A ) },   
  {  "gtd",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x1B ) },   
  {  "led",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x1C ) },   
  {  "ged",             FORMAT_R,  REG,      (RD | RS1 | RS2), INSTR_FP, SFP( 0x1D ) },   
  {  "fp_func_undef_1E",FORMAT_J,  NONE,     0               , INSTR_FP, SFP( 0x1E ) },
  {  "fp_func_undef_1F",FORMAT_J,  NONE,     0               , INSTR_FP, SFP( 0x1F ) }
};

const dlx_instr_entry *dlx_get_instr_by_opcode( char *opname ) {
  int i;

  for( i=0; i<64; i++ ) { 
  if( strcasecmp( opname,  DLX_INSTR_TABLE[i].opname )    == 0 ) return &DLX_INSTR_TABLE[i];
  if( strcasecmp( opname,  DLX_INSTR_SP_TABLE[i].opname ) == 0 ) return &DLX_INSTR_SP_TABLE[i];
  }
  for( i=0; i<32; i++ ) 
  if( strcasecmp( opname,  DLX_INSTR_FP_TABLE[i].opname ) == 0 ) return &DLX_INSTR_FP_TABLE[i];

  return NULL;
}

