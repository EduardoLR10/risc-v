#ifndef __ALUCONTROL__
#define __ALUCONTROL__

#include <systemc.h>

SC_MODULE(aluControl) {
	sc_in< sc_uint<7> > ex_funct7;
	sc_in< sc_uint<3> > ex_funct3;
	sc_in< bool > alu_op;
	sc_out< sc_uint<4> > opcode_alu;

	void proc(void);

	SC_CTOR(aluControl) {
		SC_METHOD(proc);
		sensitive << ex_funct7 << ex_funct3 << alu_op;
	}
};

#endif