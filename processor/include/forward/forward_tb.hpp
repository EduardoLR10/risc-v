#ifndef __FORWARD_TB__
#define __FORWARD_TB__

#include <systemc.h>

SC_MODULE(forward_tb) {
	sc_out< sc_uint<5> > ID_EX_rs1, ID_EX_rs2, EX_MEM_rd, MEM_WB_rd;
	sc_out< bool > EX_MEM_write, MEM_WB_write;
	sc_in< sc_uint<2> > forwardA, forwardB;

	void aciona();

	SC_CTOR(forward_tb) {
		SC_THREAD(aciona);
	}
};

#endif