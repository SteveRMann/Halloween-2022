//=============== setup ===============
void setup() {
  pinMode(closedSwitch, INPUT_PULLUP);
  pinMode(openSwitch, INPUT_PULLUP);
  pinMode (BUTTON_PIN, INPUT_PULLUP);
  pinMode (LOOP_PIN, INPUT_PULLUP);
  pinMode(BLUE_LED_PIN, OUTPUT);
  analogWrite(MOTOR_PIN, 0);             //PWM pin, start at zero.
  pinMode(EYES_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  beginSerial();
  ///setup_wifi();
  setup_wifiMulti();
  start_OTA();
  setup_mqtt();                         //Generate the topics
  client.setServer(mqttServer, mqttPort);
  mqttConnect();

  //lidState = 0;     //Open
  drawMenu();

  attachInterrupt(BUTTON_PIN, actionButtonHandler, RISING);
  attachInterrupt(LOOP_PIN, loopButtonHandler, RISING);

  //  button.attachDoubleClick(doubleclick);
  //  button.attachClick(singleClick);
  //  button.attachLongPressStop(longPress);


  //Cycle through the eyes' LED intensity.
  Serial.println(F("Test the eyes."));
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
  Serial.println(F("Test the fan."));
  analogWrite(FAN_PIN, FAN_MAX);
  delay(2000);
  analogWrite(FAN_PIN, FAN_MIN);
  delay(2000);
  analogWrite(FAN_PIN, FAN_OFF);

  //Lid
  Serial.println(F("Test the lid."));
  loopFlag = false;
  openTheLid();
  delay(1000);
  closeTheLid();

  loopFlag = false;
  dbgLoopFlg();




  //Start the timers
  eyes_ON();
  //eyes_OFF();

  /*
    // ========== MOTORTEST ==========
    // Neverending function to find the minimum torque needed
    // to run the motor
    maxTorque = 255;
    while (1) {
      sensorValue = analogRead(sensorPin);
      runTorque = sensorValue;
      Serial.print(F("runTorque= "));
      Serial.println(runTorque);
      startTheMotor();
      delay(1000);
    }
  */



} //End of setup()
