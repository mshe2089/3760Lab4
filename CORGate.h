#ifndef _CORGATE_H
#define _CORGATE_H

//--Includes-------------------------------------------------------------------
#include "CLogic.h"

//---CORGate Declaration-------------------------------------------------------
// Subclass of CLogic that simulates an OR gate
class CORGate: public CLogic
{
public:
    /**
     * Constructor
    */
    CORGate();

private:
    /**
     * Compute the output levels of this Clogic object
    */
    void ComputeOutput();

    static const int nInputs = 2;       // number of inputs for a OR gate
    static const int nOutputs = 1;      // number of outputs for a OR gate
};


#endif