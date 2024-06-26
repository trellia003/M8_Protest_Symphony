bool is_any_selection_different() {
  if (is_decade_selection_different() || is_region_selection_different() || is_protest_selection_different()) {
    return true;
  } else {
    return false;
  }
}

bool are_all_selection_different() {
  if (is_decade_selection_different() && is_region_selection_different() && is_protest_selection_different()) {
    return true;
  } else {
    return false;
  }
}

bool is_decade_selection_different() {
  if (decade_selection_value[0] != decade_selection_value[1]) {
    return true;
  } else {
    return false;
  }
}
bool is_region_selection_different() {
  if (region_selection_value[0] != region_selection_value[1]) {
    return true;
  } else {
    return false;
  }
}
bool is_protest_selection_different() {
  if (protest_selection_value[0] != protest_selection_value[1]) {
    return true;
  } else {
    return false;
  }
}



bool are_all_selection_valid() {
  if (is_selection_decade_valid() && is_selection_region_valid() && is_selection_protest_valid()) {
    return true;
  } else {
    return false;
  }
}

bool is_selection_decade_valid() {
  if (decade_selection_value[0] != 0 && decade_selection_value[0] <= 3) {
    return true;
  } else {
    return false;
  }
}

bool is_selection_region_valid() {
  if (region_selection_value[0] != 0 && region_selection_value[0] <= 3) {
    return true;
  } else {
    return false;
  }
}

bool is_selection_protest_valid() {
  if (protest_selection_value[0] != 0 && protest_selection_value[0] <= 3) {
    return true;
  } else {
    return false;
  }
}