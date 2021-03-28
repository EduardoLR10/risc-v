#include <systemc.h>
#include "top/topDBRANCH.hpp"

int sc_main (int argc, char* argv[]) {

    topDBRANCH db("dbranch");

    sc_start();

    return 0;// Terminate simulation

}
