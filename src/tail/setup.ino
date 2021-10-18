// --------------- setup ---------------
void setup() {
  //configure GPIO pins
  pinMode (MOTOR1, OUTPUT);
  pinMode (MOTOR2, OUTPUT);
  pinMode (BUTTON_PIN, INPUT_PULLUP);
  pinMode (BLUE_LED_PIN, OUTPUT);

  Serial.begin( 115200 );
  Serial.println();
  Serial.print(SKETCH);
  Serial.println(F(".ino"));

  beginSerial();
  setup_wifi();                       // MUST be before setupMqtt()
  start_OTA();                        // If using OTA
  setup_mqtt();                       // Generate the topics

  // Call the setServer method on the PubSubClient object
  client.setServer(mqttServer, mqttPort);
  mqttConnect();

  button.attachDoubleClick(doubleclick);
  button.attachClick(singleClick);
  button.attachLongPressStop(longPress);

  twitch(1);
  drawMenu();

  //Start the timers
  oneSlowWag();
}
