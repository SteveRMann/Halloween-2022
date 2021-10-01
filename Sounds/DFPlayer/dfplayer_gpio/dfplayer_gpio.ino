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

  pinMode(D5, INPUT);                 //This makes the GPIO pins float.
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  drawMenu();
}


// ---------- loop ----------
void loop() {
  menu();
}
