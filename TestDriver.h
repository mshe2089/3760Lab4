#ifndef _TESTDRIVER_H
#define _TESTDRIVER_H

//--Includes-------------------------------------------------------------------
#include "CLogic.h"

#include <string>

//---TestDriver Declaration--------------------------------------------------
//
// Testdriver for combinatorial logic circuit (CLC) simulator
//
// Provides classes and methods to create and test combinatorial circuits. 
//
// CLogic is a template of a logic cell: any gate or circuit of gates.
// CLogic units can be connected with CWires inside CCircuits and driven to get simulated outputs.
//
// CGates and CCircuit implement CLogic.
// CGates simulate simple logic gates with hard coded behaviour.
// CCircuits simulate complex combinatorial circuits, containing any number of CCircuits and CGates connected together.
//
// Circuit accepts CLCs defined by .circuit files, piped directly into the executable.
// Each .circuit file shall define only one CLC.
// Syntax:
//                  Command                        |                Definition
//    _____________________________________________|________________________________________________________
//
//      component {gateType} {gateName}               > "component" declares new component of type 
//                                                       {gateType}[and, or, xor, not] and name {gateName}
//
//      wire {wireName} {inputNo} {gateName}          > "wire" declares new wire {wireName} if it doesnt exist
//                                                        and connects it to input {inputNo} of gate {gateName}    
//
//      connect {gateName} {outputNo} {wireName}      > "connect" connects output {inputNo} of gate
//                                                        {gateName} to wire {wireName}
//
//      testerOutput {gateName} {outputNo}            > "testerOutput" adds output {inputNo} of gate
//                                                        {gateName} as an output of the whole circuit.
//
//      testerInput {wireName} {outputNo}             > "testerInput" adds wire {wireName} as an output 
//                                                        of the whole circuit.
//
//      end {circuitName}                             > "end" signifies the end of the declaration for
//                                                        circuit {circuitName}
//
// Copyright (c) Daniel Shen 2023

class TestDriver
{
  public:
    /**
     * Creates a new circuit from a .circuit file piped to cin.
     * 
     * @return pair containing circuit name and circuit object pointer
    */
    std::pair<std::string, CLogic*>  NewCircuit ();

    /**
     * Generates truth table for a circuit. Recursively finds all possible assignments.
     * 
     * @param CircuitInfo pair containing circuit name and circuit object pointer
     * @param Input empty non-const string buffer used in recursion. 
     *              Initialize an empty string and pass as this argument when calling.
     * @param i integer argument used in recursion. When calling, you don't have to provide this.
    */
    void TestCircuit (std::pair<std::string, CLogic*> &CircuitInfo, std::string &Input, int i = 0);

  private:
    /**
     * Private function for testing a particular assignment on a circuit.
     * 
     * @param Name circuit name
     * @param Circuit circuit pointer
     * @param Input input assignment as a boolean number string
    */
    void TestInput (std::string Name, CLogic* Circuit, std::string Input);

};

#endif