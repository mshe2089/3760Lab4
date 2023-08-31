#include "CLogic.h"

#include <string>
#include <utility>        // std::pair
#include <vector>

//---CLogic Implementation--------------------------------------------------
CLogic::CLogic(int nInputs, int nOutputs)
{
    mInputs = std::vector<eLogicLevel>(nInputs, LOGIC_UNDEFINED);
    mOutputs = std::vector<eLogicLevel>(nOutputs, LOGIC_UNDEFINED);
    mpOutputConnections = std::vector<CWire*>(nOutputs, NULL);
}

CLogic::~CLogic(){}

void CLogic::ConnectOutput(int aOutputIndex, CWire *apOutputConnection)
{
    mpOutputConnections[aOutputIndex] = apOutputConnection;
}

void CLogic::DriveInput(int aInputIndex, eLogicLevel aNewLevel)
{
    mInputs[aInputIndex] = aNewLevel;
    ComputeOutput();
}

eLogicLevel CLogic::GetOutputState(int aOutputIndex)
{
    return mOutputs[aOutputIndex];
}