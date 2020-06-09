//buzzer
#include "pitches.h"

//card scanner
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//7 segment
#include "TM1637.h"
const int DIO = 16;                 // setup 7-segment to A2
const int CLK = 17;                 // setup 7-segment to A3
TM1637 sevenSegment(CLK, DIO);      // 7-segment 
 
//define input
int Button = 2;                     // button at pin 2
int Buzzer = 8;                  // buzzer at pin 8

//define colour
int PIN_BLUE = 3;                   // blue color at pin 3
int PIN_GREEN = 5;                  // green color at pin 5
int PIN_RED = 6;                    // red color at pin 6
int counter = 0;
int numColors = 255;
int animationDelay = 10;            // RGB changes to the next color like it wip-wup

//define state
int buttonState;
int programState = 0;
long buttonMillis = 0;
const long intervalButton = 3000;

void setColor (unsigned char red, unsigned char green, unsigned char blue)
{       
    analogWrite(PIN_RED, red);
    analogWrite(PIN_GREEN, green);
    analogWrite(PIN_BLUE, blue);
}

void setup() 
{
    Serial.begin(9600);                 // show in the monitor screen
    pinMode(Button, INPUT);             // make the button to be the input
    digitalWrite(Button, HIGH);         // make the button state high
    pinMode(Buzzer, OUTPUT);            // make the buzzer to be the output
    SPI.begin();                        // Initiate  SPI bus
    mfrc522.PCD_Init();                 // Initiate MFRC522

    //7-segment showing
    sevenSegment.init();                // wake the 7-segment
    sevenSegment.set(7);                // BRIGHT 0-7;
    sevenSegment.displayNum(1234);      // showing number
    delay(700);
    sevenSegment.displayStr("LINK");     // showing word
}

void loop()
{
    //defined state LOW & HIGH
    unsigned long currentMillis = millis();
    buttonState = digitalRead(Button);
    if(buttonState == LOW && programState == 0)
    {
        buttonMillis = currentMillis;
        programState = 1;
    }
    else if(programState == 1 && buttonState == HIGH)
    {
        programState = 0;                //reset
    }
    if(currentMillis - buttonMillis > intervalButton && programState == 1) 
    {
        programState = 2;
    }

    if(programState == 2) 
    {
        programState = 0;
    }

    float colorNumber = counter > numColors ? counter - numColors: counter;
    float saturation = 1;                                   // Between 0 and 1 (0 = gray, 1 = full color)
    float brightness = .05;                                 // Between 0 and 1 (0 = dark, 1 is full brightness)
    float hue = (colorNumber / float(numColors)) * 360;     // Number between 0 and 360
    long color = HSBtoRGB(hue, saturation, brightness);
    int red = color >> 16 & 255;                            // to get red 
    int green = color >> 8 & 255;                           // to get green
    int blue = color & 255;                                 // to get blue

    setColor(red, green, blue);

    counter = (counter + 1) % (numColors * 2);              // method to showing the color 
    //another mehod >>> counter = (counter + 1) % (numColors);   **adjust it to be faster in changing color**

    delay(animationDelay);
}

//HSB to RGB colour Equation
long HSBtoRGB(float _hue, float _sat, float _brightness) 
{
    float red = 0.0;                // set red cost to 0.0
    float green = 0.0;              // set green cost to 0.0
    float blue = 0.0;               // set blue cost to 0.0
    if (_sat == 0.0)                
        {
        red = _brightness;          // set as the same brightness
        green = _brightness;        // set as the same brightness
        blue = _brightness;         // set as the same brightness
        } 
    else
        {
        if (_hue == 360.0) 
        {
            _hue = 0;
        }

        int slice = _hue / 60.0;
        float hue_frac = (_hue / 60.0) - slice;
        float aa = _brightness * (1.0 - _sat);
        float bb = _brightness * (1.0 - _sat * hue_frac);
        float cc = _brightness * (1.0 - _sat * (1.0 - hue_frac));
        switch(slice) 
        {
            case 0:
               red = _brightness;
               green = cc;
               blue = aa;
               break;
            case 1:
               red = bb;
               green = _brightness;
               blue = aa;
               break;
            case 2:
               red = aa;
               green = _brightness;
               blue = cc;
               break;
            case 3:
               red = aa;
               green = bb;
               blue = _brightness;
               break;
            case 4:
               red = cc;
               green = aa;
               blue = _brightness;
               break;
            case 5:
               red = _brightness;
               green = aa;
               blue = bb;
               break;
            default:
               red = 0.0;
               green = 0.0;
               blue = 0.0;
            break;
        }
    }
    long ired = red * 255.0;                // cost x number of the colour
    long igreen = green * 255.0;            // cost x number of the colour
    long iblue = blue * 255.0;              // cost x number of the colour

    return long((ired << 16) | (igreen << 8) | (iblue));
}