#ifndef _CWIRE_H
#define _CWIRE_H

//--Forward Declaration
class CLogic;

//--Consts and enums-----------------------------------------------------------
enum eLogicLevel // enum defining the possible states of a logic line
{
    LOGIC_UNDEFINED = -1,
    LOGIC_LOW = 0,
    LOGIC_HIGH = 1
};

//---CWire Declaration-----------------------------------------------------------
// CWire is used to connect devices in this simulation
// A CWire has a single input, and may drive multiple outputs
// The global variable MaxFanout controls how many outputs each wire can have
// Each wire output drives a specific input of a specific gate
// The wire's input is controlled via the DriveLevel function
class CWire
{
  public:
    /**
     * Constructor
    */
    CWire();

    /**
     * Adds to the list of outputs that this wire drives
     * 
     * @param apGateToDrive gate to drive
     * @param aGateInputToDrive input of gate to drive
    */
    void AddOutputConnection(CLogic *apGateToDrive, int aGateInputToDrive);

    /**
     * Drives the wire's value, so that each of its connected outputs
     * 
     * @param aNewLevel levels to drive this wire with
    */
    void DriveLevel(eLogicLevel aNewLevel);

  private:
    static const int MaxFanout = 2;     // max gate inputs that one gate output can drive 
    int mNumOutputConnections;            // how many outputs are connected
    CLogic *mpGatesToDrive[MaxFanout];    // list of connected gates
    int mGateInputIndices[MaxFanout];     // list of input to drive in each gate
};

#endif