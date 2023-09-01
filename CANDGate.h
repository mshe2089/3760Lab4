#ifndef _CANDGATE_H
#define _CANDGATE_H

//--Includes-------------------------------------------------------------------
#include "CLogic.h"

//---CANDGate Declaration-------------------------------------------------------
// Subclass of CLogic that simulates an AND gate
class CANDGate: public CLogic
{
public:
    /**
     * Constructor
    */
    CANDGate();

private:
    /**
     * Compute the output levels of this Clogic object
    */
    void ComputeOutput();

    static const int nInputs = 2;       // number of inputs for an AND gate
    static const int nOutputs = 1;      // number of outputs for an AND gate
};

#endif