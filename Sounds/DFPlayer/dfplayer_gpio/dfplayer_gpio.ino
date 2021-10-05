/*
  Control the DFPlayer ADKEY1 pin through a GPIO port.
*/

const int TRACK1_PIN = D5;
const int TRACK2_PIN = D3;
const int PLAY_PAUSE_PIN = D6;
const int PREV_VOLdn_PIN = D1;
const int NEXT_VOLup_PIN = D2;


// ---------- setup ----------
void setup() {
  Serial.begin(115200);
  delay(1);
  Serial.println();
  Serial.println();
  Serial.print(F("dfplayer_gpio.ino"));

  //This makes the GPIO pins float.
  pinMode(D5, INPUT);                   //Track 1
  pinMode(D6, INPUT);                   //Play/Pause
//  pinMode(D7, INPUT);                   //Tx
//  pinMode(D8, INPUT);                   //Rx
  pinMode(D1, INPUT);                   //Prev/Vol-
  pinMode(D2, INPUT);                   //Next/Vol+
  pinMode(D3, INPUT);                   //Track 2
  drawMenu();
}


// ---------- loop ----------
void loop() {
  menu();
}
