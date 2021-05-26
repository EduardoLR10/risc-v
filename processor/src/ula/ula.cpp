#include "ula/ula.hpp"

void ula::proc()
{
    switch (ula_op.read())
    {
        case ULA_ADD: 
            z.write(a.read() + b.read());
            break;
        
        case ULA_SUB:
            z.write(a.read() - b.read());
            break;
        
        case ULA_AND:
            z.write(a.read() & b.read());
            break;
        
        case ULA_OR:
            z.write(a.read() | b.read());
            break;
        
        case ULA_XOR:
            z.write(a.read() ^ b.read());
            break;

        case ULA_NOR:
            z.write(~(a.read() | b.read()));
            break;
        case ULA_SLL:
            z.write(a.read() << b.read());
            break;

        case ULA_SRL:
            z.write(static_cast< sc_uint<SIZE> >(a.read()) >> b.read());
            break;
        
        case ULA_SRA:
            z.write(static_cast< sc_int<SIZE> >(a.read()) >> b.read());
            break;
        
        case ULA_SLTU:
            if(a.read() < b.read())
                z.write(1);
            else
                z.write(0);
            break;
        
        case ULA_SLT:
            if(static_cast< sc_int<SIZE> >(a.read()) <
                static_cast< sc_int<SIZE> >(b.read()))
                z.write(1);
            else
                z.write(0);
            break;

        case ULA_SGEU:
            if(a.read() >= b.read())
                z.write(1);
            else
                z.write(0);
            break;
        
        case ULA_SGE:
            if(static_cast< sc_int<SIZE> >(a.read()) >=
                static_cast< sc_int<SIZE> >(b.read()))
                z.write(1);
            else
                z.write(0);
            break;
        
        case ULA_SEQ:
            if(a.read() == b.read())
                z.write(1);
            else
                z.write(0);
            break;
        
        case ULA_SNE:
            if(a.read() != b.read())
                z.write(1);
            else
                z.write(0);
            break;

        default:
            cout << "Instruction not Recognized";
            break;
    }
}

void ula::check_zero()
{
    if(z.read() == 0)
        zero.write(1);
    else
        zero.write(0);
}


