#ifndef _CORGATE_H
#define _CORGATE_H

#include "CLogic.h"

//---CORGate Interface-------------------------------------------------------
// Subclass of CLogic that simulates an OR gate
class CORGate: public CLogic
{
public:
    // Constructor
    CORGate();

private:

    static const int nInputs = 2; // number of inputs per nand gate
    static const int nOutputs = 1; // maximum fanout: max gate inputs that one gate output can drive 
    
    // ComputeOutput contains OR logic and drives the output wire if it exists
    void ComputeOutput();
};


#endif