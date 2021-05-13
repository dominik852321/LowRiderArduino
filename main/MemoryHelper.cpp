#include "MemoryHelper.h"
#include "Configuration.h"

MemoryHelper::MemoryHelper() {
  this->EepromStorage = Storage();
}
//Inicjalizacja i przypisanie do wyników na 3 stronie
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

//Pobierz jedną wartosc z eepromu value to numer czujnika
String MemoryHelper::RestoreFromStorageValue(int value){
  String storedValue = this->EepromStorage.GetStoredValue(value);
  return storedValue;
  }

void MemoryHelper::RestoreFromStorageToPressureManipulators(PressureManipulator manipulators[]) {
  //wartosc ze storage wysylamy do manipulatora cisnienia
  
    int storedValues[NumberOfPressureSensors];
    this->EepromStorage.GetStoredValues(storedValues);
    for (int i = 0; i < NumberOfPressureSensors; i++) {
      manipulators[i].SetExpectedValue(storedValues[i]);
    }
    for (int i = 0; i < NumberOfPressureSensors; i++) {
      manipulators[i].Run();
    }
}
