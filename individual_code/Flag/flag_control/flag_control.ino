#include <Servo.h>

#define FLAG_SERVO_PIN 9
#define FLAG_FAN_PIN 8

Servo flagServo;  // Create a Servo object

void setup() {
  flagServo.attach(FLAG_SERVO_PIN);  // Attach the ATS90M 360 servo to pin 9
  //pinMode(FLAG_FAN_PIN, OUTPUT);  // Set the fan control pin as output
  digitalWrite(FLAG_FAN_PIN, LOW);  // Ensure the fan is off initially
}

void loop() {
  // Stop the servo
  flagServo.write(90);  // 90 degrees (1500 microseconds) stops the servo
  //digitalWrite(FLAG_FAN_PIN, LOW);  // Turn the fan off
  delay(1000);  // Wait for 1 second

  // Rotate servo in one direction - RAISE FLAG
  flagServo.write(180);  // Less than 90 degrees for one direction
  //digitalWrite(FLAG_FAN_PIN, HIGH);  // Ensure the fan is on
  delay(700);  // Servo spin time 

  // Stop the servo - KEEP THE FLAG VISIBLE
  flagServo.write(90);  // Stop the servo
  delay(5000);  // Flag stay up for 5s

  // Rotate servo in the opposite direction - LOWER FLAG
  flagServo.write(0);  // More than 90 degrees for the opposite direction
  //digitalWrite(FLAG_FAN_PIN, LOW);  // Turn the fan off
  delay(750);  // Servo spin time

  // Stop the servo
  flagServo.write(90);  // Stop the servo
  while (true) {
    // Do nothing, effectively stopping the servo indefinitely
  }
}
