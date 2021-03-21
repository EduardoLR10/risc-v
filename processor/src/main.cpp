#include <systemc.h>
#include "top/topMUX2.hpp"

int sc_main (int argc, char* argv[]) {

    topMUX2 m("mux2");

    sc_start();

    return 0;// Terminate simulation

}
