#include "CORGate.h"

//---CORGate Implementation--------------------------------------------------
CORGate::CORGate() : CLogic()
{
    for(int i = 0; i < nOutputs; i++)
    {
        mOutputs.push_back(LOGIC_UNDEFINED);
        mpOutputConnections.push_back(NULL);
    }
    for(int i = 0; i < nInputs; i++)
    {
        mInputs.push_back(LOGIC_UNDEFINED);
    }
    ComputeOutput();
}

void CORGate::ComputeOutput()
{
    // XOR logic
    if (mInputs[0] == LOGIC_UNDEFINED || mInputs[1] == LOGIC_UNDEFINED)
    {
        mOutputs[0] = LOGIC_UNDEFINED;
    }
    else 
    {
        mOutputs[0] = (mInputs[0] == LOGIC_HIGH || mInputs[1] == LOGIC_HIGH) ? LOGIC_HIGH : LOGIC_LOW;
    }
    // Drive output
    if (mpOutputConnections[0] != NULL) mpOutputConnections[0]->DriveLevel(mOutputs[0]);
}