// See CNOTGate.h
//
//--Includes-------------------------------------------------------------------
#include "CNOTGate.h"

//---CNOTGate Implementation--------------------------------------------------
CNOTGate::CNOTGate() : CLogic()
{
    mInputs = std::vector<eLogicLevel>(nInputs, LOGIC_UNDEFINED);
    mOutputs = std::vector<eLogicLevel>(nOutputs, LOGIC_UNDEFINED);
    mpOutputConnections = std::vector<CWire*>(nOutputs, NULL);
    ComputeOutput();
}

void CNOTGate::ComputeOutput()
{
    // NOT logic
    if (mInputs[0] == LOGIC_HIGH)
    {
        mOutputs[0] = LOGIC_LOW;
    }
    else if (mInputs[0] == LOGIC_LOW)
    {
        mOutputs[0] = LOGIC_HIGH;
    }
    else 
    {
        mOutputs[0] = LOGIC_UNDEFINED;
    }
    // Drive output
    if (mpOutputConnections[0] != NULL) mpOutputConnections[0]->DriveLevel(mOutputs[0]);
}