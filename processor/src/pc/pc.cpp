#include "pc/pc.hpp"

void pc::proc(void) {
  if (ld_pc) {
    count = pc_in.read();
  } else {
    count += 1;
  }
  pc_out.write(count);
}