void playResponseSound(int response) {
  bool isPlayerRunning;
  isPlayerRunning = !digitalRead(BUSY_PIN_DFPLAYER_PIN);
  if (!isPlayerRunning) {
    player.playFoler(1, response);
    Serial.println("response sound played")
  } else {
    Serial.println("response sound not played")
  }
}

void playSelectionVoiceOver(int region, int decade, int protest) {
  delay(1000);
  playVoiceOverBegin();
  delay(5000);
  playSelectionRegion(region);
  delay(5000);
  playSelectionDecade(decade);
  delay(5000);
  playSelectionProtest(protest);
}

void playVoiceOverBegin() {
  bool isPlayerRunning;
  isPlayerRunning = !digitalRead(SOUND_CONTROL_PIN);
  if (!isPlayerRunning) {
    player.playFolder(2, 1);
    // Serial.println("VO - begin");
  } else {
    // Serial.println("VO - not begin");
  }
}

void playSelectionRegion(int region) {
  bool isPlayerRunning;
  isPlayerRunning = !digitalRead(SOUND_CONTROL_PIN);
  if (!isPlayerRunning) {
    switch (region) {
      case 1:
        player.playFolder(2, 11);
        // Serial.println("VO - europe");
        break;
      case 2:
        player.playFolder(2, 12);
        // Serial.println("VO - asia");
        break;
      case 3:
        player.playFolder(2, 13);
        // Serial.println("VO - na");
        break;
    }
  } else {
    Serial.println("VO - not region");
  }
}

void playSelectionDecade(int decade) {
  bool isPlayerRunning;
  isPlayerRunning = !digitalRead(SOUND_CONTROL_PIN);
  if (!isPlayerRunning) {
    switch (decade) {
      case 1:
        player.playFolder(2, 21);
        // Serial.println("VO - 1990");
        break;
      case 2:
        player.playFolder(2, 22);
        // Serial.println("VO - 2000");
        break;
      case 3:
        player.playFolder(2, 23);
        // Serial.println("VO - 2010");
        break;
    }
  } else {
    Serial.println("VO - not decade");
  }
}

void playSelectionProtest(int protest) {
  bool isPlayerRunning;
  isPlayerRunning = !digitalRead(SOUND_CONTROL_PIN);
  if (!isPlayerRunning) {
    switch (protest) {
      case 1:
        player.playFolder(2, 31);
        // Serial.println("VO - political");
        break;
      case 2:
        player.playFolder(2, 32);
        // Serial.println("VO - wage");
        break;
      case 3:
        player.playFolder(2, 33);
        // Serial.println("VO - police");
        break;
    }
  } else {
    Serial.println("VO - not protest");
  }
}