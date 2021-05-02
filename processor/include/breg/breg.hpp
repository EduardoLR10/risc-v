#ifndef __BREG__
#define __BREG__

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE(breg) {
	sc_in< sc_uint<5> > rs1, rs2, rd;
	sc_in< sc_uint<SIZE> > d_in;
	sc_in< bool > wren, clk;
	sc_out< sc_uint<SIZE> > ra, rb;
	
    void write(void);
    void read(void);

	SC_CTOR(breg) {
		SC_METHOD(write);
		sensitive << clk.pos();
		
		SC_METHOD(read);
		sensitive << rs1 << rs2 << rd << d_in << wren << clk;
	}
	
private:
	sc_uint<SIZE> bank[32];
	
};

#endif