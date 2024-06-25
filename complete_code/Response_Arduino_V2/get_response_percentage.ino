void get_response_percentages() {
  while (datasetFile.available()) {
    String line = datasetFile.readStringUntil('\n');
    processLine(line);
  }
  datasetFile.close();
}

void processLine(String line) {
  int colIndex = 0;
  int col4 = -1, col5 = -1, col6 = -1, col7 = -1, col8 = -1;
  bool match = true;

  for (int i = 0; i < line.length(); i++) {
    if (line[i] == ',' || i == line.length() - 1) {
      String value = line.substring(0, i);
      line = line.substring(i + 1);
      i = -1;  // reset the index to start from the next character

      if (colIndex == 0 && value.toInt() != region_selection_value) {
        match = false;
        break;
      } else if (colIndex == 1 && value.toInt() != decade_selection_value) {
        match = false;
        break;
      } else if (colIndex == 2 && value.toInt() != protest_selection_value) {
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
    accomodation_percentage = col4;
    ignore_percentage = col5;
    dispersal_percentage = col6;
    arrest_percentage = col7;
    violence_percentage = col8;

    // Serial.print("Accomodate: ");
    // Serial.print(accomodatePercent);
    // Serial.print(", Ignore: ");
    // Serial.print(ignorePercent);
    // Serial.print(", Disperse: ");
    // Serial.print(dispersePercent);
    // Serial.print(", Arrest: ");
    // Serial.print(arrestPercent);
    // Serial.print(", Violence: ");
    // Serial.println(violencePercent);
  }
}