#include "Configuration.h"
int NumberOfPressureSensors=2;
//HIGH != 0
//LOW = 0.
int RelayIncrease = 0;
int RelayDecrease = 1;

//Nextion values on top 
NexText t0 = NexText (1, 7, "t0");
NexText t1 = NexText (1, 8, "t1");

//Nextion progress bar
NexProgressBar j0 = NexProgressBar (2, 9, "j0");

//Nextion values on save memory
NexText t2 = NexText (3, 16, "t2");
NexText t3 = NexText (3, 17, "t3");
NexText t4 = NexText (3, 10, "t4");
NexText t5 = NexText (3, 11, "t5");
NexText t6 = NexText (3, 12, "t6");
NexText t7 = NexText (3, 13, "t7");
NexText t8 = NexText (3, 14, "t8");
NexText t9 = NexText (3, 15, "t9");

//Buttons to save value
NexButton save_1 = NexButton (3, 6, "b2");
NexButton save_2 = NexButton (3, 7, "b3");
NexButton save_3 = NexButton (3, 8, "b4");
NexButton save_4 = NexButton (3, 9, "b5");

//Buttons to restore value
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
