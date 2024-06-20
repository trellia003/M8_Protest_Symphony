/*
THIS IS THE INPUT ARDUINO CODE
the input arduino code hanles all the user inputs. if there is any change it sends a reset message to the response_arduino.
wheras if the selection is valid and all 3 hands are placed it sends a starting message to the response arduino containing the selections
*/

#include <SoftwareSerial.h>  //arduino communication
#include <SPI.h>             // Include the SPI library for communication RFID
#include <MFRC522.h>         // Include the MFRC522 library for RFID operations RFID


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
#define BILLBOARD_RFID_SDA_PIN 10  // Define the RFID SDA pin
#define BILLBOARD_RFID_RST_PIN 9   // Define the RFID Reset pin

#define INPUT_ARDUINO_RX_PIN 0  //connect to RESPONSE_ARDUINO_TX_PIN
#define INPUT_ARDUINO_TX_PIN 1  //connect to RESPONSE_ARDUINO_RX_PIN



#define BUZZER_DECADE_FEEDBACK_PIN 3
#define BUZZER_REGION_FEEDBACK_PIN 5
#define BUZZER_PROTEST_FEEDBACK_PIN 7

#define LED_DECADE_FEEDBACK_PIN 2
#define LED_REGION_FEEDBACK_PIN 4
#define LED_PROTEST_FEEDBACK_PIN 6


#define DECADE_POTENTIOMETER_PIN A0



SoftwareSerial serial_arduino(INPUT_ARDUINO_RX_PIN, INPUT_ARDUINO_TX_PIN);  // RX, TX pins for communication
MFRC522 billboard_rfid(BILLBOARD_RFID_SDA_PIN, BILLBOARD_RFID_RST_PIN);     // Create MFRC522 instance


int selected_decade[2] = { 0, 0 };   //first value is the new, second is the old
int selected_region[2] = { 0, 0 };   //first value is the new, second is the old
int selected_protest[2] = { 0, 0 };  //first value is the new, second is the old //mapping{0:none, 1:,2;,3:}
// bool is_response_running = false;    //this value is used to tell the response arduino whether to start or not


int decade_potentiomiter_readings[] = { 0, 0, 0 };  // Array to store the readings
int decade_potentiomiter_readIndex = 0;             // The index of the current reading
int decade_potentiomiter_total = 0;                 // The running total
int billboard_RFID_buffer_readings[] = { 0, 0 };    //needed to filter out the ddouble reading(0) of the RFID


void setup() {
  Serial.begin(9600);          //start the Serial communication
  serial_arduino.begin(9600);  //start SoftwareSerial communication
  SPI.begin();                 // Initialize SPI bus RFID
  billboard_rfid.PCD_Init();   // Initialize MFRC522 RFID


  // Initialize buzzer pins as output
  pinMode(BUZZER_DECADE_FEEDBACK_PIN, OUTPUT);
  pinMode(BUZZER_REGION_FEEDBACK_PIN, OUTPUT);
  pinMode(BUZZER_PROTEST_FEEDBACK_PIN, OUTPUT);

  // Initialize LED pins as output
  pinMode(LED_DECADE_FEEDBACK_PIN, OUTPUT);
  pinMode(LED_REGION_FEEDBACK_PIN, OUTPUT);
  pinMode(LED_PROTEST_FEEDBACK_PIN, OUTPUT);
}

void loop() {
  update_selections();                  //the function read all the sensors and update the variables with the new mapped values
  give_feedback_to_user();              //provide feedback to the user with 3 buzzer sound(when a selection is changed) and 3 led (if the selction is correct). 1led and 1 buzzer per input
  communication_to_response_arduino();  //send messages to the response arduino reset=(if a selection is changed) and start=( if the input is valud and the hands are there )
  delay(10);                            //MAYBE INCREASE IT ? FOR BUZZER SOUND AND RFID READING
  // Serial.println("decade:"+String(selected_decade[0])+"   region:"+String(selected_region[0])+"   protest:"+String(selected_protest[0]));
}
