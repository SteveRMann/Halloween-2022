//=============== setup ===============
void setup() {
  pinMode(closedSwitch, INPUT_PULLUP);
  pinMode(openSwitch, INPUT_PULLUP);
  //pinMode(buttonPin, INPUT_PULLUP);
  pinMode (BUTTON_PIN, INPUT_PULLUP);
  pinMode(BLUE_LED_PIN, OUTPUT);
  analogWrite(motorPin, 0);             //PWM pin, start at zero.
  pinMode(EYES_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  beginSerial();
  setup_wifi();
  start_OTA();
  setup_mqtt();                         //Generate the topics
  client.setServer(mqttServer, mqttPort);
  mqttConnect();

  Serial.println(F("---------- Starting ----------"));
  client.publish (statusTopic, "Starting");

  lidState = 0;     //Open
  drawMenu();

  button.attachDoubleClick(doubleclick);
  button.attachClick(singleClick);
  button.attachLongPressStop(longPress);


  //Cycle through the eyes' LED intensity.
  for (int j = 0; j < 4; j++) {
    for (int i = 10; i < 255; i++) {
      analogWrite(EYES_PIN, i);
      delay(2);
    }
    for (int i = 255; i > 10; i--) {
      analogWrite(EYES_PIN, i);
      delay(2);
    }
  }
  eyes = EYES_MIN;
  analogWrite(EYES_PIN, eyes);
  delay(1000);

  //Fan
  analogWrite(FAN_PIN, FAN_MAX);
  delay(2000);
  analogWrite(FAN_PIN, 0);
  delay(1000);                                //Wait a second before opening the lid

  //Lid
  openTheLid();
  delay(1000);
  closeTheLid();
  
  analogWrite(FAN_PIN, FAN_MIN);
}
