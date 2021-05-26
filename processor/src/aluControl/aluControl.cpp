#include "aluControl/aluControl.hpp"

void aluControl::proc() {
    bool op, f7;
    ULA_OPCODE opcode_result;
    sc_uint<3> f3;
    f3 = ex_funct3.read();
    op = alu_op.read();
    f7 = ex_funct7.read();

    if (op == 0)			// memory access, AUIPC, LUI
        opcode_result = ULA_ADD;

    else {					// arithmetic-logic operations

        switch (f3) {		// funct3

            case 0b000:					// add, sub
                opcode_result = ULA_ADD;
                if(f7 == true)
                    opcode_result = ULA_SUB;
                break;

            case 0b001:					// slli
                opcode_result = ULA_SLL;
                break;

            case 0b010:					// slt, slti
                opcode_result = ULA_SLT;
                break;

            case 0b011:					// sltu, sltui
                opcode_result = ULA_SLTU;
                break;

            case 0b100:					// xor, xori
                opcode_result = ULA_XOR;
                break;

            case 0b101:					// srli, srai
                if (f7 == false)
                    opcode_result = ULA_SRL;
                else if (f7 == true)
                    opcode_result = ULA_SRA;
                break;

            case 0b110:					// or, ori
                opcode_result = ULA_OR;
                break;

            case 0b111:					// and, andi
                opcode_result = ULA_AND;
                break;
        }
    }
    opcode_alu.write(opcode_result);
}