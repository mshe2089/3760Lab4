#ifndef _TESTDRIVER_H
#define _TESTDRIVER_H

#include "CLogic.h"

#include <string>

class TestDriver
{
  public:
    CLogic* NewCircuit ();

    void TestCircuit3 (std::string Name, CLogic* Circuit);

  private:
    void TestInput (std::string Name, CLogic* Circuit, std::string Input);

};

#endif // _TESTDRIVER_H