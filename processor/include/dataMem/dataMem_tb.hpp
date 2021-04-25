#ifndef __DATA_MEMORY_TB__
#define __DATA_MEMORY_TB__

#include <systemc.h>
#include <iostream>
#include <iomanip>
#include "top/macros.hpp"
#include "dataMem/dataMem.hpp"

SC_MODULE(dataMem_tb) {
  sc_in< bool > clk;
  sc_out< bool > rd_en, wr_en;
  sc_out< sc_uint<3> > d_size;
  sc_out< sc_uint<SIZE> > mem_addr;
  sc_out< sc_int<IMMSIZE> > imm;
  sc_out< sc_int<SIZE> > wr_data;
  sc_in< sc_int<SIZE> > mem_out;

  void execute();

  SC_CTOR(dataMem_tb) {
    SC_THREAD(execute);
  }
};

#endif
