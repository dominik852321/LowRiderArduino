#include <Arduino.h>
#include "Storage.h"
#include "PressureManipulator.h"
class MemoryHelper {
  private:
    Storage EepromStorage;
    static int EepromIndexCounter;
  public:
    MemoryHelper();
    void Init();
    void SaveToStorage(int values[], PressureManipulator manipulators[]);
    void RestoreFromStorageToPressureManipulators(PressureManipulator manipulators[]);
};
