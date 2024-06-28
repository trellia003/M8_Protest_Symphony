void displayLED(int current_response, int percentage) {

  responseLED(inner_LED_strip, current_response, percentage);
  responseLED(outer_LED_strip, current_response, percentage);

  updateLED(percentage);
}

void responseLED(Adafruit_NeoPixel& strip, int current_response, int percentage) {
  int num_led = strip.numPixels();
  int offset = num_led * violence_percentage / 100;
  int start = (num_led * percentage_revealed / 100 + offset) % num_led;
  int end = (start + num_led * percentage / 100) % num_led;
  uint32_t colorCode = get_LED_color(strip, current_response);
  // Serial.println("start: " + String(start));
  // Serial.println("end: " + String(end));

  if (start < end) {
    // Normal case where no wrapping is necessary
    set_section_color(strip, start, end + 1, colorCode);
  } else {
    // Handle wrapping
    set_section_color(strip, start, num_led, colorCode);  // From start to end of strip
    set_section_color(strip, 0, end + 1, colorCode);      // From beginning of strip to wrapped end
  }
  strip.show();
}

void updateLED(int percentage) {
  percentage_revealed += percentage;
  Serial.println(String(percentage_revealed));
  if (percentage_revealed >= 100) {
    percentage_revealed = 0;
    Serial.println("percentage 0" );
  }  // Reset after full cycle
}

uint32_t get_LED_color(Adafruit_NeoPixel& strip, int current_response) {
  switch (current_response) {
    case 0:
      return strip.Color(255, 255, 255);  //White
    case 1:
      if (compareLED(strip, inner_LED_strip)) {
        return strip.Color(0, 255, 0);
      } else if (compareLED(strip, outer_LED_strip)) {
        return strip.Color(0, 0, 255);
      }
      //Accomodation - Green
    case 2:
      if (compareLED(strip, inner_LED_strip)) {
        return strip.Color(0, 0, 255);
      } else if (compareLED(strip, outer_LED_strip)) {
        return strip.Color(0, 255, 0);
      }
      //Ignore - Blue
    case 3:
      if (compareLED(strip, inner_LED_strip)) {
        return strip.Color(255, 255, 0);
      } else if (compareLED(strip, outer_LED_strip)) {
        return strip.Color(255, 0, 250);
      }
      //Disperse - Yellow
    case 4:
      if (compareLED(strip, inner_LED_strip)) {
        return strip.Color(255, 124, 0);
      } else if (compareLED(strip, outer_LED_strip)) {
        return strip.Color(255, 0, 124);
      }
      //Arrest - Orange
    case 5:
      // Serial.println("Red");
      return strip.Color(255, 0, 0);  //Violence - Red
  }
}

//function to set set Color for each section
void set_section_color(Adafruit_NeoPixel& strip, int start, int end, uint32_t color_code) {
  for (int i = start; i < end; i++) {
    strip.setPixelColor(i, color_code);
  }
}

//function to set Color for the whole strip
void set_all_color(uint32_t color) {
  for (int i = 0; i < NUM_LEDS_INNER; i++) {
    inner_LED_strip.setPixelColor(i, color);
  }
  for (int i = 0; i < NUM_LEDS_OUTER; i++) {
    outer_LED_strip.setPixelColor(i, color);
  }
}

bool compareLED(Adafruit_NeoPixel& strip1, Adafruit_NeoPixel& strip2) {
  return (strip1.numPixels() == strip2.numPixels() && strip1.getPin() == strip2.getPin() && strip1.getBrightness() == strip2.getBrightness());
}

void reset_LED() {
  for (int i = 0; i <= NUM_LEDS_INNER; i++) {
    // Serial.println("Resetting inner LED: " + String(i)); // Debug print
    inner_LED_strip.setPixelColor(i, inner_LED_strip.Color(0, 0, 0));
  }
  for (int i = 0; i <= NUM_LEDS_OUTER; i++) {
    // Serial.println("Resetting outer LED: " + String(i)); // Debug print
    outer_LED_strip.setPixelColor(i, outer_LED_strip.Color(0, 0, 0));
  }
  inner_LED_strip.show();
  outer_LED_strip.show();
}
