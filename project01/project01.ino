//define buzzer note section 
#define NOTE_B0  31         // te sound
#define NOTE_C1  33         // do sound
#define NOTE_CS1 35
#define NOTE_D1  37         // re sound
#define NOTE_DS1 39
#define NOTE_E1  41         // me sound
#define NOTE_F1  44         // fa sound
#define NOTE_FS1 46
#define NOTE_G1  49         // sol sound
#define NOTE_GS1 52
#define NOTE_A1  55         // ra sound
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

//7 segment
#include "TM1637.h"
const int DIO = 16;                 // setup 7-segment to A2
const int CLK = 17;                 // setup 7-segment to A3
TM1637 sevenSegment(CLK, DIO);      // 7-segment 
 
//define input
int Button = 2;                     // button at pin 2
int BuzzerPin = 3;                  // buzzer at pin 8

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
    Serial.begin(9600);
    pinMode(Button, INPUT);             // make the button to be the input
    digitalWrite(Button, HIGH);         // make the button state high
    pinMode(BuzzerPin, OUTPUT);         // make the buzzer to be the output

    //7-segment showing
    sevenSegment.init();                // wake the 7-segment
    sevenSegment.set(7);                // BRIGHT 0-7;
    sevenSegment.displayNum(1234);      // showing number
    delay(500);
    sevenSegment.displayNum(5678);
    delay(500);
    sevenSegment.displayStr("OPEN");     // showing word
    delay(500);
    sevenSegment.displayStr("OFF");
    delay(500);
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

    //define button state for holding guide
    //int button1State;               // variables to hold the pushbutton states
    //int count;                      // variables to count the time button that is held
    //button1State = digitalRead(Button);
    //if (button1State == HIGH)
    //{
    //    count = count + 1;
    //}

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

//HSB to RGB colour cases
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