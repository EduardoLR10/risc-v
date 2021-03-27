#include <systemc.h>
#include "top/topBREG.hpp"

int sc_main (int argc, char* argv[]) {

    topBREG br("breg");

    sc_start(650, SC_NS);

    return 0;// Terminate simulation

}
