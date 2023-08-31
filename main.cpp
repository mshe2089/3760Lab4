// A combinatorial logic circuit simulator
//
// Provides classes and methods to build combinatorial circuits. 
// CLogic is a template of a logic cell: any gate or circuit of gates.
// CLogic units can be connected with CWires inside CCircuits and driven to get simulated outputs.
//
// CGates and CCircuit implement CLogic.
// CGates simulate simple logic gates with hard coded behaviour.
// CCircuits simulate complex combinatorial circuits, containing any number of CCircuits and CGates connected together.
//
// Copyright (c) Daniel Shen 2023

//--Includes-------------------------------------------------------------------
#include "TestDriver.h"
#include "CANDGate.h"
#include "CORGate.h"
#include "CXORGate.h"
#include "CCircuit.h"

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

//---Forward Declarations------------------------------------------------------
void HalfAdderTest(string A, string B);
void FullAdderTest(string A, string B, string C);
void ThreeBitAdderTest(string A, string B);
void CarryEnableHalfAdderTest(string A, string B, string E);

//---main----------------------------------------------------------------------
int main()
{
    TestDriver T = TestDriver();

    auto CircuitInfo = T.NewCircuit();

    T.TestCircuit3(CircuitInfo);
    
    delete(CircuitInfo.second);

    return 0;
}