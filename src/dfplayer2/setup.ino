void setup() {
  pinMode(BLUE_LED_PIN, OUTPUT);      // Must be before calling setup_wifi
  
  beginSerial();
  setup_wifi();
  start_OTA();


  //This makes the GPIO pins float.
  pinMode(D5, INPUT);                   //Track 1
  pinMode(D6, INPUT);                   //Play/Pause
  pinMode(D1, INPUT);                   //Prev/Vol-
  pinMode(D2, INPUT);                   //Next/Vol+
  pinMode(D3, INPUT);                   //Track 2

  //pulse(PLAY_PAUSE_PIN);                //Always start here?
  //delay(1000);
  hold(TRACK1_PIN);                    //PLay track 1 once.
}
