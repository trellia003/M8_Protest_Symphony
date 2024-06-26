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


// void playResponseSound(int response) {
//   bool isPlayerRunning;
//   isPlayerRunning = !digitalRead(BUSY_PIN_DFPLAYER_PIN);
//   if (!isPlayerRunning) {
//     audio_player.playFoler(1, response);
//     Serial.println("response sound played")
//   } else {
//     Serial.println("response sound not played")
//   }
// }

// void playSelectionVoiceOver(int region, int decade, int protest) {
//   // delay(1000);
//   playVoiceOverBegin();
//   // delay(5000);
//   playSelectionRegion(region);
//   // delay(5000);
//   playSelectionDecade(decade);
//   // delay(5000);
//   playSelectionProtest(protest);
// }

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
  // bool isPlayerRunning;
  // isPlayerRunning = !digitalRead(SOUND_CONTROL_PIN);
  // if (!isPlayerRunning) {
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
  // } else {
  //   Serial.println("VO - not region");
  // }
}

void playSelectionDecade() {
  // bool isPlayerRunning;
  // isPlayerRunning = !digitalRead(SOUND_CONTROL_PIN);
  // if (!isPlayerRunning) {
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
  // } else {
  //   Serial.println("VO - not decade");
  // }
}

void playSelectionProtest() {
  // bool isPlayerRunning;
  // isPlayerRunning = !digitalRead(SOUND_CONTROL_PIN);
  // if (!isPlayerRunning) {
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
  // } else {
  //   Serial.println("VO - not protest");
  // }
}