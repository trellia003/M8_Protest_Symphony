//MAYBE ADD A BUFFER SO IT SENSD MSG ONLY IF THE PREVIOUS MESSAGE IS DIFFERENT(OnLY start reset), it does not matter the selections
bool is_reset_button_state[2] = { false, false };       //first one is the current reading, second is the last one changed. i use this to see if the two values changes
bool are_all_hands_placed_state[2] = { false, false };  //first one is the current reading, second is the last one changed. i use this to see if the two values changes

void communication_to_response_arduino() {
  is_reset_button_state[0] = digitalRead(RESET_BUTTON_PIN);

  if (is_reset_button_state[0] != is_reset_button_state[1]) {
    if (is_reset_button_state[0]) {  //if reset button is pressed
      Serial1.println("RESET");
      Serial.println("RESET");
    } else {
      //button released
    }
    is_reset_button_state[1] = is_reset_button_state[0];
  }

  are_all_hands_placed_state[0] = are_all_hands_placed();
  if (are_all_hands_placed_state[0] != are_all_hands_placed_state[1]) {
    if (are_all_hands_placed_state[0]) {
      if (are_all_selection_valid()) {
        Serial1.println("START,D:" + String(selected_decade[0]) + ",R:" + String(selected_region[0]) + ",P:" + String(selected_protest[0]));
        Serial.println("START,D:" + String(selected_decade[0]) + ",R:" + String(selected_region[0]) + ",P:" + String(selected_protest[0]));
      }
    } else {
      //hands released
    }
    are_all_hands_placed_state[1] = are_all_hands_placed_state[0];
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
  int LDR_threshold1 = 300;  // different LDRS have different threshold for when it is dark, real values need to be checked when LDRs are installed
  int LDR_threshold2 = 300;
  int LDR_threshold3 = 300;

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
