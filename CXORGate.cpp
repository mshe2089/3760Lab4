#include "CXORGate.h"

//---CXORGate Implementation--------------------------------------------------
CXORGate::CXORGate() : CLogic(2, 1)
{
    mInputs[0] = mInputs[1] = LOGIC_UNDEFINED;
    mpOutputConnections[0] = NULL;
    ComputeOutput();
}

void CXORGate::ComputeOutput()
{
    // XOR logic
    if (mInputs[0] == LOGIC_UNDEFINED || mInputs[1] == LOGIC_UNDEFINED)
    {
        mOutputs[0] = LOGIC_UNDEFINED;
    }
    else 
    {
        mOutputs[0] = ((mInputs[0] == LOGIC_HIGH || mInputs[1] == LOGIC_HIGH) && mInputs[0] != mInputs[1]) ? LOGIC_HIGH : LOGIC_LOW;
    }
    // Drive output
    if (mpOutputConnections[0] != NULL) mpOutputConnections[0]->DriveLevel(mOutputs[0]);
}