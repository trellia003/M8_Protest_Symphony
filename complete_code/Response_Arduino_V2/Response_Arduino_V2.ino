

#include <SPI.h>  //SD card reader
#include <SD.h>   //SD card reader


/*
Reader PIN - Arduino Uno PIN - Arduino Mega PIN
-----------------------------------------------
GND        - GND             - GND
VCC        - 5V              - 
MISO*      - 12              - 50
MOSI*      - 11              - 51
SCK *      - 13              - 52
CS         - 10              - 53
*SPI pin
*/
#define DATA_SD_CS_PIN 53  // Change this to the pin used for SD card module



File datasetFile;  //SD card reader




bool is_reset_pressed = false;
int decade_selection_value = 0;
int region_selection_value = 0;
int protest_selection_value = 0;

int accomodation_percentage = 0;
int ignore_percentage = 0;
int dispersal_percentage = 0;
int arrest_percentage = 0;
int violence_percentage = 0;


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  initializeSD();
  openFile("protest.csv");
}

void loop() {
  get_selection_data();
  if (is_reset_pressed) {
    reset_installation();
  } else if (are_all_selection_value_valid()) {
    get_response_percentages();  //this runs every time, but we actually only need it to run when the selection are different from the preious, not a big deal
    Serial.print("selection:" + String(decade_selection_value) + ":" + String(region_selection_value) + ":" + String(protest_selection_value));
    Serial.println("    percentage:" + String(accomodation_percentage) + ":" + String(ignore_percentage) + ":" + String(dispersal_percentage) + ":" + String(arrest_percentage) + ":" + String(violence_percentage));
  }
}
