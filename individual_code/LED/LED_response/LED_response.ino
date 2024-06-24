#include <Adafruit_NeoPixel.h>
// Define the pin where the LED data line is connected
#define STRIP_LED_PIN 6 //might be changed
// Define the number of LEDs
#define NUM_LEDS 240

// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel strip(NUM_LEDS, STRIP_LED_PIN, NEO_GRB + NEO_KHZ800);

int percentage = 0;
int percentage_shown = 0;

void setup() {
  // put your setup code here, to run once:
  strip.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  strip.clear();
}

//function to set set Color for each section
void setSectionColor(int start, int end, uint32_t color) {
  for (int i = start; i < end; i++) {
    strip.setPixelColor(i, color);
  }
}

//function to set Color for the whole strip 
void setAllColor(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
}

//function to display LED color for each response 
//to be used in functions of each response
//Example:
//accomodation(int percentage) {
//  responseLED(1, percentage);
//}
void responseLED(int current_response, int percentage) {
  int start = NUM_LEDS * percentage_shown/100;
  int end = start + NUM_LEDS * percentage/100;
  setSectionColor(start, end, getLEDColorCode(current_response));
  strip.show();
  delay(5000);
  percentage_shown += percentage;
}

//function to get the LED color for each response
uint32_t getLEDColorCode(int current_response) {
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





