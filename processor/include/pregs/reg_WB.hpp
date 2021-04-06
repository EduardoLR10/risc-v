#ifndef __REG_WB_H__
#define __REG_WB_H__

#include <systemc.h>
#include "top/macros.hpp"

// ************************** MEM/WB
SC_MODULE (reg_WB){
    sc_in< sc_uint<5> > mem_rd;
    sc_in< sc_uint<SIZE> > mem_alu_out, mem_mdata_out;
    sc_in<bool> clk, wren, rst;
    sc_out< sc_uint<5> > wb_rd;
    sc_out< sc_uint<SIZE> > wb_alu_out, wb_mdata_out;

    void load();

    SC_CTOR(reg_WB) {
        SC_METHOD(load);
        sensitive << clk.pos();
    }

private:
    sc_uint<SIZE> alu_out_buf, mdata_buf;
    sc_uint<5> rd_buf;
};

#endif