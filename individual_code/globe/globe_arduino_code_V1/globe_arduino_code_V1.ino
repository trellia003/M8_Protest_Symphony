/* code for the globe potentiometer for the module 8 project of CreaTe by Jarne Groenewegen
Connect ground of potentiometer to ground and 5v to Vin, wire for data from potmeter should be connected to analog pin
*/
const int potPin = A0;
const int num_measurements = 15;  //how many measurements we want to make for the value descion
const int threshold = 3;          //how much difference there can be between the values
int measurements[num_measurements];
int pot_value;          // variable that saves the pot data
bool country_selected;  // boolean to see if an actual value is selected

void setup() {
  pinMode(potPin, INPUT);  //pin for potentiometer
  Serial.begin(9600);
}

void loop() {
  int total = 0;  // sum of measurements values
  country_selected = false;
  for (int i = 0; i < num_measurements; i++) {
    pot_value = analogRead(potPin);  //Read and save analog value from potentiometer
    Serial.println(pot_value);
    measurements[i] = pot_value;
    total = total + pot_value;
    delay(100);
  }
  float average = total / (num_measurements);
  float devi_1 = measurements[0] - measurements[num_measurements];  // measures the deviation between first and last value
  float devi_2 = measurements[num_measurements] - measurements[0];  // measures the deviation between first and last value
  Serial.println(average);
  Serial.println(devi_1);
  Serial.println(devi_2);

  if (devi_1 <= threshold && devi_1 >= 0 || devi_2 <= threshold && devi_2 >= 0) {
    //output the country and change selected to true
    Serial.println("official reading");
    // then for the induvdual countries
    country_selected = true;
  }
}
