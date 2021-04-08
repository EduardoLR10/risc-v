#include <systemc.h>
#include "top/topMUX3.hpp"
#include "top/top_instruction_memory.hpp"

int sc_main (int argc, char* argv[]) {

    // topMUX3 m("mux3");
    TopInstructionMemory tim("TopInstructionMemory");

    sc_start();

    return 0;// Terminate simulation

}
