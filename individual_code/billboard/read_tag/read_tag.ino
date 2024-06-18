/*
 * Initial Author: ryand1011 (https://github.com/ryand1011)
 *
 * Reads data written by a program such as "rfid_write_personal_data.ino"
 *
 * See: https://github.com/miguelbalboa/rfid/tree/master/examples/rfid_write_personal_data
 *
 * Uses MIFARE RFID card using RFID-RC522 reader
 * Uses MFRC522 - Library
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
*/

#include <SPI.h>
#include <MFRC522.h>

#define RFID_SDA_PIN 10
#define RFID_RST_PIN 9


char RFID_value = 'n';

MFRC522 mfrc522(RFID_SDA_PIN, RFID_RST_PIN);  // Create MFRC522 instance.



void setup() {
  Serial.begin(9600);         // Initialize serial communications with the PC
  SPI.begin();                // Init SPI bus
  mfrc522.PCD_Init();         // Init MFRC522
}



void loop() {
  RFID_reading();
  Serial.println(RFID_value);
}


void RFID_reading(){
   if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      String content = "";
      byte letter;
      for (byte i = 0; i < mfrc522.uid.size; i++) {
         Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      content.toUpperCase();
      if (content.substring(1) == "E3 E7 49 9F") {  // First UID: E3 E7 49 9F
        RFID_value = '1';
      } else if (content.substring(1) == "53 D0 D9 9E") {  // Second UID: 53 D0 D9 9E
        RFID_value = '2';
      } else if (content.substring(1) == "E3 18 4A 9F") {  // Third UID: E3 18 4A 9F
        RFID_value = '3';
      } else {
        RFID_value = 'n';
      }
    } else {
      RFID_value = 'n';
    }
}


