#ifndef _CCIRCUIT_H
#define _CCIRCUIT_H

//--Includes-------------------------------------------------------------------
#include "CLogic.h"

#include <vector>
#include <unordered_map>
#include <tuple>
#include <string>

//---CCircuit Declaration-------------------------------------------------------
// Subclass of CLogic, providing functionality to build combinatorial circuits using CCircuit or 
// CGate objects.
class CCircuit: public CLogic
{
public:
    /**
     * Constructor
    */
    CCircuit();

    /**
     * Destuctor
    */
    ~CCircuit();

    /**
     * Connect wire to input of logic element
     * 
     * @param wire wire to connect from
     * @param logic gate to connect to
     * @param input input of gate to connect to 
    */
    void ConnectWireToLogic(std::string wire, std::string logic, int input);

    /**
     * Connect output of logic element to wire
     * 
     * @param logic logic element to connect from
     * @param output output of logic element to connect from 
     * @param wire wire to connect to
    */
    void ConnectLogicToWire(std::string logic, int output, std::string wire);

    /**
     * Add logic element to this CLogic instance
     * 
     * @param logic name of logic element
     * @param clogic pointer to logic element
    */
    void AddLogic(std::string logic, CLogic* clogic);

    /**
     * Add wire to this CLogic instance
     * 
     * @param wire name of wire
    */
    void AddWire(std::string wire);

    /**
     * Connect the circuit input to wire
     * 
     * @param wire name of wire
     * @param circuitInput which input number to bind from
    */
    void MapInput(std::string wire, int circuitInput = -1);

    /**
     * Connect the output of logic element to circuit output
     * 
     * @param logic name of logic element
     * @param output output of logic element to connect from 
     * @param circuitOnput which output number to bind to
    */
    void MapOutput(std::string logic, int logicOutput, int circuitOutput = -1);

private:
    /**
     * Compute the output levels of this Clogic object
    */
    void ComputeOutput();

    std::unordered_map<std::string, CLogic*> mLogics;                 // gate pointers
    std::unordered_map<std::string, CWire*> mWires;                   // wire pointers

    std::vector<std::tuple<int, std::string>> inputMap;               // input mapping
    std::vector<std::tuple<std::string, int, int>> outputMap;         // output mapping
};

#endif