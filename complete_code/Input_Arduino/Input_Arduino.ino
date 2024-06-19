/*
THIS IS THE INPUT ARDUINO CODE
the input arduino code hanles all the user inputs. if there is any change it sends a reset message to the response_arduino.
wheras if the selection is valid and all 3 hands are placed it sends a starting message to the response arduino containing the selections
*/

#include <SoftwareSerial.h>



/*
 * Uses MIFARE RFID card using RFID-RC522 reader
 * Uses MFRC522 - Library
 * --------------------------------------
 *             Reader/PCD   Uno/101       
 * Signal      Pin          Pin          
 * --------------------------------------
 * RST/Reset   RST          9            
 * SPI SS      SDA(SS)      10           
 * SPI MOSI    MOSI         11 / ICSP-4   
 * SPI MISO    MISO         12 / ICSP-1   
 * SPI SCK     SCK          13 / ICSP-3   
 */
#define INPUT_ARDUINO_RX_PIN 10  //connect to RESPONSE_ARDUINO_TX_PIN
#define INPUT_ARDUINO_TX_PIN 11  //connect to RESPONSE_ARDUINO_RX_PIN
#define BUZZER_DECADE_FEEDBACK_PIN 
#define BUZZER_REGION_FEEDBACK_PIN
#define BUZZER_PROTEST_FEEDBACK_PIN
#define LED_DECADE_FEEDBACK_PIN
#define LED_REGION_FEEDBACK_PIN
#define LED_PROTEST_FEEDBACK_PIN

SoftwareSerial serial_arduino(INPUT_ARDUINO_RX_PIN, INPUT_ARDUINO_TX_PIN);  // RX, TX pins for communication


int selected_decade[2] = { 0, 0 };   //first value is the new, second is the old
int selected_region[2] = { 0, 0 };   //first value is the new, second is the old
int selected_protest[2] = { 0, 0 };  //first value is the new, second is the old //mapping{0:none, 1:,2;,3:}
// bool is_response_running = false;    //this value is used to tell the response arduino whether to start or not


void setup() {
  Serial.begin(9600);          //start the Serial communication
  serial_arduino.begin(9600);  //start SoftwareSerial communication
}

void loop() {
  update_selections();                  //the function read all the sensors and update the variables with the new mapped values
  give_feedback_to_user();              //provide feedback to the user with 3 buzzer sound(when a selection is changed) and 3 led (if the selction is correct). 1led and 1 buzzer per input
  communication_to_response_arduino();  //send messages to the response arduino reset=(if a selection is changed) and start=( if the input is valud and the hands are there )
  delay(10);                            //MAYBE INCREASE IT ? FOR BUZZER SOUND AND RFID READING
}
