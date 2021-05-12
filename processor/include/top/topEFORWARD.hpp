#include <systemc.h>
#include "eforward/eforward.hpp"
#include "eforward/eforward_tb.hpp"

SC_MODULE ( topEFORWARD ) {
	eforward EFORWARD;
	eforward_tb EFORWARD_tb;

	sc_signal< sc_uint<5> > ID_EX_rs1, ID_EX_rs2, EX_MEM_rd, MEM_WB_rd;
	sc_signal< bool >	EX_MEM_write, MEM_WB_write;
	sc_signal< sc_uint<2> > forwardA, forwardB;

	SC_CTOR( topEFORWARD ) : EFORWARD("FORWARD"), EFORWARD_tb("FORWARD_tb") {
		EFORWARD.ID_EX_rs1(ID_EX_rs1);			EFORWARD_tb.ID_EX_rs1(ID_EX_rs1);
		EFORWARD.ID_EX_rs2(ID_EX_rs2);			EFORWARD_tb.ID_EX_rs2(ID_EX_rs2);
		EFORWARD.EX_MEM_rd(EX_MEM_rd);			EFORWARD_tb.EX_MEM_rd(EX_MEM_rd);
		EFORWARD.MEM_WB_rd(MEM_WB_rd);			EFORWARD_tb.MEM_WB_rd(MEM_WB_rd);
		EFORWARD.EX_MEM_write(EX_MEM_write);		EFORWARD_tb.EX_MEM_write(EX_MEM_write);
		EFORWARD.MEM_WB_write(MEM_WB_write);		EFORWARD_tb.MEM_WB_write(MEM_WB_write);
		EFORWARD.forwardA(forwardA);				EFORWARD_tb.forwardA(forwardA);
		EFORWARD.forwardB(forwardB);				EFORWARD_tb.forwardB(forwardB);
	}
};
