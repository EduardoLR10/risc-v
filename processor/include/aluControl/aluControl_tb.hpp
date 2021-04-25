#ifndef __ALUCONTROL_TB__
#define __ALUCONTROL_TB__

#include <systemc.h>

SC_MODULE(aluControl_tb) {
	sc_out< sc_uint<7> > ex_funct7;
	sc_out< sc_uint<3> > ex_funct3;
	sc_out< bool > alu_op;
	sc_in< sc_uint<4> > opcode_alu;

	void aciona();

	SC_CTOR(aluControl_tb) {
		SC_THREAD(aciona);
	}

};

#endif