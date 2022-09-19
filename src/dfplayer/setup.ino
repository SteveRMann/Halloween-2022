void setup() {
  pinMode(BLUE_LED_PIN, OUTPUT);      // Must be before calling setup_wifi

  beginSerial();
  setup_wifi();                       // MUST be before setup_Mqtt() and start_ota()
  setup_mqtt();                       // Generate the topics
  start_OTA();                        // If using OTA

  // Call the setServer method on the PubSubClient object
  client.setServer(mqttServer, mqttPort);
  mqttConnect();


  //This makes the GPIO pins float.
  pinMode(D5, INPUT);                   //Track 1
  pinMode(D6, INPUT);                   //Play/Pause
  pinMode(D1, INPUT);                   //Prev/Vol-
  pinMode(D2, INPUT);                   //Next/Vol+
  pinMode(D3, INPUT);                   //Track 2
  drawMenu();

  //pulse(PLAY_PAUSE_PIN);                //Always start here?
  //delay(1000);
  pulse(TRACK1_PIN);                    //PLay track 1 once.
}
