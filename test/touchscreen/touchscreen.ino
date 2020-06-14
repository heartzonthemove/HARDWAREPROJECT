#include "Nextion.h"
SoftwareSerial HMISerial(10, 11);

NexText t0 = NexText(0, 2, "t0");
NexSlider h0 = NexSlider(0, 1, "h0");
NexGauge z0  = NexGauge(0, 3, "z0");
NexDSButton bt0 = NexDSButton(0, 5, "bt0");


NexTouch *nex_listen_list[] = {&h0, &bt0, NULL};

void bt0PopCallback(void *ptr)
{
  uint32_t dual_state;
  NexDSButton *btn = (NexDSButton *)ptr;
  dbSerialPrintln("b0PopCallback");
  dbSerialPrint("ptr=");
  dbSerialPrintln((uint32_t)ptr);
  bt0.getValue(&dual_state);
  
  if (dual_state)               
  {
    digitalWrite(13, HIGH);           // if my dual state buton is pressed
  }
  else
  {
    digitalWrite(13, LOW);            // if not
  }

}
void h0PopCallback(void *ptr)
{
  int numberx = 0;
  int gosterge = 0;
  uint32_t number = 0;
  char temp[10] = {0};
  dbSerialPrintln("h0PopCallback");
  h0.getValue(&number);
  utoa(number, temp, 10);
  t0.setText(temp);
  numberx = number;
  gosterge = map(numberx, 0, 100, 0, 180);
  z0.setValue(gosterge);
}

void setup(void)
{
  pinMode(13, OUTPUT);
  nexInit();
  h0.attachPop(h0PopCallback);
  bt0.attachPop(bt0PopCallback, &bt0);
  dbSerialPrintln("setup done");
}

void loop(void)
{
  nexLoop(nex_listen_list);
}