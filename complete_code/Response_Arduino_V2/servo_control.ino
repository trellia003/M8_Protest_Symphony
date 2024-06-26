
void raise_flag_servo() {
  //raise
  flag_servo.write(180);
  flag_interval_before_stopping = 1199;
  flag_previous_millis = millis();
}

void stop_flag_servo() {
  if (millis() - flag_previous_millis >= flag_interval_before_stopping) {
    //stop
    // Serial.println("stop servo iner");
    flag_servo.write(90);
  }
}

void lower_flag_servo() {
  //lower
  flag_servo.write(0);
  flag_interval_before_stopping = 1000;
  flag_previous_millis = millis();
}



void servoControl() {
  unsigned long currentMillis = millis();

  switch (current_state) {
    case MOVE_OUT:
      move_out(currentMillis);
      break;

    case STOPPED:
      stop(currentMillis);
      break;

    case MOVE_IN:
      move_in(currentMillis);
      break;

    case FINAL_STOP:
      final_stop();
      break;
  }
}

void move_out(unsigned long currentMillis) {
  politician_servo_1.write(40);
  politician_servo_2.write(40);
  politician_servo_3.write(40);
  if (currentMillis - previousMillis >= 1400) {
    current_state = STOPPED;
    previousMillis = currentMillis;
  }
}

void stop(unsigned long currentMillis) {
  politician_servo_1.write(90);
  politician_servo_2.write(90);
  politician_servo_3.write(90);
  if (currentMillis - previousMillis >= 1500) {
    current_state = MOVE_IN;
    previousMillis = currentMillis;
  }
}

void move_in(unsigned long currentMillis) {
  politician_servo_1.write(120);
  politician_servo_2.write(120);
  politician_servo_3.write(120);
  if (currentMillis - previousMillis >= 2000) {
    current_state = FINAL_STOP;
    previousMillis = currentMillis;
  }
}

void final_stop() {
  politician_servo_1.write(90);
  politician_servo_2.write(90);
  politician_servo_3.write(90);
  politician_spin = 0;  // End the operation
  // current_state = MOVE_OUT;
}
