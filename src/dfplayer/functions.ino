// ********************** Function to display a string for debugging. **********************
void dbugs(const char *s, const char *v) {
  //Show a string variable. Enter with the string description and the string.
  //Example dbugs("My String= ",myString);
  Serial.print(s);
  Serial.print (F("\""));
  Serial.print(v);
  Serial.println(F("\""));
}



void beginSerial() {
  Serial.begin(115200);
  delay(1);
  Serial.println();
  Serial.println();
  Serial.print(F("Sketch Name: "));
  Serial.println(F(SKETCH));
  Serial.print(F("Sketch Version: "));
  Serial.println(F(VERSION));
  Serial.println();
  delay(2500);
}

// ---------- Functions unique to this sketch ----------
// pulse() and hold() take as argument the GPIO pins on the
// switches for playing track 1 or track 2:
// TRACK1_PIN and TRACK2_PIN.

void pulse(int d) {
  Serial.print(F("Pulse: "));
  Serial.println(d);
  digitalWrite(d, 0);
  pinMode(d, OUTPUT);
  delay(200);
  pinMode(d, INPUT);
}

void hold(int d) {
  Serial.print(F("Hold: "));
  Serial.println(d);
  digitalWrite(d, 0);
  pinMode(d, OUTPUT);
  delay(2000);
  pinMode(d, INPUT);
}
