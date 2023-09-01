// See CORGate.h
//
//--Includes-------------------------------------------------------------------
#include "CORGate.h"

//---CORGate Implementation--------------------------------------------------
CORGate::CORGate() : CLogic()
{
    mInputs = std::vector<eLogicLevel>(nInputs, LOGIC_UNDEFINED);
    mOutputs = std::vector<eLogicLevel>(nOutputs, LOGIC_UNDEFINED);
    mpOutputConnections = std::vector<CWire*>(nOutputs, NULL);
    ComputeOutput();
}

void CORGate::ComputeOutput()
{
    // XOR logic
    if (mInputs[0] == LOGIC_UNDEFINED || mInputs[1] == LOGIC_UNDEFINED)
    {
        mOutputs[0] = LOGIC_UNDEFINED;
    }
    else if (mInputs[0] == LOGIC_HIGH || mInputs[1] == LOGIC_HIGH)
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