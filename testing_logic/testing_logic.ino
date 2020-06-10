const int Button = 2;

byte CurrentSwitch, lastSwitch;
unsigned long timeStart;
bool CheckingSwitch;   

void setup()
{
    pinMode(Button, INPUT);
    lastSwitch = digitalRead(Button);
    CheckingSwitch = false;
}

void loop()
{
    CurrentSwitch = digitalRead(Button);

    if(CurrentSwitch != lastSwitch)
    {
        if(CurrentSwitch == LOW)
        {
            timeStart = millis();
            CheckingSwitch = true;
        }

        else
        {
            CheckingSwitch = false; 
        }
       
        lastSwitch = CurrentSwitch;
    }

    if( CheckingSwitch )
    {
        if( (millis() - timeStart ) >= 5000 )
        {
           
        }
    }
   
}