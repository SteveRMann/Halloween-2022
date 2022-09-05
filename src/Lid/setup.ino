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

  Serial.print(F("mqttServer= "));
  Serial.println(mqttServer);
  Serial.print(F("mqttPort= "));
  Serial.println(mqttPort);


  lidState = 0;     //Open
  //drawMenu();

  button.attachDoubleClick(doubleclick);
  button.attachClick(singleClick);
  button.attachLongPressStop(longPress);


  //Cycle through the eyes' LED intensity.
  Serial.println(F("setup() Cycle through the eyes' LED intensity."));
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
  eyesVal = EYES_MIN;
  analogWrite(EYES_PIN, eyesVal);
  delay(1000);

  //Fan
  Serial.println(F("setup() Start the fan"));
  analogWrite(FAN_PIN, FAN_MAX);
  delay(2000);
  analogWrite(FAN_PIN, 0);
  delay(1000);                                //Wait a second before opening the lid

  //Lid
  Serial.println(F("setup() Open and close the lid"));
  openTheLid();
  delay(1000);
  closeTheLid();

  analogWrite(FAN_PIN, FAN_MIN);


  //Start the timers
  Serial.println(F("setup() Start the timers"));
  eyes_ON();
  peek_OFF();


  //Reset the tblPtr (for syncing the lid with sound).
  Serial.println(F("setup() Reset the tblPtr"));
  syncPtr = 0;
  tblN = sizeof(syncTbl) / sizeof(syncTbl[0]);      //Number of sync timepoints

  Serial.println(F("setup() END"));

}
