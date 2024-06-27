#include <Servo.h>

#define FLAG_SERVO_PIN 3
#define FLAG_FAN_PIN 8

Servo flag_servo;   // Create a Servo object
int flagRaise = 1;  //Signal to raise the flag

enum FlagState {
  RAISE_FLAG,
  FLAG_RAISED,
  LOWER_FLAG,
  FLAG_LOWERED
};

FlagState flagState = RAISE_FLAG;       // Start by raising the flag
unsigned long flag_previousMillis = 0;  // Stores the last time the flag state was updated
bool is_flag_raised = false;            //used to raise or lower the flag
unsigned long flag_previous_millis = 0;
int flag_interval_before_stopping = 0;


void raise_flag_servo() {
  //raise
  flag_servo.write(180);
  flag_interval_before_stopping = 700;
  flag_previous_millis = millis();
  is_flag_raised = true;
}

void stop_flag_servo() {  //needs to be in the response loop ahahah
  // Serial.println("stop servo outer");
  // Serial.println(String(millis()) + "  " + String(flag_previous_millis) + "  " + String(flag_interval_before_stopping));
  if (millis() - flag_previous_millis >= flag_interval_before_stopping) {
    //stop
    Serial.println("stop servo iner");
    flag_servo.write(90);
  }
}

void lower_flag_servo() {
  //lower
  flag_servo.write(0);
  flag_interval_before_stopping = 800;
  flag_previous_millis = millis();
  // is_flag_raised = false;
}

void setup() {
  flag_servo.attach(FLAG_SERVO_PIN);  // Attach the ATS90M 360 servo to pin 9
  // delay(80);
  Serial.begin(9600);
  // flag_servo.write(180);
  // delay(800);

  // flag_servo.write(00);
  // delay(1000);

  // flag_servo.write(0);
  // delay(1250);

  // flag_servo.write(90);
  // delay(1000);
}

void loop() {
  // while (flagRaise == 1) {
  //   flag_servo_control();
  //   flagRaise = 0;  //set to 0 to stop the flag
  // }

  stop_flag_servo();
  if (!is_flag_raised) {
    raise_flag_servo();
    Serial.println("raise servo");
  }
  // if (current_audio_index < number_of_audios) {
  //   if (!is_audio_player_running) {
  //     play_response_sound(1);
  //     // flag_servo_control();

  //     current_audio_index++;
  //   }
  // } else if (!is_audio_player_running) {
  //   // lower_flag_servo();
  //   // Serial.println("lower servo");
  //   response_switch_index++;
  //   current_audio_index = 0;
  // // }
  if (millis() > 5000 && millis()<6000) {
    Serial.println("lower");
    lower_flag_servo();
  }
  delay(100);
}

// void flag_servo_control() {
//   unsigned long flag_currentMillis = millis();

//   switch (flagState) {
//     case RAISE_FLAG:
//       flag_servo.write(180);
//       if (flag_currentMillis - flag_previousMillis >= 700) {  // Servo spin time
//         flagState = FLAG_RAISED;
//         flag_previousMillis = flag_currentMillis;
//         flag_servo.write(90);  // Stop the servo
//       }
//       break;

//     case FLAG_RAISED:
//       if (flag_currentMillis - flag_previousMillis >= 5000) {  // Flag stay up time
//         flagState = LOWER_FLAG;
//         flag_previousMillis = flag_currentMillis;
//         flag_servo.write(0);
//       }
//       break;

//     case LOWER_FLAG:

//       if (flag_currentMillis - flag_previousMillis >= 750) {  // Servo spin time
//         flagState = FLAG_LOWERED;
//         flag_previousMillis = flag_currentMillis;
//         flag_servo.write(90);  // Stop the servo
//       }
//       break;

//     case FLAG_LOWERED:
//       // Here you can decide what to do next, restart the sequence, or stop.
//       // e.g., flagState = RAISE_FLAG; to loop or just do nothing to stop
//       break;
//   }
// }
