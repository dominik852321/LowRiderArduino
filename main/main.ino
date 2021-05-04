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
MemoryHelper memory3;
MemoryHelper memory4;
PressureManipulator manipulators[] = {PressureManipulator(RELAY_INCREASE_FRONT, RELAY_DECREASE_FRONT, reader1), PressureManipulator(RELAY_INCREASE_REAR, RELAY_DECREASE_REAR, reader2)};


int odczyty[2];
char _buffer1[5];
char _buffer2[5];
int odczyt[2];

//Zmienne nextion z danymi funkcjami
NexTouch *nex_listen_list[] = {
  &save_1,
  &save_2,
  &save_3,
  &save_4,
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
  Serial.begin(9600);
  nexInit();
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  reader1.Init();
  reader2.Init();
  
  memory1.Init();
  memory2.Init();
  memory3.Init();
  memory4.Init();
  

  manipulators[0].Init();
  manipulators[1].Init();
  
  //Domyslnie przy właczaniu arduino ustaw na memory 1
  memory1.RestoreFromStorageToPressureManipulators(manipulators);

  //Zapisz wartosci
  save_1.attachPop(SaveValues1_PushCallback, &save_1);
  save_2.attachPop(SaveValues2_PushCallback, &save_2);
  save_3.attachPop(SaveValues3_PushCallback, &save_3);
  save_4.attachPop(SaveValues4_PushCallback, &save_4);
  
  //Przywroc wartosci
  mem_1.attachPop(RestoreValues1_PushCallback, &mem_1);
  mem_2.attachPop(RestoreValues2_PushCallback, &mem_2); 
  mem_3.attachPop(RestoreValues3_PushCallback, &mem_3);
  mem_4.attachPop(RestoreValues4_PushCallback, &mem_4);
 

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
  
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
 
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

//Mapuj odczyt na volty
void MapToVolts(int odczyt, char* _buffer) {
  float value = odczyt  * (5.0 / 16.0);
  //Funkcja wrzucająca float do tablicy wyników
  //value to float, następnie jest długość znaków, pozniej ile znaków po przecinku, a pozniej tablica gdzie ma być wrzucone
  dtostrf(value, 2, 1, _buffer);
}


void RestoreValues1_PushCallback(void*prt)
{
  uint32_t m1 = 0;
  mem_1.getValue(&m1);
  
  if(m1==1)
  {
    Serial.println("\n\nPrzywroc memory 1\n");
    memory1.RestoreFromStorageToPressureManipulators(manipulators); 
  }
}

void RestoreValues2_PushCallback(void*prt)
{ 
   uint32_t m2 = 0;
   mem_2.getValue(&m2);
  
   if(m2==1)
   {
    Serial.println("\n\nPrzywroc memory 2\n");
    memory2.RestoreFromStorageToPressureManipulators(manipulators);
   }
}

void RestoreValues3_PushCallback(void*prt)
{
  uint32_t m3 = 0;
  mem_3.getValue(&m3);
  
  if(m3==1)
  {
    Serial.println("\n\nPrzywroc memory 3\n");
    memory3.RestoreFromStorageToPressureManipulators(manipulators); 
  }
}

void RestoreValues4_PushCallback(void*prt)
{
  uint32_t m4 = 0;
  mem_4.getValue(&m4);
  
  if(m4==1)
  {
    Serial.println("\n\nPrzywroc memory 4\n");
    memory4.RestoreFromStorageToPressureManipulators(manipulators); 
  }
}

//Zapisz wartosci do danych memory
void SaveValues1_PushCallback(void*prt)
{
  Serial.println("Zapisz odczyt 1");
  int odczyty[NumberOfPressureSensors];
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  memory1.SaveToStorage(odczyty, manipulators);
}

void SaveValues2_PushCallback(void*prt)
{
  Serial.println("Zapisz odczyt 2");
  int odczyty[NumberOfPressureSensors];
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  memory2.SaveToStorage(odczyty, manipulators);
}

void SaveValues3_PushCallback(void*prt)
{
  Serial.println("Zapisz odczyt 3");
  int odczyty[NumberOfPressureSensors];
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  memory3.SaveToStorage(odczyty, manipulators);
}

void SaveValues4_PushCallback(void*prt)
{
  Serial.println("Zapisz odczyt 4");
  int odczyty[NumberOfPressureSensors];
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  memory4.SaveToStorage(odczyty, manipulators);
}

//Manual manipulations
void IncreaseFront_PushCallback(void*prt)
{
  manipulators[0].IncreaseValue();
  Serial.println("Podnies przod");
}

void DecreaseFront_PushCallback(void*prt)
{
  manipulators[0].DecreaseValue();
  Serial.println("Obniz tyl");
}

void IncreaseRear_PushCallback(void*prt)
{
  manipulators[1].IncreaseValue();
   Serial.println("Podnies tyl");
}

void DecreaseRear_PushCallback(void*prt)
{
  manipulators[1].DecreaseValue();
  Serial.println("Obniz tyl");
}

void IncreaseCar_PushCallback(void*prt)
{
  manipulators[0].IncreaseValue();
  manipulators[1].IncreaseValue();
   Serial.println("Podnies auto");
}

void DecreaseCar_PushCallback(void*prt)
{
  manipulators[1].DecreaseValue();
  manipulators[0].DecreaseValue();
  Serial.println("Obniz auto");
}

void Manipulators_PopCallback(void*prt) {
  manipulators[0].StopManipulating();
  manipulators[1].StopManipulating();
  Serial.println("Manipulators");
}
