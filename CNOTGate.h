#ifndef _CNOTGATE_H
#define _CNOTGATE_H

//--Includes-------------------------------------------------------------------
#include "CLogic.h"

//---CNOTGate Declaration-------------------------------------------------------
// Subclass of CLogic that simulates a NOT gate
class CNOTGate: public CLogic
{
public:
    /**
     * Constructor
    */
    CNOTGate();

private:
    /**
     * Compute the output levels of this Clogic object
    */
    void ComputeOutput();

    static const int nInputs = 1;       // number of inputs for a NOT gate
    static const int nOutputs = 1;      // number of inputs for a NOT gate
};

#endif