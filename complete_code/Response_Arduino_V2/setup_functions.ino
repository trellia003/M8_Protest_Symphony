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


int openFile(char filename[]) {
  datasetFile = SD.open(filename);
  if (datasetFile) {
    Serial.println("File opened successfully!");
    return 1;
  } else {
    Serial.println("Error opening file...");
    return 0;
  }
}