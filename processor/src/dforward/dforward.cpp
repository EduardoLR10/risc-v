#include "dforward/dforward.hpp"

void dforward::proc(){
    if (mem_breg_wren) {
        if (rd.read() == rs1.read()) {
            rAOut.write(true);
        } else {
            rAOut.write(false);
        }
        if (rd.read() == rs2.read()) {
            rBOut.write(true);
        } else {
            rBOut.write(false);
        }
    }

}
