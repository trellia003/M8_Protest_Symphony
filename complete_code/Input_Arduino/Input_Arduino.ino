/*
THIS IS THE INPUT ARDUINO CODE

the input arduino code handles all the user input and continuously or every time there is a change,
it sends all the input to the Response arduino, which alwais listen for input, but if it gets triggerred with input play,
it will reproduce the whole animation untill resets itself.
*/

#include <SoftwareSerial.h>


#define INPUT_ARDUINO_RX_PIN 10  //connect to RESPONSE_ARDUINO_TX_PIN
#define INPUT_ARDUINO_TX_PIN 11  //connect to RESPONSE_ARDUINO_RX_PIN

SoftwareSerial serial_arduino(INPUT_ARDUINO_RX_PIN, INPUT_ARDUINO_TX_PIN);  // RX, TX pins for communication


int selected_decade[2] = { 0, 0 };        //first value is the new, second is the old
int selected_region[2] = { 0, 0 };        //first value is the new, second is the old
int selected_protest[2] = { 0, 0 };       //first value is the new, second is the old //mapping{0:none, 1:,2;,3:}
bool is_response_start = false;  //this value is used to tell the response arduino whether to start or not


void setup() {
  Serial.begin(9600);          //start the Serial communication
  serial_arduino.begin(9600);  //start SoftwareSerial communication
}

void loop() {
  get_data();               //get all the new values form the sensors
  give_feedback();          //produce sound for the user eg. with a buzzer or led
  convert_input_to_data();  //convert the sensor values to the data in the table
  send_data();              //send all the data to the Response_Arduino
  delay(10);
}

void get_data() {
  get_decade();
  get_region();
  get_protest();
}

void give_feedback() {
  //if the previous values are different make a buzzer beep
}

void get_decade() {
  //the arduino should change the decade only when in it. should have some value not assigned to the potmeter so that there is a threshold and hysterisis.
}

void get_region() {
  //the arduino should change the region only when in it. should have some value not assigned to the potmeter so that there is a threshold and hysterisis.
  //also check and remove floating points.
}

void get_protest() {
  //get the rfid values
}

void convert_input_to_data() {
  //use a table to convert the input to the values of the user to the installation values
}

void send_data() {
  String output = "S:" + String(is_response_start) + ",D:" + String(decade[0]) + ",R:" + String(region[0]) + ",P:" + String(protest[0]);
  Serial.println(output);          // Print to serial for debugging
  serial_arduino.println(output);  // Send the string via SoftwareSerial
}