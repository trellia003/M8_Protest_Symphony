void read_data(int region, int decade, int protest) {
  while (data_file.available()) {
    String line = data_file.readStringUntil('\n');
    process_line(line, region, decade, protest);
  }
  data_file.close();
}

void process_line(String line, int region, int decade, int protest) {
  int colIndex = 0;
  int col4 = -1, col5 = -1, col6 = -1, col7 = -1, col8 = -1;
  bool match = true;

  for (int i = 0; i < line.length(); i++) {
    if (line[i] == ',' || i == line.length() - 1) {
      String value = line.substring(0, i);
      line = line.substring(i + 1);
      i = -1; // reset the index to start from the next character

      if (colIndex == 0 && value.toInt() != region) {
        match = false;
        break;
      } else if (colIndex == 1 && value.toInt() != decade) {
        match = false;
        break;
      } else if (colIndex == 2 && value.toInt() != protest) {
        match = false;
        break;
      } else if (colIndex == 3) {
        col4 = value.toInt();
      } else if (colIndex == 4) {
        col5 = value.toInt();
      } else if (colIndex == 5) {
        col6 = value.toInt();
      } else if (colIndex == 6) {
        col7 = value.toInt();
      } else if (colIndex == 7) {
        col8 = value.toInt();
        break;  // No need to continue after the last required column
      }

      colIndex++;
    }
  }

  if (match) {
    accomodate_percent = col4;
    ignore_percent = col5;
    disperse_percent = col6;
    arrest_percent = col7;
    violence_percent = col8;
    
    Serial.print("SD READ: ");
    Serial.print("Accomodate: ");
    Serial.print(accomodate_percent);
    Serial.print(", Ignore: ");
    Serial.print(ignore_percent);
    Serial.print(", Disperse: ");
    Serial.print(disperse_percent);
    Serial.print(", Arrest: ");
    Serial.print(arrest_percent);
    Serial.print(", Violence: ");
    Serial.println(violence_percent);
    
  }
}

void initialize_SD() {
  Serial.println("Initializing SD card...");
  pinMode(DATA_SD_CS_PIN, OUTPUT);

  if (SD.begin()) {
    Serial.println("SD card is ready to use.");
  } else {
    Serial.println("SD card initialization failed");
    return;
  }
}

int open_file(char file_name[]) {
  data_file = SD.open(file_name);
  if (data_file) {
    Serial.println("File opened successfully!");
    return 1;
  } else {
    Serial.println("Error opening file...");
    return 0;
  }
}
