#include "mforward/mforward.hpp"

void MForward::proc() {
  if (f_breg_wr.read() && mem_rs2.read() == wb_rd.read() && mem_wr_en.read()) {
    sel_mux_mem.write(true);
  } else {
    sel_mux_mem.write(false);
  }
}