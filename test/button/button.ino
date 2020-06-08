int count = 0;
int button = 2;
int blue = 3;                   // blue color at pin 3
int green = 5;                  // green color at pin 5
int red = 6;                    // red color at pin 6

void setup() 
{
  pinMode(button, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() 
{
    if (digitalRead(button) == 0) 
    {
        switch(count) 
        {
        case 1:
        digitalWrite(red, 1);
        digitalWrite(green, 1);
        digitalWrite(blue, 1);
        break;
        case 2:
        digitalWrite(red, 1);
        digitalWrite(green, 1);
        digitalWrite(blue, 1);
        delay(100);
        digitalWrite(red, 0);
        digitalWrite(green, 0);
        digitalWrite(blue, 0);
        delay(100);
        break;
        case 3:
        digitalWrite(red, 0);
        digitalWrite(green, 0);
        digitalWrite(blue, 0);
        break;
        case 4:
        count = 1;
        break;
        }
    } 
    else 
    {
        switch(count) 
        {
        case 1:
        digitalWrite(red, 1);
        digitalWrite(green, 1);
        digitalWrite(blue, 1);
        break;
        case 2:
        digitalWrite(red, 1);
        digitalWrite(green, 1);
        digitalWrite(blue, 1);
        delay(100);
        digitalWrite(red, 0);
        digitalWrite(green, 0);
        digitalWrite(blue, 0);
        delay(100);
        break;
        case 3:
        digitalWrite(red, 0);
        digitalWrite(green, 0);
        digitalWrite(blue, 0);
        break;
        case 4:
        count = 1;
        break;
        }
        if (digitalRead(button) == 0) 
        {
        count++;
        }
    }
}