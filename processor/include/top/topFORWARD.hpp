#include <systemc.h>
#include "forward/forward.hpp"
#include "forward/forward_tb.hpp"

SC_MODULE ( topFORWARD ) {
	forward FORWARD;
	forward_tb FORWARD_tb;

	sc_signal< sc_uint<5> > ID_EX_rs1, ID_EX_rs2, EX_MEM_rd, MEM_WB_rd;
	sc_signal< bool >	EX_MEM_write, MEM_WB_write; // CHECAR O TAMANHO DO SINAL DE CONTROLE
	sc_signal< sc_uint<2> > forwardA, forwardB;

	SC_CTOR( topFORWARD ) : FORWARD("FORWARD"), FORWARD_tb("FORWARD_tb") {
		FORWARD.ID_EX_rs1(ID_EX_rs1);			FORWARD_tb.ID_EX_rs1(ID_EX_rs1);
		FORWARD.ID_EX_rs2(ID_EX_rs2);			FORWARD_tb.ID_EX_rs2(ID_EX_rs2);
		FORWARD.EX_MEM_rd(EX_MEM_rd);			FORWARD_tb.EX_MEM_rd(EX_MEM_rd);
		FORWARD.MEM_WB_rd(MEM_WB_rd);			FORWARD_tb.MEM_WB_rd(MEM_WB_rd);
		FORWARD.EX_MEM_write(EX_MEM_write);		FORWARD_tb.EX_MEM_write(EX_MEM_write);
		FORWARD.MEM_WB_write(MEM_WB_write);		FORWARD_tb.MEM_WB_write(MEM_WB_write);
		FORWARD.forwardA(forwardA);				FORWARD_tb.forwardA(forwardA);
		FORWARD.forwardB(forwardB);				FORWARD_tb.forwardB(forwardB);
	}
};