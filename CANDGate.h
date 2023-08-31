#ifndef _CANDGATE_H
#define _CANDGATE_H

#include "CLogic.h"

//---CANDGate Interface-------------------------------------------------------
// Subclass of CLogic that simulates an AND gate
class CANDGate: public CLogic
{
public:
    // Constructor
    CANDGate();

private:

    static const int nInputs = 2; // number of inputs per nand gate
    static const int nOutputs = 1; // maximum fanout: max gate inputs that one gate output can drive 
    
    // ComputeOutput contains AND logic and drives the output wire if it exists
    void ComputeOutput();
};

#endif