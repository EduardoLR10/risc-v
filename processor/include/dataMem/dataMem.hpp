#ifndef __DATA_MEMORY__
#define __DATA_MEMORY__

#include <systemc.h>
#include <stdint.h>
#include "top/macros.hpp"

#define DATAMEMSIZE 128
#define BASEADDR 0x2000
#define IMMSIZE 12

SC_MODULE (dataMem) {
  sc_in< bool > clk, rd_en, wr_en;
  sc_in< sc_uint<3> > d_size;
  sc_in< sc_uint<SIZE> > mem_addr;
  sc_in< sc_int<IMMSIZE> > imm;
  sc_in< sc_int<SIZE> > wr_data;
  sc_out< sc_int<SIZE> > mem_out;

  void load();
  void store();

  void proc(void);

  SC_CTOR(dataMem) {
    SC_METHOD(store);
    sensitive << clk.pos();

    SC_METHOD(load);
    sensitive << rd_en << d_size << mem_addr << imm;
  }

  private:
    sc_int<SIZE> memory[DATAMEMSIZE];
};

#endif
