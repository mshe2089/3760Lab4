#ifndef _CLOGIC_H
#define _CLOGIC_H

#include "CWire.h"

#include <vector>

//---Logic Interface-------------------------------------------------------
// CLogic is a template class used to represent logic cells (i.e. gates or subcircuits)
class CLogic
{
  public:
    // Constructor destructor
    CLogic();
    virtual ~CLogic();

    // ConnectOutput connects this gate's output to wire {apOutputConnection}
    // That wire will be driven by the gate's output level
    void ConnectOutput(int aOutputIndex, CWire *apOutputConnection);

    // DriveInput drives the specified input of this gate {aInputIndex}
    // with the specified level {aNewLevel}
    void DriveInput(int aInputIndex, eLogicLevel aNewLevel);

    // GetOutputState returns the current output level of this gate
    eLogicLevel GetOutputState(int aOutputIndex);

    int InputSize();

    int OutputSize();

  protected:
    // ComputeOutput is a virtual function implemented by subclasses depending on their logic.
    // Used to populate output values and drive output wires.
    virtual void ComputeOutput() = 0;

    std::vector<eLogicLevel> mInputs;            // Input levels
    std::vector<eLogicLevel> mOutputs;           // Output levels
    std::vector<CWire*> mpOutputConnections;     // Output wires
};

#endif