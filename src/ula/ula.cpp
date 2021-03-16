#include "ula/ula.hpp"

void ula::proc() {
	sc_int<SIZE> a, b, z;

	a = A.read();
	b = B.read();

	switch(opcode.read()) {
		case ALU_ADD:    z = a + b;  break;
		case ALU_SUB:    z = a - b;  break;
		case ALU_AND:    z = a & b;  break;
		case ALU_OR:     z = a | b;  break;
		case ALU_XOR:    z = a ^ b;  break;
		case ALU_SLL:    z = ((sc_uint<SIZE>)a << (sc_uint<SIZE>)b);     break;
		case ALU_SRL:    z = ((sc_uint<SIZE>)a >> (sc_uint<SIZE>)b);	 break;
		case ALU_SRA:    z = (a >> (sc_uint<SIZE>)b);	break;
		case ALU_SLT:    z = ((a < ((unsigned)b)) ? 1 : 0);	break;
		case ALU_SLTU:    z = (((sc_uint<SIZE>)a < (sc_uint<SIZE>)b) ? 1 : 0);     break;
		case ALU_SGE:    z = ((a >= b) ? 1 : 0);     break;
		case ALU_SGEU:    z = (((sc_uint<SIZE>)a >= (sc_uint<SIZE>)b) ? 1 : 0);     break;
		case ALU_SEQ:    z = ((a == b) ? 1 : 0);     break;
		case ALU_SNE:    z = ((a != b) ? 1 : 0);     break;
		default: std::cout << "Error! Invalid Opcode!" << std::endl; z = 0; break;
	}

	Z.write(z);
	zero.write(z == 0);
}
