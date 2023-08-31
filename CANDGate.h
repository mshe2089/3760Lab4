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
    // ComputeOutput contains AND logic and drives the output wire if it exists
    void ComputeOutput();
};

#endif