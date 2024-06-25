void setup() {
  // Initialize both Serial and Serial1
  Serial.begin(9600);
  Serial1.begin(9600);

  // Give some time for the serial connection to be established
  delay(1000);
}

void loop() {
  // Check if data is available on the Serial
  if (Serial.available() > 0) {
    // Read the input from Serial
    String input = Serial.readStringUntil('\n');
    input.trim();  // Remove any leading or trailing whitespace

    // Check if the input is '0'
    if (input == "0") {
      // Send RESET to Serial1
      Serial1.println("RESET");
      Serial.println("Message sent: RESET");
    }
    // Check if the input has exactly 3 characters and they are all digits
    else if (input.length() == 3 && isDigit(input[0]) && isDigit(input[1]) && isDigit(input[2])) {
      // Extract the digits
      char x = input.charAt(0);
      char y = input.charAt(1);
      char z = input.charAt(2);

      // Send formatted string to Serial1
      Serial1.print("START,D:");
      Serial1.print(x);
      Serial1.print(",R:");
      Serial1.print(y);
      Serial1.print(",P:");
      Serial1.println(z);

      // Send formatted string to Serial
      Serial.print("Message sent: START,D:");
      Serial.print(x);
      Serial.print(",R:");
      Serial.print(y);
      Serial.print(",P:");
      Serial.println(z);
    }
    // For any other input, notify user of invalid input
    else {
      Serial.println("Invalid input. Please enter '0' or exactly 3 digits.");
    }
  }
}
