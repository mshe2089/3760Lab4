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
#include "CANDGate.h"
#include "CORGate.h"
#include "CXORGate.h"
#include "CCircuit.h"

#include <iostream>
#include <vector>
#include <tuple>
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

    /*
    CarryEnableHalfAdderTest("1", "0", "0");
    CarryEnableHalfAdderTest("0", "1", "0");
    CarryEnableHalfAdderTest("0", "0", "0");
    CarryEnableHalfAdderTest("1", "1", "0");
    */

    return 0;
}

//---Testing and utility functions--------------------------------------------------

// Dynamically allocates and returns pointer to a new half adder CCircuit. No delete for now
CCircuit* NewHalfAdder(){
    CCircuit* halfAdder = new CCircuit(2, 2, 2, 2);
    halfAdder->SetLogic(0, new CXORGate());
    halfAdder->SetLogic(1, new CANDGate());

    halfAdder->ConnectWireToLogic(0, 0, 0);
    halfAdder->ConnectWireToLogic(0, 1, 0);
    halfAdder->ConnectWireToLogic(1, 0, 1);
    halfAdder->ConnectWireToLogic(1, 1, 1);

    halfAdder->MapInput(0, 0);              // 0: A
    halfAdder->MapInput(1, 1);              // 1: B

    halfAdder->MapOutput(0, 0, 0);          // 0: S
    halfAdder->MapOutput(1, 0, 1);          // 1: Cout

    return halfAdder;
}

// Dynamically allocates and returns pointer to a new full adder CCircuit. No delete for now
CCircuit* NewFullAdder(){
    CCircuit* fullAdder = new CCircuit(3, 2, 5, 6);
    
    fullAdder->SetLogic(0, new CXORGate());
    fullAdder->SetLogic(1, new CXORGate());
    fullAdder->SetLogic(2, new CANDGate());
    fullAdder->SetLogic(3, new CANDGate());
    fullAdder->SetLogic(4, new CORGate());

    fullAdder->ConnectWireToLogic(0, 0, 0);
    fullAdder->ConnectWireToLogic(0, 3, 1);
    fullAdder->ConnectWireToLogic(1, 0, 1);
    fullAdder->ConnectWireToLogic(1, 3, 0);

    fullAdder->ConnectWireToLogic(2, 1, 1);
    fullAdder->ConnectWireToLogic(2, 2, 0);

    fullAdder->ConnectLogicToWire(0, 0, 3);
    fullAdder->ConnectWireToLogic(3, 1, 0);
    fullAdder->ConnectWireToLogic(3, 2, 1);

    fullAdder->ConnectLogicToWire(2, 0, 4);
    fullAdder->ConnectLogicToWire(3, 0, 5);
    fullAdder->ConnectWireToLogic(4, 4, 0);
    fullAdder->ConnectWireToLogic(5, 4, 1);

    fullAdder->MapInput(0, 0);              // 0: A
    fullAdder->MapInput(1, 1);              // 1: B
    fullAdder->MapInput(2, 2);              // 2: Cin    

    fullAdder->MapOutput(1, 0, 0);          // 0: S
    fullAdder->MapOutput(4, 0, 1);          // 1: Cout

    return fullAdder;
}

// Dynamically allocates and returns pointer to a new three-bit adder CCircuit. No delete for now
CCircuit* NewThreeBitAdder(){

    CCircuit* threeBitAdder = new CCircuit(6, 4, 3, 8);
    
    threeBitAdder->SetLogic(0, NewHalfAdder());
    threeBitAdder->SetLogic(1, NewFullAdder());
    threeBitAdder->SetLogic(2, NewFullAdder());

    threeBitAdder->ConnectWireToLogic(0, 0, 0); 
    threeBitAdder->ConnectWireToLogic(1, 1, 0); 
    threeBitAdder->ConnectWireToLogic(2, 2, 0); 
    threeBitAdder->ConnectWireToLogic(3, 0, 1);
    threeBitAdder->ConnectWireToLogic(4, 1, 1);
    threeBitAdder->ConnectWireToLogic(5, 2, 1);

    threeBitAdder->ConnectLogicToWire(0, 1, 6);
    threeBitAdder->ConnectWireToLogic(6, 1, 2);
    threeBitAdder->ConnectLogicToWire(1, 1, 7);
    threeBitAdder->ConnectWireToLogic(7, 2, 2);

    threeBitAdder->MapInput(0, 0);              // 0: A0
    threeBitAdder->MapInput(1, 1);              // 1: A1
    threeBitAdder->MapInput(2, 2);              // 2: A2
    threeBitAdder->MapInput(3, 3);              // 3: B0
    threeBitAdder->MapInput(4, 4);              // 4: B1
    threeBitAdder->MapInput(5, 5);              // 5: B2  

    threeBitAdder->MapOutput(0, 0, 0);          // 0: S0
    threeBitAdder->MapOutput(1, 0, 1);          // 1: S1
    threeBitAdder->MapOutput(2, 0, 2);          // 2: S2
    threeBitAdder->MapOutput(2, 1, 3);          // 3: S3

    return threeBitAdder;
}

