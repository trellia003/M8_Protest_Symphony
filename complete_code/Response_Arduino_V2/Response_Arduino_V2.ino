

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




bool is_reset_pressed = false;  //check if the reset button is pressed
int decade_selection_value[] = { 0, 0 };
int region_selection_value[] = { 0, 0 }; //not sure about the array , maybe only simply int
int protest_selection_value[] = { 0, 0 };

int accomodation_percentage = 0;
int ignore_percentage = 0;
int dispersal_percentage = 0;
int arrest_percentage = 0;
int violence_percentage = 0;

int response_switch_index = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  initializeSD();
}

void loop() {
  get_selection_data();

  // if (are_all_selection_value_valid() && is_any_selection_different()) {
  //   get_response_percentages();
  //   Serial.print("selection:" + String(decade_selection_value[0]) + ":" + String(region_selection_value[0]) + ":" + String(protest_selection_value[0]));
  //   Serial.println("    percentage:" + String(accomodation_percentage) + ":" + String(ignore_percentage) + ":" + String(dispersal_percentage) + ":" + String(arrest_percentage) + ":" + String(violence_percentage));
  // }

  if (is_reset_pressed) {
    reset_installation();
  } else if (are_all_selection_valid()) {
    switch (response_switch_index) {
      case 0:
        get_response_percentages();
        Serial.print("selection:" + String(decade_selection_value[0]) + ":" + String(region_selection_value[0]) + ":" + String(protest_selection_value[0]));
        Serial.println("    percentage:" + String(accomodation_percentage) + ":" + String(ignore_percentage) + ":" + String(dispersal_percentage) + ":" + String(arrest_percentage) + ":" + String(violence_percentage));
        response_switch_index++;
        break;
      case 1:
        //accomodate
        break;
      case 2:
        //ignore
        break;
      case 3:
        //disperse
        break;
      case 4:
        //arrest
        break;
      case 5:
        // violence
        break;
    }
  }
  delay(10);
}
