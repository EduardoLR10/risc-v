//
// Created by Ricardo Jacobi on 29/03/21.
//

#include "control_rv.h"

INSTRUCTIONS get_instr_code(uint32_t opcode, uint32_t funct3, uint32_t funct7) {
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
//                case BLTU3:
//                    return I_bltu;
//                case BGEU3:
//                    return I_bgeu;
            }
            break;
        case ILType:
            switch (funct3) {
                case LB3:   return I_lb;
                case LH3:   return I_lh;
                case LW3:   return I_lw;
                case LBU3:  return I_lbu;
                case LHU3:  return I_lhu;
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
                    else                    return I_srai;
                default:    break;
            }
            break;
        case RegType:
            switch (funct3) {
                case ADDSUB3:
                    if (funct7 == SUB7)     return I_sub;
                    else                    return I_add;
//                case SLL3:                  return I_sll;
//                case SLT3:                  return I_slt;
//                case SLTU3:                 return I_sltu;
                case XOR3:                  return I_xor;
                case OR3:                   return I_or;
                case AND3:                  return I_and;
//                case SR3:
//                    if (funct7 == SRA7)     return I_sra;
//                    else                    return I_srl;
                default:
                    break;
            }
            break;
//        case ECALL:     return I_ecall;
        default:
            printf("\n\nInstrucao Invalida (PC = %08x RI = %08x)\n", pc, ri);
            break;
    }
    return I_nop;
}

void control_rv::decode() {
    INSTRUCTIONS ins_code;
    uint32_t opcode, funct3, funct7;
    int32_t aux;

    sc_uint<32> ins = instruction.read();
    opcode = ins.range(6,0);
    funct3 = ins.range(14, 12);
    funct7 = ins.range(31, 25);
    ins_code = get_instr_code(opcode, funct3, funct7);

    // reset all outputs
    rst_reg_ID = 0;         is_jal = 0;     is_jalr = 0;
    id_flush = 0            b_code = 0;     is_branch = 0;
    ex_flush = false;
    ex_ctrl = 0;
    mem_ctrl = 0;
    wb_ctrl = 0;

    switch (ins_code) {
        case I_lui:         // breg[ic.rd] = ic.imm20_u;
                    ex_ctrl.write((0, ALU_B_IMM, ALU_A_ZERO));
                    mem_ctrl.write(0);
                    wb_ctrl.write((SEL_ALU_DATA, WRITE_BREG));
                    break;
        case I_auipc:       // breg[ic.rd] = ic.imm20_u + ic.pc;
                    ex_ctrl.write((0, ALU_B_IMM, ALU_A_PC));
                    mem_ctrl.write(0);
                    wb_ctrl.write((SEL_ALU_DATA, WRITE_BREG));
                    break;
        case I_beq: b_code.write(0); is_branch.write(true); break;
        case I_bne: b_code.write(1); is_branch.write(true); break;
        case I_blt:	b_code.write(2); is_branch.write(true); break;
        case I_bge:	b_code.write(3); is_branch.write(true); break;
        //case I_bltu:	if ((uint32_t)breg[ic.rs1] < (uint32_t)breg[ic.rs2])
        //      pc = ic.pc + ic.imm13;						break;
        //case I_bgeu:	if ((uint32_t)breg[ic.rs1] >= (uint32_t)breg[ic.rs2])
        //        pc = ic.pc + ic.imm13;						break;
        case I_lb:  wb_ctrl.write((SEL_MEM_DATA, WRITE_BREG));
                    mem_ctrl.write((MEM_READ, NO_WRITE, SIGNED_DATA, BYTE_SIZE));
                    ex_ctrl.write((0, ALU_B_IMM, ALU_A_RA));
                    break;
        case I_lh:  wb_ctrl.write((SEL_MEM_DATA, WRITE_BREG));
                    mem_ctrl.write((MEM_READ, NO_WRITE, SIGNED_DATA, HALF_SIZE));
                    ex_ctrl.write((0, ALU_B_IMM, ALU_A_RA));
                    break;
        case I_lhu: wb_ctrl.write((SEL_MEM_DATA, WRITE_BREG));
                    mem_ctrl.write((MEM_READ, NO_WRITE, UNSIGNED_DATA, HALF_SIZE));
                    ex_ctrl.write((0, ALU_B_IMM, ALU_A_RA));
                    break;
        case I_lw:  wb_ctrl.write((SEL_MEM_DATA, WRITE_BREG));
                    mem_ctrl.write((MEM_READ, NO_WRITE, SIGNED_DATA, WORD_SIZE));
                    ex_ctrl.write((0, ALU_B_IMM, ALU_A_RA));
                    break;
        case I_lbu: wb_ctrl.write((SEL_MEM_DATA, WRITE_BREG));
                    mem_ctrl.write((MEM_READ, NO_WRITE, UNSIGNED_DATA, BYTE_SIZE));
                    ex_ctrl.write((0, ALU_B_IMM, ALU_A_RA));
                    break;
        case I_jal: is_jalx.write(true);
                    ex_ctrl.write((0, ALU_B_IMM, ALU_A_ZERO));
                    wb_ctrl.write((SEL_ALU_DATA, WRITE_BREG));
                    break;
        case I_jalr: is_jalx.write(true);
                     is_jalr.write(true);
                     ex_ctrl.write((0, ALU_B_IMM, ALU_A_ZERO));
                     wb_ctrl.write((SEL_ALU_DATA, WRITE_BREG));
                     break;
        case I_sb: ex_ctrl.write((0, ALU_B_IMM, ALU_A_RA));
                   mem_ctrl.write((NO_READ, MEM_WRITE, SIGNED_DATA, BYTE_SIZE));
                   break;
        case I_sh: ex_ctrl.write((0, ALU_B_IMM, ALU_A_RA));
                   mem_ctrl.write((NO_READ, MEM_WRITE, SIGNED_DATA, HALF_SIZE));
                   break;
        case I_sw: ex_ctrl.write((0, ALU_B_IMM, ALU_A_RA));
                   mem_ctrl.write((NO_READ, MEM_WRITE, SIGNED_DATA, WORD_SIZE));
                   break;
        case I_addi:
        case I_ori:
        case I_andi:
        case I_xori:
        case I_slti:
        case I_sltiu:
        case I_slli:
        case I_srai:
        case I_srli:
                    ex_ctrl.write((1, ALU_B_IMM, ALU_A_RA));
                    wb_ctrl.write((SEL_ALU_DATA, WRITE_BREG));
                    break;
        case I_sub:
        case I_add:
        case I_sll:
        case I_slt:
        case I_sltu:
        case I_xor:
        case I_or:
        case I_and:
        case I_sra:
        case I_srl:
                    ex_ctrl.write((1, ALU_B_RB, ALU_A_RA));
                    wb_ctrl.write((SEL_ALU_DATA, WRITE_BREG));
                    break;
        default:
            printf("Invalid Instruction (PC = %08x RI = %08x)\n", pc, ri);
            exit(0);
            break;

    }
}