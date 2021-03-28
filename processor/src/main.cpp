#include <systemc.h>
#include "top/topMUX2.hpp"
#include "top/topMUX3.hpp"

int sc_main (int argc, char* argv[]) {

    topMUX2 m1("mux2");
    topMUX3 m2("mux3");

    sc_start();

    return 0;
}