#include "genImm32/genImm32_tb.hpp"

void genImm32_tb::aciona() {
    instruction = 0x000002b3;
    wait(1, SC_NS);
    std::cout << "Ins = " << std::setw(W) << std::hex << instruction.read();
    std::cout << " Imm = " << imm.read() << std::endl << std::endl;

    instruction = 0x01002283;
    wait(1, SC_NS);
    std::cout << "Ins = " << std::setw(W) << std::hex << instruction.read();
    std::cout << " Imm = " << imm.read() << std::endl << std::endl;

    instruction = 0xf9c00313;
    wait(1, SC_NS);
    std::cout << "Ins = " << std::setw(W) << std::hex << instruction.read();
    std::cout << " Imm = " << imm.read() << std::endl << std::endl;

    instruction = 0xfff2c293;
    wait(1, SC_NS);
    std::cout << "Ins = " << std::setw(W) << std::hex << instruction.read();
    std::cout << " Imm = " << imm.read() << std::endl << std::endl;

    instruction = 0x16200313;
    wait(1, SC_NS);
    std::cout << "Ins = " << std::setw(W) << std::hex << instruction.read();
    std::cout << " Imm = " << imm.read() << std::endl << std::endl;

    instruction = 0x01800067;
    wait(1, SC_NS);
    std::cout << "Ins = " << std::setw(W) << std::hex << instruction.read();
    std::cout << " Imm = " << imm.read() << std::endl << std::endl;

    instruction = 0x00002437;
    wait(1, SC_NS);
    std::cout << "Ins = " << std::setw(W) << std::hex << instruction.read();
    std::cout << " Imm = " << imm.read() << std::endl << std::endl;

    instruction = 0x02542e23;
    wait(1, SC_NS);
    std::cout << "Ins = " << std::setw(W) << std::hex << instruction.read();
    std::cout << " Imm = " << imm.read() << std::endl << std::endl;

    instruction = 0xfe5290e3;
    wait(1, SC_NS);
    std::cout << "Ins = " << std::setw(W) << std::hex << instruction.read();
    std::cout << " Imm = " << imm.read() << std::endl << std::endl;

    instruction = 0x00c000ef;
    wait(1, SC_NS);
    std::cout << "Ins = " << std::setw(W) << std::hex << instruction.read();
    std::cout << " Imm = " << imm.read() << std::endl << std::endl;

}