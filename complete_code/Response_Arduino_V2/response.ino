void accomodate_response() {
  Serial.println("hello");
  play_response_sound(1);
  //LED shown
  // inner_response_LED(1, accomodation_percentage);

  // //Raise Flag
  // int flag_raise = 1;
  // while (flag_raise == 1) {
  //   flag_servo_control();
  //   flag_raise = 0;
  // }
}

void ignore_response() {
  play_response_sound(2);
}

void dispersal_response() {
  play_response_sound(3);
}

void arrest_response() {
  play_response_sound(4);
}

void violence_response() {
  play_response_sound(5);
}