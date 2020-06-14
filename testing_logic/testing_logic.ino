void setup()
{
    pinMode(2, INPUT);
    pinMode(8, OUTPUT);
}
int count = 0;
int soundTest = 1;

void loop()
{
    if (soundTest = 1)
    {
        tone(8,200,3000);
        if (digitalRead(2)==1)
        { 
            tone(8,0,5000);
        }
    }
}