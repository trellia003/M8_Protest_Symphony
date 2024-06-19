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


int selected_decade[2] = { 0, 0 };   //first value is the new, second is the old
int selected_region[2] = { 0, 0 };   //first value is the new, second is the old
int selected_protest[2] = { 0, 0 };  //first value is the new, second is the old //mapping{0:none, 1:,2;,3:}
bool is_response_running = false;    //this value is used to tell the response arduino whether to start or not


void setup() {
  Serial.begin(9600);          //start the Serial communication
  serial_arduino.begin(9600);  //start SoftwareSerial communication
}

void loop() {
  update_selections();
  



  // if(is_selection_updated(){
  //   give_feedback();  //produce sound for the user eg. with a buzzer or led
  //   if (is_response_running) {
  //     send_reset_msg();
  //   }
  // }
  // if (is_selection_valid()) {
  //   send_data();  //send all the data to the Response_Arduino
  // }
  delay(10);
}

















void give_feedback() {
  //if the previous values are different make a buzzer beep
}
bool is_selection_updated() {
  if (selected_decade[0] = selected_decade[1]) return true;
  if (selected_region[0] = selected_region[1]) return true;
  if (selected_protest[0] = selected_protest[1]) return true;
  return false;
}

bool is_selection_valid() {
}

void send_data() {
  //if perceive any change
  // String output = "S:" + String(is_response_start) + ",D:" + String(decade[0]) + ",R:" + String(region[0]) + ",P:" + String(protest[0]);
  //Serial.println(output);          // Print to serial for debugging
  //serial_arduino.println(output);  // Send the string via SoftwareSerial
}