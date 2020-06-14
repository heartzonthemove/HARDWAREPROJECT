int PIN_BLUE = 3;                   // blue color at pin 3
int PIN_GREEN = 5;                  // green color at pin 5
int PIN_RED = 6;                    // red color at pin 6

void setup() 
{
    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);
}
void loop() 
{
    digitalWrite(PIN_RED, 1);
    delay(1000);
    digitalWrite(PIN_RED, 0);
    digitalWrite(PIN_GREEN, 1);
    delay(1000);
    digitalWrite(PIN_GREEN, 0);
    digitalWrite(PIN_BLUE, 1);
    delay(1000);
    digitalWrite(PIN_BLUE, 0);
}
