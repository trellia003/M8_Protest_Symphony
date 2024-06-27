void save_selection_values() {
  save_value_decade();
  save_value_region();
  save_value_protest();
}

void save_value_decade() {
  decade_selection_value[1] = decade_selection_value[0];
}
void save_value_region() {
  region_selection_value[1] = region_selection_value[0];
}
void save_value_protest() {
  protest_selection_value[1] = protest_selection_value[0];
}


bool are_all_saved_selection_valid() {
  if (is_saved_selection_decade_valid() && is_saved_selection_region_valid() && is_saved_selection_protest_valid()) {
    return true;
  } else {
    return false;
  }
}

bool is_saved_selection_decade_valid() {
  if (decade_selection_value[1] != 0 && decade_selection_value[1] <= 3) {
    return true;
  } else {
    return false;
  }
}

bool is_saved_selection_region_valid() {
  if (region_selection_value[1] != 0 && region_selection_value[1] <= 3) {
    return true;
  } else {
    return false;
  }
}

bool is_saved_selection_protest_valid() {
  if (protest_selection_value[1] != 0 && protest_selection_value[1] <= 3) {
    return true;
  } else {
    return false;
  }
}

void update_is_audio_player_running() {
  is_audio_player_running = !digitalRead(BUSY_PIN_DFPLAYER_PIN);
}