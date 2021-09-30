//=============== setup ===============
void setup() {
  pinMode(closedSwitch, INPUT_PULLUP);
  pinMode(openSwitch, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
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

  //Testing D5 LEDs (yellow) and D6 FAN (green)
  eyesTicker.attach(0.1, eyesTick);          // Start eyesTick
  delay(1000);
  eyesTicker.detach();
  delay(550);

  //Fan
  analogWrite(FAN_PIN, 250);
  delay(2000);
  analogWrite(FAN_PIN, 0);

  //Lid
  openTheLid();
  delay(1000);
  closeTheLid();
}
