void give_feedback_to_user() {
  audio_feedback();   //if the new value is valid and different from the previou one make a buzzer beep
  visual_feedback();  //if the selection is correct light up the led
}

void audio_feedback() {
  // Serial.println(String(is_selection_decade_different())+String(is_selection_region_different())+String(is_selection_protest_different()));
  if (is_selection_decade_different() && is_selection_decade_valid()) {
    digitalWrite(BUZZER_DECADE_FEEDBACK_PIN, HIGH);  // Buzzer high
  } else {
    digitalWrite(BUZZER_DECADE_FEEDBACK_PIN, LOW);  // Buzzer low
  }
  if (is_selection_region_different() && is_selection_region_valid()) {
    digitalWrite(BUZZER_REGION_FEEDBACK_PIN, HIGH);  // Buzzer high
  } else {
    digitalWrite(BUZZER_REGION_FEEDBACK_PIN, LOW);  // Buzzer low
  }
  if (is_selection_protest_different() && is_selection_protest_valid()) {
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