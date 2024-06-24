//function to display LED color for each response 
//to be used in functions of each response
//Example:
//accomodation(int percentage) {
//  responseLED(1, percentage);
//}
void response_LED(int current_response, int percentage) {
  int start = NUM_LEDS * percentage_shown/100;
  int end = start + NUM_LEDS * percentage/100;
  set_section_color(start, end, get_LED_color_code(current_response));
  strip.show();
  delay(5000);
  percentage_shown += percentage;
}

//function to get the LED color for each response
uint32_t get_LED_color_code(int current_response) {
  switch (current_response) {
    case 0:
      return strip.Color(255, 255, 255); //White
    case 1: 
      return strip.Color(0, 255, 0); //Accomodation - Green
    case 2:
      return strip.Color(0, 0, 255); //Ignore - Blue
    case 3:
      return strip.Color(255, 255, 0); //Disperse - Yellow
    case 4:
      return strip.Color(255, 239, 0); //Arrest - Orange
    case 5:
      return strip.Color(255, 0 , 0); //Violence - Red
  }
}

//function to set set Color for each section
void set_section_color(int start, int end, uint32_t color) {
  for (int i = start; i < end; i++) {
    strip.setPixelColor(i, color);
  }
}

//function to set Color for the whole strip 
void set_all_color(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
}