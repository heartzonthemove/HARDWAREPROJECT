int pin = A5;
int val = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(pin,INPUT);
}

void loop()
{
    val = digitalRead(pin);
    if (val == 0)
    {
        Serial.print("page 0");     //show "page 0" in the serial monitor
        Serial.write(0xff);         //record what is see on the display.
        Serial.write(0xff);         //record what is see on the display.
        Serial.write(0xff);         //record what is see on the display.
    }
    else
    {
        Serial.print("page 1");     //show "page 1" in the serial monitor
        Serial.write(0xff);         //record what is see on the display.
        Serial.write(0xff);         //record what is see on the display.
        Serial.write(0xff);         //record what is see on the display.
    }
}