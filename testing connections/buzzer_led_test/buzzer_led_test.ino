void setup() {
  // Start the serial communication
  Serial.begin(9600);

  // Set digital pins 2 to 7 as outputs
  for (int pin = 2; pin <= 7; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  // Turn on LEDs sequentially
  for (int pin = 2; pin <= 7; pin++) {
    digitalWrite(pin, HIGH); // Turn on the LED
    Serial.print("LED on pin ");
    Serial.print(pin);
    Serial.println(" is ON");
    delay(1000); // Wait for half a second

    digitalWrite(pin, LOW); // Turn off the LED
    Serial.print("LED on pin ");
    Serial.print(pin);
    Serial.println(" is OFF");
    delay(1000); // Wait for half a second
  }
}
