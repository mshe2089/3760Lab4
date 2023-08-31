#ifndef _CWIRE_H
#define _CWIRE_H

//---Forward Declaration
class CLogic;

//--Consts and enums-----------------------------------------------------------
enum eLogicLevel // enum defining the possible states of a logic line
{
    LOGIC_UNDEFINED = -1,
    LOGIC_LOW,
    LOGIC_HIGH
};

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
    static const int MaxFanout = 2;     // maximum fanout: max gate inputs that one gate output can drive 

    int mNumOutputConnections;            // how many outputs are connected
    CLogic *mpGatesToDrive[MaxFanout];    // list of connected gates
    int mGateInputIndices[MaxFanout];     // list of input to drive in each gate
};

#endif