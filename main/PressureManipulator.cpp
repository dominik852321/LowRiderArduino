#include "PressureManipulator.h"
#include "Configuration.h"
PressureManipulator::PressureManipulator(byte positivePin, byte negativePin, InputReader& pressureReader): PressureReader(pressureReader) {
  this->Epsylon = 10;       
  this->PositivePin = positivePin;
  this->NegativePin = negativePin;
}
void PressureManipulator::Init()  {
  this->StopManipulating();
}

void PressureManipulator::SetExpectedValue(int expectedValue){ 
  this->ExpectedValue = expectedValue;
}
void PressureManipulator::Run(){  
  int currentValue = PressureReader.ReadAverageInput();
  while(abs(currentValue - this->ExpectedValue) > Epsylon){    
    if(this->ExpectedValue > currentValue){
//      Serial.println("Za malo, zwiekszamy");
      IncreaseValue();
    }
    else{      
//      Serial.println("Za duzo, zmiejszamy");
      DecreaseValue();
    }    
    delay(50);
    currentValue = PressureReader.ReadAverageInput();
  }  
//  Serial.println("Stop");
  StopManipulating();
}
void PressureManipulator::IncreaseValue(){
  digitalWrite(PositivePin, RelayIncrease);
  digitalWrite(NegativePin, RelayDecrease);
}

void PressureManipulator::DecreaseValue(){
  digitalWrite(NegativePin, RelayIncrease);
  digitalWrite(PositivePin, RelayDecrease);
}
void PressureManipulator::StopManipulating(){
  digitalWrite(NegativePin, RelayDecrease);
  digitalWrite(PositivePin, RelayDecrease);
}
