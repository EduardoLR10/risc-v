#include "dbranch/dbranch_tb.hpp"

void dbranch_tb::aciona() {
    ra = 0x0000ffff; rb = 0x0000ffff; opcode = BEQ;
    wait(1, SC_NS);
    std::cout << "ra = " << std::setw(W) << std::hex << ra.read();
    std::cout << " rb = " << std::setw(W) << rb.read();
    std::cout << " op = " << std::setw(W) << opcode.read();
    std::cout << " Bout = " << Bout << std::endl << std::endl;

    ra = 0x0000ffff; rb = 0x0000ffff; opcode = BNE;
    wait(1, SC_NS);
    std::cout << "ra = " << std::setw(W) << std::hex << ra.read();
    std::cout << " rb = " << std::setw(W) << rb.read();
    std::cout << " op = " << std::setw(W) << opcode.read();
    std::cout << " Bout = " << Bout << std::endl << std::endl;

    ra = 0x0fffffff; rb = 0x0000ffff; opcode = BLT;
    wait(1, SC_NS);
    std::cout << "ra = " << std::setw(W) << std::hex << ra.read();
    std::cout << " rb = " << std::setw(W) << rb.read();
    std::cout << " op = " << std::setw(W) << opcode.read();
    std::cout << " Bout = " << Bout << std::endl << std::endl;

    ra = 0xffffffff; rb = 0x0000ffff; opcode = BLT;
    wait(1, SC_NS);
    std::cout << "ra = " << std::setw(W) << std::hex << ra.read();
    std::cout << " rb = " << std::setw(W) << rb.read();
    std::cout << " op = " << std::setw(W) << opcode.read();
    std::cout << " Bout = " << Bout << std::endl << std::endl;

    ra = 0x0fffffff; rb = 0x0000ffff; opcode = BGE;
    wait(1, SC_NS);
    std::cout << "ra = " << std::setw(W) << std::hex << ra.read();
    std::cout << " rb = " << std::setw(W) << rb.read();
    std::cout << " op = " << std::setw(W) << opcode.read();
    std::cout << " Bout = " << Bout << std::endl << std::endl;

    ra = 0xffffffff; rb = 0x0000ffff; opcode = BGE;
    wait(1, SC_NS);
    std::cout << "ra = " << std::setw(W) << std::hex << ra.read();
    std::cout << " rb = " << std::setw(W) << rb.read();
    std::cout << " op = " << std::setw(W) << opcode.read();
    std::cout << " Bout = " << Bout << std::endl << std::endl;

}