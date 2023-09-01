// See CLogic.h
//
//--Includes-------------------------------------------------------------------
#include "CCircuit.h"

//---CCircuit Implementation--------------------------------------------------

CCircuit::CCircuit():CLogic(){}

CCircuit::~CCircuit()
{
    // Delete all dynamically allocated wires and logic elements
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
    // Add logic if its name is not already used
    if (mLogics.find(logic) == mLogics.end()) 
    {
        mLogics[logic] = clogic;
    }
}

void CCircuit::AddWire(std::string wire)
{
    // Add wire if its name is not already used
    if (mWires.find(wire) == mWires.end()) 
    {
        mWires[wire] = new CWire();
    }
}

void CCircuit::MapInput(std::string wire, int circuitInput)
{
    // If circuitInput is default value, set it as a new input
    if (circuitInput < 0){
        circuitInput = mInputs.size();
    }

    // Expand inputs
    while(int(mInputs.size()) < circuitInput + 1){
        mInputs.push_back(LOGIC_UNDEFINED);
    }

    // Add mapping
    inputMap.push_back(std::make_tuple(
        circuitInput, 
        wire
        ));
}

void CCircuit::MapOutput(std::string logic, int logicOutput, int circuitOutput)
{
    // If circuitOutput is default value, set it as a new output
    if (circuitOutput < 0){
        circuitOutput = mOutputs.size();
    }

    // Expand outputs
    while(int(mOutputs.size()) < circuitOutput + 1){
        mOutputs.push_back(LOGIC_UNDEFINED);
        mpOutputConnections.push_back(NULL);
    }

    // Add mapping
    outputMap.push_back(std::make_tuple(
        logic, 
        logicOutput, 
        circuitOutput
        ));
}

void CCircuit::ComputeOutput()
{
    // Look through input mapping and drive all inputs.
    for (std::tuple<int, std::string> t : inputMap)
    {
        mWires[std::get<1>(t)]->DriveLevel(mInputs[std::get<0>(t)]);
    }
    
    // Look through output mapping and drive all outputs.
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
