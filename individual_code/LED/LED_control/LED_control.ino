#include <Adafruit_NeoPixel.h>
// Define the pin where the LED data line is connected
#define LED_PIN 6 //might be changed

// Define the number of LEDs
#define NUM_LEDS 240

// Define delay between responses
#define DELAY_TIME 5000 // might be changed later on

// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// to be map with real percentage data
float accomodate_per = 0.2;
float ignore_per = 0.2;
float disperse_per = 0.2;
float arrest_per = 0.2;
float violence_per = 0.2;

void setup() {
  // Initialize the NeoPixel library
  strip.begin();
  //strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  strip.clear();
  // Define the sections and their colors
  
  int accomodate_end = NUM_LEDS * accomodate_per;
  int ignore_end = accomodate_end + NUM_LEDS * ignore_per;
  int disperse_end = ignore_end + NUM_LEDS * disperse_per;
  int arrest_end = disperse_end + NUM_LEDS * arrest_per;
  int violence_end = arrest_end + NUM_LEDS * violence_per;
  

  //Selection Phase begin
  setAllColor(strip.Color(255, 255, 255)); //White
  strip.show();
  delay(DELAY_TIME * 2);
   
  // Set colors for each section
  // Accomodate
  setSectionColor(0, accomodate_end, strip.Color(0, 255, 0)); // Green
  strip.show();
  delay(DELAY_TIME);

  //Ignore
  setSectionColor(accomodate_end, ignore_end, strip.Color(0, 0, 255)); //Blue
  strip.show();
  delay(DELAY_TIME);

  //Disperse
  setSectionColor(ignore_end, disperse_end, strip.Color(255, 255, 0)); //Yellow
  strip.show();
  delay(DELAY_TIME);

  //Arrest
  setSectionColor(disperse_end, arrest_end, strip.Color(184, 53, 255)); // Purple
  strip.show();
  delay(DELAY_TIME);

  //Violence
  setSectionColor(arrest_end, violence_end, strip.Color(255, 0, 0)); // Red
  strip.show();
  delay(DELAY_TIME);
}

void setSectionColor(int start, int end, uint32_t color) {
  for (int i = start; i < end; i++) {
    strip.setPixelColor(i, color);
  }
}

void setAllColor(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
}

void turnOffStrip() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0); // Set the color to '0' (off)
  }
  strip.show(); // Update the strip to turn off all LEDs
}




