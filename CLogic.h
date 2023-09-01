#ifndef _CLOGIC_H
#define _CLOGIC_H

//--Includes-------------------------------------------------------------------
#include "CWire.h"

#include <vector>

//---Logic Declaration-------------------------------------------------------
// CLogic is a template class used to represent logic cells (i.e. gates or subcircuits)
class CLogic
{
  public:
    /**
     * Constructor
    */
    CLogic();

    /**
     * Destructor
    */
    virtual ~CLogic();

    /**
     * connect this logic element's output to a wire
     * 
     * @param aOutputIndex output number
     * @param apOutputConnection wire to connect to
    */
    void ConnectOutput(int aOutputIndex, CWire *apOutputConnection);

    /**
     * drive the specified input of this logic element
     * 
     * @param aInputIndex input number
     * @param aNewLevel level to drive input
    */
    void DriveInput(int aInputIndex, eLogicLevel aNewLevel);

    /**
     * return current output level of this logic element
     * 
     * @param aOutputIndex output number
    */
    eLogicLevel GetOutputState(int aOutputIndex);

    /**
     * return number of inputs of this logic element
     * 
     * @return number of inputs
    */
    int InputSize();

    /**
     * return number of outputs of this logic element
     * 
     * @return number of outputs
    */
    int OutputSize();

  protected:

    /**
     * Pure virtual function
     * 
     * For computing the output levels of Clogic objects
    */
    virtual void ComputeOutput() = 0;

    std::vector<eLogicLevel> mInputs;            // Input levels
    std::vector<eLogicLevel> mOutputs;           // Output levels
    std::vector<CWire*> mpOutputConnections;     // Output wires
};

#endif