#ifndef __EFORWARD__
#define __EFORWARD__

#include <systemc.h>

SC_MODULE(eforward) {
	sc_in< sc_uint<5> > ID_EX_rs1, ID_EX_rs2, EX_MEM_rd, MEM_WB_rd;
	sc_in< bool > EX_MEM_write, MEM_WB_write;
	sc_out< sc_uint<2> > forwardA, forwardB;

	void proc(void);

	SC_CTOR(eforward) {
		SC_METHOD(proc);
		sensitive << ID_EX_rs1 << ID_EX_rs2 << EX_MEM_rd << MEM_WB_rd << EX_MEM_write << MEM_WB_write;
	}
};

#endif
