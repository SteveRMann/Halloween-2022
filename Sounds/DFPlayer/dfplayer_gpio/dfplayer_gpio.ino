/*
  This is a test to trigger ADKEY1 through a GPIO port.
*/


// ---------- setup ----------
void setup() {
   Serial.begin(115200);
  delay(1);
  Serial.println();
  Serial.println();
  Serial.print(F("dfplayer_gpio.ino"));
  
  pinMode(D5, OUTPUT);
  digitalWrite(D5, 1);
  digitalWrite(D6, 1);
  digitalWrite(D7, 1);
  digitalWrite(D8, 1);
  drawMenu();
}


// ---------- loop ----------
void loop() {
  menu();
}
