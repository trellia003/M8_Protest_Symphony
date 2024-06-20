/* code for the module 8 project to check if the hand is place on the LDR, made by Jarne Groenewegen CreaTe
Connect the LDR in a voltage divider circuit with 10k ohm resistor, threshold values should be changed for the different LDRs as they are physical components with different values
     5V
      |
      |
     (/) LDR
      |
      |---- Arduino Connection
      |
     [ ] 10kΩ
      |
     GND
*/
#define HANDSELECT_LDR_ANALOG_Pin1 A1
#define HANDSELECT_LDR_ANALOG_Pin2 A2
#define HANDSELECT_LDR_ANALOG_Pin3 A3
int LDR_threshold1 = 300;  // different LDRS have different threshold for when it is dark, real values need to be checked when LDRs are installed
int LDR_threshold2 = 600;
int LDR_threshold3 = 400;
bool system_triggerd;


void setup() {

  pinMode(HANDSELECT_LDR_ANALOG_Pin1, INPUT);
  pinMode(HANDSELECT_LDR_ANALOG_Pin2, INPUT);
  pinMode(HANDSELECT_LDR_ANALOG_Pin3, INPUT);

  Serial.begin(9600);
}

void loop() {

  hands_activated();
  delay(1000);
}

boolean hands_activated() {

  //value parameters and reading of value
  int LDR_value1, LDR_value2, LDR_value3;
  LDR_value1 = analogRead(HANDSELECT_LDR_ANALOG_Pin1);
  LDR_value2 = analogRead(HANDSELECT_LDR_ANALOG_Pin2);
  LDR_value3 = analogRead(HANDSELECT_LDR_ANALOG_Pin3);

 //print values of LDR
  // Serial.print(LDR_value1);
  // Serial.print(",");
  // Serial.print(LDR_value2);
  // Serial.print(",");
  // Serial.println(LDR_value3);
  // delay(1000);

  //checks if light level is below threshold and therefore hand placed
  if (LDR_value1 <= LDR_threshold1 && LDR_value2 <= LDR_threshold2 && LDR_value3 <= LDR_threshold3) {
    Serial.println("Hands activated");
    return true;
  } else {
    Serial.println("Not all hands active");
    return false;
  }
 
}
