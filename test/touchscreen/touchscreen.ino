#include <Nextion.h>
int val = 0;

void setup() 
{
    Serial.begin(9600);
    pinMode(pin, INPUT);
}
void loop() 
{
    Serial.print("page 1");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    delay(2000);

    Serial.print("page 0");
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    delay(2000);
}