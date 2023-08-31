#include "CLogic.h"

#include <string>
#include <utility>        // std::pair
#include <vector>

//---CLogic Implementation--------------------------------------------------
CLogic::CLogic(){}

CLogic::~CLogic(){}

void CLogic::ConnectOutput(int aOutputIndex, CWire *apOutputConnection)
{
    mpOutputConnections[aOutputIndex] = apOutputConnection;
    ComputeOutput();
}

void CLogic::DriveInput(int aInputIndex, eLogicLevel aNewLevel)
{
    mInputs[aInputIndex] = aNewLevel;
    ComputeOutput();
}

eLogicLevel CLogic::GetOutputState(int aOutputIndex)
{
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