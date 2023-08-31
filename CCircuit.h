#ifndef _CCIRCUIT_H
#define _CCIRCUIT_H

#include "CLogic.h"

#include <vector>
#include <tuple>

//---CCircuit Interface-------------------------------------------------------
// Subclass of CLogic, providing functionality to build combinatorial circuits using CCircuit or CGate objects.
class CCircuit: public CLogic
{
public:
    // Constructor, Destructor
    // Circuit will contain {nInputs} inputs, {nOutputs} outputs, {nLogics} logic elements and {nWires} wires
    CCircuit(int nInputs, int nOutputs, int nLogics, int nWires);
    ~CCircuit();

    // Connect wire {wire} to input {input} of logic element {logic}
    void ConnectWireToLogic(int wire, int logic, int input);

    // Connect output {output} of logic element {logic} to wire {wire}
    void ConnectLogicToWire(int logic, int output, int wire);

    // Set logic element {logic} to a specific CLogic instance specified by {clogic}
    void SetLogic(int logic, CLogic* clogic);

    // Connect the circuit input {circuitInput} to wire {wire}
    void MapInput(int circuitInput, int wire);

    // Connect output {logicOutput} of logic element {logic} to circuit output {circuitOutput}
    void MapOutput(int logic, int logicOutput, int circuitOutput);

private:
    // ComputeOutput executes circuit logic and drives connected output wires if any exist
    void ComputeOutput();

    int nLogics;    // number of logic cells
    int nWires;     // number of wires

    std::vector<CLogic*> mLogics; 
    std::vector<CWire*> mWires; 

    std::vector<std::tuple<int, int>> inputMap;               // input mapping
    std::vector<std::tuple<int, int, int>> outputMap;         // output mapping
};

#endif