#include "MemoryHelper.h"
#include "Configuration.h"

MemoryHelper::MemoryHelper() {
  this->EepromStorage = Storage();
}
void MemoryHelper::Init() {
  this->EepromStorage.Init();
}
void MemoryHelper::SaveToStorage(int values[], PressureManipulator manipulators[]) {
    //zapisujemy wartosc do storage
    for (int i = 0; i < NumberOfPressureSensors; i++) {
      this->EepromStorage.StoreValues(values);
    }
    return;
}

void MemoryHelper::RestoreFromStorageToPressureManipulators(PressureManipulator manipulators[]) {
  //wartosc ze storage wysylamy do manipulatora cisnienia
  {
    int storedValues[NumberOfPressureSensors];
    this->EepromStorage.GetStoredValues(storedValues);
    for (int i = 0; i < NumberOfPressureSensors; i++) {
      manipulators[i].SetExpectedValue(storedValues[i]);
    }
  }
}
