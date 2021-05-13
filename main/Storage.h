#ifndef STORAGE_H
#define STORAGE_H
#include <Arduino.h>
class Storage {
  private:  
    int StorageBaud;
  public:    
    short StorageIndex;
    Storage();       
    void Init();
    String GetStoredValue(int value);
    void GetStoredValues(int* values);    
    void StoreValues(int* values);
};
#endif
