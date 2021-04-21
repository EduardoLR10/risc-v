#ifndef __REG_ID_H__
#define __REG_ID_H__

#include <systemc.h>
#include "top/macros.hpp"

// ************************** IF/ID
SC_MODULE (reg_ID) {
    sc_in< sc_uint<SIZE> > pc_cur, inst, next_pc;
    sc_in<bool> clk, wren, rst;
    sc_out< sc_uint<SIZE> > id_pc, id_inst, id_next_pc;
    sc_out< sc_uint<5> > id_rs1, id_rs2, id_rd;
    sc_out< sc_uint<7> > id_ins_code;

    void load();

    SC_CTOR(reg_ID) {
        SC_METHOD(load);
        sensitive << clk.pos();
    }

private:
    sc_uint<SIZE> pc_buf, inst_buf, next_pc_buf;
    sc_uint<5> rs1_buf, rs2_buf, rd_buf;
    sc_uint<7> ins_code_buf;
};

#endif
