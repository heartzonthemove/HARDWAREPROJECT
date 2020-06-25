//buzzer
#include "pitches.h"                                            // buzzer library
const int Buzzer = 8;                                           // buzzer at pin 8
int melody1[] = 
{
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations1[] = 
{
  4, 8, 8, 4, 4, 4, 4, 4
};

int melody2[] = 
{
  NOTE_C4, NOTE_B3
};
int noteDurations2[] = 
{
  4, 4
};

//potentiometer
int val = 0;                                                    // variable to store the value coming from the potentiometer
int potPin = 1;                                                 // select the input pin for the potentiometer

//card scanner
#include <SPI.h>                                                // card scanner library
#include <MFRC522.h>                                            // card scanner library
#define RST_PIN 9                                               // card scanner rst at pin 9
#define SS_PIN 10                                               // card scanner ss at pin 10
MFRC522 mfrc522(SS_PIN, RST_PIN);                               // Create MFRC522 instance

//7 segment
#include "TM1637.h"                                             // 7-segment library
const int DIO = 16;                                             // setup 7-segment to A2
const int CLK = 17;                                             // setup 7-segment to A3
TM1637 sevenSegment(CLK, DIO);                                  // 7-segment 
 
//define button
const int Button = 2;                                           // button at pin 2
long lasttimestatechange = 0;
String state = "ON";

//define colors
const int PIN_BLUE = 3;                                         // blue color at pin 3
const int PIN_GREEN = 5;                                        // green color at pin 5
const int PIN_RED = 6;                                          // red color at pin 6
int counter = 0;                                                // counter color
int numColors = 255;                                            // number of all color 0-255
int animationDelay = 10;                                        // RGB changes to the next color like it wip-wup

void setColor (unsigned char red, unsigned char green, unsigned char blue)
{       
    analogWrite(PIN_RED, red);
    analogWrite(PIN_GREEN, green);
    analogWrite(PIN_BLUE, blue);
}

void setup() 
{
    //beginner setup
    Serial.begin(9600);                                         // show in the monitor screen
    pinMode(Button, INPUT);                                     // make the button to be the input
    
    //card reader setup
    SPI.begin();                                                // Initiate  SPI bus 
    mfrc522.PCD_Init();                                         // Initiate MFRC522
    Serial.println("Waiting for the card...");
    Serial.println();

    //7-segment setup
    sevenSegment.init();                                        // wake the 7-segment
    sevenSegment.set(7);                                        // BRIGHT 0-7;
    sevenSegment.displayNum(1234);                              // showing number
    delay(700);                                                 // waiting for 0.7 sec
    sevenSegment.displayStr("LINK");                            // showing word

    //buzzer setup
    pinMode(Buzzer, OUTPUT);                                    // make the buzzer to be the output
    for (int thisNote = 0; thisNote < 8; thisNote++) 
    {
        int noteDuration1 = 1000 / noteDurations1[thisNote];
        tone(8, melody1[thisNote], noteDuration1);
        int pauseBetweenNotes1 = noteDuration1 * 1.30;
        delay(pauseBetweenNotes1);
        noTone(8);
    }
}

void loop()
{
    //rgb color
    float colorNumber = counter > numColors ? counter - numColors : counter;
    float saturation = 1;                                       // Between 0 and 1 (0 = gray, 1 = full color)
    float brightness = .05;                                     // Between 0 and 1 (0 = dark, 1 is full brightness)
    float hue = (colorNumber / float(numColors)) * 360;         // Number between 0 and 360
    long color = HSBtoRGB(hue, saturation, brightness);
    int red = color >> 16 & 255;                                // to get red 
    int green = color >> 8 & 255;                               // to get green
    int blue = color & 255;                                     // to get blue
    
    setColor(red, green, blue);
    counter = (counter + 1) % (numColors * 2);                  // method to showing the color
    delay(animationDelay);

    //card reader
    if ( ! mfrc522.PICC_IsNewCardPresent())                     // Look for new cards
    {
        return;
    }
    if ( ! mfrc522.PICC_ReadCardSerial())                       // Select one of the cards
    {
        return;
    }
    Serial.print("UID tag :");                                  //Show UID on the serial monitor
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == "FA 2F 2E 58" || "22 BC 9B 34")
    {
        Serial.println("Authorized access");
        Serial.println();
        delay(2000);
    }
    else   
    {
        Serial.println("Access denied");
        Serial.println();
        delay(2000);
    }
}

//HSB to RGB colour Equation
long HSBtoRGB(float _hue, float _sat, float _brightness) 
{
    float red = 0.0;                                            // set red cost to 0.0
    float green = 0.0;                                          // set green cost to 0.0
    float blue = 0.0;                                           // set blue cost to 0.0

    if (_sat == 0.0)                
    {
        red = _brightness;                                      // set as the same brightness
        green = _brightness;                                    // set as the same brightness
        blue = _brightness;                                     // set as the same brightness
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

    long ired = red * 255.0;                                    // cost x number of the color
    long igreen = green * 255.0;                                // cost x number of the color
    long iblue = blue * 255.0;                                  // cost x number of the color

    return long((ired << 16) | (igreen << 8) | (iblue));
}

//=============================================================================
//                            E N D  O F  C O D E
//=============================================================================