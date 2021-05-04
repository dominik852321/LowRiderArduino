#include "Configuration.h"
int NumberOfPressureSensors=2;
//HIGH != 0
//LOW = 0.
int RelayIncrease = 0;
int RelayDecrease = 1;

//NEXTION BUTTONS
NexText t1 = NexText (1, 7, "t0");
NexText t2 = NexText (1, 8, "t1");

NexButton save_1 = NexButton (3, 6, "b2");
NexButton save_2 = NexButton (3, 9, "b3");
NexButton save_3 = NexButton (3, 10, "b4");
NexButton save_4 = NexButton (3, 11, "b5");

NexDSButton mem_1 = NexDSButton (2, 3, "bt0");
NexDSButton mem_2 = NexDSButton (2, 4, "bt1");
NexDSButton mem_3 = NexDSButton (2, 5, "bt2");
NexDSButton mem_4 = NexDSButton (2, 6, "bt3");



NexButton inc_front = NexButton (1, 3, "b2");
NexButton inc_rear = NexButton (1, 4, "b3");  
NexButton inc_car = NexButton (1, 10, "b6");  
NexButton dec_front = NexButton (1, 5, "b4");
NexButton dec_rear = NexButton (1, 6, "b5");
NexButton dec_car = NexButton (1, 11, "b7");
