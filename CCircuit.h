#ifndef _CCIRCUIT_H
#define _CCIRCUIT_H

#include "CLogic.h"

#include <vector>
#include <unordered_map>
#include <tuple>
#include <string>

//---CCircuit Interface-------------------------------------------------------
// Subclass of CLogic, providing functionality to build combinatorial circuits using CCircuit or CGate objects.
class CCircuit: public CLogic
{
public:
    // Constructor, Destructor
    // Circuit will contain {nInputs} inputs, {nOutputs} outputs, {nLogics} logic elements and {nWires} wires
    CCircuit();
    ~CCircuit();

    // Connect wire {wire} to input {input} of logic element {logic}
    void ConnectWireToLogic(std::string wire, std::string logic, int input);

    // Connect output {output} of logic element {logic} to wire {wire}
    void ConnectLogicToWire(std::string logic, int output, std::string wire);

    // Add logic element {logic} to a specific CLogic instance specified by {clogic}
    void AddLogic(std::string logic, CLogic* clogic);

    // Add a new wire with name {wire}
    void AddWire(std::string wire);

    // Connect the circuit input {circuitInput} to wire {wire}
    void MapInput(std::string wire, int circuitInput = -1);

    // Connect output {logicOutput} of logic element {logic} to circuit output {circuitOutput}
    void MapOutput(std::string logic, int logicOutput, int circuitOutput = -1);

private:
    // ComputeOutput executes circuit logic and drives connected output wires if any exist
    void ComputeOutput();

    std::unordered_map<std::string, CLogic*> mLogics; 
    std::unordered_map<std::string, CWire*> mWires; 

    std::vector<std::tuple<int, std::string>> inputMap;               // input mapping
    std::vector<std::tuple<std::string, int, int>> outputMap;         // output mapping
};

#endif