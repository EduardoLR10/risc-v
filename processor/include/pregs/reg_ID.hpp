#ifndef __REG_ID_H__
#define __REG_ID_H__

#include <systemc.h>
#include "top/macros.hpp"

// ************************** IF/ID
SC_MODULE (reg_ID) {
    sc_in< sc_uint<SIZE> > pc_cur, inst;
    sc_in<bool> clk, wren, rst;
    sc_out< sc_uint<SIZE> > id_pc, id_inst;

    void load();

    SC_CTOR(reg_ID) {
        SC_METHOD(load);
        sensitive << clk.pos();
    }

private:
    sc_uint<SIZE> pc_buf, inst_buf;
    sc_uint<SIZE> imm_buf, regA_buf, regB_buf;
    sc_uint<5> rs1_buf, rs2_buf, rd_buf;
};

#endif