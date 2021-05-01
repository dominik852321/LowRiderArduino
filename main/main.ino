#include "MemoryHelper.h"
#include "InputReader.h"
#include "Configuration.h"
#include "PressureManipulator.h"
#include "Nextion.h"
#include <math.h>

InputReader reader1(PRESSURE_READER1);
InputReader reader2(PRESSURE_READER2);
InputReader readers[] = {reader1, reader2};
MemoryHelper memory1;
MemoryHelper memory2;
PressureManipulator manipulators[] = {PressureManipulator(RELAY_INCREASE_FRONT, RELAY_DECREASE_FRONT, reader1), PressureManipulator(RELAY_INCREASE_REAR, RELAY_DECREASE_REAR, reader2)};


int odczyty[2];
char _buffer1[5];
char _buffer2[5];
int odczyt[2];

//Zmienne nextion z danymi funkcjami
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
  //Inicjalizacja funkcji nextion
  nexLoop(nex_listen_list);  
  
  odczyty[0] = round(reader1.ReadAverageInput() / 64.0);
  odczyty[1] = round(reader2.ReadAverageInput() / 64.0);
 
  if(odczyty[0] != odczyt[0]){ 
    odczyt[0] = odczyty[0];
    MapToVolts(odczyty[0], _buffer1);
    t1.setText(_buffer1);
   }
  else if (odczyty[1] != odczyt[1])
   {
    odczyt[1] = odczyty[1];
    MapToVolts(odczyty[1], _buffer2);
    t2.setText(_buffer2);
   }
   
   delay(25);
}

void MapToVolts(int odczyt, char* _buffer) {
  float value = odczyt  * (5.0 / 16.0);
  //Funkcja wrzucająca float do tablicy wyników
  //value to float, następnie jest długość znaków, pozniej ile znaków po przecinku, a pozniej tablica gdzie ma być wrzucone
  dtostrf(value, 2, 1, _buffer);
}


//NEXTION BINDS
//Memory
void SaveValues1_PushCallback(void*prt)
{
  int odczyty[NumberOfPressureSensors];
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  memory1.SaveToStorage(odczyty, manipulators);
  Serial.print("Zapisz odczyt 1");
}

void SaveValues2_PushCallback(void*prt)
{
  int odczyty[NumberOfPressureSensors];
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  memory2.SaveToStorage(odczyty, manipulators);
   Serial.print("Zapisz odczyt 2");
}

void RestoreValues1_PushCallback(void*prt)
{
  memory1.RestoreFromStorageToPressureManipulators(manipulators);
   Serial.print("Przywroc memory 1");
}

void RestoreValues2_PushCallback(void*prt)
{
  memory2.RestoreFromStorageToPressureManipulators(manipulators);
  Serial.print("Przywroc memory 2");
}

//Manual manipulations
void IncreaseFront_PushCallback(void*prt)
{
  manipulators[0].IncreaseValue();
  Serial.print("Podnies przod");
}

void DecreaseFront_PushCallback(void*prt)
{
  manipulators[0].DecreaseValue();
  Serial.print("Obniz tyl");
}

void IncreaseRear_PushCallback(void*prt)
{
  manipulators[1].IncreaseValue();
   Serial.print("Podnies tyl");
}

void DecreaseRear_PushCallback(void*prt)
{
  manipulators[1].DecreaseValue();
  Serial.print("Obniz tyl");
}

void IncreaseCar_PushCallback(void*prt)
{
  manipulators[0].IncreaseValue();
  manipulators[1].IncreaseValue();
   Serial.print("Podnies auto");
}

void DecreaseCar_PushCallback(void*prt)
{
  manipulators[1].DecreaseValue();
  manipulators[0].DecreaseValue();
  Serial.print("Obniz auto");
}

void Manipulators_PopCallback(void*prt) {
  manipulators[0].StopManipulating();
  manipulators[1].StopManipulating();
  Serial.print("Manipulators");
}
