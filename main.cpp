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
    TestDriver t = TestDriver();
    t.NewCircuit();


    /*
    HalfAdderTest("0", "0");
    HalfAdderTest("0", "1");
    HalfAdderTest("1", "0");
    HalfAdderTest("1", "1");

    FullAdderTest("0", "0", "0");
    FullAdderTest("0", "1", "0");
    FullAdderTest("1", "0", "0");
    FullAdderTest("1", "1", "0");
    FullAdderTest("0", "0", "1");
    FullAdderTest("0", "1", "1");
    FullAdderTest("1", "0", "1");
    FullAdderTest("1", "1", "1");

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            ThreeBitAdderTest(bitset<3>(i).to_string(), bitset<3>(j).to_string());
        }
    }

    CarryEnableHalfAdderTest("1", "0", "0");
    CarryEnableHalfAdderTest("0", "1", "0");
    CarryEnableHalfAdderTest("0", "0", "0");
    CarryEnableHalfAdderTest("1", "1", "0");
    */

    return 0;
}