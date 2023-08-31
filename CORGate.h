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
    // ComputeOutput contains OR logic and drives the output wire if it exists
    void ComputeOutput();
};


#endif