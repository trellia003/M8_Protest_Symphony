void setup() {
  // Start the serial communication
  Serial.begin(9600);

  // Explicitly set analog pins A0 to A5 as inputs
  for (int i = 0; i < 6; i++) {
    pinMode(i, INPUT);
  }
}

void loop() {
  // Read and print the values from analog pins A0 to A5
  for (int i = 0; i < 6; i++) {
    int sensorValue = analogRead(i);
    Serial.print("  A");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(sensorValue);
  }
  Serial.println();

  // Wait for a second before the next loop
  delay(300);
}
