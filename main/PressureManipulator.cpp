#include "PressureManipulator.h"
#include "Configuration.h"
PressureManipulator::PressureManipulator(byte positivePin, byte negativePin, InputReader& pressureReader): PressureReader(pressureReader) {
  this->Epsylon = 0;       
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
  Serial.println("Start maniupulate");
  int currentValue = PressureReader.ReadAverageInput();
 
  while(abs(currentValue - this->ExpectedValue) > Epsylon)
  {    
    Serial.print("Obecna wartosc = ");
    if(this->ExpectedValue > currentValue){
      Serial.print(currentValue);
      Serial.print("   oczekiwana = ");
      Serial.print(this->ExpectedValue);
      Serial.print("\n");
      IncreaseValue();
    }
    else{
      Serial.print(currentValue);      
      Serial.print("   oczekiwana = ");
      Serial.print(this->ExpectedValue);
      Serial.print("\n");
      DecreaseValue();
    } 
    delay(50);
    currentValue = PressureReader.ReadAverageInput();
  };
 
  Serial.println("Stop");
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
