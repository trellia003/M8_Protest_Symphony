void communication_to_response_arduino() {
  if (is_any_selection_different()) {
    //send reset
    Serial.println("reset");
  }
  if (are_all_selection_valid() && are_all_hands_placed()) {
    //send message start installation
    Serial.println("start");
  }
}


bool are_all_hands_placed(){
  return true;
}

void send_data() {
  //if perceive any change
  // String output = "S:" + String(is_response_start) + ",D:" + String(decade[0]) + ",R:" + String(region[0]) + ",P:" + String(protest[0]);
  //Serial.println(output);          // Print to serial for debugging
  //serial_arduino.println(output);  // Send the string via SoftwareSerial
}