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
#include <iostream>
#include <vector>
#include <tuple>
#include <bitset>

using namespace std;

//--Consts and enums-----------------------------------------------------------
const int InputsPerGate = 2; // number of inputs per nand gate
const int MaxFanout = 2;     // maximum fanout: max gate inputs that one gate output can drive

enum eLogicLevel // enum defining the possible states of a logic line
{
    LOGIC_UNDEFINED = -1,
    LOGIC_LOW,
    LOGIC_HIGH
};

//---Forward Declarations------------------------------------------------------
class CLogic;
class CCircuit;
CCircuit* NewHalfAdder();
CCircuit* NewFullAdder();
CCircuit* NewThreeBitAdder();
void HalfAdderTest(string A, string B);
void FullAdderTest(string A, string B, string C);
void ThreeBitAdderTest(string A, string B);
void CarryEnableHalfAdderTest(string A, string B, string E);

//---CWire Interface-----------------------------------------------------------
// CWire is used to connect devices in this simulation
// A CWire has a single input, and may drive multiple outputs
// The global variable MaxFanout controls how many outputs each wire can have
// Each wire output drives a specific input of a specific gate
// The wire's input is controlled via the DriveLevel function
class CWire
{
public:
    // Constructor
    CWire();

    // AddOutputConnection adds to the list of outputs that this wire drives
    // It accepts as parameters the nand gate whose input should be driven
    // and the index specifying which of that gate's inputs should be driven.
    void AddOutputConnection(CLogic *apGateToDrive, int aGateInputToDrive);

    // DriveLevel drives the wire's value, so that each of its connected outputs
    // get set to the corresponding level
    void DriveLevel(eLogicLevel aNewLevel);

private:
    int mNumOutputConnections;            // how many outputs are connected
    CLogic *mpGatesToDrive[MaxFanout];    // list of connected gates
    int mGateInputIndices[MaxFanout];     // list of input to drive in each gate
};

//---Logic Interface-------------------------------------------------------
// CLogic is a template class used to represent logic cells (i.e. gates or subcircuits)
class CLogic
{
public:
    // Constructor destructor
    CLogic(int nInputs, int nOutputs);
    virtual ~CLogic();

    // ConnectOutput connects this gate's output to wire {apOutputConnection}
    // That wire will be driven by the gate's output level
    void ConnectOutput(int aOutputIndex, CWire *apOutputConnection);

    // DriveInput drives the specified input of this gate {aInputIndex}
    // with the specified level {aNewLevel}
    void DriveInput(int aInputIndex, eLogicLevel aNewLevel);

    // GetOutputState returns the current output level of this gate
    eLogicLevel GetOutputState(int aOutputIndex);

protected:
    // ComputeOutput is a virtual function implemented by subclasses depending on their logic.
    // Used to populate output values and drive output wires.
    virtual void ComputeOutput() = 0;

    vector<eLogicLevel> mInputs;            // Input levels
    vector<eLogicLevel> mOutputs;           // Output levels
    vector<CWire*> mpOutputConnections;     // Output wires
};

//---CANDGate Interface-------------------------------------------------------
// Subclass of CLogic that simulates an AND gate
class CANDGate: public CLogic
{
public:
    // Constructor
    CANDGate();

private:
    // ComputeOutput contains AND logic and drives the output wire if it exists
    void ComputeOutput();
};

//---CORGate Interface-------------------------------------------------------
// Subclass of CLogic that simulates an OR gate
class CORGate: public CLogic
{
public:
    // Constructor
    CORGate();

private:
    // ComputeOutput contains OR logic and drives the output wire if it exists
    void ComputeOutput();
};

//---CXORGate Interface-------------------------------------------------------
// Subclass of CLogic that simulates a XOR gate
class CXORGate: public CLogic
{
public:
    // Constructor
    CXORGate();

private:
    // ComputeOutput contains XOR logic and drives the output wire if it exists
    void ComputeOutput();
};

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

    vector<CLogic*> mLogics; 
    vector<CWire*> mWires; 

    vector<tuple<int, int>> inputMap;               // input mapping
    vector<tuple<int, int, int>> outputMap;         // output mapping
};

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

//---CWire Implementation------------------------------------------------------
CWire::CWire()
{
    mNumOutputConnections = 0;
}

void CWire::AddOutputConnection(CLogic *apGateToDrive, int aGateInputToDrive)
{
    mpGatesToDrive[mNumOutputConnections] = apGateToDrive;
    mGateInputIndices[mNumOutputConnections] = aGateInputToDrive;
    ++mNumOutputConnections;
}

void CWire::DriveLevel(eLogicLevel aNewLevel)
{
    for (int i = 0; i < mNumOutputConnections; ++i)
        mpGatesToDrive[i]->DriveInput(mGateInputIndices[i], aNewLevel);
}

//---CLogic Implementation--------------------------------------------------
CLogic::CLogic(int nInputs, int nOutputs)
{
    mInputs = vector<eLogicLevel>(nInputs, LOGIC_UNDEFINED);
    mOutputs = vector<eLogicLevel>(nOutputs, LOGIC_UNDEFINED);
    mpOutputConnections = vector<CWire*>(nOutputs, NULL);
}

