#include "breg/breg.hpp"

void breg::write() {
	if (wren == 1) 
		bank[rd.read()] = d_in.read();
}
	
void breg::read() {
    ra.write((rs1.read() == 0)?(sc_int<SIZE>)0 : bank[rs1.read()]);
    rb.write((rs2.read() == 0)?(sc_int<SIZE>)0 : bank[rs2.read()]);
}