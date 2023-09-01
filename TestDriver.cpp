// See TestDriver.h
//
//--Includes-------------------------------------------------------------------
#include "TestDriver.h"
#include "CANDGate.h"
#include "CORGate.h"
#include "CXORGate.h"
#include "CNOTGate.h"
#include "CCircuit.h"

#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <cmath>

//--TestDriver Implementation-------------------------------------------------------------------
std::pair<std::string, CLogic*> TestDriver::NewCircuit () {
    
    std::string CircuitName = "Unknown circuit";
    CCircuit* Circuit = new CCircuit();

    while(true)
    {
        std::string Request;
        std::cin >> Request;  // get the next word from the input stream
        std::cout << "Processing input token: " << Request << std::endl;
        
        if( Request[0] == '#' )
        {
            // a comment line
            // get the rest of the line and ignore it
            std::string DummyVar;
            getline( std::cin, DummyVar );
        }
        else if( Request.compare( "component" ) == 0 )
        {
            std::string GateType;
            std::string GateName;
            std::cin >> GateType;
            std::cin >> GateName;
            std::cout << "Adding gate of type " << GateType << " named " << GateName << std::endl;
            // Allocate new gate of specified type
            CLogic* Gate;
            if (GateType.compare( "or" ) == 0)
            {
                Gate = new CORGate();
            }
            else if (GateType.compare( "and" ) == 0)
            {
                Gate = new CANDGate();
            }
            else if (GateType.compare( "xor" ) == 0)
            {
                Gate = new CXORGate();
            }
            else if (GateType.compare( "not" ) == 0)
            {
                Gate = new CNOTGate();
            }
            else 
            {
                std::cout << "Unrecognised gate " << GateType << std::endl;
                std::cout << "Continuing to next line" << std::endl;
                // get the rest of the line and ignore it
                std::string DummyVar;
                getline( std::cin, DummyVar );
                continue;
            }
            // Add new gate to circuit
            Circuit->AddLogic(GateName, Gate);
        }

        else if( Request.compare( "wire" ) == 0 )
        {
            std::string GateName;
            std::string Input;
            std::string WireName;

            std::cin >> WireName;
            std::cin >> Input;
            std::cin >> GateName;
            
            // Add new wire to circuit, and connect it
            Circuit->AddWire(WireName);
            Circuit->ConnectWireToLogic(WireName, GateName, stoi(Input));
        }

        else if( Request.compare( "connect" ) == 0 )
        {
            std::string GateName;
            std::string Output;
            std::string WireName;

            std::cin >> GateName;
            std::cin >> Output;
            std::cin >> WireName;
        
            // Connect specified output of named gate to named wire
            Circuit->ConnectLogicToWire(GateName, stoi(Output), WireName);
        }

        else if( Request.compare( "testerOutput" ) == 0 )
        {
            std::string GateName;
            std::string Output;

            std::cin >> GateName;
            std::cin >> Output;
        
            // Set specified output of named gate as output
            Circuit->MapOutput(GateName, stoi(Output));
        }

        else if( Request.compare( "testerInput" ) == 0 )
        {
            std::string WireName;
            std::cin >> WireName;
        
            // Set named wire as input
            Circuit->MapInput(WireName);
        }
        
        else if( Request.compare( "end" ) == 0 )
        {
            // Save circuit name and stop reading file
            std::cin >> CircuitName;
            break;
        }

        else
        {
            std::cout << "Unrecognised command " << Request << std::endl;
            std::cout << "Continuing to next line" << std::endl;
            // get the rest of the line and ignore it
            std::string DummyVar;
            getline( std::cin, DummyVar );
        }
    }

    // Return circuit name and pointer
    return std::make_pair(CircuitName, Circuit);
}

void TestDriver::TestCircuit (std::pair<std::string, CLogic*> &CircuitInfo, std::string &Input, int i)
{
    if (i >= CircuitInfo.second->InputSize())
    {
        TestInput(CircuitInfo.first, CircuitInfo.second, Input);
    }
    else 
    {
        // Recursion
        Input.push_back('0');
        TestCircuit(CircuitInfo, Input, i+1);
        Input.pop_back();

        Input.push_back('1');
        TestCircuit(CircuitInfo, Input, i+1);
        Input.pop_back();
    }
    return;
}

void TestDriver::TestInput (std::string Name, CLogic* Circuit, std::string Input){
    
    std::string Output;
    const std::size_t InputWidth = Circuit->InputSize();
    const std::size_t OutputWidth = Circuit->OutputSize();

    // Drive each input with corressponding assignment
    for (int j = 0; j < int(InputWidth); j++){
        Circuit->DriveInput(j, (Input[j] == '1') ? LOGIC_HIGH : LOGIC_LOW);
    }

    // Get all outputs and print 
    Output = "";
    for (int j = 0; j < int(OutputWidth); j++){
        if (Circuit->GetOutputState(j) == LOGIC_HIGH) 
        {
            Output.push_back('1');
        }
        else if (Circuit->GetOutputState(j) == LOGIC_LOW) 
        {
            Output.push_back('0');
        }
        else {
            Output.push_back('Z');
        }
    }

    std::cout << "[" << Name << "]"
                << " Input: " << Input
                << " >>> "
                << " Output: " << Output
                << std::endl;

    return;
}