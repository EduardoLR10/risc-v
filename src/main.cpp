#include <systemc.h>
#include "top/sistema.hpp"

int sc_main (int argc, char* argv[]) {

    sistema s("sistema");

    sc_start();

    return 0;// Terminate simulation

}
