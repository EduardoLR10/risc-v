/*
 *  riscv.cpp
 *
 *  Created by Ricardo Jacobi on 26/01/18.
 *  Copyright 2018 Universidade de Brasilia. All rights reserved.
 *
 * Instructions: (v1.0)
 *   add,	addi,   and,  andi, auipc,
 *   beq,	bge,	bgeu, blt,  bltu,
 *   bne,   jal,	jalr, lb,	lbu,
 *   lw,    lh,     lhu,  lui,  sb,
 *   sh,    sw,     sll,  slt,  slli,
 *   srl,   sra,    sub,  slti, sltiu,
 *   xor,	or,	    srli, srai,  sltu,
 *   ori,   ecall,  xori, nop
 *
 */

#include <iomanip>
#include "globals.h"
#include "riscv.h"
#include "memoria.h"

using namespace std;

//
// Initial values for registers
//

void init() {
    pc = 0; ri = 0;
    stop_prg = false;
    sp = 0x3ffc;
    gp = 0x1800;
    build_dic();
}

void fetch (instruction_context_st& ic) {
	ri = lw(pc, 0);
	ic.ir = ri;
	ic.pc = pc;
    pc = pc + 4;
}

void decode (instruction_context_st& ic) {
    int32_t tmp;
    opcode	= ri & 0x7F;
    rs2		= (ri >> 20) & 0x1F;
    rs1		= (ri >> 15) & 0x1F;
    rd		= (ri >> 7)  & 0x1F;
    shamt	= (ri >> 20) & 0x1F;
    funct3	= (ri >> 12) & 0x7;
    funct7  = (ri >> 25);
    imm12_i = ((int32_t)ri) >> 20;
    tmp     = get_field(ri, 7, 0x1f);
    imm12_s = set_field(imm12_i, 0, 0x1f, tmp);
    imm13   = imm12_s;
    imm13 = set_bit(imm13, 11, imm12_s&1);
    imm13 = imm13 & ~1;
    imm20_u = ri & (~0xFFF);
    // mais aborrecido...
    imm21 = (int32_t)ri >> 11;			// estende sinal
    tmp = get_field(ri, 12, 0xFF);		// le campo 19:12
    imm21 = set_field(imm21, 12, 0xFF, tmp);	// escreve campo em imm21
    tmp = get_bit(ri, 20);				// le o bit 11 em ri(20)
    imm21 = set_bit(imm21, 11, tmp);			// posiciona bit 11
    tmp = get_field(ri, 21, 0x3FF);
    imm21 = set_field(imm21, 1, 0x3FF, tmp);
    imm21 = imm21 & ~1;					// zero bit 0
    ic.ins_code = get_instr_code(opcode, funct3, funct7);
    ic.ins_format = get_i_format(opcode, funct3, funct7);
    ic.rs1 = (REGISTERS)rs1;
    ic.rs2 = (REGISTERS)rs2;
    ic.rd = (REGISTERS)rd;
    ic.shamt = shamt;
    ic.imm12_i = imm12_i;
    ic.imm12_s = imm12_s;
    ic.imm13 = imm13;
    ic.imm21 = imm21;
    ic.imm20_u = imm20_u;
}

void debug_decode(instruction_context_st& ic) {
	cout    << "PC = " << pc << endl
	        << " instruction = "   << instr_str[ic.ins_code]  << endl
	        << " format = "        << iformat_str[ic.ins_format] << endl
            << hex << "opcode = "  << ic.ins_code           << endl
            << dec << " rs1 = "    << ic.rs1
            << " rs2 = "           << ic.rs2
            << " rd = "            << ic.rd
            << " shamt = "         << ic.shamt << endl
            << "Immediates: "                  << endl
            << " imm12_i = "       << ic.imm12_i
            << " imm12_s = "       << ic.imm12_s
            << " imm13 = "      << ic.imm13
            << " imm21 = "      << ic.imm21
            << " imm20_u = "    << ic.imm20_u
            << endl;
 }

