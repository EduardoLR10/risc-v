#include <systemc.h>
#include "top/topWFORWARD.hpp"

int sc_main (int argc, char* argv[]) {

    topWFORWARD wf1("wforward");

    sc_start();

    return 0;
}