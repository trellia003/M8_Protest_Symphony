// This is a basic script. It should not be included in the final project, but offers the right values for politican servos.

#include <Servo.h>

#define SERVO_POLITICIAN_A_PIN 4
#define SERVO_POLITICIAN_B_PIN 5
#define SERVO_POLITICIAN_C_PIN 6

Servo politicianServo1;
Servo politicianServo2;
Servo politicianServo3;

int servo_spin = 1;

void setup() {
  // The servo control wire is connected to Arduino D2 pin.
  politicianServo1.attach(SERVO_POLITICIAN_A_PIN);
  politicianServo2.attach(SERVO_POLITICIAN_B_PIN);
  politicianServo3.attach(SERVO_POLITICIAN_C_PIN);
}

void loop() {
  while (servo_spin == 1) {
    politicianServo1.write(60);
    politicianServo2.write(60);
    politicianServo3.write(60);
    delay(700);

    politicianServo1.write(90);
    politicianServo2.write(90);
    politicianServo3.write(90);
    delay(1000);

    politicianServo1.write(120);
    politicianServo2.write(120);
    politicianServo3.write(120);
    delay(2000);

    politicianServo1.write(90);
    politicianServo2.write(90);
    politicianServo3.write(90);

    servo_spin = 0;
  }
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
  // myservo.write(63);
  // delay(830);
  // Stationary
  // myservo.write(90);
  // delay(1000);
  // Back
  // myservo.write(122);
  // delay(910);
  // Stationary
  // myservo.write(90);
  // delay(2000);
}