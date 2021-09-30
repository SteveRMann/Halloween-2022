//=============== loop ===============
void loop() {
  ArduinoOTA.handle();
  mqttReconnect();         //Make sure we stay connected to the mqtt broker
  menu();

  int i = digitalRead(buttonPin);
  if (i == 0) {
    eyesOn();
    fanOn();
    openTheLid();
    delay(1000);
    closeTheLid();
    eyesOff();
    fanOff();
  }
}