void print_instr(instruction_context_st& ic) {
    switch (ic.ins_format) {
        case RType:
            cout << setw(10) << left << instr_str[ic.ins_code]
                 << setw(4)  << reg_str[ic.rd]
                 << ", "
                 << setw(4)  << reg_str[ic.rs1]
                 << ", "
                 << setw(4)  << reg_str[ic.rs2]
                 << endl;
            break;
        case IType:
            cout << setw(10) << left << instr_str[ic.ins_code]
                 << setw(4)  << reg_str[ic.rd]
                 << ", "
                 << setw(4)  << reg_str[ic.rs1]
                 << ", "
                 << setw(4)  << imm12_i
                 << endl;

            break;
        case SType:
            cout << setw(10) << left << instr_str[ic.ins_code]
                 << setw(4)  << reg_str[ic.rd]
                 << ", "
                 << setw(4)  << reg_str[ic.rs1]
                 << ", "
                 << setw(4)  << imm12_s
                 << endl;
            break;
        case SBType:
            cout << setw(10) << left << instr_str[ic.ins_code]
                 << setw(4)  << reg_str[ic.rs1]
                 << ", "
                 << setw(4)  << reg_str[ic.rs2]
                 << ", "
                 << setw(4)  << imm13
                 << endl;
            break;
        case UType:
            cout << setw(10) << left << instr_str[ic.ins_code]
                 << setw(4)  << reg_str[ic.rd]
                 << ", "
                 << setw(4)  << imm20_u
                 << endl;
            break;
        case UJType:
            cout << setw(10) << left << instr_str[ic.ins_code]
                 << setw(4)  << reg_str[ic.rd]
                 << ", "
                 << setw(4)  << imm21
                 << endl;

            break;
        default:
            cout << "Unknown format" << endl;
    }
}

void dump_breg() {
	for (int i=0; i<32; i++) {
		printf("BREG[%s] = \t%8d \t\t\t%8x\n", instr_str[i].c_str(), breg[i], breg[i]);
	}
}

void dump_asm(int start_ins, int end_ins) {
    instruction_context_st ic;

    for (int i = start_ins; i <= end_ins; i++) {
        fetch(ic);
        //cout  << "mem[" << i << "] =  " << x << endl;
        decode(ic);
        print_instr(ic);
    }
}

void dump_mem(int start_byte, int end_byte, char format) {
	switch (format) {
		case 'h':
		case 'H':
			for (uint32_t i = start_byte; i <= (int)(end_byte); i+=4)
				printf("%x \t%x\n", i, lw(i, 0));
			break;
		case 'd':
		case 'D':
			for (int i = start_byte; i <= (int)(end_byte); i+=4)
				printf("%x \t%d\n", i, lw(i, 0));
			break;
		default:
			break;
	}
}

int load_mem(const char *fn, int start) {
	FILE *fptr;
	int *m_ptr = mem + (start>>2);  
	int size = 0;
	
	fptr = fopen(fn, "rb");
	if (!fptr) {
		printf("Arquivo nao encontrado!");
		return -1;
	}
	else {
		while (!feof(fptr)) {
			fread(m_ptr, 4, 1, fptr);
			m_ptr++;
			size++;
		}
		fclose(fptr);
	}
	return size;
}

FORMATS get_i_format(uint32_t opcode, uint32_t func3, uint32_t func7) {
    switch(opcode) {
        case 0x33 :  return RType;
        case 0x03: case 0x13: case 0x67: case 0x73:
            return IType;
        case 0x23 :
            return SType;
        case 0x63 :
            return SBType;
        case 0x37 :
            return UType;
        case 0x6F: case 0x17 :
            return UJType;
        case 0x00:
            if (func3 == 0 && func7 == 0)
                return NOPType;
            else
                return NullFormat;
        default:
            cout << "Undefined Format";
            return NullFormat;
            break;
    }
}

