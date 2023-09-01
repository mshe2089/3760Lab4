// Main
//
// Calls TestDriver class to test combinatorial logic circuits.
//
// Copyright (c) Daniel Shen 2023

//--Includes-------------------------------------------------------------------
#include "TestDriver.h"

#include <string>
#include <iostream>

//---Main----------------------------------------------------------------------
int main()
{
    // Create new testdriver
    TestDriver T = TestDriver();

    // Create new circuit
    auto CircuitInfo = T.NewCircuit();

    // Test circuit with all assignments
    std::string Assignment = "";
    T.TestCircuit(CircuitInfo, Assignment);
    
    // Delete circuit
    delete(CircuitInfo.second);

    return 0;
}