// This is a basic script. It should not be included in the final project, but offers the right values for politican servos.

#include <Servo.h>

Servo politicianServo; 

int initalServoPos = 0;

void setup() {
  // The servo control wire is connected to Arduino D2 pin.
  politicianServo.attach(2);
}

void loop() {
  // // Servo 1
  // // Forward
  // myservo.write(70);
  // delay(800);
  // // Stationary
  // myservo.write(90);
  // delay(1000);
  // // Back
  // myservo.write(115);
  // delay(880);
  // // Stationary
  // myservo.write(90);
  // delay(1000);

  // // Servo 2
  // // Forward
  // myservo.write(65);
  // delay(840);
  // // Stationary
  // myservo.write(90);
  // delay(1000);
  // // Back
  // myservo.write(121);
  // delay(890);
  // // Stationary
  // myservo.write(90);
  // delay(2000);

  // Servo 3
  // Forward
  myservo.write(63);
  delay(830);
  // Stationary
  myservo.write(90);
  delay(1000);
  // Back
  myservo.write(122);
  delay(910);
  // Stationary
  myservo.write(90);
  delay(2000);

}