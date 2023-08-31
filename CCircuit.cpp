#include "CCircuit.h"

//---CCircuit Implementation--------------------------------------------------
CCircuit::CCircuit(int nInputs, int nOutputs) : CLogic(nInputs, nOutputs){}

CCircuit::~CCircuit()
{
    for (std::pair<std::string, CWire*> p : mWires) delete p.second;
    for (std::pair<std::string, CLogic*> p : mLogics) delete p.second;
}

void CCircuit::ConnectWireToLogic(std::string wire, std::string logic, int input)
{
    mWires[wire]->AddOutputConnection(mLogics[logic], input);
}

void CCircuit::ConnectLogicToWire(std::string logic, int output, std::string wire)
{
    mLogics[logic]->ConnectOutput(output, mWires[wire]);
}

void CCircuit::AddLogic(std::string logic, CLogic* clogic)
{
    mLogics[logic] = clogic;
}

void CCircuit::AddWire(std::string wire)
{
    mWires[wire] = new CWire();
}

void CCircuit::MapInput(int circuitInput, std::string wire)
{
    inputMap.push_back(std::make_tuple(circuitInput, wire));
}

void CCircuit::MapOutput(std::string logic, int logicOutput, int circuitOutput)
{
    outputMap.push_back(std::make_tuple(logic, logicOutput, circuitOutput));
}

void CCircuit::ComputeOutput()
{
    for (std::tuple<int, std::string> t : inputMap){
        mWires[std::get<1>(t)]->DriveLevel(mInputs[std::get<0>(t)]);
    }

    for (std::tuple<std::string, int, int> t : outputMap){
        eLogicLevel output = mLogics[std::get<0>(t)]->GetOutputState(std::get<1>(t));
        mOutputs[std::get<2>(t)] = output;
        if (mpOutputConnections[std::get<2>(t)] != NULL) mpOutputConnections[std::get<2>(t)]->DriveLevel(output);
    }
}
