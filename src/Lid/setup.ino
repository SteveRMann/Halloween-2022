//=============== setup ===============
void setup() {
  pinMode(closedSwitch, INPUT_PULLUP);
  pinMode(openSwitch, INPUT_PULLUP);
  //pinMode(buttonPin, INPUT_PULLUP);
  pinMode (BUTTON_PIN, INPUT_PULLUP);
  pinMode(BLUE_LED_PIN, OUTPUT);
  analogWrite(motorPin, 0);             //PWM pin, start at zero.
  pinMode(LEDS_PIN, OUTPUT);
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

  //Testing D5 LEDs (yellow) and D6 FAN (green)
  eyesTicker.attach(0.1, eyesTick);           //Start eyesTick
  delay(1000);                                //Blink eyes for one second
  eyesTicker.detach();
  delay(1000);                                //Wait a second before turning the fan on

  //Fan
  analogWrite(FAN_PIN, 250);
  delay(2000);
  analogWrite(FAN_PIN, 0);
  delay(1000);                                //Wait a second before opening the lid
  
  //Lid
  openTheLid();
  delay(1000);
  closeTheLid();
}
