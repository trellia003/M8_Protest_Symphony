
void play_selection_voiceover() {
  switch (current_audio_index) {
    case 0:
      playVoiceOverBegin();
      break;
    case 1:
      playSelectionRegion();
      break;
    case 2:
      playSelectionDecade();
      break;
    case 3:
      playSelectionProtest();
      break;
  }
}

void playVoiceOverBegin() {
  // bool isPlayerRunning;
  // isPlayerRunning = !digitalRead(SOUND_CONTROL_PIN);
  // if (!isPlayerRunning) {
  audio_player.playFolder(2, 1);
  // Serial.println("VO - begin");
  // } else {
  //   // Serial.println("VO - not begin");
  // }
}

void playSelectionRegion() {
  switch (region_selection_value[0]) {
    case 1:
      audio_player.playFolder(2, 11);
      // Serial.println("VO - europe");
      break;
    case 2:
      audio_player.playFolder(2, 12);
      // Serial.println("VO - asia");
      break;
    case 3:
      audio_player.playFolder(2, 13);
      // Serial.println("VO - na");
      break;
  }
}

void playSelectionDecade() {
  switch (decade_selection_value[0]) {
    case 1:
      audio_player.playFolder(2, 21);
      // Serial.println("VO - 1990");
      break;
    case 2:
      audio_player.playFolder(2, 22);
      // Serial.println("VO - 2000");
      break;
    case 3:
      audio_player.playFolder(2, 23);
      // Serial.println("VO - 2010");
      break;
  }
}

void playSelectionProtest() {
  switch (protest_selection_value[0]) {
    case 1:
      audio_player.playFolder(2, 31);
      // Serial.println("VO - political");
      break;
    case 2:
      audio_player.playFolder(2, 32);
      // Serial.println("VO - wage");
      break;
    case 3:
      audio_player.playFolder(2, 33);
      // Serial.println("VO - police");
      break;
  }
}

void play_response_sound(int value) {
  Serial.println("jo");
  if (!is_audio_player_running) {
    audio_player.playFolder(1, value);
    Serial.println("response sound played");
  }
}
