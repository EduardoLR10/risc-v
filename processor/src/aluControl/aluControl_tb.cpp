#include "aluControl/aluControl_tb.hpp"

void aluControl_tb::aciona() {
	ex_funct7 = 0b0000000;		ex_funct3 = 0b000;		alu_op = 0;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;

	ex_funct7 = 0b1111111;		ex_funct3 = 0b111;		alu_op = 0;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;

	ex_funct7 = 0b0000000;		ex_funct3 = 0b000;		alu_op = 1;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;

	ex_funct7 = 0b0100000;		ex_funct3 = 0b000;		alu_op = 1;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;

	ex_funct7 = 0b1000100;		ex_funct3 = 0b111;		alu_op = 1;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;

	ex_funct7 = 0b0111100;		ex_funct3 = 0b010;		alu_op = 1;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;

	ex_funct7 = 0b0100110;		ex_funct3 = 0b110;		alu_op = 1;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;

	ex_funct7 = 0b0101001;		ex_funct3 = 0b100;		alu_op = 1;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;

	ex_funct7 = 0b1110000;		ex_funct3 = 0b001;		alu_op = 1;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;

	ex_funct7 = 0b0000000;		ex_funct3 = 0b101;		alu_op = 1;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;

	ex_funct7 = 0b0100000;		ex_funct3 = 0b101;		alu_op = 1;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;

	ex_funct7 = 0b0101001;		ex_funct3 = 0b011;		alu_op = 1;
	wait(1, SC_NS);
	std::cout << "Funct7 = " << hex << ex_funct7 << "\tFunct3 = " << hex << ex_funct3 <<
		"\tAlu_op = " << alu_op << "\nOpcode Alu = " << hex << opcode_alu << std::endl << std::endl;
}