// the idea is that the string should be splitted into parts by the ","
// the first part should be "START", 
// and than all the other parts are splitter by ":" 
// the value after the ":" is assigned based on the letter before the ":"


//example of possible strings:
//RESET
//START,D:x,R:y,P:z

void get_selection_data() {
  if (Serial1.available() > 0) {
    // Read data until newline character
    String receivedString = Serial1.readStringUntil('\n');
    receivedString.trim();  // Remove any leading or trailing whitespace

    // Print received string for debugging
    Serial.println("Received string: " + receivedString);

    // Check if the received string is "RESET"
    if (receivedString == "RESET") {
      is_reset_pressed = true;
    }
    // Check if the received string starts with "START" and follows the expected format
    else if (receivedString.startsWith("START")) {
      // Split the string by commas
      int startIndex = 0;
      int endIndex = receivedString.indexOf(',');

      while (endIndex != -1) {
        String part = receivedString.substring(startIndex, endIndex);
        processPart(part);
        startIndex = endIndex + 1;
        endIndex = receivedString.indexOf(',', startIndex);
      }

      // Process the last part after the final comma
      processPart(receivedString.substring(startIndex));
    }
  }
}

void processPart(String part) {
  // Split the part by colon
  int colonIndex = part.indexOf(':');
  if (colonIndex != -1) {
    String key = part.substring(0, colonIndex);
    String value = part.substring(colonIndex + 1);

    // Print extracted key-value pairs for debugging
    // Serial.println("Key: " + key + ", Value: " + value);

    // Assign values based on the key
    if (key == "D") {
      decade_selection_value = value.toInt();
    } else if (key == "R") {
      region_selection_value = value.toInt();
    } else if (key == "P") {
      protest_selection_value = value.toInt();
    }
  }
}