#include "aluControl/aluControl.hpp"

void aluControl::proc() {
	sc_uint<1> op;
	sc_uint<4> opcode_result;
	sc_uint<7> f7;
	sc_uint<3> f3;


	f7 = ex_funct7.read();
	f3 = ex_funct3.read();
	op = alu_op.read();

	if (op == 0)			// memory access, AUIPC, LUI
		opcode_result = 0b0000;

	else {					// arithmetic-logic operations

		switch (f3) {		// funct3

		case 0b000:					// add, sub
			opcode_result = 0b0000;
			if(f7 == 0b0100000)
				opcode_result = 0b0001;
			break;

		case 0b001:					// slli
			opcode_result = 0b0101;
			break;

		case 0b010:					// slt, slti
			opcode_result = 0b1000;
			break;

		case 0b011:					// sltu, sltui
			opcode_result = 0b1001;
			break;

		case 0b100:					// xor, xori
			opcode_result = 0b0100;
			break;

		case 0b101:					// srli, srai
			if (f7 == 0b0000000)
				opcode_result = 0b0110;
			else if (f7 == 0b0100000)
				opcode_result = 0b0111;
			break;

		case 0b110:					// or, ori
			opcode_result = 0b0011;
			break;

		case 0b111:					// and, andi
			opcode_result = 0b0010;
			break;
		}
		//}
	}

	opcode_alu.write(opcode_result);
}