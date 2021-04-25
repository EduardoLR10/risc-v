#include <systemc.h>
#include "wforward/wforward.hpp"
#include "wforward/wforward_tb.hpp"

SC_MODULE ( topWFORWARD ) {

    wforward WFORWARD;
    wforward_tb WFORWARD_tb;

    sc_signal< sc_uint<5> > rs1, rs2, rd;
	sc_signal< bool > rAOut, rBOut;

    SC_CTOR(topWFORWARD): WFORWARD("WFORWARD"), WFORWARD_tb("WFORWARD_tb") {
		WFORWARD.rs1(rs1);		    WFORWARD_tb.rs1(rs1);
        WFORWARD.rs2(rs2);          WFORWARD_tb.rs2(rs2);
        WFORWARD.rd(rd);            WFORWARD_tb.rd(rd);
		WFORWARD.rAOut(rAOut);		WFORWARD_tb.rAOut(rAOut);
        WFORWARD.rBOut(rBOut);      WFORWARD_tb.rBOut(rBOut);
		
	}
};