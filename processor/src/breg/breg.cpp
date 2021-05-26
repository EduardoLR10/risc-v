#include "breg/breg.hpp"

void breg::write() {
	if (wren == 1) {
        bank[rd.read()] = d_in.read();
        std::cout << "BREG.write: rd = " << rd.read() << " data = " << d_in.read() << std::endl;
    }

//    for (int i = 0; i < 8; i++) {
//        std::cout << "W " << i << " " << bank[i] << std::endl;
//    }
}
	
void breg::read() {
    if (rd.read() == rs1.read()) {
        ra.write(d_in.read());
    } else {
        ra.write((rs1.read() == 0) ? (sc_int<SIZE>) 0 : bank[rs1.read()]);
    }
    if (rd.read() == rs2.read()) {
        rb.write(d_in.read());
    } else {
        rb.write((rs2.read() == 0) ? (sc_int<SIZE>) 0 : bank[rs2.read()]);
    }
}

void breg::dump_breg() {
    for (int i = 0; i < 32; i++) {
        std::cout << "R " << i << " " << std::dec << bank[i] << std::hex << " " << bank[i] << std::endl;
    }
}