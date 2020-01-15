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
                                                                              
#ifndef __DLXINSTSET_H__
#define __DLXINSTSET_H__


//-- DLX Instruction type and format --//
typedef enum { NONE, SPECIAL, IMM, REG, STORE, LOAD, BRANCH, MOVE} instr_type_t;
typedef enum { FORMAT_I, FORMAT_J, FORMAT_R } instr_format;

//-- DLX Instruction property --//
#define REGTARGET (1<<0)
#define RS1       (1<<1)
#define RS2       (1<<2)
#define RD        (1<<3)
#define SIMM      (1<<4)
#define UIMM      (1<<5)
#define NAME      (1<<6)
#define UNAME     (1<<7)

#define INSTR_NORM 0
#define INSTR_SP   1
#define INSTR_FP   2

typedef struct dlx_instr_entry {
  char *opname;
  instr_format format;
  instr_type_t type;
  int property;
  int reg_type;
  int opcode_value;
} dlx_instr_entry;

#define ISPECIAL          0
#define FPARITH           1
#define J                 2
#define JAL               3
#define BEQZ              4
#define BNEZ              5
#define BFPT              6
#define BFPF              7
#define ADDI              8
#define ADDUI             9
#define SUBI             10
#define SUBUI            11
#define ANDI             12
#define ORI              13
#define XORI             14
#define LHI              15

#define RFE              16
#define TRAP             17
#define JR               18
#define JALR             19
#define SLLI             20
#define op_undef_15      21
#define SRLI             22
#define SRAI             23
#define SEQI             24
#define SNEI             25
#define SLTI             26
#define SGTI             27
#define SLEI             28
#define SGEI             29
#define op_undef_1E      30
#define op_undef_1F      31

#define LB               32
#define LH               33
#define op_undef_22      34
#define LW               35
#define LBU              36
#define LHU              37
#define LF               38
#define LD               39
#define SB               40
#define SH               41
#define op_undef_2A      42
#define SW               43
#define op_undef_2C      44 
#define op_undef_2D      45
#define SF               46
#define SD               47

#define SEQUI            48
#define SNEUI            49
#define SLTUI            50
#define SGTUI            51
#define SLEUI            52
#define SGEUI            53
#define op_undef_36      54
#define op_undef_37      55
#define op_undef_38      56
#define op_undef_39      57
#define op_undef_3A      58
#define op_undef_3B      59
#define op_undef_3C      60
#define op_undef_3D      61
#define op_undef_3E      62
#define op_undef_3F      63

#define NOP              0
#define sp_func_undef_01 1
#define sp_func_undef_02 2
#define sp_func_undef_03 3
#define SLL              4
#define sp_func_undef_05 5
#define SRL              6
#define SRA              7
#define sp_func_undef_08 8
#define sp_func_undef_09 9
#define sp_func_undef_0A 10
#define sp_func_undef_0B 11
#define sp_func_undef_0C 12
#define sp_func_undef_0D 13
#define sp_func_undef_0E 14
#define sp_func_undef_0F 15

#define SEQU             16
#define SNEU             17
#define SLTU             18
#define SGTU             19
#define SLEU             20
#define SGEU             21
#define sp_func_undef_16 22
#define sp_func_undef_17 23
#define sp_func_undef_18 24
#define sp_func_undef_19 25
#define sp_func_undef_1A 26
#define sp_func_undef_1B 27
#define sp_func_undef_1C 28
#define sp_func_undef_1D 29
#define sp_func_undef_1E 30
#define sp_func_undef_1F 31

#define ADD              32
#define ADDU             33 
#define SUB              34
#define SUBU             35
#define AND              36
#define OR               37
#define XOR              38
#define sb_func_undef_27 39
#define SEQ              40
#define SNE              41
#define SLT              42
#define SGT              43
#define SLE              44
#define SGE              45
#define sp_func_undef_2E 46
#define sp_func_undef_2F 47

#define MOVI2S           48
#define MOVS2I           49
#define MOVF             50
#define MOVD             51
#define MOVFP2I          52
#define MOVI2FP          53
#define sp_func_undef_36 54
#define sp_func_undef_37 55
#define sp_func_undef_38 56
#define sp_func_undef_39 57
#define sp_func_undef_3A 58
#define sp_func_undef_3B 59
#define sp_func_undef_3C 60
#define sp_func_undef_3D 61
#define sp_func_undef_3E 62
#define sp_func_undef_3F 63

#define ADDF              1
#define SUBF              2
#define MULTF             3            
#define DIVF              4 
#define ADDD              5
#define SUBD              6
#define MULTD             7
#define DIVD              8
#define CVTF2D            9
#define CVTF2I           10
#define CVTD2F           11
#define CVTD2I           12
#define CVTI2F           13
#define MULT             14
#define DIV              15

#define EQF              16
#define NEF              17
#define LTF              18
#define GTF              19
#define LEF              20
#define GEF              21
#define MULTU            22
#define DIVU             23
#define EQD              24
#define NED              25
#define LTD              26
#define GTD              27
#define LED              28
#define GED              29
#define fp_func_undef_1E 30
#define fp_func_undef_1F 31

#define MAX_DLX_INSTR 64
#define MAX_DLX_SP_INSTR 64
#define MAX_DLX_FP_INSTR 32

extern const dlx_instr_entry DLX_INSTR_TABLE[];      
extern const dlx_instr_entry DLX_INSTR_SP_TABLE[];
extern const dlx_instr_entry DLX_INSTR_FP_TABLE[];

const dlx_instr_entry *dlx_get_instr_by_opcode( char *opname );

#endif
