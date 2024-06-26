void flag_servo_control() {
  //Raise the flag
  flag_servo.write(180); //More then 90 degree to raise the flag
  delay(700);            //Servo spin time

  // Stop the servo - KEEP THE FLAG VISIBLE
  flag_servo.write(90);  // Stop the servo
  delay(5000);           // Flag stay up for 5s

  //Lower flag
  flag_servo.write(0);  // Less than 90 degrees to lower the flag
  delay(750);           // Servo spin time

  //Stop the servo
  flag_servo.write(90);
}