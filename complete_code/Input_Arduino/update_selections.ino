void update_selections() {  //retreive the new vales, add them in the array and shift the old values
  update_decade();
  update_region();
  update_protest();
}

void update_decade() {
  int new_decade = get_decade();            //get the new value
  selected_decade[1] = selected_decade[0];  //shift old value
  selected_decade[0] = new_decade;          //add new value
}

void update_region() {
  int new_region = get_region();
  selected_region[1] = selected_region[0];
  selected_region[0] = new_region;
}

void update_protest() {
  int new_protest = get_protest();
  selected_protest[1] = selected_protest[0];
  selected_protest[0] = new_protest;
}

int get_decade() {
  int average = 0;  // The average
  int arrayLength = sizeof(decade_potentiomiter_readings) / sizeof(decade_potentiomiter_readings[0]);
  decade_potentiomiter_total -= decade_potentiomiter_readings[decade_potentiomiter_readIndex];           // Remove the oldest entry
  decade_potentiomiter_readings[decade_potentiomiter_readIndex] = analogRead(DECADE_POTENTIOMETER_PIN);  // Read from the sensor
  decade_potentiomiter_total += decade_potentiomiter_readings[decade_potentiomiter_readIndex];           // Add the newest reading to the total
  decade_potentiomiter_readIndex = (decade_potentiomiter_readIndex + 1) % arrayLength;                   // Advance to the next position
  average = decade_potentiomiter_total / arrayLength;                                                    // Calculate the average

  int decade = 0;
  if (120 <= average && average <= 280) {
    decade = 3;  //2010
    // Serial.println("3: 2010");
  } else if (360 <= average && average <= 560) {
    decade = 2;  //2000
    // Serial.println("2: 2000");
  } else if (660 <= average && average <= 820) {
    decade = 1;  //1990
    // Serial.println("1: 1990");
  }
  return decade;
}


int get_region() {  //read the region and convert it to 0,1europe,2asia,3notrth america
}


int get_protest() {  //read the protest and convert it to 0,1politics,2wages,3police brutality
  //usually the reading of the rfid output the card number and then a 0, I tried to fix it a lot. i just used a buffer

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
