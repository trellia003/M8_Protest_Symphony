void reset_installation() {
  // delay(1000);
  set_all_color((255,255,255));
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
