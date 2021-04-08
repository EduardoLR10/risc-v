#ifndef __REG_EX_H__
#define __REG_EX_H__

#include <systemc.h>
#include "top/macros.hpp"

// ************************** ID/EX
SC_MODULE (reg_EX){
    // control
    sc_in< sc_uint<5> > ex_ctrl;
    sc_in< sc_uint<3> > mem_ctrl;
    sc_in< sc_uint<2> > wb_ctrl;
    sc_out< bool > alu_src;
    sc_out< sc_uint<4> > alu_op;
    sc_out< sc_uint<3> > mem_ctrl;
    sc_out< sc_uint<2> > wb_ctrl;
    
    // data
    sc_in< sc_uint<5> > id_rs1, id_rs2, id_rd;
    sc_in< sc_uint<SIZE> > id_imm, id_regA, id_regB;
    sc_in<bool> clk, wren, rst;
    sc_out< sc_uint<5> > ex_rs1, ex_rs2, ex_rd;
    sc_out< sc_uint<SIZE> > ex_imm, ex_regA, ex_regB;

    void load();

    SC_CTOR(reg_EX) {
        SC_METHOD(load);
        sensitive << clk.pos();
    }

private:
    sc_uint<SIZE> imm_buf, regA_buf, regB_buf;
    sc_uint<5> rs1_buf, rs2_buf, rd_buf;
};

#endif
