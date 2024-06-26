#include <Servo.h>

#define SERVO_POLITICIAN_A_PIN 9
#define SERVO_POLITICIAN_B_PIN 10
#define SERVO_POLITICIAN_C_PIN 11

Servo politicianServo1;
Servo politicianServo2;
Servo politicianServo3;

enum ServoState {
  MOVE_OUT,
  STOPPED,
  MOVE_IN,
  FINAL_STOP
};

ServoState currentState = MOVE_OUT; // Initial state
unsigned long previousMillis = 0;   // Last time update
int servoSpin = 1;

void setup() {
  politicianServo1.attach(SERVO_POLITICIAN_A_PIN);
  politicianServo2.attach(SERVO_POLITICIAN_B_PIN);
  politicianServo3.attach(SERVO_POLITICIAN_C_PIN);
  Serial.begin(9600);
}

void loop() {
  if (servoSpin == 1) {
    servoControl();
  }
}

void servoControl() {
  unsigned long currentMillis = millis();

  switch (currentState) {
    case MOVE_OUT:
      politicianServo1.write(60);
      politicianServo2.write(60);
      politicianServo3.write(60);
      if (currentMillis - previousMillis >= 700) {
        currentState = STOPPED;
        previousMillis = currentMillis;
        // Stop the puppets
        politicianServo1.write(90);
        politicianServo2.write(90);
        politicianServo3.write(90);
      }
      break;

    case STOPPED:
      if (currentMillis - previousMillis >= 1000) {
        currentState = MOVE_IN;
        previousMillis = currentMillis;
        // Move the puppets back in
        politicianServo1.write(120);
        politicianServo2.write(120);
        politicianServo3.write(120);
      }
      break;

    case MOVE_IN:
      if (currentMillis - previousMillis >= 2000) {
        currentState = FINAL_STOP;
        previousMillis = currentMillis;
        // Stop the puppets at their original positions
        politicianServo1.write(90);
        politicianServo2.write(90);
        politicianServo3.write(90);
      }
      break;

    case FINAL_STOP:
      servoSpin = 0; // End the operation
      break;
  }
}
