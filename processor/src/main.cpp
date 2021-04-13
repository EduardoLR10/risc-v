#include <systemc.h>
#include "top/topPC.hpp"

int sc_main(int argc, char *argv[])
{
    TopPC top("TopPC");

    sc_start();

    return 0;
}