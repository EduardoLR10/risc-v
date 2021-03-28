#include <systemc.h>
#include "dbranch/dbranch.hpp"
#include "dbranch/dbranch_tb.hpp"

SC_MODULE ( topDBRANCH ) {

    dbranch_tb DBRANCH_tb;
    dbranch DBRANCH;

    sc_signal< sc_int<SIZE> > ra, rb;
    sc_signal< sc_bv<2>> opcode;
    sc_signal<bool> Bout;

    SC_CTOR ( topDBRANCH ) : DBRANCH_tb("DBRANCH_tb"), DBRANCH("DBRANCH") {
        DBRANCH.ra(ra); DBRANCH_tb.ra(ra);
        DBRANCH.rb(rb); DBRANCH_tb.rb(rb);
        DBRANCH.opcode(opcode); DBRANCH_tb.opcode(opcode);
        DBRANCH.Bout(Bout); DBRANCH_tb.Bout(Bout);
    }
};