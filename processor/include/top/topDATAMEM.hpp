#include <systemc.h>
#include "dataMem/dataMem.hpp"
#include "dataMem/dataMem_tb.hpp"

SC_MODULE ( topDATAMEM ) {
    
    dataMem_tb DATAMEM_tb;
    dataMem DATAMEM;

    sc_signal< bool > rd_en, wr_en;
    sc_signal< sc_uint<3> > d_size;
    sc_signal< sc_uint<SIZE> > mem_addr;
    sc_signal< sc_uint<IMMSIZE> > imm;
    sc_signal< sc_uint<SIZE> > wr_data, mem_out;

    sc_clock clk;

    SC_CTOR (topDATAMEM): DATAMEM_tb("DATAMEM_tb"), DATAMEM("DATAMEM"), clk("clk", 10.0, SC_NS) {
        DATAMEM.rd_en(rd_en); DATAMEM_tb.rd_en(rd_en);
        DATAMEM.wr_en(wr_en); DATAMEM_tb.wr_en(wr_en);
        DATAMEM.d_size(d_size); DATAMEM_tb.d_size(d_size);
        DATAMEM.mem_addr(mem_addr); DATAMEM_tb.mem_addr(mem_addr);
        DATAMEM.imm(imm); DATAMEM_tb.imm(imm);
        DATAMEM.wr_data(wr_data); DATAMEM_tb.wr_data(wr_data);
        DATAMEM.mem_out(mem_out); DATAMEM_tb.mem_out(mem_out);
        DATAMEM.clk(clk); DATAMEM_tb.clk(clk);
    }
};