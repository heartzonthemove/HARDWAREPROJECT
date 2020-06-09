#include "pitches.h"

int melody[] = {
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
    NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
    NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, 
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, 
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
    NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_F4,
    NOTE_G4, 0, NOTE_G4, NOTE_D5,
    NOTE_C5, 0, NOTE_AS4, 0,
    NOTE_A4, 0, NOTE_A4, NOTE_A4,
    NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4, 0, NOTE_G4, NOTE_D5,
    NOTE_C5, 0, NOTE_AS4, 0,
    NOTE_A4, 0, NOTE_A4, NOTE_A4,
    NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5
};

int noteDurations[] = {
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
};

void setup() 
{
        for (int thisNote = 0; thisNote < 112; thisNote++)
        {
            int noteDuration = 750 / noteDurations[thisNote];
            tone(8, melody[thisNote], noteDuration);
            int pauseBetweenNotes = noteDuration * 1.30;
            delay(pauseBetweenNotes);
            noTone(8);
        }
}

void loop() 
{

}