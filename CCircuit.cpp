#include "CCircuit.h"

//---CCircuit Implementation--------------------------------------------------
CCircuit::CCircuit() : CLogic(){}

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
    if (mLogics.find(logic) == mLogics.end()) 
    {
        mLogics[logic] = clogic;
    }
}

void CCircuit::AddWire(std::string wire)
{
    if (mWires.find(wire) == mWires.end()) 
    {
        mWires[wire] = new CWire();
    }
}

void CCircuit::MapInput(std::string wire, int circuitInput)
{
    circuitInput = circuitInput < 0 ? int(mInputs.size()) : circuitInput;

    while(int(mInputs.size()) < circuitInput + 1){
        mInputs.push_back(LOGIC_UNDEFINED);
    }

    inputMap.push_back(std::make_tuple(
        circuitInput, 
        wire
        ));
}

void CCircuit::MapOutput(std::string logic, int logicOutput, int circuitOutput)
{
    circuitOutput = circuitOutput < 0 ? int(mOutputs.size()) : circuitOutput;

    while(int(mOutputs.size()) < circuitOutput + 1){
        mOutputs.push_back(LOGIC_UNDEFINED);
        mpOutputConnections.push_back(NULL);
    }

    outputMap.push_back(std::make_tuple(
        logic, 
        logicOutput, 
        circuitOutput
        ));
}

void CCircuit::ComputeOutput()
{
    for (std::tuple<int, std::string> t : inputMap)
    {
        mWires[std::get<1>(t)]->DriveLevel(mInputs[std::get<0>(t)]);
    }
    
    for (std::tuple<std::string, int, int> t : outputMap)
    {
        eLogicLevel output = mLogics[std::get<0>(t)]->GetOutputState(std::get<1>(t));
        mOutputs[std::get<2>(t)] = output;
        if (mpOutputConnections[std::get<2>(t)] != NULL)
        {
            mpOutputConnections[std::get<2>(t)]->DriveLevel(output);
        }
    }
}
