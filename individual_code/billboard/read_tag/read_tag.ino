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

int billboard_RFID_buffer_readings[] = { 0, 0 };

void setup() {
  Serial.begin(9600);         // Initialize serial communications with the PC
  SPI.begin();                // Initialize SPI bus
  billboard_rfid.PCD_Init();  // Initialize MFRC522
}

void loop() {
  Serial.println(filter_data());
  delay(5);  //needs some delay? but it prints 0 and value,0 value, 0 value etc...
}


int filter_data() {       //usually the reading of the rfid output the card number and then a 0, I tried to fix it a lot. i just used a buffer
  billboard_RFID_buffer_readings[1] = billboard_RFID_buffer_readings[0];  //use the buffer to store the last two readings, if a card is read one of them should be 0 and the other not.
  billboard_RFID_buffer_readings[0] = read_the_RFID();
  if (billboard_RFID_buffer_readings[1] != 0) {  //if the last element is not 0, we want to use that card number
    return billboard_RFID_buffer_readings[1];
  } else {  //otherwise if the buffer[1] is 0, the buffer[0] is either a 0 oe a number, and we just use that because yes.
    return billboard_RFID_buffer_readings[0];
  }
}

int read_the_RFID() {
  int billboard_protest_code = 0;  // Initialize the protest code to 0

  // Check if a new RFID card is present and read its serial number
  if (billboard_rfid.PICC_IsNewCardPresent() && billboard_rfid.PICC_ReadCardSerial()) {
    String content = "";  // Initialize an empty string to store the UID

    // Loop through each byte of the UID and convert it to a hexadecimal string
    for (byte i = 0; i < billboard_rfid.uid.size; i++) {
      // Append a leading zero if the byte is less than 0x10 for proper formatting
      content.concat(String(billboard_rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
      // Append the byte in hexadecimal format
      content.concat(String(billboard_rfid.uid.uidByte[i], HEX));
    }
    content.toUpperCase();  // Convert UID string to uppercase for uniformity

    // Check if the UID matches a known protest code
    if (content.substring(1) == "73 F3 0B 1A") {         // First UID
      billboard_protest_code = 1;                        // Set protest code to 1
    } else if (content.substring(1) == "03 B7 86 15") {  // Second UID
      billboard_protest_code = 2;                        // Set protest code to 2
    } else if (content.substring(1) == "D3 6F 65 95") {  // Third UID
      billboard_protest_code = 3;                        // Set protest code to 3
    } else {
      billboard_protest_code = 0;  // Unknown UID, set protest code to 0
    }
  }
  return billboard_protest_code;  // Return the protest code
}
