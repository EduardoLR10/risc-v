#ifndef __ADDER__
#define __ADDER__

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE (adder) {
	sc_in<sc_uint<SIZE>> A, B;       // inputs
	sc_out<sc_uint<SIZE>> Z;         // output

	void proc(void);

	SC_CTOR(adder) {
		SC_METHOD(proc);
		sensitive << A << B;
	}
};

#endif
