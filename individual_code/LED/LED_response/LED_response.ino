#include <Adafruit_NeoPixel.h>
// Define the pin where the LED data line is connected
#define INNER_STRIP_LED_PIN 9  //might be changed
#define OUTER_STRIP_LED_PIN 10
// Define the number of LEDs
#define INNER_NUM_LEDS 91
#define OUTER_NUM_LEDS 60


// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel inner_LED_strip(INNER_NUM_LEDS, INNER_STRIP_LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel outer_LED_strip(OUTER_NUM_LEDS, OUTER_STRIP_LED_PIN, NEO_GRB + NEO_KHZ800);

int accomodate_percent = 8;
int ignore_percent = 54;
int disperse_percent = 22;
int arrest_percent = 9;
int violence_percent = 7;

int percentage_shown = 0;


String inputString = "";         // A string to hold incoming data
boolean stringComplete = false;  // Whether the string is complete

int int1, int2, int3;  // Variables to store the received integers


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  inner_LED_strip.begin();
  outer_LED_strip.begin();

  // reset_LED();
}

void loop() {
  readSerialData();

  // If a string has been received and is complete
  if (stringComplete) {
    // Parse the string to extract the integers
    parseData();
    // Print the received integers to the serial monitor
    Serial.print("Received integers: ");
    Serial.print(int1);
    Serial.print(", ");
    Serial.print(int2);
    Serial.print(", ");
    Serial.println(int3);

    // Clear the string for the next data
    inputString = "";
    stringComplete = false;
  }
  // // while (led_shown) {
  // responseLED(inner_LED_strip, 1, accomodate_percent);
  // responseLED(outer_LED_strip, 1, accomodate_percent);
  // updateLED(accomodate_percent);
  // delay(1000);
  // responseLED(inner_LED_strip, 2, ignore_percent);
  // responseLED(outer_LED_strip, 2, ignore_percent);
  // updateLED(ignore_percent);
  // delay(1000);
  // responseLED(inner_LED_strip, 3, disperse_percent);
  // responseLED(outer_LED_strip, 3, disperse_percent);
  // updateLED(disperse_percent);
  // delay(1000);
  // responseLED(inner_LED_strip, 4, arrest_percent);
  // responseLED(outer_LED_strip, 4, arrest_percent);
  // updateLED(arrest_percent);
  // delay(1000);
  // responseLED(inner_LED_strip, 5, violence_percent);
  // responseLED(outer_LED_strip, 5, violence_percent);
  // updateLED(violence_percent);
  // delay(1000);
  // // led_shown = 0;

  // reset_LED();
  // delay(3000);
  // // }
}



void readSerialData() {
  while (Serial.available()) {
    // Get the new byte
    char inChar = (char)Serial.read();
    // Add it to the inputString
    inputString += inChar;
    // If the incoming character is a newline, set stringComplete to true
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void parseData() {
  // Split the inputString at each comma
  int commaIndex1 = inputString.indexOf(',');
  int commaIndex2 = inputString.indexOf(',', commaIndex1 + 1);

  // Convert the substrings to integers
  int1 = inputString.substring(0, commaIndex1).toInt();
  int2 = inputString.substring(commaIndex1 + 1, commaIndex2).toInt();
  int3 = inputString.substring(commaIndex2 + 1).toInt();
}

void setSectionColor(Adafruit_NeoPixel& strip, int start, int end, uint32_t colorCode) {
  for (int i = start; i < end; i++) {
    strip.setPixelColor(i, colorCode);  // Wrap around using modulo
  }
}

//function to set Color for the whole strip
void setAllColor(uint32_t color) {
  for (int i = 0; i < INNER_NUM_LEDS; i++) {
    inner_LED_strip.setPixelColor(i, color);
  }
  for (int i = 0; i < OUTER_NUM_LEDS; i++) {
    outer_LED_strip.setPixelColor(i, color);
  }
}

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
    setSectionColor(strip, 0, end + 1, colorCode);      // From beginning of strip to wrapped end
  }
  strip.show();
}

void updateLED(int percentage) {
  percentage_shown += percentage;
  if (percentage_shown >= 100) {
    percentage_shown = 0;
  }  // Reset after full cycle
}

void reset_LED() {
  for (int i = 0; i < INNER_NUM_LEDS; i++) {
    inner_LED_strip.setPixelColor(i, inner_LED_strip.Color(0, 0, 0));
  }
  for (int i = 0; i < OUTER_NUM_LEDS; i++) {
    outer_LED_strip.setPixelColor(i, outer_LED_strip.Color(0, 0, 0));
  }
  inner_LED_strip.show();
  outer_LED_strip.show();
}


//function to get the LED color for each response
uint32_t getLEDColorCode(Adafruit_NeoPixel& strip, int current_response) {
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
        return strip.Color(255, 0, 255);
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

bool compareLED(Adafruit_NeoPixel& strip1, Adafruit_NeoPixel& strip2) {
  return (strip1.numPixels() == strip2.numPixels() && strip1.getPin() == strip2.getPin() && strip1.getBrightness() == strip2.getBrightness());
}
