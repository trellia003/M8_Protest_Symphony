#include <Adafruit_NeoPixel.h>
// Define the pin where the LED data line is connected
#define INNER_STRIP_LED_PIN 9  //might be changed
#define OUTER_STRIP_LED_PIN 10
// Define the number of LEDs
#define INNER_NUM_LEDS 91
#define OUTER_NUM_LEDS 60


// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel inner_strip(INNER_NUM_LEDS, INNER_STRIP_LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel outer_strip(OUTER_NUM_LEDS, OUTER_STRIP_LED_PIN, NEO_GRB + NEO_KHZ800);

int accomodate_percent = 8;
int ignore_percent = 54;
int disperse_percent = 22;
int arrest_percent = 9;
int violence_percent = 7;

int percentage_shown = 0;


int led_shown = 1;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  inner_strip.begin();
  outer_strip.begin();
}

void loop() {
  while (led_shown) {
    responseLED(inner_strip, 1, accomodate_percent);
    responseLED(outer_strip, 1, accomodate_percent);
    updateLED(accomodate_percent);
    // delay(1000);
    responseLED(inner_strip, 2, ignore_percent);
    responseLED(outer_strip, 2, ignore_percent);
    updateLED(ignore_percent);
    // delay(1000);
    responseLED(inner_strip, 3, disperse_percent);
    responseLED(outer_strip, 3, disperse_percent);
    updateLED(disperse_percent);
    // delay(1000);
    responseLED(inner_strip, 4, arrest_percent);
    responseLED(outer_strip, 4, arrest_percent);
    updateLED(arrest_percent);
    // delay(1000);
    responseLED(inner_strip, 5, violence_percent);
    responseLED(outer_strip, 5, violence_percent);
    updateLED(violence_percent);
    // delay(1000);
    led_shown = 0;
  }
}


//function to set set Color for each section
// void setSectionColor(int start, int end, uint32_t color) {
//   for (int i = start; i < end; i++) {
//     inner_strip.setPixelColor(i, color);
//     outer_strip.setPixelColor(i, color);
//   }
// }

void setSectionColor(Adafruit_NeoPixel& strip, int start, int end, uint32_t colorCode) {
  for (int i = start; i < end; i++) {
    strip.setPixelColor(i, colorCode);  // Wrap around using modulo
  }
}

//function to set Color for the whole strip
void setAllColor(uint32_t color) {
  for (int i = 0; i < INNER_NUM_LEDS; i++) {
    inner_strip.setPixelColor(i, color);
  }
  for (int i = 0; i < OUTER_NUM_LEDS; i++) {
    outer_strip.setPixelColor(i, color);
  }
}

// void responseLED(int current_response, int percentage) {
//   int offset = INNER_NUM_LEDS * violence_percent / 100;  // Start at the 10th LED
//   int start = (INNER_NUM_LEDS * percentage_shown / 100 + offset) % INNER_NUM_LEDS;
//   int end = (start + INNER_NUM_LEDS * percentage / 100) % INNER_NUM_LEDS;
//   uint32_t colorCode = getLEDColorCode(inner_strip, current_response);

//   if (start < end) {
//     // Normal case where no wrapping is necessary
//     setSectionColor(start, end, colorCode);
//   } else {
//     // Handle wrapping
//     setSectionColor(start, INNER_NUM_LEDS, colorCode);  // From start to end of strip
//     setSectionColor(0, end, colorCode);           // From beginning of strip to wrapped end
//   }
//   inner_strip.show();
//   // delay(5000); // You can adjust or enable delay for testing
//   percentage_shown += percentage;
//   if (percentage_shown >= 100) {
//     percentage_shown = 0;
//   }  // Reset after full cycle
// }

void responseLED(Adafruit_NeoPixel& strip, int current_response, int percentage) {
  int num_led = strip.numPixels();
  int offset = num_led * violence_percent / 100;
  int start = (num_led * percentage_shown / 100 + offset) % num_led;
  int end = (start + num_led * percentage / 100) % num_led;
  uint32_t colorCode = getLEDColorCode(strip, current_response);

  if (start < end) {
    // Normal case where no wrapping is necessary
    setSectionColor(strip, start, end + 1, colorCode);
  } else {
    // Handle wrapping
    setSectionColor(strip, start, num_led, colorCode);  // From start to end of strip
    setSectionColor(strip, 0, end + 1, colorCode);          // From beginning of strip to wrapped end
  }
  strip.show();
}

void updateLED(int percentage) {
  percentage_shown += percentage;
  if (percentage_shown >= 100) {
    percentage_shown = 0;
  }  // Reset after full cycle
}

//function to get the LED color for each response
uint32_t getLEDColorCode(Adafruit_NeoPixel& strip, int current_response) {
  switch (current_response) {
    case 0:
      return strip.Color(255, 255, 255);  //White
    case 1:
      if (compareLED(strip, inner_strip)) {
        return strip.Color(0, 255, 0);
      } else if (compareLED(strip, outer_strip)) {
        return strip.Color(0, 0, 255);
      }
      //Accomodation - Green
    case 2:
      if (compareLED(strip, inner_strip)) {
        return strip.Color(0, 0, 255);
      } else if (compareLED(strip, outer_strip)) {
        return strip.Color(0, 255, 0);
      }
      //Ignore - Blue
    case 3:
      if (compareLED(strip, inner_strip)) {
        return strip.Color(255, 255, 0);
      } else if (compareLED(strip, outer_strip)) {
        return strip.Color(255, 0, 255);
      }
      //Disperse - Yellow
    case 4:
      if (compareLED(strip, inner_strip)) {
        return strip.Color(255, 124, 0);
      } else if (compareLED(strip, outer_strip)) {
        return strip.Color(255, 0, 124);
      }
      //Arrest - Orange
    case 5:
      // Serial.println("Red");
      return strip.Color(255, 0, 0);  //Violence - Red
  }
}

bool compareLED(Adafruit_NeoPixel& strip1, Adafruit_NeoPixel& strip2) {
  return (strip1.numPixels() == strip2.numPixels() && strip1.getPin() == strip2.getPin() && strip1.getBrightness() == strip2.getBrightness());
}
