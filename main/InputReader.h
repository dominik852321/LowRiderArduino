#ifndef INPUT_READER_H
#define INPUT_READER_H
#include <Arduino.h>
class InputReader {
  private:
    byte Pin;
    byte Iteration;
    int InputValues[10];
    int ReadInput();

  public:
    InputReader(byte pin);
    void Init();
    int ReadAverageInput();
};
#endif
