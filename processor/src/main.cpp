#include <systemc.h>
#include "top/topRISCV.hpp"

int sc_main(int argc, char *argv[])
{
    topRISCV t("Testing_RISCV");

    sc_start(8, SC_NS);
    

    return 0;
}