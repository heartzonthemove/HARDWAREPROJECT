#include "TM1637.h"
const int DIO = 16;                 // setup 7-segment to A2
const int CLK = 17;                 // setup 7-segment to A3
TM1637 sevenSegment(CLK, DIO);      // 7-segment 

int number = 0;

void setup() 
{
  sevenSegment.init();
  sevenSegment.set(7);              // BRIGHT 0-7;
  sevenSegment.displayNum(10);
  delay(500);
  sevenSegment.displayNum(1234);
  delay(500);
  sevenSegment.displayStr("OFF");
  delay(500);
}

void loop() 
{
  sevenSegment.displayNum(number++);
  delay(100);
}