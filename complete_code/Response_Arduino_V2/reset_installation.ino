void reset_installation() {
  delay(1000);

  restore_default_values();
  Serial.println("reset succesfully!");
}


void restore_default_values() {
  restore_reset_button();
  restore_selections();
  restore_percentages();
}

void restore_reset_button() {
  is_reset_pressed = false;
}
void restore_selections() {
  decade_selection_value = 0;
  region_selection_value = 0;
  protest_selection_value = 0;
}

void restore_percentages() {
  accomodation_percentage = 0;
  ignore_percentage = 0;
  dispersal_percentage = 0;
  arrest_percentage = 0;
  violence_percentage = 0;
}