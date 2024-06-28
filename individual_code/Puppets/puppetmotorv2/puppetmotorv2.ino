#include <Stepper.h>
#include <Servo.h>

//constants
#define STEPS_PER_REV 200  //This is the maximum
#define gear_ratio 1.15    //multiplying by this converts from rotation in degrees from the arm, to rotation in steps of the motor.
#define stepdeg_ratio 4
#define STEPPER_MOTOR_ENA_PIN 11
#define STEPPER_MOTOR_ENB_PIN 12
#define SERVO_NET_PIN 3
#define SERVO_PUPPETS_1_PIN 10  //inner puppet ring
#define SERVO_PUPPETS_2_PIN 9
#define SERVO_PUPPETS_3_PIN 6
#define SERVO_PUPPETS_4_PIN 5  //outer puppet ring

//objects
Stepper stepper(STEPS_PER_REV, STEPPER_MOTOR_IN1_PIN, STEPPER_MOTOR_IN2_PIN, STEPPER_MOTOR_IN3_PIN, STEPPER_MOTOR_IN4_PIN);
Servo armservo_net;
Servo armservo1;
Servo armservo2;
Servo armservo3;
Servo armservo4;

//basic variables
int stepstaken = 0;   //tracks movement relative to
int acc_start_angle;  //starting location/angle of the response reveals(accomodation), relative to the static net mast.

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(40);
  pinMode(STEPPER_MOTOR_ENA_PIN, OUTPUT);
  pinMode(STEPPER_MOTOR_ENB_PIN, OUTPUT);
  armservo_net.attach(SERVO_NET_PIN);
  armservo1.attach(SERVO_PUPPETS_1_PIN);
  armservo2.attach(SERVO_PUPPETS_2_PIN);
  armservo3.attach(SERVO_PUPPETS_3_PIN);
  armservo4.attach(SERVO_PUPPETS_4_PIN);
  delay(5000);
  setArmNetServo(false);
  all_up();
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil("\n");
    Serial.print("moving by: ");
    Serial.println(msg.toInt());
    float step_with_gear_ratio = msg.toFloat() * gear_ratio * stepdeg_ratio;

    if (step_with_gear_ratio > 1000) {
      int response = 1;
      Serial.println("Acc");
      accomodation(get_percentage(response));
      response++;
      Serial.println("Ign");
      ignore(get_percentage(response));
      response++;
      Serial.println("Dis");
      disperse(get_percentage(response));
      response++;
      Serial.println("Arr");
      arrests(get_percentage(response));
      response++;
      Serial.println("Vio");
      violence(get_percentage(response));
      //Here would be the Standby phase
      reset_puppets();
    } else {
      move_arm(msg.toInt());
    }
  }
}

void prepare_response() {
  //calculates the starting location of the response, and adjusts LEDS and arm.
  //The response reveals go clockwise so the starting position is:
  //the end of arrests(which is fixed) + the size of the violence section.
  acc_start_angle = get_percentage(5);
  move_arm(acc_start_angle);
  stepstaken = 0;
  //shift LED's here
}

void reset_arm() {  //called after resetting puppets
  // arm moves to absolute reset location:
  // underneath the static net mast / end of arrest section
  all_down();
  setArmNetServo(false);
  move_arm_to(-acc_start_angle);
}


void move_arm(int degrees) {  //move arm to angle relative to its current position.
  //like stepper.step but keeps track of movement, and converts to degrees.
  int steps = int(degrees * gear_ratio * stepdeg_ratio);
  digitalWrite(STEPPER_MOTOR_ENA_PIN, HIGH);
  digitalWrite(STEPPER_MOTOR_ENB_PIN, HIGH);
  stepper.step(steps);
  delay(300);       //allow for bounce back
  stepper.step(5);  //cancel bounce back
  digitalWrite(STEPPER_MOTOR_ENA_PIN, LOW);
  digitalWrite(STEPPER_MOTOR_ENB_PIN, LOW);
  stepstaken += steps;
}

void move_arm_to(int degrees) {  //move arm to angle relative to the starting position, not 100% sure it works. Can only travel to target through the starting position.
  int absolute_steps = int(degrees * gear_ratio * stepdeg_ratio) - stepstaken;
  digitalWrite(STEPPER_MOTOR_ENA_PIN, HIGH);
  digitalWrite(STEPPER_MOTOR_ENB_PIN, HIGH);
  stepper.step(absolute_steps);
  digitalWrite(STEPPER_MOTOR_ENA_PIN, LOW);
  digitalWrite(STEPPER_MOTOR_ENB_PIN, LOW);
  delay(300);       //allow for bounce back
  stepper.step(5);  //cancel bounce back
  stepstaken += absolute_steps;
}

void arm_accomodation(int percentage) {
  all_up();
  move_arm(percentage);
}

void arm_ignore(int percentage) {
  move_arm(percentage);
}

void arm_disperse(int percentage) {
  all_up();
  move_arm(-percentage);
}

void arm_arrests(int percentage) {
  move_arm(-percentage);
}

void arm_violence(int percentage) {
  move_arm(percentage);
}

void reset_puppets() {  //function is called when arm is at end
  all_down();
  move_arm_to(0);  // go to start
  all_up();
  setArmNetServo(true);
  move_arm_to(100 - get_percentage(5));  //end of arrests section, where the nets should go
  setArmNetServo(false);
  move_arm_to(100);  // reset remaining puppets
  reset_arm();       //move down servo's and put arm back in starting position.
}

int get_percentage(int response) {
  switch (response) {
    case 1: return 35;
    case 2: return 10;
    case 3: return 20;
    case 4: return 30;
    case 5: return 5;
  }
}

void all_down() {
  setArmServo(armservo1, false);
  setArmServo(armservo2, false);
  setArmServo(armservo3, false);
  setArmServo(armservo4, false);
}

void all_up() {
  setArmServo(armservo1, true);
  setArmServo(armservo2, true);
  setArmServo(armservo3, true);
  setArmServo(armservo4, true);
}

void setArmServo(Servo servo, bool status) {  //True = up, False = down
  if (status) {
    servo.write(180);
  } else
    servo.write(80);
  delay(200);  //necessary
}

void setArmNetServo(bool status) {
  Serial.print("what");
  if (status) {
    armservo_net.write(0);
  } else {
    armservo_net.write(120);
  }
  delay(200);
}