bool are_all_seleciton_valid() {
  if (is_selection_decade_valid() && is_selection_region_valid() && is_selection_protest_valid()) {
    return true;
  } else {
    return false;
  }
}

bool is_selection_decade_valid() {
  if (selected_decade[0] != 0) {
    return true;
  } else {
    return false;
  }
}

bool is_selection_region_valid() {
  if (selected_region[0] != 0) {
    return true;
  } else {
    return false;
  }
}

bool is_selection_protest_valid() {
  if (selected_protest[0] != 0) {
    return true;
  } else {
    return false;
  }
}