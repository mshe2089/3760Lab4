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
    if (mInputs[0] == LOGIC_UNDEFINED)
    {
        mOutputs[0] = LOGIC_UNDEFINED;
    }
    else 
    {
        mOutputs[0] = (mInputs[0] == LOGIC_HIGH) ? LOGIC_LOW : LOGIC_HIGH;
    }
    // Drive output
    if (mpOutputConnections[0] != NULL) mpOutputConnections[0]->DriveLevel(mOutputs[0]);
}