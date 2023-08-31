#include "CLogic.h"
#include "CWire.h"

//---CWire Implementation------------------------------------------------------
CWire::CWire()
{
    mNumOutputConnections = 0;
}

void CWire::AddOutputConnection(CLogic *apGateToDrive, int aGateInputToDrive)
{
    mpGatesToDrive[mNumOutputConnections] = apGateToDrive;
    mGateInputIndices[mNumOutputConnections] = aGateInputToDrive;
    ++mNumOutputConnections;
}

void CWire::DriveLevel(eLogicLevel aNewLevel)
{
    for (int i = 0; i < mNumOutputConnections; ++i)
        mpGatesToDrive[i]->DriveInput(mGateInputIndices[i], aNewLevel);
}