//RESPONSE ARUDINO


int decade = 0;
int region = 0;
int protest = 0;
bool is_start = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  if (Serial.available() > 0) {
    //seri
    // String input = Serial.readStringUntil('\n');
    // parseData(input);
    Serial.println("input");
  }
  // Serial.println("hi");
  delay(10);
}

void parseData(String data) {
  int sIndex = data.indexOf("S:") + 2;
  int dIndex = data.indexOf("D:") + 2;
  int rIndex = data.indexOf("R:") + 2;
  int pIndex = data.indexOf("P:") + 2;

  String isStartStr = data.substring(sIndex, data.indexOf(",", sIndex));
  String decadeStr = data.substring(dIndex, data.indexOf(",", dIndex));
  String regionStr = data.substring(rIndex, data.indexOf(",", rIndex));
  String protestStr = data.substring(pIndex);

  is_start = isStartStr.toInt() == 1 ? true : false;
  decade = decadeStr.toInt();
  region = regionStr.toInt();
  protest = protestStr.toInt();

  // Debug print to verify the values
  Serial.print("is_start: "); Serial.println(is_start);
  Serial.print("decade: "); Serial.println(decade);
  Serial.print("region: "); Serial.println(region);
  Serial.print("protest: "); Serial.println(protest);
}
