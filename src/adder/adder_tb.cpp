#include "adder/adder_tb.hpp"

void adder_tb::aciona() {
    A = 0x0000ffff; B = 0; Cin = true;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Cin = " << std::setw(W) << Cin.read();
    std::cout << " C = " << std::setw(W) << C.read();
    std::cout << " Cout = " << Cout << std::endl << std::endl;

    A = 0xffffffff; B = 0x00000001; Cin = false;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Cin = " << std::setw(W) << Cin.read();
    std::cout << " C = " << std::setw(W) << C.read();
    std::cout << " Cout = " << Cout << std::endl << std::endl;

}