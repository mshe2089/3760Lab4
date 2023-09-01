#ifndef _CNOTGATE_H
#define _CNOTGATE_H

#include "CLogic.h"

//---CNOTGate Interface-------------------------------------------------------
// Subclass of CLogic that simulates a NOT gate
class CNOTGate: public CLogic
{
public:
    // Constructor
    CNOTGate();

private:

    static const int nInputs = 1; // number of inputs for a NOT gate
    static const int nOutputs = 1; // // number of inputs for a NOT gate
    
    // ComputeOutput contains NOT logic and drives the output wire if it exists
    void ComputeOutput();
};

#endif