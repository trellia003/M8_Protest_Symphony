void initializeSD() {
  Serial.println("Initializing SD card...");
  pinMode(DATA_SD_CS_PIN, OUTPUT);

  if (SD.begin()) {
    Serial.println("SD card is ready to use.");
  } else {
    Serial.println("SD card initialization failed");
    return;
  }
}

