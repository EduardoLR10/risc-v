#include "ula/ula_tb.hpp"

void ula_tb::aciona() {
    std::cout << "Testing ALU_ADD" << std::endl;
    A = 0x0000ffff; B = 0; opcode = ALU_ADD;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0xffffffff; B = 0x00000001; opcode = ALU_ADD;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;
    
    std::cout << "Testing ALU_SUB" << std::endl;
    A = 0x00000fff; B = 0X00000ffe; opcode = ALU_SUB;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0x80008000; B = 0x0fff0fff; opcode = ALU_SUB;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_AND" << std::endl;
    A = 0x0000ffff; B = 0Xffff0000; opcode = ALU_AND;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0xf0f0f0f0; B = 0xffffffff; opcode = ALU_AND;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_OR" << std::endl;
    A = 0x0000ffff; B = 0Xffff0000; opcode = ALU_OR;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0xf0f0f0f0; B = 0x0f0f0f0f; opcode = ALU_OR;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_XOR" << std::endl;
    A = 0x0000ffff; B = 0X00000000; opcode = ALU_XOR;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0xffffffff; B = 0xffffffff; opcode = ALU_XOR;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_SLL" << std::endl;
    A = 0x000000ff; B = 0X00000004; opcode = ALU_SLL;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0x00000ff0; B = 0x00000008; opcode = ALU_SLL;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_SRL" << std::endl;
    A = 0xffffff00; B = 0X00000004; opcode = ALU_SRL;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0xfffff000; B = 0x00000008; opcode = ALU_SRL;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_SRA" << std::endl;
    A = 0xfffffff0; B = 0X00000004; opcode = ALU_SRA;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0x0fff0f00; B = 0x00000008; opcode = ALU_SRA;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_SLT" << std::endl;
    A = 0xffffffff; B = 0X00000004; opcode = ALU_SLT;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0x0fff0fff; B = 0x00000008; opcode = ALU_SLT;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_SLTU" << std::endl;
    A = 0xffffffff; B = 0X00000004; opcode = ALU_SLTU;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0x0fff0fff; B = 0xffffffff; opcode = ALU_SLTU;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_SGE" << std::endl;
    A = 0xffffffff; B = 0X00000004; opcode = ALU_SGE;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0x0fff0fff; B = 0x00000004; opcode = ALU_SGE;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_SGEU" << std::endl;
    A = 0xffffffff; B = 0X00000004; opcode = ALU_SGEU;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0x0fff0fff; B = 0xffffffff; opcode = ALU_SGEU;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_SEQ" << std::endl;
    A = 0xffffffff; B = 0X00000000; opcode = ALU_SEQ;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0x0fff0fff; B = 0x0fff0fff; opcode = ALU_SEQ;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    std::cout << "Testing ALU_SNE" << std::endl;
    A = 0xffffffff; B = 0X00000000; opcode = ALU_SNE;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

    A = 0x0fff0fff; B = 0x0fff0fff; opcode = ALU_SNE;
    wait(1, SC_NS);
    std::cout << "A = " << std::setw(W) << std::hex << A.read();
    std::cout << " B = " << std::setw(W) << B.read();
    std::cout << " Z = " << std::setw(W) << Z.read();
    std::cout << " zero = " << zero << std::endl;

}