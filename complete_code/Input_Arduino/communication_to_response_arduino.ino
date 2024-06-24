//MAYBE ADD A BUFFER SO IT SENSD MSG ONLY IF THE PREVIOUS MESSAGE IS DIFFERENT(OnLY start reset), it does not matter the selections

void communication_to_response_arduino() {
  // if (is_any_selection_different_and_valid()) {  //if any selection is different from it's previous one and valid
  if (digitalRead(RESET_BUTTON_PIN)) {  //if reset button is pressed
    Serial1.println("RESET/");
  }
  if (are_all_selection_valid() && are_all_hands_placed()) {
    Serial1.println("START;D:" + String(selected_decade[0]) + ";R:" + String(selected_region[0]) + ";P:" + String(selected_protest[0]));
  }
}

bool is_any_selection_different_and_valid() {  //if any selection is different from it's previous one and valid
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
