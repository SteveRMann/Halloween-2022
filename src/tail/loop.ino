//--------------- loop ---------------
void loop() {
  ArduinoOTA.handle();
  mqttReconnect();          //Make sure we stay connected to the mqtt broker
  slowWagTime.update();     //Check the slowWag timer
  button.tick();            //Check the button status
  menu();

}
