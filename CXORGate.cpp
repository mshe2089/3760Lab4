// See CXORGate.h
//
//--Includes-------------------------------------------------------------------
#include "CXORGate.h"

//---CXORGate Implementation--------------------------------------------------
CXORGate::CXORGate() : CLogic()
{
    mInputs = std::vector<eLogicLevel>(nInputs, LOGIC_UNDEFINED);
    mOutputs = std::vector<eLogicLevel>(nOutputs, LOGIC_UNDEFINED);
    mpOutputConnections = std::vector<CWire*>(nOutputs, NULL);
    ComputeOutput();
}

void CXORGate::ComputeOutput()
{
    // XOR logic
    if (mInputs[0] == LOGIC_UNDEFINED || mInputs[1] == LOGIC_UNDEFINED)
    {
        mOutputs[0] = LOGIC_UNDEFINED;
    }
    else if ((mInputs[0] == LOGIC_HIGH || mInputs[1] == LOGIC_HIGH) && mInputs[0] != mInputs[1])
    {
        mOutputs[0] = LOGIC_HIGH;
    }
    else
    {
        mOutputs[0] = LOGIC_LOW;
    }
    // Drive output
    if (mpOutputConnections[0] != NULL) mpOutputConnections[0]->DriveLevel(mOutputs[0]);
}