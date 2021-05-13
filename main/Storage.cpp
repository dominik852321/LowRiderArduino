#include "Storage.h"
#include "Configuration.h"
#include <EEPROM.h>

static short StorageIndexCounter = 0;
Storage::Storage() {  
}
void Storage::Init() { 
  this->StorageBaud = 1;  
  this->StorageIndex = StorageIndexCounter++;
}

void Storage::GetStoredValues(int* values) {
 //Adres bitu
 int addr = StorageBaud * NumberOfPressureSensors * StorageIndex;
  for(int i=0; i< NumberOfPressureSensors; i++){
    //Jedna wartosc
    int storedValue = 0;
    short val = EEPROM.read(addr);
    storedValue += val;
    addr = addr + 1;
    if (addr == EEPROM.length()) {
       addr = 0;
    } 
    values[i] = storedValue;
    Serial.println("Stored value");
    Serial.println(storedValue);
  }
}

//Wyciagniecie jednej wartosci
String Storage::GetStoredValue(int value) {
  //pobierz adres poczatkowy
  int addr = StorageBaud * NumberOfPressureSensors * StorageIndex;
  float storedValue = 0;
  //wybor 1 lub 2 czujnika
  if(value == 1){
    short val = EEPROM.read(addr);
    storedValue += val;
    }
  else {
    short val = EEPROM.read(addr+1);
    storedValue += val;
   }

  storedValue = storedValue * (5.0 / 16.0);
  return String(storedValue, 2);
}

void Storage::StoreValues(int* values) {
  int addr = StorageBaud * NumberOfPressureSensors * StorageIndex;
  for(int i=0; i< NumberOfPressureSensors; i++){
    int valueToStore = values[i];
   
    short val = 0;
    if(valueToStore > 255){        
      val = 255;
    }
    else{
      val = valueToStore % 256;
    }
    EEPROM.write(addr, val);  
    valueToStore -= val;
    addr = addr + 1;
    if (addr == EEPROM.length()) {
      addr = 0;
      } 
   }
  }
