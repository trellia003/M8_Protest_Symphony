// void inner_response_LED(int response, int percentage) {
//   int start = NUM_LEDS_INNER * percentage_revealed/100;
//   int end = start + NUM_LEDS_INNER * percentage/100;
//   set_section_color(start, end, get_LED_color(response));
//   strip.show();
//   delay(5000);
//   percentage_revealed += percentage;
// }

// uint32_t get_LED_color(int response) {
//   switch (response) {
//     case 0:
//       return strip.Color(255, 255, 255); //White
//     case 1: 
//       return strip.Color(0, 255, 0); //Accomodation - Green
//     case 2:
//       return strip.Color(0, 0, 255); //Ignore - Blue
//     case 3:
//       return strip.Color(255, 255, 0); //Disperse - Yellow
//     case 4:
//       return strip.Color(255, 239, 0); //Arrest - Orange
//     case 5:
//       return strip.Color(255, 0 , 0); //Violence - Red
//   }
// }

// //function to set set Color for each section
// void set_section_color(int start, int end, uint32_t color) {
//   for (int i = start; i < end; i++) {
//     strip.setPixelColor(i, color);
//   }
// }

// //function to set Color for the whole strip 
// void set_all_color(uint32_t color) {
//   for (int i = 0; i < NUM_LEDS; i++) {
//     strip.setPixelColor(i, color);
//   }
// }