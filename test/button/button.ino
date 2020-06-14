int button = 2;                 // button at pin 2
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
        digitalWrite(red, 0);                       // red light power on
        digitalWrite(green, 0);                     // green light power on
        digitalWrite(blue, 0);                      // blue light power on
    }
    else 
    {
        digitalWrite(red, 1);                       // red light power on
        digitalWrite(green, 1);                     // green light power on
        digitalWrite(blue, 1);
    }
}