#include <systemc.h>
#include "top/topGENIMM32.hpp"

int sc_main (int argc, char* argv[]) {

    topGENIMM32 t("imediatos");

    sc_start();

    return 0;// Terminate simulation

}
