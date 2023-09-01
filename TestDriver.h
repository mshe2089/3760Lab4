#ifndef _TESTDRIVER_H
#define _TESTDRIVER_H

#include "CLogic.h"

#include <string>

class TestDriver
{
  public:
    std::pair<std::string, CLogic*>  NewCircuit ();

    void TestCircuit2 (std::pair<std::string, CLogic*> CircuitInfo);

    void TestCircuit3 (std::pair<std::string, CLogic*> CircuitInfo);

  private:
    void TestInput (std::string Name, CLogic* Circuit, std::string Input);

};

#endif // _TESTDRIVER_H