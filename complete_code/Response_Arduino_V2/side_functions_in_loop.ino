bool are_all_selection_value_valid() {
  if (decade_selection_value != 0 && region_selection_value != 0 && protest_selection_value != 0) {
    return true;
  } else {
    return false;
  }
}