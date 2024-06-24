/*
THIS IS THE RESPONSE ARDUINO CODE

*/

#include <SoftwareSerial.h>
#include <Stepper.h>
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <SD.h>

#define RESPONSE_ARDUINO_RX_PIN 19 //connect to INPUT_ARDUINO_TX_PIN
#define RESPONSE_ARDUINO_TX_PIN 18  //connect to INPUT_ARDUINO_RX_PIN

#define stepper_pin1 1      //revise this later, used to initialize the steppermotor
#define stepper_pin2 2      //revise this later, used to initialize the steppermotor
#define stepper_pin3 3      //revise this later, used to initialize the steppermotor
#define stepper_pin4 4      //revise this later, used to initialize the steppermotor
#define motor_to_arm_ratio  //amount of rotations the motor needs to do one full rotation of the arm

#define STRIP_LED_PIN 6     //might be changed

#define NUM_LEDS 240 //number of LEDs on the strip

#define DATA_SD_CS_PIN 53 //CS pin on the MicroSD reader

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


SoftwareSerial serial_arduino(RESPONSE_ARDUINO_RX_PIN, RESPONSE_ARDUINO_TX_PIN);  // RX, TX pins for communication
Stepper stepper = Stepper(360, stepper_pin1, stepper_pin2, stepper_pin3, stepper_pin4);

Adafruit_NeoPixel strip(NUM_LEDS, STRIP_LED_PIN, NEO_GRB + NEO_KHZ800); // Create an instance of the Adafruit_NeoPixel class

File data_file;  //Create a File object to store all of Protest data 

//change these variables to match the received information from the table sent from arduino 1.
int region = 0;
int decade = 0;
int protest = 0;

int accomodate_percent = 0;
int ignore_percent = 0;
int disperse_percent = 0;
int arrest_percent = 0;
int violence_percent = 0;

int phase = 1;       //Can be 'Selection' (1), 'Response'(2) or 'Reset'(3). Phases go in a loop: Selection->Response->Reset->Selection, and should only ever go to the 'next' phase.
int current_response = 0;         //used to switch from one response to the other.
int percentage_shown = 0;
int stepstaken = 0;               //keeps track of where the stepper motor is

void setup() {
  Serial.begin(9600);
  serial_arduino.begin(9600);
  stepper.setSpeed(300);  //RPM, a high value, because in the code we assume movements are instant.

  strip.begin();
  initialize_SD();
  open_file("protest.csv");
  read_data(region, decade, protest);
}

void loop() {
  strip.clear();
  receive_data(); // triggers phase updates & updates decade,region & demand
  switch (phase) {
    case 1:
      //there is actually no code to be run repeatedly by the response Arduino during the selection phase.
      break;
    case 2:
      show_response();
      break;
    case 3:
      full_reset();
      break;
  }
}

void show_response() {
  Serial.println("Showing response:"+ current_response);  
  int percentage = get_percentage(current_response);
  percentage_shown += percentage;
  if (percentage != 0) {
    switch (current_response) {
      case 0:  //selection voiceover
        selection_voiceover();
        break;
      case 1:
        accomodation(percentage);
        break;
      case 2:
        ignore(percentage);
        break;
      case 3:
        dispersal(percentage);
        break;
      case 4:
        arrest(percentage);
        break;
      case 5:
        violence(percentage);
        break;
      case 6:
        all_responses_on();
        break;
      case 7: //after all responses are shown complete, do nothing
        delay(100);
        break;
    }
  }
  current_response++;
}

void selection_voiceover(){
  //All LED's off
  //Play selection voice over
}

void accomodation(int percentage) {  //should take 5 seconds total
  //add new LED's
  response_LED(current_response, percentage);
  //play new sound
  //Raise flag + flag LEDS
}

void ignore(int percentage) {  //should take 5 seconds total
  //add new LED's
  response_LED(current_response, percentage);
  //play new sound
  //turn around politician
}

void dispersal(int percentage) {  //should take 5 seconds total
  //add new LED's
  response_LED(current_response, percentage);
  //play new sound
  //enable smoke machine
  //drop puppets
}

void arrest(int percentage) {  //should take 5 seconds total
  //add new LED's
  response_LED(current_response, percentage);
  //play new sound
  //move netmast with arm
  //lower net
  //drop puppets
}

void violence(int percentage) {  //should take 5 seconds total
  //add new LED's
  response_LED(current_response, percentage);
  //play shooting sounds timed with (random) puppets dropping
}

void all_responses_on() {  //after all responses are shown, this code runs
  //disable smoke machine
  //let sound fade out
}

void full_reset() {
  // play slow whoop reset sound? (reset volume if necessary)
  // make red LED loading bar while resetting puppets

  // lower flag+(led's) if needed
  // return politicians if needed
  // reset puppets if needed
  // raise net if needed
  // move net mast back if needed

  // microwave ping (?)
  enter_selection_phase();
}

void enter_selection_phase(){
  // set LED rings to white
  // play general protesting sounds
  phase = 1;
}

int get_percentage(int response) { //table colums: region,decade,protest,acc,ign,dis,arr,vio.  Region 1 = Europe, 2 = Asia, 3 = N.A., Protest: 1 = Political, 2 = wages, 3 = Police Brutality
  if (response >= 1 && response <= 5) {
    int percentage = 0;
    switch (response) {
      case 1:
        percentage = accomodate_percent;
        break;
      case 2:
        percentage = ignore_percent;
        break;
      case 3:
        percentage = disperse_percent;
        break;
      case 4:
        percentage = arrest_percent;
        break;
      case 5:
        percentage = violence_percent;
        break;
    }
    return percentage;
  }
  return 0;
}

void receive_data() { //reads selection or reset messages and transitions to the appropriate phase
  if (serial_arduino.available()) {
    String receivedString = serial_arduino.readStringUntil('\n');  // Read data until newline character
    Serial.println("Received: " + receivedString);                 // Print received string for debugging

    // if (receivedString.startsWith("RESPOND") && phase = 1) {
    //   //use message to update decade variable
    //   //use message to update region variable
    //   //use message to update demand variable
    //   phase = 2;
    // }
    // if (receivedString = "RESET" && phase = 2){
    //   phase = 3;
    // }
  }
}
