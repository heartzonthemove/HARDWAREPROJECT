int button = 7;                 // button at pin 7

void setup() 
{
    Serial.begin(9600);
    pinMode(button, INPUT);
}

void loop() 
{
    if (digitalRead(button) == 0)
    {
        Serial.println("BUTTON OFF STATE");
    }

    else 
    {
        Serial.println("BUTTON ON STATE");
    }
}