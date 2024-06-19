/*
THIS IS THE RESPONSE ARDUINO CODE

*/

#include <SoftwareSerial.h>

#define RESPONSE_ARDUINO_RX_PIN 10  //connect to INPUT_ARDUINO_RX_PIN
#define RESPONSE_ARDUINO_TX_PIN 11  //connect to INPUT_ARDUINO_RX_PIN

SoftwareSerial serial_arduino(RESPONSE_ARDUINO_RX_PIN, RESPONSE_ARDUINO_TX_PIN);  // RX, TX pins for communication


//change these variables to match the received information from the table sent from arduino 1.
// int decade = 0; //variable to store the received information from the 
// int region = 0;
// int protest = 0;
bool is_response_running = false;
int current_response_running = 0;//used to switch from one response to the other.

void setup() {
  Serial.begin(9600);
  serial_arduino.begin(9600);
}

void loop() {
  if (is_response_running) {  //the response is running until it gets stop, when it is stop, it starts reading agian
    switch (current_response_running) {
      case 0:
        accomodation();
        break;
      case 1:
        ignore();
        break;
      case 2:
        dispersal();
        break;
      case 3:
        arrest();
        break;
      case 4:
        violence();
        break;
      case 5:
        // default statements

        //when done reset is_response_running to false and the current_response_running to false
        break;
    }
    else {
      get_data();
    }
  }

  void get_data() {
    if (serial_arduino.available()) {
      String receivedString = serial_arduino.readStringUntil('\n');  // Read data until newline character
      Serial.println("Received: " + receivedString);                 // Print received string for debugging

      if (receivedString.startsWith("S:1")) {
        Serial.println("LED toggled!");  // Print message for debugging
      }
    }
  }
