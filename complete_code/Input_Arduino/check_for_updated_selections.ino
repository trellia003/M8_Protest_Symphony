bool is_any_selection_different() {  //any of the 3 selection is different from it's previous one
  if (is_selection_decade_different() || is_selection_region_different() || is_selection_protest_different()) {
    return true;
  } else {
    return false;
  }
}

bool is_selection_decade_different() {  //if the current decade is different from the previous
  if (selected_decade[0] != selected_decade[1]) {
    return true;
  } else {
    return false;
  }
}

bool is_selection_region_different() {
  if (selected_region[0] != selected_region[1]) {
    return true;
  } else {
    return false;
  }
}

bool is_selection_protest_different() {
  if (selected_protest[0] != selected_protest[1]) {
    return true;
  } else {
    return false;
  }
}