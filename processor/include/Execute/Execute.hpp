//
// Created by Ricardo Jacobi on 22/05/21.
//

#ifndef DEBUG_EXECUTE_H
#define DEBUG_EXECUTE_H

#include <systemc.h>
#include "top/macros.hpp"
#include "aluControl/aluControl.hpp"
#include "ula/ula.hpp"
#include "mux2/mux2.hpp"
#include "mux3/mux3.hpp"
#include "eforward/eforward.hpp"
#include "signals/signals.hpp"

SC_MODULE(Execute) {
    // inputs
    sc_in< sc_uint<SIZE> > ex_pc, ex_ra, ex_rb, ex_imm, wb_mux_data, mem_alu_out;
    sc_in< bool > alu_src_B, funct7, alu_op, mem_breg_wren, wb_breg_wren;
    sc_in< sc_uint<5> > ex_rs1, ex_rs2, ex_rd, mem_rd, wb_rd;
    sc_in< sc_uint<2> > alu_src_A;
    sc_in< sc_uint<3> > funct3;
    // outputs
    sc_out< sc_uint<SIZE> > alu_out, alu_in_B;

    SC_CTOR(Execute):
            EXECUTE_ULA("EXECUTE_ULA"), EXECUTE_EFORWARD("EXECUTE_FORWARD"), EXECUTE_ALUCONTROL("EXECUTE_ALUCONTROL"),
            EXECUTE_MUX_FORWARDA("EXECUTE_MUX_FORWARDA"), EXECUTE_MUX_FORWARDB("EXECUTE_MUX_FORWARDB"),
            EXECUTE_MUX_ALUA("EXECUTE_MUX_ALUA"), EXECUTE_MUX_ALUB("EXECUTE_MUX_ALUB")
    {
        EXECUTE_MUX_FORWARDA.in0(ex_ra);
        EXECUTE_MUX_FORWARDA.in1(wb_mux_data);
        EXECUTE_MUX_FORWARDA.in2(mem_alu_out);
        EXECUTE_MUX_FORWARDA.sel(forward_a);
        EXECUTE_MUX_FORWARDA.Z(mux_forward_a);

        EXECUTE_MUX_FORWARDB.in0(ex_rb);
        EXECUTE_MUX_FORWARDB.in1(wb_mux_data);
        EXECUTE_MUX_FORWARDB.in2(mem_alu_out);
        EXECUTE_MUX_FORWARDB.sel(forward_b);
        EXECUTE_MUX_FORWARDB.Z(mux_forward_b);

        EXECUTE_MUX_ALUA.in0(K_ZERO);
        EXECUTE_MUX_ALUA.in1(ex_pc);
        EXECUTE_MUX_ALUA.in2(mux_forward_a);
        EXECUTE_MUX_ALUA.sel(alu_src_A);
        EXECUTE_MUX_ALUA.Z(mux_alu_a);

        EXECUTE_MUX_ALUB.in0(mux_forward_b);
        EXECUTE_MUX_ALUB.in1(ex_imm);
        EXECUTE_MUX_ALUB.sel(alu_src_B);
        EXECUTE_MUX_ALUB.Z(mux_alu_b);

        EXECUTE_EFORWARD.ID_EX_rs1(ex_rs1);
        EXECUTE_EFORWARD.ID_EX_rs2(ex_rs2);
        EXECUTE_EFORWARD.EX_MEM_rd(mem_rd);
        EXECUTE_EFORWARD.MEM_WB_rd(wb_rd);
        EXECUTE_EFORWARD.EX_MEM_write(mem_breg_wren);
        EXECUTE_EFORWARD.MEM_WB_write(wb_breg_wren);
        EXECUTE_EFORWARD.forwardA(forward_a);
        EXECUTE_EFORWARD.forwardB(forward_b);

        EXECUTE_ALUCONTROL.ex_funct7(funct7);
        EXECUTE_ALUCONTROL.ex_funct3(funct3);
        EXECUTE_ALUCONTROL.alu_op(alu_op);
        EXECUTE_ALUCONTROL.opcode_alu(opcode_alu);

        EXECUTE_ULA.a(mux_alu_a);
        EXECUTE_ULA.b(mux_alu_b);
        EXECUTE_ULA.z(alu_out);
        EXECUTE_ULA.ula_op(opcode_alu);
        EXECUTE_ULA.zero(zero_alu);
    };
private:
    ula EXECUTE_ULA;
    eforward EXECUTE_EFORWARD;
    aluControl EXECUTE_ALUCONTROL;
    mux3<sc_uint<SIZE> > EXECUTE_MUX_FORWARDA;
    mux3<sc_uint<SIZE> > EXECUTE_MUX_FORWARDB;
    mux3<sc_uint<SIZE> > EXECUTE_MUX_ALUA;
    mux2<sc_uint<SIZE> > EXECUTE_MUX_ALUB;

    sc_signal< sc_uint<SIZE> > mux_forward_a;
    sc_signal< sc_uint<SIZE> > mux_forward_b;
    sc_signal< sc_uint<SIZE> > mux_alu_a;
    sc_signal< sc_uint<SIZE> > mux_alu_b;
    sc_signal< sc_uint<2> > forward_a;              // select mux forward A
    sc_signal< sc_uint<2> > forward_b;              // select mux forward B
    sc_signal< sc_uint<4> > opcode_alu;             // alu opcode

};

#endif //DEBUG_EXECUTE_H
