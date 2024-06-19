void give_feedback_to_user() {
  audio_feedback();  //if the previous values are different make a buzzer beep
  visual_feedback(); //if the selection is correct light up the led
}

void audio_feedback() {
  if (is_selection_decade_different()) {
    //buzzer high
  } else {
    //buzzer low
  }
  if (is_selection_region_different()) {
    //buzzer high
  } else {
    //buzzer low
  }
  if (is_selection_protest_different()) {
    //buzzer high
  } else {
    //buzzer low
  }
}

void visual_feedback() {
  if (is_selection_decade_valid()) {
    //led high
  } else {
    //led low
  }
  if (is_selection_region_valid()) {
    //led high
  } else {
    //led low
  }
  if (is_selection_protest_valid()) {
    //led high
  } else {
    //led low
  }
}