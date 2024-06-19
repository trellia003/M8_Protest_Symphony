void communication_to_response_arduino(){
  if(is_any_selection_different()){
    //send reset
  }
  if (are_all_selection_valid() && all hands){
    //send message start installation
  }
}


void send_data() {
  //if perceive any change
  // String output = "S:" + String(is_response_start) + ",D:" + String(decade[0]) + ",R:" + String(region[0]) + ",P:" + String(protest[0]);
  //Serial.println(output);          // Print to serial for debugging
  //serial_arduino.println(output);  // Send the string via SoftwareSerial
}