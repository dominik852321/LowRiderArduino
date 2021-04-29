#ifndef PRESSURE_MANIPULATOR_H
#define PRESSURE_MANIPULATOR_H
#include <Arduino.h>
#include "InputReader.h"
class PressureManipulator {
  private:  
    byte PositivePin;
    byte NegativePin;
    int ExpectedValue;
    InputReader& PressureReader;
    short Epsylon;
  public:   
    PressureManipulator(byte positivePin, byte negativePin, InputReader& pressureReader);    
    void Init();
    void SetExpectedValue(int expectedValue);
    void Run();
    void IncreaseValue();
    void DecreaseValue();
    void StopManipulating();
};
#endif
