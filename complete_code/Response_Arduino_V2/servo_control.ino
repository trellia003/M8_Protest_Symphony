// FLAG SERVO
enum FlagState {
  RAISE_FLAG,
  FLAG_RAISED,
  LOWER_FLAG,
  FLAG_LOWERED
};

FlagState flag_state = RAISE_FLAG;       // Start by raising the flag
unsigned long flag_previousMillis = 0;  // Stores the last time the flag state was updated

void flag_servo_control() {
  unsigned long flag_currentMillis = millis();

  switch(flag_state) {
    case RAISE_FLAG:
      flag_servo.write(180);
      if (flag_currentMillis - flag_previousMillis >= 700) {  // Servo spin time
        flag_state = FLAG_RAISED;
        flag_previousMillis = flag_currentMillis;
        flag_servo.write(90);  // Stop the servo
      }
      break;

    case FLAG_RAISED:
      if (flag_currentMillis - flag_previousMillis >= 5000) { // Flag stay up time
        flag_state = LOWER_FLAG;
        flag_previousMillis = flag_currentMillis;
      }
      break;

    case LOWER_FLAG:
      flag_servo.write(0);
      if (flag_currentMillis - flag_previousMillis >= 750) {  // Servo spin time
        flag_state = FLAG_LOWERED;
        flag_previousMillis = flag_currentMillis;
        flag_servo.write(90);  // Stop the servo
      }
      break;

    case FLAG_LOWERED:
      flag_raise = 0;
      // Here you can decide what to do next, restart the sequence, or stop.
      // e.g., flag_state = RAISE_FLAG; to loop or just do nothing to stop
      break;
  }
}

// POLITICIAN SERVOS
enum PoliticianState {
  MOVE_OUT,
  STOPPED,
  MOVE_IN,
  FINAL_STOP
};

PoliticianState politician_state = MOVE_OUT; // Initial state
unsigned long politician_previousMillis = 0;   // Last time update


void servoControl() {
  unsigned long politician_currentMillis = millis();

  switch (politician_state) {
    case MOVE_OUT:
      politician_servo_1.write(60);
      politician_servo_2.write(60);
      politician_servo_3.write(60);
      if (politician_currentMillis - politician_previousMillis >= 700) {
        politician_state = STOPPED;
        politician_previousMillis = politician_currentMillis;
        // Stop the puppets
        politician_servo_1.write(90);
        politician_servo_2.write(90);
        politician_servo_3.write(90);
      }
      break;

    case STOPPED:
      if (politician_currentMillis - politician_previousMillis >= 1000) {
        politician_state = MOVE_IN;
        politician_previousMillis = politician_currentMillis;
        // Move the puppets back in
        politician_servo_1.write(120);
        politician_servo_2.write(120);
        politician_servo_3.write(120);
      }
      break;

    case MOVE_IN:
      if (politician_currentMillis - politician_previousMillis >= 2000) {
        politician_state = FINAL_STOP;
        politician_previousMillis = politician_currentMillis;
        // Stop the puppets at their original positions
        politician_servo_1.write(90);
        politician_servo_2.write(90);
        politician_servo_3.write(90);
      }
      break;

    case FINAL_STOP:
      politician_spin = 0; // End the operation
      break;
  }
}