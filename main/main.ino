#include "MemoryHelper.h"
#include "InputReader.h"
#include "Configuration.h"
#include "PressureManipulator.h"
#include "Nextion.h"

InputReader reader1(PRESSURE_READER1);
InputReader reader2(PRESSURE_READER2);
InputReader readers[] = {reader1, reader2};
MemoryHelper memory1;
MemoryHelper memory2;
PressureManipulator manipulators[] = {PressureManipulator(RELAY_INCREASE_FRONT, RELAY_DECREASE_FRONT, reader1), PressureManipulator(RELAY_INCREASE_REAR, RELAY_DECREASE_REAR, reader2)};

int displayCounter = 0;
int displayDelay = 25;

int odczyty[2];
char _buffer[10];


NexTouch *nex_listen_list[] = {
  &mem_1,
  &mem_2,
  &mem_3,
  &mem_4,
  &inc_front,
  &inc_rear,
  &inc_car,
  &dec_front,
  &dec_rear,
  &dec_car,
  NULL,
};
void setup() {
  nexInit();
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  reader1.Init();
  reader2.Init();
  memory1.Init();
  memory2.Init();

  manipulators[0].Init();
  manipulators[1].Init();
  memory1.RestoreFromStorageToPressureManipulators(manipulators);
  mem_1.attachPush(SaveValues1_PushCallback, &mem_1);
  mem_2.attachPush(SaveValues2_PushCallback, &mem_2);
  mem_3.attachPush(RestoreValues1_PushCallback, &mem_3);
  mem_4.attachPush(RestoreValues2_PushCallback, &mem_4);

  //Inicjalizacja manualnego podnoszenia
  inc_front.attachPush(IncreaseFront_PushCallback, &inc_front);
  inc_front.attachPop(Manipulators_PopCallback, &inc_front);
  
  inc_rear.attachPush(IncreaseRear_PushCallback, &inc_rear);
  inc_rear.attachPop(Manipulators_PopCallback, &inc_rear);
  
  inc_car.attachPush(IncreaseCar_PushCallback, &inc_car);
  inc_car.attachPop(Manipulators_PopCallback, &inc_car);
  
  dec_front.attachPush(DecreaseFront_PushCallback, &dec_front);
  dec_front.attachPop(Manipulators_PopCallback, &dec_front);
  
  dec_rear.attachPush(DecreaseRear_PushCallback, &dec_rear);
  dec_rear.attachPop(Manipulators_PopCallback, &dec_rear);

  dec_car.attachPush(DecreaseCar_PushCallback, &dec_car);
  dec_car.attachPop(Manipulators_PopCallback, &dec_car);
}

void loop() {
  nexLoop(nex_listen_list);  
  DisplayCurrentPreassures();
  delay(20);
}
void DisplayCurrentPreassures() {    
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  
  ++displayCounter;
  if(displayCounter > displayDelay)
    displayCounter = 0;
  if(displayCounter < displayDelay)
    return;
  
  MapToVolts(odczyty[0], _buffer);
  t1.setText(_buffer);
  
  MapToVolts(odczyty[1], _buffer);
  t2.setText(_buffer);
}
void MapToVolts(int odczyt, char* _buffer) {
  float value = odczyt  * (5.0 / 1024.0);
  //4 is mininum width, 3 is precision; float value is copied onto buff
  dtostrf(value, 4, 3, _buffer);
}


//NEXTION BINDS
//Memory
void SaveValues1_PushCallback(void*prt)
{
  int odczyty[NumberOfPressureSensors];
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  memory1.SaveToStorage(odczyty, manipulators);
}

void SaveValues2_PushCallback(void*prt)
{
  int odczyty[NumberOfPressureSensors];
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  memory2.SaveToStorage(odczyty, manipulators);
}

void RestoreValues1_PushCallback(void*prt)
{
  memory1.RestoreFromStorageToPressureManipulators(manipulators);
}

void RestoreValues2_PushCallback(void*prt)
{
  memory2.RestoreFromStorageToPressureManipulators(manipulators);
}

//Manual manipulations
void IncreaseFront_PushCallback(void*prt)
{
  manipulators[0].IncreaseValue();
}

void DecreaseFront_PushCallback(void*prt)
{
  manipulators[0].DecreaseValue();
}

void IncreaseRear_PushCallback(void*prt)
{
  manipulators[1].IncreaseValue();
}

void DecreaseRear_PushCallback(void*prt)
{
  manipulators[1].DecreaseValue();
}

void IncreaseCar_PushCallback(void*prt)
{
  manipulators[0].IncreaseValue();
  manipulators[1].IncreaseValue();
}

void DecreaseCar_PushCallback(void*prt)
{
  manipulators[1].DecreaseValue();
  manipulators[0].DecreaseValue();
}

void Manipulators_PopCallback(void*prt) {
  manipulators[0].StopManipulating();
  manipulators[1].StopManipulating();
}
