#ifndef __ADDER__
#define __ADDER__

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE (adder) {
	sc_in<sc_uint<SIZE>> A, B;       // inputs
	sc_in<bool> Cin;
	sc_out<sc_uint<SIZE>> C;         // output
	sc_out<bool> Cout;         // zero flag

	void proc(void);

	SC_CTOR(adder) {
		SC_METHOD(proc);
		sensitive << A << B << Cin;
	}
};

#endif