// Dynamically allocates and returns pointer to a new half adder CCircuit with carry enable. No delete for now
// (Testing CCircuit that contain both CCircuits and CGates)
CCircuit* NewCarryEnableHalfAdder(){
    CCircuit* enableHalfAdder = new CCircuit(3, 2, 2, 4);
    
    enableHalfAdder->SetLogic(0, NewHalfAdder());
    enableHalfAdder->SetLogic(1, new CANDGate());

    enableHalfAdder->ConnectWireToLogic(0, 0, 0); 
    enableHalfAdder->ConnectWireToLogic(1, 0, 1); 
    enableHalfAdder->ConnectWireToLogic(2, 1, 1);

    enableHalfAdder->ConnectLogicToWire(0, 1, 3);
    enableHalfAdder->ConnectWireToLogic(3, 1, 0);

    enableHalfAdder->MapInput(0, 0);              // 0: A
    enableHalfAdder->MapInput(1, 1);              // 1: B
    enableHalfAdder->MapInput(2, 2);              // 2: Carry Enable

    enableHalfAdder->MapOutput(0, 0, 0);          // 0: S
    enableHalfAdder->MapOutput(1, 0, 1);          // 1: Carry

    return enableHalfAdder;
}

// Takes A, B bits as strings, returns half adder result as string
void HalfAdderTest(string A, string B){

    CCircuit* halfAdder = NewHalfAdder();
    halfAdder->DriveInput(0, (A[0]=='1')?LOGIC_HIGH:LOGIC_LOW);
    halfAdder->DriveInput(1, (B[0]=='1')?LOGIC_HIGH:LOGIC_LOW);

    string result = "";
    result.append(to_string(halfAdder->GetOutputState(1)));
    result.append(to_string(halfAdder->GetOutputState(0)));

    cout << "[Half Adder]" 
        << " A: " << A 
        << " B: " << B
        << "   >>>   "
        << " C: " << halfAdder->GetOutputState(1) 
        << " S: " << halfAdder->GetOutputState(0) 
        << endl;
    
    delete halfAdder;
    return;
}

// Takes A, B, Carry bits as strings, returns full adder result as string
void FullAdderTest(string A, string B, string C){

    CCircuit* fullAdder = NewFullAdder();
    fullAdder->DriveInput(0, (A[0]=='1')?LOGIC_HIGH:LOGIC_LOW);
    fullAdder->DriveInput(1, (B[0]=='1')?LOGIC_HIGH:LOGIC_LOW);
    fullAdder->DriveInput(2, (C[0]=='1')?LOGIC_HIGH:LOGIC_LOW);

    string result = "";
    result.append(to_string(fullAdder->GetOutputState(1)));
    result.append(to_string(fullAdder->GetOutputState(0)));

    cout << "[Full Adder]" 
        << " A: " << A 
        << " B: " << B
        << " Cin: " << C
        << "   >>>   "
        << " Cout: " << fullAdder->GetOutputState(1) 
        << " S: " << fullAdder->GetOutputState(0) 
        << endl;
    
    delete fullAdder;
    return;
}

// Takes A, B 3-bits as strings, returns three bit adder result as string
void ThreeBitAdderTest(string A, string B){
    CCircuit* threeBitAdder = NewThreeBitAdder();
    threeBitAdder->DriveInput(0, (A[2]=='1')?LOGIC_HIGH:LOGIC_LOW);
    threeBitAdder->DriveInput(1, (A[1]=='1')?LOGIC_HIGH:LOGIC_LOW);
    threeBitAdder->DriveInput(2, (A[0]=='1')?LOGIC_HIGH:LOGIC_LOW);

    threeBitAdder->DriveInput(3, (B[2]=='1')?LOGIC_HIGH:LOGIC_LOW);
    threeBitAdder->DriveInput(4, (B[1]=='1')?LOGIC_HIGH:LOGIC_LOW);
    threeBitAdder->DriveInput(5, (B[0]=='1')?LOGIC_HIGH:LOGIC_LOW);

    string result = "";
    result.append(to_string(threeBitAdder->GetOutputState(3)));
    result.append(to_string(threeBitAdder->GetOutputState(2)));
    result.append(to_string(threeBitAdder->GetOutputState(1)));
    result.append(to_string(threeBitAdder->GetOutputState(0)));

    cout << "[Three Bit Adder]" 
        << " A: " << A 
        << " B: " << B
        << "   >>>   "
        << " Result: " 
        << threeBitAdder->GetOutputState(3)
        << threeBitAdder->GetOutputState(2)
        << threeBitAdder->GetOutputState(1)
        << threeBitAdder->GetOutputState(0)
        << endl;
    
    delete threeBitAdder;
    return;
}

// Takes A, B, E bits as strings, returns half adder result as string (with carry enable)
void CarryEnableHalfAdderTest(string A, string B, string E){

    CCircuit* enableHalfAdder = NewCarryEnableHalfAdder();
    enableHalfAdder->DriveInput(0, (A[0]=='1')?LOGIC_HIGH:LOGIC_LOW);
    enableHalfAdder->DriveInput(1, (B[0]=='1')?LOGIC_HIGH:LOGIC_LOW);
    enableHalfAdder->DriveInput(2, (E[0]=='1')?LOGIC_HIGH:LOGIC_LOW);

    string result = "";
    result.append(to_string(enableHalfAdder->GetOutputState(1)));
    result.append(to_string(enableHalfAdder->GetOutputState(0)));

    cout << "[Three Bit Adder]" 
        << " A: " << A 
        << " B: " << B
        << " Enable: " << E
        << "   >>>   "
        << " C: " << enableHalfAdder->GetOutputState(1) 
        << " S: " << enableHalfAdder->GetOutputState(0) 
        << endl;

    return;
}