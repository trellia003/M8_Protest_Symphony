//Code for Arduino for sound for M8 Project
// Unit 01022024-13022024-0x6A-0x67
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"


#define SOUND_DFP_TX_PIN 11   // Digital 11  connected with 1k ohm to pin 2 DFPlayer
#define SOUND_DFP_RX_PIN 10   // Digital 10  connected to pin 3 of DFPlayer
#define SOUND_CONTROL_PIN 12  // used to check if the dfplayer is running


SoftwareSerial softwareSerial(SOUND_DFP_RX_PIN, SOUND_DFP_TX_PIN);

// Create the Player object
DFRobotDFPlayerMini player;
void printDetail(uint8_t type, int value);




void setup() {
  pinMode(SOUND_CONTROL_PIN, INPUT);
  Serial.begin(9600);
  softwareSerial.begin(9600);
  if (player.begin(softwareSerial)) {
    player.volume(30);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() {


  delay(3000);
  playTheSound('v');
  delay(7000);
  playTheSound('u');
}

int playTheSound(char sound) {
  bool isPlayerRunning;
  isPlayerRunning =! digitalRead(SOUND_CONTROL_PIN);
  if (!isPlayerRunning) {
    switch (sound) {
      case 'v':          // violence
        player.play(1);  // for example
        //Serial.println("playing1");
        return 1;

      case 'u':          // violence
        player.play(2);  // for example
        //Serial.println("playing2");
        return 1;
    }

  } else {
    Serial.println("else");
    return 0;
  }
}
