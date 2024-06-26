

#include <SPI.h>  //SD card reader
#include <SD.h>   //SD card reader
#include <Adafruit_NeoPixel.h> //LED Strip


/*
Reader PIN - Arduino Uno PIN - Arduino Mega PIN
-----------------------------------------------
GND        - GND             - GND
VCC        - 5V              - 
MISO*      - 12              - 50
MOSI*      - 11              - 51
SCK *      - 13              - 52
CS         - 10              - 53
*SPI pin
*/
#define DATA_SD_CS_PIN 53  // Change this to the pin used for SD card module

#define BUSY_PIN_DFPLAYER_PIN 47  //busy pin of the dfplayer to check if the sound is playing

#define LED_INNER_STRIP_PIN 43
#define LED_OUTER_STRIP_PIN 42

#define STEPPER_MOTOR_ENA_PIN 39
#define STEPPER_MOTOR_IN1_PIN 37
#define STEPPER_MOTOR_IN2_PIN 35
#define STEPPER_MOTOR_IN3_PIN 33
#define STEPPER_MOTOR_IN4_PIN 31
#define STEPPER_MOTOR_ENB_PIN 29

#define FOG_PIN 2

#define SERVO_FLAG_PIN 3
#define SERVO_POLITICIAN_A_PIN 4
#define SERVO_POLITICIAN_B_PIN 5
#define SERVO_POLITICIAN_C_PIN 6

//CONVENTION: 1 IS THE INNER SERVO(smaller circle) AND 4 IS THE OUTER(bigger circle)
#define SERVO_PUPPETS_1_PIN 7
#define SERVO_PUPPETS_2_PIN 8
#define SERVO_PUPPETS_3_PIN 9
#define SERVO_PUPPETS_4_PIN 10

#define SERVO_NET_PIN 11

//Number of LEDs of each strip
#define NUM_LEDS_INNER 240
#define NUM_LEDS_OUTER 


File datasetFile;  //SD card reader
DFRobotDFPlayerMini audio_player;  //DF Player
Adafruit_NeoPixel inner_LED_strip(NUM_LEDS_INNER, LED_INNER_STRIP_PIN, NEO_GRB + NEO_KHZ800); //Inner LED Strip



bool is_reset_pressed = false;  //check if the reset button is pressed
int decade_selection_value[] = { 0, 0 };
int region_selection_value[] = { 0, 0 };  //not sure about the array , maybe only simply int
int protest_selection_value[] = { 0, 0 };

int accomodation_percentage = 0;
int ignore_percentage = 0;
int dispersal_percentage = 0;
int arrest_percentage = 0;
int violence_percentage = 0;

int response_switch_index = 0;

int percentage_revealed = 0;


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  setup_SD();
  setup_DFPlayer();
  setup_led_strips();
  setup_stepper_motor();
  setup_fog();
  setup_flag();
  setup_politician();
  setup_puppets();
  setup_net();
}



void loop() {
  get_selection_data();
  if (is_reset_pressed) {
    reset_installation();
  } else if (are_all_selection_valid()) {
    switch (response_switch_index) {
      case 0:
        get_response_percentages();
        Serial.print("selection:" + String(decade_selection_value[0]) + ":" + String(region_selection_value[0]) + ":" + String(protest_selection_value[0]));
        Serial.println("    percentage:" + String(accomodation_percentage) + ":" + String(ignore_percentage) + ":" + String(dispersal_percentage) + ":" + String(arrest_percentage) + ":" + String(violence_percentage));
        response_switch_index++;
        break;
      case 1:
        //accomodate
        break;
      case 2:
        //ignore
        break;
      case 3:
        //disperse
        break;
      case 4:
        //arrest
        break;
      case 5:
        // violence
        break;
    }
  }
  delay(10);
}
