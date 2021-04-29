#include "InputReader.h"
InputReader::InputReader(byte pin) {
  this->Pin = pin;
  this->Iteration = 0;
}
void InputReader::Init() {
  Iteration = 0;
  for (int i = 0; i < 10; i++) {
    InputValues[i] = 0;
  }
}


int InputReader::ReadAverageInput() {
  int sum = 0;
  InputValues[Iteration] = ReadInput();
  Iteration = (Iteration + 1) % 10;
  for (int i = 0; i < 10; i++) {
    sum += InputValues[i];
  }
  return sum / 10;
}

int InputReader::ReadInput() {
  int odczyt = analogRead(Pin);
  return odczyt;
}
