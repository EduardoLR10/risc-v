/*
 *  riscv.h
 *  RV32I
 *
 *  Created by Ricardo Jacobi on 17/09/19.
 *  Copyright 2019 Universidade de Brasilia / York. All rights reserved.
 *
 */

#ifndef __RISCV_H__
#define __RISCV_H__

#include <iostream>
#include <map>
#include "globals.h"

using namespace std;

#define get_byte_0(w) (w & 0xFF)
#define get_byte_1(w) ((w>>8) & 0xFF)
#define get_byte_2(w) ((w>>16) & 0xFF)
#define get_byte_3(w) ((w>>24) & 0xFF)

//
// banco de registradores do MIPS
//

int32_t breg[32];

//
// registradores especiais
//

uint32_t	pc,				// contador de programa
            sp,				// stack pointer
            gp,				// global pointer
            ri;				// registrador de intrucao


//
// campos das instrucoes RISCV
//
// Formato R:  | funct7       | rs2 | rs1 | funct3      | rd | opcode |
// Formato I:  |    imm[11:0]       | rs1 | funct3      | rd | opcode |
// Formato S:  | imm[11:5]    | rs2 | rs1 | imm[4:0]    | rd | opcode |
// Formato SB: | imm[12-11:5] | rs2 | rs1 | imm[4:1-11] | rd | opcode |
// Formato U:  |               imm[31:12]               | rd | opcode |
// Formato UJ: | imm[20] imm[10:1] imm[11] imm[19:12]   | rd | opcode |

uint32_t	opcode,					// codigo da operacao
            rs1,					// indice registrador rs
            rs2,					// indice registrador rt
            rd,						// indice registrador rd
            shamt,					// deslocamento
            funct3,					// campos auxiliares
            funct7;					// constante instrucao tipo J

int32_t		imm12_i,				// constante 12 bits
            imm12_s,				// constante 12 bits
            imm13,					// constante 13 bits
            imm20_u,				// constante 20 bis mais significativos
            imm21;					// constante 21 bits

string instr_str[39];
// init instruction strings
void build_dic() {
    instr_str[I_add]	= "ADD";	instr_str[I_addi] = "ADDi";	instr_str[I_and] = "AND";
    instr_str[I_andi]	= "ANDi";	instr_str[I_auipc] = "AUIPC";
    instr_str[I_beq]	= "BEQ";	instr_str[I_bge] = "BGE";
    instr_str[I_bgeu]	= "BGEU";	instr_str[I_blt] = "BLT";	instr_str[I_bltu] = "BLTU";
    instr_str[I_bne]	= "BNE";
    instr_str[I_jal]	= "JAL";	instr_str[I_jalr] = "JALR";
    instr_str[I_lb]		= "LB";		instr_str[I_lbu] = "LBU";	instr_str[I_lh] = "LH";
    instr_str[I_lhu]	= "LHU";	instr_str[I_lui] = "LUI";	instr_str[I_lw] = "LW";
    instr_str[I_or]		= "OR";		instr_str[I_ori] = "ORi";
    instr_str[I_sb]		= "SB";		instr_str[I_sh] = "SH";		instr_str[I_sll] = "SLL";
    instr_str[I_slt]	= "SLT";	instr_str[I_slli] = "SLLi";
    instr_str[I_slti]	= "SLTi";	instr_str[I_sltiu] = "SLTIU";
    instr_str[I_sltu]	= "SLTU";	instr_str[I_srl] = "SRL";
    instr_str[I_sra]	= "SRA";	instr_str[I_srli] = "SRLi";
    instr_str[I_srai]	= "SRAi";	instr_str[I_sub] = "SUB";
    instr_str[I_sw]		= "SW";		instr_str[I_xor] = "XOR";	instr_str[I_xori] = "XORi";
    instr_str[I_ecall]  = "ECALL";  instr_str[I_nop]  = "NOP";
}

string iformat_str[8] = { "RType", "IType", "SType", "SBType", "UType", "UJType", "NullFormat", "NOPType" };

//
// identificacao dos registradores do banco do RV32I
//
string reg_str[] = {
    "ZERO", "RA",	"SP",	"GP",
    "TP",	"T0",	"T1",	"T2",
    "S0",	"S1",	"A0",	"A1",
    "A2",	"A3",	"A4",	"A5",
    "A6",	"A7",  "S2",	"S3",
    "S4",	"S5", 	"S6",	"S7",
    "S8",	"S9",  "S10",	"S11",
    "T3",	"T4",	"T5",	"T6"
};

instruction_context_st gic;

bool stop_prg;

#endif
