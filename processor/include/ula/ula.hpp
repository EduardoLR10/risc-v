#ifndef __ULA_H__
#define __ULA_H__

#include <systemc.h>
#include "top/macros.hpp"

enum OPCODE {
    ALU_ADD, ALU_SUB, ALU_AND, ALU_OR, ALU_XOR, ALU_SLL, ALU_SRL, ALU_SRA, ALU_SLT, ALU_SLTU, ALU_SGE, ALU_SGEU, ALU_SEQ, ALU_SNE,
};

SC_MODULE (ula) {
  sc_in<sc_uint<4>> opcode;
  sc_in<sc_uint<SIZE>> A, B;       // inputs
  sc_out<sc_uint<SIZE>> Z;         // output
  sc_out<bool> zero;         // zero flag

  void proc(void);

  SC_CTOR(ula) {
    SC_METHOD(proc);
    sensitive << A << B << opcode;
  }
};

#endif
