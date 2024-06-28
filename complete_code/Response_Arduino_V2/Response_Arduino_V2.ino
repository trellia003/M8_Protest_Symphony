#include <DFRobotDFPlayerMini.h>  //DFplayer
#include <SPI.h>                  //SD card reader
#include <SD.h>                   //SD card reader
#include <Adafruit_NeoPixel.h>    //LED Strip
#include <Servo.h>                //Flag, poltician

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

#define LED_INNER_STRIP_PIN 12
#define LED_OUTER_STRIP_PIN 13


//Number of LEDs of each strip
#define NUM_LEDS_INNER 91
#define NUM_LEDS_OUTER 60


File datasetFile;                                                                              //SD card reader
DFRobotDFPlayerMini audio_player;                                                              //DF Player
Adafruit_NeoPixel inner_LED_strip(NUM_LEDS_INNER, LED_INNER_STRIP_PIN, NEO_GRB + NEO_KHZ800);  //Inner LED Strip
Adafruit_NeoPixel outer_LED_strip(NUM_LEDS_OUTER, LED_OUTER_STRIP_PIN, NEO_GRB + NEO_KHZ800);

Servo flag_servo;  //Flag
Servo politician_servo_1;
Servo politician_servo_2;  //Politicians
Servo politician_servo_3;


bool is_reset_pressed = false;  //check if the reset button is pressed(by reading it from the arduino input)
int decade_selection_value[] = { 0, 0 };
int region_selection_value[] = { 0, 0 };  //first value is the readed one, second value is the one locked during the showcasing of the installation
int protest_selection_value[] = { 0, 0 };

int accomodation_percentage = 0;
int ignore_percentage = 0;
int dispersal_percentage = 0;
int arrest_percentage = 0;
int violence_percentage = 0;

int response_switch_index = 0;  //used to go throught all the different phases of the installations

int percentage_revealed = 0;  //this is not in the reset now

bool is_audio_player_running = false;  //use to see if the audio player is playing an audio at the moment
int current_audio_index = 0;           //used to play multiple different audios in one response


int politician_spin = 1;

int led_strip_threshold = 2;



// POLITICIAN SERVOS
enum PoliticianState {
  MOVE_OUT,
  STOPPED,
  MOVE_IN,
  FINAL_STOP
};
PoliticianState current_state = MOVE_OUT;  // Initial state
unsigned long previousMillis = 0;          // Last time update

bool has_run_once_every_response = false;  //used to raise or lower the flag
unsigned long flag_previous_millis = 0;
int flag_interval_before_stopping = 0;


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial3.begin(9600);
  setup_SD();
  setup_DFPlayer();
  setup_stepper_motor();
  setup_led_strip();
  setup_fog();
  setup_flag();
  setup_politician();
  setup_puppets();
  setup_net();
}



void loop() {

  // Serial.println("saved" + String(decade_selection_value[1]) + String(region_selection_value[1]) + String(protest_selection_value[1]));
  // Serial.println("selection:" + String(decade_selection_value[0]) + ":" + String(region_selection_value[0]) + ":" + String(protest_selection_value[0]));

  get_selection_data();              //alyays listen for new messages and stores them in the index [0] of the decade,region and protest array
  update_is_audio_player_running();  //always update if the audio player is playing something or not
  // Serial.println("player boolean:" + String(is_audio_player_running));
  if (is_reset_pressed) {  //if the reset button is pressed reset
    reset_installation();
  } else if (are_all_saved_selection_valid()) {  //if reset button is not pressed and the saved value are valid, play the response
    // Serial.println("response");
    response();
  } else {  //otherwise if both saved selections and reset buttons are false, we saved the selections
    // Serial.println("saved selections");
    save_selection_values();
  }
  delay(400);
}


void response() {
  if (response_switch_index == 0) {
    Serial.println("case 0");
    get_response_percentages();
    Serial.println("    percentage:" + String(accomodation_percentage) + ":" + String(ignore_percentage) + ":" + String(dispersal_percentage) + ":" + String(arrest_percentage) + ":" + String(violence_percentage));
  } else if (response_switch_index == 1) {
    // Serial.println("case 1");
    confermation_voiceover_sound();
  } else if (response_switch_index == 2 && accomodation_percentage > led_strip_threshold) {
    // Serial.println("case 2");
    accomodate_response();
  } else if (response_switch_index == 3 && ignore_percentage > led_strip_threshold) {
    stop_flag_servo();
    // Serial.println("case 3");
    ignore_response();
  } else if (response_switch_index == 4 && dispersal_percentage > led_strip_threshold) {
    // Serial.println("case 4");
    dispersal_response();
  } else if (response_switch_index == 5 && arrest_percentage > led_strip_threshold) {
    // Serial.println("case 5");
    arrest_response();
  } else if (response_switch_index == 6 && violence_percentage > led_strip_threshold) {
    // Serial.println("case 6");
    violence_response();
  } else {
    Serial.println("fucker, let me be, i'm in standby!");
  }
}