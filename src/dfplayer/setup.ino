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
  pinMode(TRACK1_PIN, INPUT);         //D5
  pinMode(PLAY_PAUSE_PIN, INPUT);     //D6
  pinMode(PREV_VOLdn_PIN, INPUT);     //D1
  pinMode(NEXT_VOLup_PIN, INPUT);     //D2
  pinMode(TRACK2_PIN, INPUT);         //D3
  drawMenu();

  delay(1000);
  pulse(PLAY_PAUSE_PIN);              //Always start here?
  delay(1000);
  hold(TRACK1_PIN);                   //Loop track 1
  delay(2000);
  //pulse(PLAY_PAUSE_PIN);
}
