#include <systemc.h>
#include "aluControl/aluControl.hpp"
#include "aluControl/aluControl_tb.hpp"

SC_MODULE( topALUCONTROL ) {
	aluControl ALUCONTROL;
	aluControl_tb ALUCONTROL_tb;

	sc_signal< sc_uint<7> > ex_funct7;
	sc_signal< sc_uint<3> > ex_funct3;
	sc_signal< bool > alu_op;
	sc_signal< sc_uint<4> > opcode_alu;

	SC_CTOR( topALUCONTROL ) : ALUCONTROL("ALUCONTROL"), ALUCONTROL_tb("ALUCONTROL_tb") {
		ALUCONTROL.ex_funct7(ex_funct7);			ALUCONTROL_tb.ex_funct7(ex_funct7);
		ALUCONTROL.ex_funct3(ex_funct3);			ALUCONTROL_tb.ex_funct3(ex_funct3);
		ALUCONTROL.alu_op(alu_op);					ALUCONTROL_tb.alu_op(alu_op);
		ALUCONTROL.opcode_alu(opcode_alu);			ALUCONTROL_tb.opcode_alu(opcode_alu);
	}
};