#include "MemoryHelper.h"
#include "InputReader.h"
#include "Configuration.h"
#include "PressureManipulator.h"
#include "Nextion.h"



InputReader reader1(PRESSURE_READER1);
InputReader reader2(PRESSURE_READER2);
InputReader reader3(PRESSURE_READER3);

InputReader readers[] = {reader1, reader2, reader3};
MemoryHelper memory1;
MemoryHelper memory2;
MemoryHelper memory3;
MemoryHelper memory4;
PressureManipulator manipulators[] = {PressureManipulator(RELAY_INCREASE_FRONT, RELAY_DECREASE_FRONT, reader1), PressureManipulator(RELAY_INCREASE_REAR, RELAY_DECREASE_REAR, reader2)};


int odczyty[3];
int odczyt[3];

bool displayOn = false;

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
  displayOn = nexInit();
  Serial.begin(9600);
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
      
      //Sprawdzenie polaczenia z wyswietlaczem
      if(!displayOn){
        bool  tryCon = nexInit();
        if(tryCon){
             delay(5000);
             SetAllTxt();
             displayOn = true;
          }
        else {
            displayOn = false;
          }
      }  

      odczyty[0] = reader1.ReadAverageInput();
      odczyty[1] = reader2.ReadAverageInput();
      odczyty[2] = reader3.ReadAverageInput();
    
      if(odczyty[0] != odczyt[0]){ 
        odczyt[0] = odczyty[0];
        setT0();
      }
      else if(odczyty[1] != odczyt[1]){
        odczyt[1] = odczyty[1];
        setT1();
      } 
     else if(odczyty[2] != odczyt[2]){
        odczyt[2] = odczyty[2];
        setValue();
      }

      //Zauwazylem ze po inicjalizacji danej strony jej pamiec juz zostaje
      //Przy zmianie strony refreshuja sie dane
      delay(25);   
}

//Mapuj odczyt na volty
void setT0() {
  char bufer[3];
  float value = odczyt[0]  * (5.0 / 16.0);
  //value to float, następnie jest długość znaków, pozniej ile znaków po przecinku, a pozniej tablica gdzie ma być wrzucone
  dtostrf(value, 3, 2, bufer);
  t0.setText(bufer);
}

void setT1(){
   char bufer[3];
   float value = odczyt[1]  * (5.0 / 16.0);
   dtostrf(value, 3, 2, bufer);
   t1.setText(bufer);
  }

void setValue() {
   j0.setValue(odczyt[2] * 6.25);
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
  SetAllTxt();
}

void SaveValues2_PushCallback(void*prt)
{
  Serial.println("Zapisz odczyt 2");
  int odczyty[NumberOfPressureSensors];
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  memory2.SaveToStorage(odczyty, manipulators);
  SetAllTxt();
}

void SaveValues3_PushCallback(void*prt)
{
  Serial.println("Zapisz odczyt 3");
  int odczyty[NumberOfPressureSensors];
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  memory3.SaveToStorage(odczyty, manipulators);
  SetAllTxt();
}

void SaveValues4_PushCallback(void*prt)
{
  Serial.println("Zapisz odczyt 4");
  int odczyty[NumberOfPressureSensors];
  odczyty[0] = reader1.ReadAverageInput();
  odczyty[1] = reader2.ReadAverageInput();
  memory4.SaveToStorage(odczyty, manipulators);
  SetAllTxt();
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

void SetAllTxt(){
  char b[5];
  
  memory1.RestoreFromStorageValue(1).toCharArray(b,5);
  t2.setText(b);
  t2.setText(b);
  
  
  memory1.RestoreFromStorageValue(2).toCharArray(b,5);
  t3.setText(b);

  memory2.RestoreFromStorageValue(1).toCharArray(b,5);
  t4.setText(b);
  
  memory2.RestoreFromStorageValue(2).toCharArray(b,5);
  t5.setText(b);
  
  memory3.RestoreFromStorageValue(1).toCharArray(b,5);
  t6.setText(b);

  memory3.RestoreFromStorageValue(2).toCharArray(b,5);
  t7.setText(b);

  memory4.RestoreFromStorageValue(1).toCharArray(b,5);
  t8.setText(b);
  
  memory4.RestoreFromStorageValue(2).toCharArray(b,5);
  t9.setText(b);
}
