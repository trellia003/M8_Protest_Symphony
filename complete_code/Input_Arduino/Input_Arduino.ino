/*
THIS IS THE INPUT ARDUINO CODE
the input arduino code hanles all the user inputs. if there is a valid change in any selection it sends a reset message to the response_arduino.
wheras if the selection is valid and all 3 hands are placed it sends a starting message to the response arduino containing the selections
*/

#include <SPI.h>                // Include the SPI library for communication RFID
#include <MFRC522.h>            // Include the MFRC522 library for RFID operations RFID
#include <Adafruit_NeoPixel.h>  //led globe strip

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


/* 
Connect the buzzer and LED as follow

Digital pin arduino
  |
  |
 (/) 270ohm
  |
  |
  |
 [ ] buzzer or led
  |
 GND
*/
#define BUZZER_DECADE_FEEDBACK_PIN 3
#define BUZZER_REGION_FEEDBACK_PIN 7
#define BUZZER_PROTEST_FEEDBACK_PIN 5

#define LED_DECADE_FEEDBACK_PIN 2
#define LED_REGION_FEEDBACK_PIN 6
#define LED_PROTEST_FEEDBACK_PIN 4


#define DECADE_POTENTIOMETER_PIN A0

/* code for the module 8 project to check if the hand is place on the LDR, made by Jarne Groenewegen CreaTe
Connect the LDR in a voltage divider circuit with 10k ohm resistor, threshold values should be changed for the different LDRs as they are physical components with different values
     5V
      |
      |
     (/) LDR
      |
      |---- Arduino Connection
      |
     [ ] 10kΩ
      |
     GND
*/
#define HANDSELECT_LDR_ANALOG_Pin1 A1
#define HANDSELECT_LDR_ANALOG_Pin2 A2
#define HANDSELECT_LDR_ANALOG_Pin3 A3


/*
arduino
    |
  510 omh
    |
LED connection 
*/
#define GLOBE_LED_STRIP_PIN 8  //uses a 510 omh between arduino and connection
#define GLOBE_POTMETER_ANALOG_PIN A4
#define GLOBE_LED_QUANTITY 6


#define RESET_BUTTON_PIN A5

MFRC522 billboard_rfid(BILLBOARD_RFID_SDA_PIN, BILLBOARD_RFID_RST_PIN);                                // Create MFRC522 instance
Adafruit_NeoPixel strip = Adafruit_NeoPixel(GLOBE_LED_QUANTITY, GLOBE_LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);  //needed for the led strip


int selected_decade[2] = { 0, 0 };   //first value is the new, second is the old
int selected_region[2] = { 0, 0 };   //first value is the new, second is the old
int selected_protest[2] = { 0, 0 };  //first value is the new, second is the old //mapping{0:none, 1:,2;,3:}


int decade_potentiomiter_readings[] = { 0, 0, 0 };  // Array to store the readings
int decade_potentiomiter_readIndex = 0;             // The index of the current reading
int decade_potentiomiter_total = 0;                 // The running total

int billboard_RFID_buffer_readings[] = { 0, 0 };  //needed to filter out the ddouble reading(0) of the RFID

const int num_measurements_globe_buffer = 15;                  //how many measurements we want to make for the value descion
const int threshold_globe = 2;                                 //how much difference there can be between the values
int globe_measurements_buffer[num_measurements_globe_buffer];  //initialize the buffer
int pot_value_globe;                                           // variable that saves the pot data


void setup() {
  Serial1.begin(9600);          //start the Serial communication
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

  //initialize LDR pins as input
  pinMode(HANDSELECT_LDR_ANALOG_Pin1, INPUT);
  pinMode(HANDSELECT_LDR_ANALOG_Pin2, INPUT);
  pinMode(HANDSELECT_LDR_ANALOG_Pin3, INPUT);

  //GLOBE LED
  pinMode(GLOBE_POTMETER_ANALOG_PIN, INPUT);  //pin for potentiometer

  //reset button
  pinMode(RESET_BUTTON_PIN, INPUT); // Set the button pin as input
}

void loop() {
  update_selections();                  //the function read all the sensors and update the variables with the new mapped values
  give_feedback_to_user();              //provide feedback to the user with 3 buzzer sound(when a selection is changed) and 3 led (if the selction is correct). 1led and 1 buzzer per input
  communication_to_response_arduino();  //send messages to the response arduino reset=(if a selection is changed) and start=( if the input is valud and the hands are there )
  delay(10);                            //MAYBE INCREASE IT ? FOR BUZZER SOUND AND RFID READING
}
