#include <SPI.h>
#include <SD.h>

#define DATA_SD_CS_PIN 10  // Change this to the pin used for SD card module

/*
Reader PIN - Arduino PIN
------------------------
GND        - GND
VCC        - 5V
MISO*      - 12
MOSI*      - 11
SCK *      - 13
CS         - 10

*fixed pin

*/

File dataFile;

// Example input values
int region = 1;
int decade = 2;
int protest = 3;

int accomodatePercent = 0;
int ignorePercent = 0;
int dispersePercent = 0;
int arrestPercent = 0;
int violencePercent = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect
  }
  initializeSD();
  openFile("protest.csv");
  //readData(region, decade, protest);
}

void loop() {
  //Nothing
  readData(region, decade, protest);
}

void readData(int region, int decade, int protest) {
  while (dataFile.available()) {
    String line = dataFile.readStringUntil('\n');
    processLine(line, region, decade, protest);
  }
  dataFile.close();
}

void processLine(String line, int region, int decade, int protest) {
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
    accomodatePercent = col4;
    ignorePercent = col5;
    dispersePercent = col6;
    arrestPercent = col7;
    violencePercent = col8;
    
    
    Serial.print("Accomodate: ");
    Serial.print(accomodatePercent);
    Serial.print(", Ignore: ");
    Serial.print(ignorePercent);
    Serial.print(", Disperse: ");
    Serial.print(dispersePercent);
    Serial.print(", Arrest: ");
    Serial.print(arrestPercent);
    Serial.print(", Violence: ");
    Serial.println(violencePercent);
    
  }
}

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
  dataFile = SD.open(filename);
  if (dataFile) {
    Serial.println("File opened successfully!");
    return 1;
  } else {
    Serial.println("Error opening file...");
    return 0;
  }
}
