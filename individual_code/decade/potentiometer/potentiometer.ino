#define DECADE_POTENTIOMETER_PIN A0

int decade_potentiomiter_readings[] = { 0, 0, 0 };  // Array to store the readings
int decade_potentiomiter_readIndex = 0;           // The index of the current reading
int decade_potentiomiter_total = 0;               // The running total



void setup() {
  Serial.begin(9600);
  // for (int thisReading = 0; thisReading < numReadings; thisReading++) {
  //   readings[thisReading] = 0; // Initialize all the readings to 0
  // }
}

void loop() {
  // updatePotentioReadings();
  //Conditions to return decade
  // getDecade(average);
  Serial.println(updatePotentioReadings());  // Send it to the computer
  delay(1);                // Delay in between reads for stability
}

int updatePotentioReadings() {
  int average = 0;  // The average
  int arrayLength = sizeof(decade_potentiomiter_readings) / sizeof(decade_potentiomiter_readings[0]);
  decade_potentiomiter_total -=  decade_potentiomiter_readings[decade_potentiomiter_readIndex];                         // Remove the oldest entry
  decade_potentiomiter_readings[decade_potentiomiter_readIndex] = analogRead(DECADE_POTENTIOMETER_PIN);  // Read from the sensor
  decade_potentiomiter_total += decade_potentiomiter_readings[decade_potentiomiter_readIndex];                         // Add the newest reading to the total
  decade_potentiomiter_readIndex = (decade_potentiomiter_readIndex + 1) % arrayLength;                   // Advance to the next position
  average = decade_potentiomiter_total / arrayLength;                               // Calculate the average

  int decade = 0;
  if (120 <= average && average <= 280) {
    decade = 3;  //2010
    // Serial.println("3: 2010");
  } else if (360 <= average && average <= 560) {
    decade = 2;  //2000
    // Serial.println("2: 2000");
  } else if (660 <= average && average <= 820) {
    decade = 1;  //1990
    // Serial.println("1: 1990");
  }
  return decade;
}
