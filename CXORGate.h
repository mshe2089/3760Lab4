#ifndef _CXORGATE_H
#define _CXORGATE_H

//--Includes-------------------------------------------------------------------
#include "CLogic.h"

//---CXORGate Declaration-------------------------------------------------------
// Subclass of CLogic that simulates a XOR gate
class CXORGate: public CLogic
{
public:
    /**
     * Constructor
    */
    CXORGate();

private:
    /**
     * Compute the output levels of this Clogic object
    */
    void ComputeOutput();

    static const int nInputs = 2;       // number of inputs for a XOR gate
    static const int nOutputs = 1;      // number of outputs for a XOR gate
};

#endif