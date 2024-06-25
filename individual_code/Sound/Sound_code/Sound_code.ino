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
  playResponseSound(5);
  //playSelectionVoiceOver(1, 1, 1);
  /*
  delay(5000);
  playTheSound(2);
  delay(5000);
  playTheSound(3);
  delay(5000);
  playTheSound(4);
  delay(5000);
  playTheSound(5);
  delay(5000);
  */
}

int playResponseSound(int response) {
  bool isPlayerRunning;
  isPlayerRunning =! digitalRead(SOUND_CONTROL_PIN);
  if (!isPlayerRunning) {
    switch (response) {
      case 1:          // accomodate
        player.playFolder(1, 1);  
        Serial.println("cheering");
        return 1;
      case 2:         // ignore
        player.playFolder(1, 2); 
        Serial.println("crikets");
        return 1;
      case 3:        // disperse
        player.playFolder(1, 3);
        Serial.println("booing");
        return 1;
      case 4:        // arrest
        player.playFolder(1, 4);
        Serial.println("police"); 
        return 1;
      case 5:       // violence
        player.playFolder(1, 5);
        Serial.println("gunfire");
        return 1;
    }
  } else {
    Serial.println("else");
    return 0;
  }
}

int playSelectionVoiceOver(int region, int decade, int protest) {
  playVoiceOverBegin();
  delay(5000);
  playSelectionRegion(region);
  delay(5000);
  playSelectionDecade(decade);
  delay(5000);
  playSelectionProtest(protest);
}

void playVoiceOverBegin() {
  bool isPlayerRunning;
  isPlayerRunning =! digitalRead(SOUND_CONTROL_PIN);
  if (!isPlayerRunning) {
    player.playFolder(2, 1);
    Serial.println("begin");
  } else {
    Serial.println("not begin");
  }
}

void playSelectionRegion(int region) {
  bool isPlayerRunning;
  isPlayerRunning =! digitalRead(SOUND_CONTROL_PIN);
  if (!isPlayerRunning) {
    switch (region) {
      case 1:
        player.playFolder(2, 11);
        Serial.println("europe");
        break;
      case 2: 
        player.playFolder(2, 12);
        Serial.println("asia");
        break;
      case 3:
        player.playFolder(2, 13);
        Serial.println("na");
        break;
    }
  } else {
    Serial.println("region - else");
  }
}

void playSelectionDecade(int decade) {
  bool isPlayerRunning;
  isPlayerRunning =! digitalRead(SOUND_CONTROL_PIN);
  if (!isPlayerRunning) {
    switch(decade) {
      case 1:
        player.playFolder(2, 21);
        Serial.println("1990");
        break;
      case 2: 
        player.playFolder(2, 22);
        Serial.println("2000");
        break;
      case 3:
        player.playFolder(2, 23);
        Serial.println("2010");
        break;
    }
  } else {
    Serial.println("decade - else");
  }
}

void playSelectionProtest(int protest) {
  bool isPlayerRunning;
  isPlayerRunning =! digitalRead(SOUND_CONTROL_PIN);
  if (!isPlayerRunning) {
    switch(protest) {
      case 1:
        player.playFolder(2, 31);
        Serial.println("political");
        break;
      case 2: 
        player.playFolder(2, 32);
        Serial.println("wage");
        break;
      case 3:
        player.playFolder(2, 33);
        Serial.println("police");
        break;
    }
  } else {
    Serial.println("protest - else");
  }
}