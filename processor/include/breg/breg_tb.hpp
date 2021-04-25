#ifndef __BREG_TB__
#define __BREG_TB__

#include <systemc.h>
#include "top/macros.hpp"
#include <string>
#include <iomanip>

SC_MODULE(breg_tb) {
    sc_out< sc_uint<5> > rs1, rs2, rd;
	sc_out< sc_int<SIZE> > d_in;
	sc_out< bool > wren;
    sc_in< bool > clk;
	sc_in< sc_int<SIZE> > ra, rb;
	
	void drive();
	void monitor();

	SC_CTOR(breg_tb) {
		SC_THREAD(drive);
		sensitive << clk.neg();
		SC_METHOD(monitor);
		sensitive << clk.pos();
		
	}

};

#endif


