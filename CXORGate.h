#ifndef _CXORGATE_H
#define _CXORGATE_H

#include "CLogic.h"

//---CXORGate Interface-------------------------------------------------------
// Subclass of CLogic that simulates a XOR gate
class CXORGate: public CLogic
{
public:
    // Constructor
    CXORGate();

private:

    static const int nInputs = 2; // number of inputs per nand gate
    static const int nOutputs = 1; // maximum fanout: max gate inputs that one gate output can drive 
    
    // ComputeOutput contains XOR logic and drives the output wire if it exists
    void ComputeOutput();
};

#endif