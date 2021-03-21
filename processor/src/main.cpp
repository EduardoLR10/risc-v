#include <systemc.h>
#include "top/topMUX3.hpp"

int sc_main (int argc, char* argv[]) {

    topMUX3 m("mux3");

    sc_start();

    return 0;// Terminate simulation

}
