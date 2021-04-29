#include "Storage.h"
#include "Configuration.h"
#include <EEPROM.h>

static short StorageIndexCounter = 0;
Storage::Storage() {  
}
void Storage::Init() { 
  this->StorageBaud = 5;  
  this->StorageIndex = StorageIndexCounter++;
}

void Storage::GetStoredValues(int* values) {
 int addr = StorageBaud * NumberOfPressureSensors * StorageIndex;
  for(int i=0; i< NumberOfPressureSensors; i++){
    int storedValue = 0;
    for(int j=0; j < this->StorageBaud; j++){
      short val = EEPROM.read(addr);
      storedValue += val;
      addr = addr + 1;
      if (addr == EEPROM.length()) {
        addr = 0;
      } 
    }
    values[i] = storedValue;
  }
}

void Storage::StoreValues(int* values) {
  int addr = StorageBaud * NumberOfPressureSensors * StorageIndex;
  for(int i=0; i< NumberOfPressureSensors; i++){
    int valueToStore = values[i];
    for(int j=0; j < this->StorageBaud; j++){
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
}
