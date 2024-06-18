/*
 * Uses MIFARE RFID card using RFID-RC522 reader
 * Uses MFRC522 - Library
 * --------------------------------------
 *             Reader/PCD   Uno/101       
 * Signal      Pin          Pin          
 * --------------------------------------
 * RST/Reset   RST          9            
 * SPI SS      SDA(SS)      10           
 * SPI MOSI    MOSI         11 / ICSP-4   
 * SPI MISO    MISO         12 / ICSP-1   
 * SPI SCK     SCK          13 / ICSP-3   
 */

#include <SPI.h>      // Include the SPI library for communication
#include <MFRC522.h>  // Include the MFRC522 library for RFID operations

#define BILLBOARD_RFID_SDA_PIN 10  // Define the RFID SDA pin
#define BILLBOARD_RFID_RST_PIN 9   // Define the RFID Reset pin

MFRC522 billboard_rfid(BILLBOARD_RFID_SDA_PIN, BILLBOARD_RFID_RST_PIN);  // Create MFRC522 instance

int billboard_protest_code = 0;  // Variable to store protest code based on UID

void setup() {
  Serial.begin(9600);         // Initialize serial communications with the PC
  SPI.begin();                // Initialize SPI bus
  billboard_rfid.PCD_Init();  // Initialize MFRC522
}

void loop() {
  // Check if a new RFID card is present and read its serial number (UID)
  if (billboard_rfid.PICC_IsNewCardPresent() && billboard_rfid.PICC_ReadCardSerial()) {
    // If a card is present and UID is successfully read
    String content = "";  // String to store UID as hexadecimal
    byte letter;

    // Construct the UID string in hexadecimal format
    for (byte i = 0; i < billboard_rfid.uid.size; i++) {
      content.concat(String(billboard_rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));  // Add leading 0 if byte is less than 0x10
      content.concat(String(billboard_rfid.uid.uidByte[i], HEX));  // Convert byte to hexadecimal string
    }
    content.toUpperCase();  // Convert UID string to uppercase for uniformity

    // Compare UID string to known values and set protest code accordingly
    if (content.substring(1) == "73 F3 0B 1A") {  // First UID: E3 E7 49 9F
      billboard_protest_code = 1;  // Set protest code 1
    } else if (content.substring(1) == "03 B7 86 15") {  // Second UID: 53 D0 D9 9E
      billboard_protest_code = 2;  // Set protest code 2
    } else if (content.substring(1) == "D3 6F 65 95") {  // Third UID: E3 18 4A 9F
      billboard_protest_code = 3;  // Set protest code 3
    } else {
      billboard_protest_code = 0;  // Unknown UID, set protest code to 0
    }
  } else {
    billboard_protest_code = 0;  // No card present or UID read failed, set protest code to 0
  }

  // Print the protest code to the Serial monitor
  Serial.println(billboard_protest_code);
}
