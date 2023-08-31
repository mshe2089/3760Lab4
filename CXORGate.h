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
    // ComputeOutput contains XOR logic and drives the output wire if it exists
    void ComputeOutput();
};

#endif