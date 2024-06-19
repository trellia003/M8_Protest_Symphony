void give_feedback_to_user() {
  audio_feedback();   //if the previous values are different make a buzzer beep
  visual_feedback();  //if the selection is correct light up the led
}

void audio_feedback() {
  if (is_selection_decade_different()) {
    digitalWrite(BUZZER_DECADE_FEEDBACK_PIN, HIGH);  // Buzzer high
  } else {
    digitalWrite(BUZZER_DECADE_FEEDBACK_PIN, LOW);  // Buzzer low
  }
  if (is_selection_region_different()) {
    digitalWrite(BUZZER_REGION_FEEDBACK_PIN, HIGH);  // Buzzer high
  } else {
    digitalWrite(BUZZER_REGION_FEEDBACK_PIN, LOW);  // Buzzer low
  }
  if (is_selection_protest_different()) {
    digitalWrite(BUZZER_PROTEST_FEEDBACK_PIN, HIGH);  // Buzzer high
  } else {
    digitalWrite(BUZZER_PROTEST_FEEDBACK_PIN, LOW);  // Buzzer low
  }
}

void visual_feedback() {
  if (is_selection_decade_valid()) {
    digitalWrite(LED_DECADE_FEEDBACK_PIN, HIGH);  // LED high
  } else {
    digitalWrite(LED_DECADE_FEEDBACK_PIN, LOW);  // LED low
  }
  if (is_selection_region_valid()) {
    digitalWrite(LED_REGION_FEEDBACK_PIN, HIGH);  // LED high
  } else {
    digitalWrite(LED_REGION_FEEDBACK_PIN, LOW);  // LED low
  }
  if (is_selection_protest_valid()) {
    digitalWrite(LED_PROTEST_FEEDBACK_PIN, HIGH);  // LED high
  } else {
    digitalWrite(LED_PROTEST_FEEDBACK_PIN, LOW);  // LED low
  }
}