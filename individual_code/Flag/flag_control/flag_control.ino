#include <Servo.h>

#define FLAG_SERVO_PIN 9
#define FLAG_FAN_PIN 8

Servo flagServo;  // Create a Servo object
int flagRaise = 1; //Signal to raise the flag

void setup() {
  flagServo.attach(FLAG_SERVO_PIN);  // Attach the ATS90M 360 servo to pin 9
}

void loop() {
  while (flagRaise == 1) {
    // Stop the servo
    flagServo.write(90);  // 90 degrees (1500 microseconds) stops the servo
    delay(1000);  // Wait for 1 second

    // Rotate servo in one direction - RAISE FLAG
    flagServo.write(180);  // Less than 90 degrees for one direction
    delay(700);  // Servo spin time 

    // Stop the servo - KEEP THE FLAG VISIBLE
    flagServo.write(90);  // Stop the servo
    delay(5000);  // Flag stay up for 5s

    // Rotate servo in the opposite direction - LOWER FLAG
    flagServo.write(0);  // More than 90 degrees for the opposite direction
    delay(750);  // Servo spin time

    // Stop the servo
    flagServo.write(90);  // Stop the servo
    
    flagRaise = 0; //set to 0 to stop the flag
  }
}