INSTRUCTIONS get_instr_code(uint32_t opcode, uint32_t func3, uint32_t func7) {
    switch (opcode) {
        case LUI:   return I_lui;
        case AUIPC: return I_auipc;
        case BType:
            switch (funct3) {
                case BEQ3:
                    return I_beq;
                case BNE3:
                    return I_bne;
                case BLT3:
                    return I_blt;
                case BGE3:
                    return I_bge;
                case BLTU3:
                    return I_bltu;
                case BGEU3:
                    return I_bgeu;
            }
            break;
        case ILType:
            switch (funct3) {
                case LB3:   return I_lb;
                case LH3:   return I_lh;
                case LW3:   return I_lw;
                case LBU3:  return I_lbu;
                default:    break;
            }
            break;
        case JAL:       return I_jal;
        case JALR:      return I_jalr;
        case StoreType:
            switch (funct3) {
                case SB3:   return I_sb;
                case SH3:   return I_sh;
                case SW3:   return I_sw;
                default:    break;
            }
            break;
        case ILAType:
            switch (funct3) {
                case ADDI3:     return I_addi;
                case ORI3:      return I_ori;
                case ANDI3:     return I_andi;
                case XORI3:     return I_xori;
                case SLTI3:     return I_slti;
                case SLTIU3:    return I_sltiu;
                case SLLI3:     return I_slli;
                case SRI3:
                    if (funct7 == SRLI7)    return I_srli;
                    else        return I_srai;
                default:    break;
            }
            break;
        case RegType:
            switch (funct3) {
                case ADDSUB3:
                    if (funct7 == SUB7)     return I_sub;
                    else                    return I_add;
                case SLL3:                  return I_sll;
                case SLT3:                  return I_slt;
                case SLTU3:                 return I_sltu;
                case XOR3:                  return I_xor;
                case OR3:                   return I_or;
                case AND3:                  return I_and;
                case SR3:
                    if (funct7 == SRA7)     return I_sra;
                    else                    return I_srl;
                default:
                    break;
            }
            break;
        case ECALL:     return I_ecall;
        default:
            printf("Instrucao Invalida (PC = %08x RI = %08x)\n", pc, ri);
            break;
    }
    return I_nop;
}

