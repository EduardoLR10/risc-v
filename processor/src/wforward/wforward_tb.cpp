#include "wforward/wforward_tb.hpp"

void wforward_tb::aciona() {
    rs1 = 1; rs2 = 0; rd = 1;
    wait(1, SC_NS);
    std::cout << "rs1 = " << std::setw(W) << rs1.read();
    std::cout << " rs2 = " << std::setw(W) << rs2.read();
    std::cout << " rd = " << std::setw(W) << rd.read();
    std::cout << " raOut = " << std::setw(W) << rAOut.read();
    std::cout << " rbOut = " << std::setw(W) << rBOut.read() << std::endl;

    rs1 = 1; rs2 = 15; rd = 15;
    wait(1, SC_NS);
    std::cout << "rs1 = " << std::setw(W) << rs1.read();
    std::cout << " rs2 = " << std::setw(W) << rs2.read();
    std::cout << " rd = " << std::setw(W) << rd.read();
    std::cout << " raOut = " << std::setw(W) << rAOut.read();
    std::cout << " rbOut = " << std::setw(W) << rBOut.read() << std::endl;

    rs1 = 10; rs2 = 20; rd = 5;
    wait(1, SC_NS);
    std::cout << "rs1 = " << std::setw(W) << rs1.read();
    std::cout << " rs2 = " << std::setw(W) << rs2.read();
    std::cout << " rd = " << std::setw(W) << rd.read();
    std::cout << " raOut = " << std::setw(W) << rAOut.read();
    std::cout << " rbOut = " << std::setw(W) << rBOut.read() << std::endl;

    rs1 = 3; rs2 = 3; rd = 3;
    wait(1, SC_NS);
    std::cout << "rs1 = " << std::setw(W) << rs1.read();
    std::cout << " rs2 = " << std::setw(W) << rs2.read();
    std::cout << " rd = " << std::setw(W) << rd.read();
    std::cout << " raOut = " << std::setw(W) << rAOut.read();
    std::cout << " rbOut = " << std::setw(W) << rBOut.read() << std::endl;

}