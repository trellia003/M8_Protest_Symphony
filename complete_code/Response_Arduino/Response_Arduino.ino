/*
THIS IS THE RESPONSE ARDUINO CODE

*/

#include <SoftwareSerial.h>


#define RESPONSE_ARDUINO_RX_PIN 10  //connect to INPUT_ARDUINO_RX_PIN
#define RESPONSE_ARDUINO_TX_PIN 11  //connect to INPUT_ARDUINO_RX_PIN

SoftwareSerial serial_arduino(RESPONSE_ARDUINO_RX_PIN, RESPONSE_ARDUINO_TX_PIN);  // RX, TX pins for communication

int decade = 0;
int region = 0;
int protest = 0;
bool is_response_running = false;

void setup() {
  Serial.begin(9600);
  serial_arduino.begin(9600);
}

void loop() {
  if (is_response_running) {  //the response is running until it gets stop, when it is stop, it starts reading agian


  } else {
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
