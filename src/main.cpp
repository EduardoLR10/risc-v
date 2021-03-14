#include <systemc.h>
#include "sistema.hpp"
#include "ula.hpp"

int sc_main (int argc, char* argv[]) {

    sistema s("sistema");

    sc_start();

    return 0;// Terminate simulation

}
