void setup_SD() {
  Serial.println("Initializing SD card...");
  pinMode(DATA_SD_CS_PIN, OUTPUT);

  if (SD.begin()) {
    Serial.println("SD card is ready to use.");
  } else {
    Serial.println("SD card initialization failed");
    return;
  }
}

void setup_DFPlayer() {
  pinMode(BUSY_PIN_DFPLAYER_PIN, INPUT);
  Serial2.begin(9600);
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!audio_player.begin(Serial2)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("DFplayer Unable to begin:"));
  } else {
    Serial.println(F("DFPlayer Mini online."));
  }
  audio_player.volume(24);  //Set volume value. From 0 to 30
}

void setup_stepper_motor() {
  pinMode(STEPPER_MOTOR_ENA_PIN, OUTPUT);
  pinMode(STEPPER_MOTOR_IN1_PIN, OUTPUT);
  pinMode(STEPPER_MOTOR_IN2_PIN, OUTPUT);
  pinMode(STEPPER_MOTOR_IN3_PIN, OUTPUT);
  pinMode(STEPPER_MOTOR_IN4_PIN, OUTPUT);
  pinMode(STEPPER_MOTOR_ENB_PIN, OUTPUT);
}

void setup_fog() {
  pinMode(FOG_PIN, OUTPUT);
}

void setup_led_strip() {
  inner_LED_strip.begin();
  outer_LED_strip.begin();
}
void setup_flag() {
  flag_servo.attach(SERVO_FLAG_PIN);
  flag_servo.write(90);
}

void setup_politician() {
  politician_servo_1.attach(SERVO_POLITICIAN_A_PIN);
  politician_servo_2.attach(SERVO_POLITICIAN_B_PIN);
  politician_servo_3.attach(SERVO_POLITICIAN_C_PIN);
}

void setup_puppets() {
  pinMode(SERVO_PUPPETS_1_PIN, OUTPUT);
  pinMode(SERVO_PUPPETS_2_PIN, OUTPUT);
  pinMode(SERVO_PUPPETS_3_PIN, OUTPUT);
  pinMode(SERVO_PUPPETS_4_PIN, OUTPUT);
}

void setup_net() {
  pinMode(SERVO_NET_PIN, OUTPUT);
}
