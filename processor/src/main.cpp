#include <systemc.h>
#include "top/topRISCV.hpp"

int sc_main(int argc, char *argv[]) {

    sc_clock clk("clk", 10.0, SC_NS);
    RISCV rv("rv");
    rv.clock(clk);

    sc_start(250.0, SC_NS);
    rv.dump_breg();

    if (not sc_end_of_simulation_invoked()) {
        std::cout << "Chamando sc_stop()!" << endl;
        sc_stop();
    }//endif
    return 0;
}
