#include <systemc.h>
#include "dforward/dforward.hpp"
#include "dforward/dforward_tb.hpp"

SC_MODULE ( topDFORWARD ) {

    dforward DFORWARD;
    dforward_tb DFORWARD_tb;

    sc_signal< sc_uint<5> > rs1, rs2, rd;
	sc_signal< bool > rAOut, rBOut;

    SC_CTOR(topWFORWARD): DFORWARD("DFORWARD"), DFORWARD_tb("DFORWARD_tb") {
		DFORWARD.rs1(rs1);		    DFORWARD_tb.rs1(rs1);
        DFORWARD.rs2(rs2);          DFORWARD_tb.rs2(rs2);
        DFORWARD.rd(rd);            DFORWARD_tb.rd(rd);
		DFORWARD.rAOut(rAOut);		DFORWARD_tb.rAOut(rAOut);
        DFORWARD.rBOut(rBOut);      DFORWARD_tb.rBOut(rBOut);
		
	}
};
