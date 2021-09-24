//--------------- loop ---------------
void loop() {
  ArduinoOTA.handle();
  mqttReconnect();          // Make sure we stay connected to the mqtt broker
  menu();

  int sw = digitalRead(BUTTON_PIN);
  if (sw == 0)largeTwitch(1);
}
