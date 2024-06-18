/*
THIS IS THE INPUT ARDUINO CODE

the input arduino code handles all the user input and continuously or every time there is a change,
it sends all the input to the Response arduino, which alwais listen for input, but if it gets triggerred with input play,
it will reproduce the whole animation untill resets itself.
*/

int decade[2] = {5, 0};  //first value is the new, second is the old
int region[2] = {3, 0};  //first value is the new, second is the old
int protest[2] = {1, 0}; //first value is the new, second is the old
bool is_start = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  get_data();   //get all the new values form the sensors
  give_feedback();  //produce sound for the user eg. with a buzzer 
  send_data();  //send all the data to the Response_Arduino
  delay(1000);
}

void get_data() {
  get_decade();
  get_region();
  get_protest();
}

void give_feedback(){
  //if the previous values are different make a buzzer beep
}

void get_decade(){
  //the arduino should change the decade only when in it. should have some value not assigned to the potmeter so that there is a threshold and hysterisis.
}

void get_region(){
  //the arduino should change the region only when in it. should have some value not assigned to the potmeter so that there is a threshold and hysterisis.
  //also check and remove floating points.
}

void get_protest(){
  //get the rfid values
}


void send_data() {
  String output = "S:" + String(is_start) + ",D:" + String(decade[0]) + ",R:" + String(region[0]) + ",P:" + String(protest[0]);
  Serial.println(output);
}