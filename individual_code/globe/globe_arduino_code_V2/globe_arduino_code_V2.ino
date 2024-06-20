/* code for the globe potentiometer for the module 8 project of CreaTe by Jarne Groenewegen
Connect ground of potentiometer to ground and 5v to Vin, wire for data from potmeter should be connected to analog pin, led strip connect data with small resistor  to arduino pin gnd and 5v.
*/
#include <Adafruit_NeoPixel.h>
#define GLOBE_POTMETER_ANALOG_PIN A0
#define GLOBE_LED_PIN 6


const int num_leds = 6;
const int num_measurements_globe_buffer = 15;  //how many measurements we want to make for the value descion
const int threshold_globe = 2;                 //how much difference there can be between the values
int globe_measurements_buffer[num_measurements_globe_buffer];
int pot_value_globe;  // variable that saves the pot data


Adafruit_NeoPixel strip = Adafruit_NeoPixel(num_leds, GLOBE_LED_PIN, NEO_GRB + NEO_KHZ800);  //needed for the led strip

void setup() {
  pinMode(GLOBE_POTMETER_ANALOG_PIN, INPUT);  //pin for potentiometer
  Serial.begin(9600);
}

void loop() {

  country_selected();
}

int country_selected() {

  int total_globe = 0;  // sum of measurements values
  for (int i = 0; i < num_measurements_globe_buffer; i++) {
    pot_value_globe = analogRead(GLOBE_POTMETER_ANALOG_PIN);  //Read and save analog value from potentiometer
    Serial.println(pot_value_globe);
    globe_measurements_buffer[i] = pot_value_globe;
    total_globe = total_globe + pot_value_globe;
    delay(100);
  }
  float average_globe = total_globe / (num_measurements_globe_buffer);
  float deviation_1_globe = globe_measurements_buffer[0] - globe_measurements_buffer[num_measurements_globe_buffer];  // measures the deviation between first and last value
  float deviation_2_globe = globe_measurements_buffer[num_measurements_globe_buffer] - globe_measurements_buffer[0];  // measures the deviation between first and last value

  Serial.println(average_globe);
  Serial.println(deviation_1_globe);
  Serial.println(deviation_2_globe);

  if (deviation_1_globe <= threshold_globe && deviation_1_globe >= 0 || deviation_2_globe <= threshold_globe && deviation_2_globe >= 0) {
    if (average_globe > 100 && average_globe < 200) {  // region 1
      display_led('g');
      return 1;
    } else if (average_globe > 200 && average_globe < 300) {  // region 2
      display_led('g');
      return 2;
    } else if (average_globe > 300 && average_globe < 400) {  // region 3
      display_led('g');
      return 3;
    }
  } else {
    display_led('r');
    return 0;
  }
}

void display_led(char color) {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
switch(color){
  
case 'r':
  // red
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(255, 0, 0));  // Red color
    }
    strip.show();
  
  break;

case 'g':  // green
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 255, 0));  // Green color
    }
    strip.show();
  
  break;
}
}