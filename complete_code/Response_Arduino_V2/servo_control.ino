
void raise_flag_servo() {
  //raise
  flag_servo.write(180);
  flag_interval_before_stopping = 1199;
  flag_previous_millis = millis();
  is_flag_raised = true;
}

void stop_flag_servo() {  //needs to be in the response loop ahahah
  // Serial.println("stop servo outer");
  // Serial.println(String(millis()-flag_previous_millis)+"  "+String(flag_interval_before_stopping));
  if (millis() - flag_previous_millis >= flag_interval_before_stopping) {
    //stop
    Serial.println("stop servo iner");
    flag_servo.write(90);
  }
}

void lower_flag_servo() {
  //lower
  flag_servo.write(0);
  flag_interval_before_stopping = 1000;
  flag_previous_millis = millis();
  is_flag_raised = false;
}


// // POLITICIAN SERVOS
// enum PoliticianState {
//   MOVE_OUT,
//   STOPPED,
//   MOVE_IN,
//   FINAL_STOP
// };

// PoliticianState politician_state = MOVE_OUT;  // Initial state
// unsigned long politician_previousMillis = 0;  // Last time update


// void servoControl() {
//   unsigned long politician_currentMillis = millis();

//   switch (politician_state) {
//     case MOVE_OUT:
//       politician_servo_1.write(60);
//       politician_servo_2.write(60);
//       politician_servo_3.write(60);
//       if (politician_currentMillis - politician_previousMillis >= 700) {
//         politician_state = STOPPED;
//         politician_previousMillis = politician_currentMillis;
//         // Stop the puppets
//         politician_servo_1.write(90);
//         politician_servo_2.write(90);
//         politician_servo_3.write(90);
//       }
//       break;

//     case STOPPED:
//       if (politician_currentMillis - politician_previousMillis >= 1000) {
//         politician_state = MOVE_IN;
//         politician_previousMillis = politician_currentMillis;
//         // Move the puppets back in
//         politician_servo_1.write(120);
//         politician_servo_2.write(120);
//         politician_servo_3.write(120);
//       }
//       break;

//     case MOVE_IN:
//       if (politician_currentMillis - politician_previousMillis >= 2000) {
//         politician_state = FINAL_STOP;
//         politician_previousMillis = politician_currentMillis;
//         // Stop the puppets at their original positions
//         politician_servo_1.write(90);
//         politician_servo_2.write(90);
//         politician_servo_3.write(90);
//       }
//       break;

//     case FINAL_STOP:
//       politician_spin = 0;  // End the operation
//       break;
//   }
// }