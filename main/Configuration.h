#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include "Nextion.h"

#define PRESSURE_READER1 A0
#define PRESSURE_READER2 A1

#define RELAY_INCREASE_FRONT 4
#define RELAY_DECREASE_FRONT 5
#define RELAY_INCREASE_REAR 6
#define RELAY_DECREASE_REAR 7

extern int NumberOfPressureSensors;
//HIGH != 0
//LOW = 0.
extern int RelayIncrease;
extern int RelayDecrease;
//NEXTION BUTTONS
extern NexText t1;
extern NexText t2;

//Save values
extern NexButton save_1;
extern NexButton save_2;
extern NexButton save_3;
extern NexButton save_4;

//Restore values
extern NexDSButton mem_1;
extern NexDSButton mem_2;
extern NexDSButton mem_3;
extern NexDSButton mem_4;

//Change pressure
extern NexButton inc_front;
extern NexButton inc_rear;  
extern NexButton inc_car;  
extern NexButton dec_front;
extern NexButton dec_rear;
extern NexButton dec_car;
#endif
