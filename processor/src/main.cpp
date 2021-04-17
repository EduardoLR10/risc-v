#include <systemc.h>
#include "top/topDBRANCH.hpp"

int sc_main (int argc, char* argv[]) {

    topDBRANCH d1("dbranch");

    sc_start();

    return 0;
}