int potPin = 1;                         // select the input pin for the potentiometer
int blue = 3;                           // blue color at pin 3
int green = 5;                          // green color at pin 5
int red = 6;                            // red color at pin 6
int val = 0;                            // variable to store the value coming from the potentiometer

void setup() 
{
  pinMode(red, OUTPUT);                 // make the red light to be the output
  pinMode(blue, OUTPUT);                // make the blue light to be the output
  pinMode(green, OUTPUT);               // make the green light to be the output
}

void loop() 
{
    val = analogRead(potPin);           // read the value from the potentiometer
    digitalWrite(red, HIGH);            // turn the red light on
    digitalWrite(blue, HIGH);           // turn the red light on
    digitalWrite(green, HIGH);          // turn the red light on
    delay(val);                         // wip-wup from the potentiometer
    digitalWrite(red, LOW);             // turn the red light off
    digitalWrite(blue, LOW);            // turn the red light on
    digitalWrite(green, LOW);           // turn the red light on
    delay(val);                         // wip-wup from the potentiometer
}
 