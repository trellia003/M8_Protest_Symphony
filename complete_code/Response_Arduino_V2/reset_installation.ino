void reset_installation() {
  delay(1000);

  restore_default_values();
  Serial.println("reset succesfully!");
}


void restore_default_values() {
  restore_reset_button();
  restore_selections();
  restore_percentages();
  restore_switch_index();
}

void restore_switch_index() {
  response_switch_index = 0;
}

void restore_reset_button() {
  is_reset_pressed = false;
}
void restore_selections() {
  add_new_value_decade(0);
  add_new_value_region(0);
  add_new_value_protest(0);
}

void restore_percentages() {
  accomodation_percentage = 0;
  ignore_percentage = 0;
  dispersal_percentage = 0;
  arrest_percentage = 0;
  violence_percentage = 0;
}

void add_new_value_decade(int new_value) {
  decade_selection_value[1] = decade_selection_value[0];
  decade_selection_value[0] = new_value;
}
void add_new_value_region(int new_value) {
  region_selection_value[1] = region_selection_value[0];
  region_selection_value[0] = new_value;
}
void add_new_value_protest(int new_value) {
  protest_selection_value[1] = protest_selection_value[0];
  protest_selection_value[0] = new_value;
}