CLogic::~CLogic(){}

void CLogic::ConnectOutput(int aOutputIndex, CWire *apOutputConnection)
{
    mpOutputConnections[aOutputIndex] = apOutputConnection;
}

void CLogic::DriveInput(int aInputIndex, eLogicLevel aNewLevel)
{
    mInputs[aInputIndex] = aNewLevel;
    ComputeOutput();
}

eLogicLevel CLogic::GetOutputState(int aOutputIndex)
{
    return mOutputs[aOutputIndex];
}

//---CANDGate Implementation--------------------------------------------------
CANDGate::CANDGate() : CLogic(2, 1)
{
    mInputs[0] = mInputs[1] = LOGIC_UNDEFINED;
    mpOutputConnections[0] = NULL;
    ComputeOutput();
}

void CANDGate::ComputeOutput()
{
    // AND logic
    if (mInputs[0] == LOGIC_UNDEFINED || mInputs[1] == LOGIC_UNDEFINED)
    {
        mOutputs[0] = LOGIC_UNDEFINED;
    }
    else 
    {
        mOutputs[0] = (mInputs[0] == LOGIC_HIGH && mInputs[1] == LOGIC_HIGH) ? LOGIC_HIGH : LOGIC_LOW;
    }
    // Drive output
    if (mpOutputConnections[0] != NULL) mpOutputConnections[0]->DriveLevel(mOutputs[0]);
}

//---CXORGate Implementation--------------------------------------------------
CXORGate::CXORGate() : CLogic(2, 1)
{
    mInputs[0] = mInputs[1] = LOGIC_UNDEFINED;
    mpOutputConnections[0] = NULL;
    ComputeOutput();
}

void CXORGate::ComputeOutput()
{
    // XOR logic
    if (mInputs[0] == LOGIC_UNDEFINED || mInputs[1] == LOGIC_UNDEFINED)
    {
        mOutputs[0] = LOGIC_UNDEFINED;
    }
    else 
    {
        mOutputs[0] = ((mInputs[0] == LOGIC_HIGH || mInputs[1] == LOGIC_HIGH) && mInputs[0] != mInputs[1]) ? LOGIC_HIGH : LOGIC_LOW;
    }
    // Drive output
    if (mpOutputConnections[0] != NULL) mpOutputConnections[0]->DriveLevel(mOutputs[0]);
}

//---CORGate Implementation--------------------------------------------------
CORGate::CORGate() : CLogic(2, 1)
{
    mInputs[0] = mInputs[1] = LOGIC_UNDEFINED;
    mpOutputConnections[0] = NULL;
    ComputeOutput();
}

void CORGate::ComputeOutput()
{
    // XOR logic
    if (mInputs[0] == LOGIC_UNDEFINED || mInputs[1] == LOGIC_UNDEFINED)
    {
        mOutputs[0] = LOGIC_UNDEFINED;
    }
    else 
    {
        mOutputs[0] = (mInputs[0] == LOGIC_HIGH || mInputs[1] == LOGIC_HIGH) ? LOGIC_HIGH : LOGIC_LOW;
    }
    // Drive output
    if (mpOutputConnections[0] != NULL) mpOutputConnections[0]->DriveLevel(mOutputs[0]);
}

//---CCircuit Implementation--------------------------------------------------
CCircuit::CCircuit(int nInputs, int nOutputs, int nLogics, int nWires) : CLogic(nInputs, nOutputs)
{
    nLogics = nLogics;     
    nWires = nWires;

    mLogics = vector<CLogic*>(nLogics);
    for (int i = 0; i < nWires; i++) mWires.push_back(new CWire());
}

CCircuit::~CCircuit()
{
    for (CWire* w : mWires) delete w;
    for (CLogic* l : mLogics) delete l;
}

void CCircuit::ConnectWireToLogic(int wire, int logic, int input)
{
    mWires[wire]->AddOutputConnection(mLogics[logic], input);
}

void CCircuit::ConnectLogicToWire(int logic, int output, int wire)
{
    mLogics[logic]->ConnectOutput(output, mWires[wire]);
}

void CCircuit::SetLogic(int logic, CLogic* clogic)
{
    mLogics[logic] = clogic;
}

void CCircuit::MapInput(int circuitInput, int wire)
{
    inputMap.push_back(make_tuple(circuitInput, wire));
}

void CCircuit::MapOutput(int logic, int logicOutput, int circuitOutput)
{
    outputMap.push_back(make_tuple(logic, logicOutput, circuitOutput));
}

void CCircuit::ComputeOutput()
{
    for (tuple<int, int> t : inputMap){
        mWires[get<1>(t)]->DriveLevel(mInputs[get<0>(t)]);
    }

    for (tuple<int, int, int> t : outputMap){
        eLogicLevel output = mLogics[get<0>(t)]->GetOutputState(get<1>(t));
        mOutputs[get<2>(t)] = output;
        if (mpOutputConnections[get<2>(t)] != NULL) mpOutputConnections[get<2>(t)]->DriveLevel(output);
    }
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