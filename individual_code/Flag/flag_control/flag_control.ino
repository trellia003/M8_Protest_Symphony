#include <Servo.h>

#define FLAG_SERVO_PIN 9
#define FLAG_FAN_PIN 8

Servo flagServo;  // Create a Servo object
int flagRaise = 1; //Signal to raise the flag

enum FlagState {
  RAISE_FLAG,
  FLAG_RAISED,
  LOWER_FLAG,
  FLAG_LOWERED
};

FlagState flagState = RAISE_FLAG; // Start by raising the flag
unsigned long flag_previousMillis = 0; // Stores the last time the flag state was updated

void setup() {
  flagServo.attach(FLAG_SERVO_PIN);  // Attach the ATS90M 360 servo to pin 9
}

void loop() {
  while (flagRaise == 1) {
    flag_servo_control();
    flagRaise = 0; //set to 0 to stop the flag
  }
}

void flag_servo_control() {
  unsigned long flag_currentMillis = millis();

  switch(flagState) {
    case RAISE_FLAG:
      flag_servo.write(180);
      if (flag_currentMillis - flag_previousMillis >= 700) {  // Servo spin time
        flagState = FLAG_RAISED;
        flag_previousMillis = flag_currentMillis;
        flag_servo.write(90);  // Stop the servo
      }
      break;

    case FLAG_RAISED:
      if (currentMillis - flag_previousMillis >= 5000) { // Flag stay up time
        flagState = LOWER_FLAG;
        flag_previousMillis = flag_currentMillis;
      }
      break;

    case LOWER_FLAG:
      flag_servo.write(0);
      if (flag_currentMillis - flag_previousMillis >= 750) {  // Servo spin time
        flagState = FLAG_LOWERED;
        flag_previousMillis = flag_currentMillis;
        flag_servo.write(90);  // Stop the servo
      }
      break;

    case FLAG_LOWERED:
      // Here you can decide what to do next, restart the sequence, or stop.
      // e.g., flagState = RAISE_FLAG; to loop or just do nothing to stop
      break;
  }
}
