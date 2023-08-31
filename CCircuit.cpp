#include "CCircuit.h"

//---CCircuit Implementation--------------------------------------------------
CCircuit::CCircuit(int nInputs, int nOutputs, int nLogics, int nWires) : CLogic(nInputs, nOutputs)
{
    nLogics = nLogics;     
    nWires = nWires;

    mLogics = std::vector<CLogic*>(nLogics);
    for (int i = 0; i < nWires; i++) mWires.push_back(new CWire());
}

CCircuit::~CCircuit()
{
    for (CWire* w : mWires) delete w;
    for (CLogic* l : mLogics) delete l;
}

void CCircuit::ConnectWireToLogic(int wire, int logic, int input)
{
    mWires[wire]->AddOutputConnection(mLogics[logic], input);
}

void CCircuit::ConnectLogicToWire(int logic, int output, int wire)
{
    mLogics[logic]->ConnectOutput(output, mWires[wire]);
}

void CCircuit::SetLogic(int logic, CLogic* clogic)
{
    mLogics[logic] = clogic;
}

void CCircuit::MapInput(int circuitInput, int wire)
{
    inputMap.push_back(std::make_tuple(circuitInput, wire));
}

void CCircuit::MapOutput(int logic, int logicOutput, int circuitOutput)
{
    outputMap.push_back(std::make_tuple(logic, logicOutput, circuitOutput));
}

void CCircuit::ComputeOutput()
{
    for (std::tuple<int, int> t : inputMap){
        mWires[std::get<1>(t)]->DriveLevel(mInputs[std::get<0>(t)]);
    }

    for (std::tuple<int, int, int> t : outputMap){
        eLogicLevel output = mLogics[std::get<0>(t)]->GetOutputState(std::get<1>(t));
        mOutputs[std::get<2>(t)] = output;
        if (mpOutputConnections[std::get<2>(t)] != NULL) mpOutputConnections[std::get<2>(t)]->DriveLevel(output);
    }
}