void execute (instruction_context_st& ic) {
    int32_t aux;

    char *c;

    breg[0] = 0;
    switch (ic.ins_code) {
        case I_lui:
            breg[ic.rd] = ic.imm20_u;							        break;
        case I_auipc:
            breg[ic.rd] = ic.imm20_u + ic.pc; 					        break;
        case I_beq:	if (breg[ic.rs1] == breg[ic.rs2]) {pc = ic.pc + ic.imm13;}
                        						break;
        case I_bne: if (breg[ic.rs1] != breg[ic.rs2]) {pc = ic.pc + ic.imm13;}
                        					    break;
        case I_blt:	if (breg[ic.rs1] < breg[ic.rs2]) {pc = ic.pc + ic.imm13;}
                        						break;
        case I_bge:	if (breg[ic.rs1] >= breg[ic.rs2]) {pc = ic.pc + ic.imm13;}
                        						break;
        case I_bltu:	if ((uint32_t)breg[ic.rs1] < (uint32_t)breg[ic.rs2]) {pc = ic.pc + ic.imm13;}
                        						break;
        case I_bgeu:	if ((uint32_t)breg[ic.rs1] >= (uint32_t)breg[ic.rs2]) {pc = ic.pc + ic.imm13;}
                        						break;
        case I_lb:
                    breg[ic.rd] = lb(breg[ic.rs1], ic.imm12_i);     break;
        case I_lh:
                    breg[ic.rd] = lh(breg[ic.rs1], ic.imm12_i);     break;
        case I_lw:
                    breg[ic.rd] = lw(breg[ic.rs1], ic.imm12_i);     break;
        case I_lbu:
                    breg[ic.rd] = lbu(breg[ic.rs1], ic.imm12_i);       break;
        case I_jal:
            breg[ic.rd] = ic.pc + 4;
            pc = ic.pc + imm21;                                     break;
        case I_jalr:
            breg[ic.rd] = ic.pc + 4;
            pc = (breg[ic.rs1] + ic.imm12_i) & ~1;                  break;
        case I_sb:
            sb(breg[ic.rs1],  ic.imm12_s, (int8_t)breg[ic.rs2]);    break;
        case I_sh:
            sh(breg[ic.rs1],  ic.imm12_s, (int16_t)breg[ic.rs2]);   break;
        case I_sw:
            sw(breg[ic.rs1],  ic.imm12_s, (int8_t)breg[ic.rs2]);    break;
        case I_addi:
                    breg[ic.rd] = breg[ic.rs1] + ic.imm12_i;        break;
        case I_ori:
                    breg[ic.rd] = breg[ic.rs1] | ic.imm12_i;        break;
        case I_andi:
                    breg[ic.rd] = breg[ic.rs1] & ic.imm12_i;        break;
        case I_xori:
                    breg[ic.rd] = breg[ic.rs1] ^ ic.imm12_i;        break;
        case I_slti:
                    breg[ic.rd] = breg[ic.rs1] < ic.imm12_i;        break;
        case I_sltiu:
                    breg[ic.rd] = (uint32_t)breg[ic.rs1] < (uint32_t)ic.imm12_i;
                    break;
        case I_slli:
                    breg[ic.rd] = breg[ic.rs1] << ic.shamt;         break;
        case I_srai:
                    breg[ic.rd] = breg[ic.rs1] >> ic.shamt;         break;
        case I_srli:
                    breg[ic.rd] = (uint32_t)breg[ic.rs1] >> ic.shamt;
                    break;
        case I_sub:
                    breg[ic.rd] = breg[ic.rs1] - breg[ic.rs2];      break;
        case I_add:
                    breg[ic.rd] = breg[ic.rs1] + breg[ic.rs2];      break;
        case I_sll:
                breg[ic.rd] = breg[ic.rs1] << breg[ic.rs2];         break;
        case I_slt:
            breg[ic.rd] = breg[ic.rs1] < breg[ic.rs2];              break;
        case I_sltu:
            breg[ic.rd] = (uint32_t)breg[ic.rs1] < (uint32_t)breg[ic.rs2];
            break;
        case I_xor:
                    breg[ic.rd] = breg[ic.rs1] ^ breg[rs2];         break;
        case I_or:
                    breg[ic.rd] = breg[ic.rs1] | breg[ic.rs2];      break;
        case I_and:
                    breg[ic.rd] = breg[ic.rs1] & breg[ic.rs2];      break;
        case I_sra:
                    breg[ic.rd] = breg[ic.rs1] >> breg[ic.rs2];     break;
        case I_srl:
                    breg[ic.rd] = (uint32_t)breg[ic.rs1] >> breg[ic.rs2];
                    break;
        case I_ecall:
            switch (breg[A7]) {
                case 1:	cout << breg[A0];	break;
                case 4:	aux = breg[A0];
                    c = (char *)mem + breg[A0];
                    printf("%s", c);
                    break;
                case 5:	cout << breg[A0]; break;
                case 6:	cout << breg[A0]; break;
                case 10: stop_prg = true; break;
                default:
                    break;
            }
            break;
        default:
            printf("Invalid Instruction (PC = %08x RI = %08x)\n", pc, ri);
            break;
    }
}

void step() {
    instruction_context_st ic;
	fetch(ic);
	decode(ic);
    execute(ic);
}

void run() {
	init();
	while ((pc < DATA_SEGMENT_START) && !stop_prg)
        step();
}
