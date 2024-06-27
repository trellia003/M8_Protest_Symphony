void reset_installation() {
  // delay(1000);
  reset_LED();
  current_audio_index = 0;
  has_run_once_every_response = false;

  flag_servo.write(0);

  delay(1000);
  flag_servo.write(90);

  politician_servo_1.write(120);
  politician_servo_2.write(120);
  politician_servo_3.write(120);
  delay(2000);
  politician_servo_1.write(90);
  politician_servo_2.write(90);
  politician_servo_3.write(90);

  digitalWrite(FOG_PIN, LOW);
  restore_default_values();
  Serial.println("reset succesfully!");
}


void restore_default_values() {
  restore_reset_button();
  restore_saved_selections();
  restore_selections();
  restore_percentages();
  restore_switch_index();
  restore_current_audio_index();
}
void restore_current_audio_index() {
  current_audio_index = 0;
}

void restore_switch_index() {
  response_switch_index = 0;
}

void restore_reset_button() {
  is_reset_pressed = false;
}
void restore_saved_selections() {
  decade_selection_value[1] = 0;
  region_selection_value[1] = 0;
  protest_selection_value[1] = 0;
}
void restore_selections() {
  decade_selection_value[0] = 0;
  region_selection_value[0] = 0;
  protest_selection_value[0] = 0;
}
void restore_percentages() {
  accomodation_percentage = 0;
  ignore_percentage = 0;
  dispersal_percentage = 0;
  arrest_percentage = 0;
  violence_percentage = 0;
}
