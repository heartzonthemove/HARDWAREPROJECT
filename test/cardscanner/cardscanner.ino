#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup() 
{
    Serial.begin(9600);   // Initiate a serial communication
    SPI.begin();      // Initiate  SPI bus
    mfrc522.PCD_Init();   // Initiate MFRC522
    Serial.println("Approximate your card to the reader...");
    Serial.println();

}
void loop() 
{
    if ( ! mfrc522.PICC_IsNewCardPresent())     // Look for new cards
    {
        return;
    }
    if ( ! mfrc522.PICC_ReadCardSerial())       // Select one of the cards
    {
        return;
    }
    Serial.print("UID tag :");                  //Show UID on serial monitor
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
        delay(3000);
    }
    else   
    {
        Serial.println(" Access denied");
        delay(3000);
    }
} 