#include <systemc.h>
#include "breg/breg.hpp"
#include "breg/breg_tb.hpp"

SC_MODULE ( topBREG ) {

    breg BREG;
    breg_tb BREG_tb;

    sc_signal< sc_uint<5> > rs1, rs2, rd;
	sc_signal< sc_uint<SIZE> > d_in;
	sc_signal< bool > wren;
	sc_signal< sc_int<SIZE> > ra, rb;
    sc_clock clk;

    SC_CTOR(topBREG): BREG("BREG"), BREG_tb("BREG_tb"), clk("clk", 10.0, SC_NS) {
		BREG.rs1(rs1);		BREG_tb.rs1(rs1);
        BREG.rs2(rs2);      BREG_tb.rs2(rs2);
        BREG.rd(rd);        BREG_tb.rd(rd);
		BREG.d_in(d_in);    BREG_tb.d_in(d_in);
		BREG.wren(wren);	BREG_tb.wren(wren);
        BREG.clk(clk);      BREG_tb.clk(clk);
		BREG.ra(ra);		BREG_tb.ra(ra);
        BREG.rb(rb);        BREG_tb.rb(rb);
		
	}
};