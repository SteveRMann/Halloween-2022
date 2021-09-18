// ********************** Function to display a string for debugging. **********************
void dbugs(const char *s, const char *v) {
  //Show a string variable. Enter with the string description and the string.
  //Example dbugs("My String= ",myString);
  Serial.print(s);
  Serial.print (F("\""));
  Serial.print(v);
  Serial.println(F("\""));
}


/* --------------- Typical setup ---------------
void setup() {
  beginSerial();
  setup_wifi();
  start_OTA();
}
*/

void beginSerial() {
  Serial.begin(115200);
  delay(1);
  Serial.println();
  Serial.println();
  Serial.print(F("Sketch Name: "));
  Serial.println(F(SKETCH_NAME));
  Serial.print(F("Sketch Version: "));
  Serial.println(F(SKETCH_VERSION));
  Serial.println();
  delay(2500);
}
