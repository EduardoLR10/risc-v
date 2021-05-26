//
// Created by Ricardo Jacobi on 18/05/21.
//

#ifndef DEBUG_FETCH_H
#define DEBUG_FETCH_H

#include <systemc.h>
#include "top/macros.hpp"
#include "pc/pc.hpp"
#include "adder/adder.hpp"
#include "mux2/mux2.hpp"
#include "instruction_memory/instruction_memory.hpp"


SC_MODULE(Fetch) {
    sc_in< bool > clock;
    sc_in< sc_uint<SIZE> > pc_branch_in;
    sc_in< bool > fetch_sel_in, wren_pc_in;
    sc_out< sc_uint<SIZE> > next_pc_out;
    sc_out< sc_uint<SIZE> > instruction_out;
    sc_out< sc_uint<SIZE> > pc_out;

    void update( void ) {
        pc_out.write(program_counter);
        next_pc_out.write(next_pc);
    }

    SC_CTOR(Fetch) :
      FETCH_ADDER("FETCH_ADDER"), FETCH_PC("FETCH_PC"), FETCH_MUX("FETCH_MUX"),
      FETCH_INSTRUCTION_MEMORY("FETCH_INSTRUCTION_MEMORY")
      {
        SC_METHOD(update);
          sensitive << program_counter << next_pc;

        K_FOUR.write(4);
        K_ONE.write(1);

        FETCH_INSTRUCTION_MEMORY.load_contents("decode.bin");
        FETCH_ADDER.A(K_FOUR);
        FETCH_ADDER.B(program_counter);
        FETCH_ADDER.Z(next_pc);

        FETCH_PC.pc_in(pc_in);
        FETCH_PC.ld_pc(K_ONE);
        FETCH_PC.clock(clock);
        FETCH_PC.pc_out(program_counter);

        FETCH_MUX.in0(next_pc);
        FETCH_MUX.in1(pc_branch_in);
        FETCH_MUX.sel(fetch_sel_in);
        FETCH_MUX.Z(pc_in);

        FETCH_INSTRUCTION_MEMORY.address(program_counter);
        FETCH_INSTRUCTION_MEMORY.out(instruction_out);
    }

private:
    adder FETCH_ADDER;
    pc FETCH_PC;
    mux2<sc_uint<SIZE>> FETCH_MUX;
    InstructionMemory FETCH_INSTRUCTION_MEMORY;
    sc_signal< sc_uint<SIZE> > K_FOUR;
    sc_signal< bool > K_ONE;
    sc_signal< sc_uint<SIZE> >
            program_counter,        // riscv pc
            pc_in,                  // pc input, from mux
            next_pc;                // output of pc adder

};

#endif //DEBUG_FETCH_H
