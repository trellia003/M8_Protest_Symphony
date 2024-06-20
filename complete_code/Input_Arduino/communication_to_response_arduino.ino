void communication_to_response_arduino() {
  if (is_any_selection_different_and_valid()) {
    //send reset
    Serial.println("RESET");
    // Serial.println("decade:" + String(selected_decade[0]) + "   region:" + String(selected_region[0]) + "   protest:" + String(selected_protest[0]));
  }
  if (are_all_selection_valid() && are_all_hands_placed()) {
    //send message start installation
    // Serial.print("start====");
    Serial.println("START;D:" + String(selected_decade[0]) + ";R:" + String(selected_region[0]) + ";P:" + String(selected_protest[0]));
  }
}

bool is_any_selection_different_and_valid() {
  if (is_selection_decade_different() && is_selection_decade_valid() || is_selection_region_different() && is_selection_region_valid() || is_selection_protest_different() && is_selection_protest_valid()) {
    return true;
  } else {
    return false;
  }
}


bool are_all_hands_placed() {
  int LDR_threshold1 = 600;  // different LDRS have different threshold for when it is dark, real values need to be checked when LDRs are installed
  int LDR_threshold2 = 670;
  int LDR_threshold3 = 700;

  //value parameters and reading of value
  int LDR_value1, LDR_value2, LDR_value3;
  LDR_value1 = analogRead(HANDSELECT_LDR_ANALOG_Pin1);
  LDR_value2 = analogRead(HANDSELECT_LDR_ANALOG_Pin2);
  LDR_value3 = analogRead(HANDSELECT_LDR_ANALOG_Pin3);
  //print values of LDR
  // Serial.print(LDR_value1);
  // Serial.print(",");
  // Serial.print(LDR_value2);
  // Serial.print(",");
  // Serial.println(LDR_value3);
  // delay(1000);
  //checks if light level is below threshold and therefore hand placed
  if (LDR_value1 <= LDR_threshold1 && LDR_value2 <= LDR_threshold2 && LDR_value3 <= LDR_threshold3) {
    // Serial.println("Hands activated");
    return true;
  } else {
    // Serial.println("Not all hands active");
    return false;
  }
}

void send_data() {
  //if perceive any change
  // String output = "S:" + String(is_response_start) + ",D:" + String(decade[0]) + ",R:" + String(region[0]) + ",P:" + String(protest[0]);
  //Serial.println(output);          // Print to serial for debugging
  //serial_arduino.println(output);  // Send the string via SoftwareSerial
}