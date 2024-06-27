#include <Stepper.h>
#include <Servo.h>

//constants
#define STEPS_PER_REV 200  //This is the maximum
#define gear_ratio 1.15    //multiplying by this converts from rotation in degrees from the arm, to rotation in steps of the motor.
#define stepdeg_ratio 4
#define stepper_enable_pin1 11
#define stepper_enable_pin2 12
#define armservo_net_pin 3
#define armservo1_pin 10  //inner puppet ring
#define armservo2_pin 9
#define armservo3_pin 6
#define armservo4_pin 5  //outer puppet ring

//objects
Stepper stepper(STEPS_PER_REV, 2, 4, 7, 8);
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
  pinMode(stepper_enable_pin1, OUTPUT);
  pinMode(stepper_enable_pin2, OUTPUT);
  armservo_net.attach(armservo_net_pin);
  armservo1.attach(armservo1_pin);
  armservo2.attach(armservo2_pin);
  armservo3.attach(armservo3_pin);
  armservo4.attach(armservo4_pin);
  // delay(1000);
  // setArmServo(armservo1,true);
  // delay(1000);
  // setArmServo(armservo2,true);
  // delay(1000);
  // setArmServo(armservo3,true);
  // delay(1000);
  // setArmServo(armservo4,true);
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

void reset_arm() {//called after resetting puppets
  // arm moves to absolute reset location:
  // underneath the static net mast / end of arrest section
  all_down();
  setArmNetServo(false);
  move_arm_to(-acc_start_angle);
}


void move_arm(int degrees) {  //move arm to angle relative to its current position.
  //like stepper.step but keeps track of movement, and converts to degrees.
  int steps = int(degrees * gear_ratio * stepdeg_ratio);
  digitalWrite(stepper_enable_pin1, HIGH);
  digitalWrite(stepper_enable_pin2, HIGH);
  stepper.step(steps);
  delay(300);       //allow for bounce back
  stepper.step(5);  //cancel bounce back
  digitalWrite(stepper_enable_pin1, LOW);
  digitalWrite(stepper_enable_pin2, LOW);
  stepstaken += steps;
}

void move_arm_to(int degrees) {  //move arm to angle relative to the starting position, not 100% sure it works. Can only travel to target through the starting position.
  int absolute_steps = int(degrees * gear_ratio * stepdeg_ratio) - stepstaken;
  stepper.step(absolute_steps);
  delay(300);       //allow for bounce back
  stepper.step(5);  //cancel bounce back
  stepstaken += absolute_steps;
}

void accomodation(int percentage) {
  //go behind puppets, servo's are still down.
  move_arm(percentage);
  //Raise puppets
  all_up();
  move_arm(-percentage);
  //go to next section
  all_down();
  move_arm(percentage);
  delay(3000);
}

void ignore(int percentage) {
  //go behind puppets, servo's are still down.
  move_arm(percentage);
  //Raise puppets
  all_up();
  move_arm(-percentage);
  //go to next section
  all_down();
  move_arm(percentage);
  delay(3000);
}

void disperse(int percentage) {
  //go behind puppets, servo's are still down.
  move_arm(percentage);
  //Raise puppets
  all_up();
  move_arm(-percentage);
  //Drop puppets and go to next section
  move_arm(percentage);
  delay(3000);
}

void arrests(int percentage) {
  //go behind puppets
  all_down();
  move_arm(percentage);
  if(percentage>15){
    //move both masts seperately
    setArmNetServo(true);
    move_arm(-15);
    //switch to other masts
    setArmNetServo(false);
    stepper.step(-5);
    //move other mast
    setArmNetServo(true);
    move_arm(-(percentage-15));
    setArmNetServo(false);
  } else if(percentage>3){
    //move one mast (or both to same place, not sure yet)
    setArmNetServo(true);
    move_arm(-percentage);
    setArmNetServo(false);
  }
  //Raise puppets
  all_up();
  move_arm(-percentage);
  //Drop puppets and go to next section
  move_arm(percentage);
  delay(3000);
}

void violence(int percentage) {
  //go behind puppets
  all_down();
  move_arm(percentage);
  //Raise puppets
  all_up();
  move_arm(-percentage);
  //Drop puppets and go to next section //maybe improve to only drop a few.
  move_arm(percentage);
  delay(3000);
}

void reset_puppets() {//function is called when arm is at end
  all_down();
  move_arm_to(0); // go to start
  all_up();
  setArmNetServo(true);
  move_arm_to(100-get_percentage(5)); //end of arrests section, where the nets should go
  setArmNetServo(false);
  move_arm_to(100); // reset remaining puppets
  reset_arm(); //move down servo's and put arm back in starting position.
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