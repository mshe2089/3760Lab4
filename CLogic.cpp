// See CLogic.h
//
//--Includes-------------------------------------------------------------------
#include "CLogic.h"

//---CLogic Implementation--------------------------------------------------
CLogic::CLogic(){}

CLogic::~CLogic(){}

void CLogic::ConnectOutput(int aOutputIndex, CWire *apOutputConnection)
{
    // Connect new output and recompute outputs
    mpOutputConnections[aOutputIndex] = apOutputConnection;
    ComputeOutput();
}

void CLogic::DriveInput(int aInputIndex, eLogicLevel aNewLevel)
{
    // Connect new input and recompute outputs
    mInputs[aInputIndex] = aNewLevel;
    ComputeOutput();
}

eLogicLevel CLogic::GetOutputState(int aOutputIndex)
{
    // Resize outputs to required index
    while(int(mOutputs.size()) < aOutputIndex + 1)
    {
        mOutputs.push_back(LOGIC_UNDEFINED);
        mpOutputConnections.push_back(NULL);
    }
    return mOutputs[aOutputIndex];
}

int CLogic::InputSize()
{
    return mInputs.size();
}

int CLogic::OutputSize()
{
    return mOutputs.size();
}