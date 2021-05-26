//
// Created by Ricardo Jacobi on 18/05/21.
//

#ifndef DEBUG_DECODE_H
#define DEBUG_DECODE_H


#include <systemc.h>
#include "adder/adder.hpp"
#include "breg/breg.hpp"
#include "dbranch/dbranch.hpp"
#include "dforward/dforward.hpp"
#include "genImm32/genImm32.hpp"
#include "top/macros.hpp"
#include "mux2/mux2.hpp"
#include "mux3/mux3.hpp"
#include "signals/signals.hpp"

SC_MODULE(Decode) {
    sc_in< sc_uint<SIZE> > id_pc_i, id_inst, id_next_pc, wb_mux_data, mem_reg_data;
    sc_in< sc_uint<5> > id_rs1_i, id_rs2_i, id_rd_i, mem_rd_i, wb_rd_i;
    sc_in< bool > is_jalx, is_jalr, f_breg_wr, clock, mem_breg_wren;
    sc_in< sc_uint<2> > b_opcode;      // 0: beq  1: bne  2: blt  3: bge
    sc_out< bool > b_cond;
    sc_out< sc_uint<SIZE> > pc_branch, id_imm, breg_ra_o, breg_rb_o;

    void update();
    void dump_breg() {
        DECODE_BREG.dump_breg();
    }

    SC_CTOR(Decode) :
    DECODE_GENIMM32("DECODE_GENIMM32"), DECODE_ADDER("DECODE_ADDER"),
    DECODE_BREG("DECODE_BREG"), DECODE_DBRANCH("DECODE_DBRANCH"),
    DECODE_MUX_DBRANCH_A("DECODE_MUX_DBRANCH_A"), DECODE_MUX_DBRANCH_B("DECODE_MUX_DBRANCH_B"),
    DECODE_MUX_RETURN_ADDRESS("DECODE_MUX_BREG"),
    DECODE_MUX_ADDER("DECODE_MUX_ADDER"),
    DECODE_DFORWARD("DECODE_WFORWARD")
    {
        SC_METHOD(update);
          sensitive << breg_ra << breg_rb;

        // genImm
        DECODE_GENIMM32.instruction(id_inst);
        DECODE_GENIMM32.imm(id_imm_ws);
        // Adder
        DECODE_ADDER.A(jump_addr);
        DECODE_ADDER.B(id_imm_ws);
        DECODE_ADDER.Z(pc_branch);
        // Mux PC
        DECODE_MUX_ADDER.in0(id_pc_i);
        DECODE_MUX_ADDER.in1(breg_ra);
        DECODE_MUX_ADDER.sel(is_jalr);
        DECODE_MUX_ADDER.Z(jump_addr);
        // Breg
        DECODE_BREG.rs1(id_rs1_i);
        DECODE_BREG.rs2(id_rs2_i);
        DECODE_BREG.rd(wb_rd_i);
        DECODE_BREG.wren(f_breg_wr);
        DECODE_BREG.ra(breg_ra);
        DECODE_BREG.rb(breg_rb);
        DECODE_BREG.clk(clock);
        DECODE_BREG.d_in(wb_mux_data);
        // Mux ImmRA
        DECODE_MUX_RETURN_ADDRESS.in0(id_imm_ws);
        DECODE_MUX_RETURN_ADDRESS.in1(id_next_pc);
        DECODE_MUX_RETURN_ADDRESS.sel(is_jalx);
        DECODE_MUX_RETURN_ADDRESS.Z(id_imm);
        // DForward
        DECODE_DFORWARD.rs1(id_rs1);
        DECODE_DFORWARD.rs2(id_rs2);
        DECODE_DFORWARD.rd(mem_rd_i);
        DECODE_DFORWARD.mem_breg_wren(mem_breg_wren);
        DECODE_DFORWARD.rAOut(sel_mux_ra_dbranch);
        DECODE_DFORWARD.rBOut(sel_mux_rb_dbranch);
        // Mux DBranch A
        DECODE_MUX_DBRANCH_A.in0(breg_ra);
        DECODE_MUX_DBRANCH_A.in1(mem_reg_data);
        DECODE_MUX_DBRANCH_A.sel(sel_mux_ra_dbranch);
        DECODE_MUX_DBRANCH_A.Z(mux_dbranch_ra);
        // Mux DBranch B
        DECODE_MUX_DBRANCH_B.in0(breg_rb);
        DECODE_MUX_DBRANCH_B.in1(mem_reg_data);
        DECODE_MUX_DBRANCH_B.sel(sel_mux_rb_dbranch);
        DECODE_MUX_DBRANCH_B.Z(mux_dbranch_rb);
        // Decode DBranch
        DECODE_DBRANCH.ra(mux_dbranch_ra);
        DECODE_DBRANCH.rb(mux_dbranch_rb);
        DECODE_DBRANCH.opcode(b_opcode);
        DECODE_DBRANCH.Bout(b_cond);
    }

private:
    genImm32 DECODE_GENIMM32;
    adder DECODE_ADDER;
    breg DECODE_BREG;
    dbranch DECODE_DBRANCH;
    mux2<sc_uint<SIZE> > DECODE_MUX_DBRANCH_A;
    mux2<sc_uint<SIZE> > DECODE_MUX_DBRANCH_B;
    mux2<sc_uint<SIZE> > DECODE_MUX_RETURN_ADDRESS;
    mux2<sc_uint<SIZE> > DECODE_MUX_ADDER;
    dforward DECODE_DFORWARD;

    sc_signal< bool >
            sel_mux_ra_dbranch,
            sel_mux_rb_dbranch;


    sc_signal< sc_uint<SIZE> > id_imm_ws,              // generated immediate
                                jump_addr,              // (PC or BREG[rs1]) + Imm32
                                breg_ra,                // first breg output - a
                                breg_rb,                // second breg output - b
                                mux_dbranch_ra,         // mux output for dbranch ra
                                mux_dbranch_rb;         // mux output for dbranch rb
//    sc_signal< sc_uint<5> >
//            id_rs1,                 // rs1 instruction field in IF/ID
//            id_rs2,                 // rs2 instruction field in IF/ID
//            id_rd;                  // rd instruction field in IF/ID

};

void Decode::update() {
    breg_ra_o.write(breg_ra);
    breg_rb_o.write(breg_rb);
}

#endif //DEBUG_DECODE_H
