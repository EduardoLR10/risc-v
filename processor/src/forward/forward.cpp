#include "forward/forward.hpp"

void forward::proc() {
	sc_uint<5> idex_rs1, idex_rs2, exmem_rd, memwb_rd;
	sc_uint<1> exmem_write, memwb_write;
	sc_uint<2> forwA = 0, forwB = 0;

	idex_rs1 = ID_EX_rs1.read();
	idex_rs2 = ID_EX_rs2.read();
	exmem_rd = EX_MEM_rd.read();
	memwb_rd = MEM_WB_rd.read();
	exmem_write = EX_MEM_write.read();
	memwb_write = MEM_WB_write.read();

	if (exmem_write && exmem_rd != 0) {
		if (exmem_rd == idex_rs1)
			forwA = 2;
		if (exmem_rd == idex_rs2)
			forwB = 2;
	}

	if (memwb_write && memwb_rd != 0 && !(exmem_write && exmem_rd != 0)) {
		if (exmem_rd != idex_rs1 && memwb_rd == idex_rs1)
			forwA = 1;
		if (exmem_rd != idex_rs2 && memwb_rd == idex_rs2)
			forwB = 1;
	}

	forwardA.write(forwA);
	forwardB.write(forwB);
}