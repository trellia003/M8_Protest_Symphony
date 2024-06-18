#define DECADE_POTENTIOMETER_PIN A0

const int numReadings = 10;
int readings[numReadings]; // Array to store the readings
int readIndex = 0; // The index of the current reading
int total = 0; // The running total
int average = 0; // The average
int decade = 0;

void setup() {
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0; // Initialize all the readings to 0
  }
}

void loop() {
  total = total - readings[readIndex]; // Remove the oldest entry
  readings[readIndex] = analogRead(DECADE_POTENTIOMETER_PIN); // Read from the sensor
  total = total + readings[readIndex]; // Add the newest reading to the total
  readIndex = (readIndex + 1) % numReadings; // Advance to the next position
  average = total / numReadings; // Calculate the average

  
  //Conditions to return decade
  if (120 <= average && average <= 280) {
    decade = 2010;
    Serial.println(decade);
  } else if (360 <= average && average <= 560) {
    decade = 2000;
    Serial.println(decade);
  } else if (660 <= average && average <= 820) {
    decade = 1990;
    Serial.println(decade);
  } else {
    decade = 9999;
    Serial.println(decade);
  }
  
  //Serial.println(average); // Send it to the computer
  delay(1); // Delay in between reads for stability
}
