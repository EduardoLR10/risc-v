#include "dforward/dforward.hpp"

void dforward::proc(){
    if(rd.read() == rs1.read() && mem_wr_en.read()){
        rAOut.write(true);
    } else {
        rAOut.write(false);
    }
    if(rd.read() == rs2.read() && mem_wr_en.read()){
        rBOut.write(true);
    } else {
        rBOut.write(false);
    }

}
