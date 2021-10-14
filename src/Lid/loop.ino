//=============== loop ===============
void loop() {
  ArduinoOTA.handle();
  mqttReconnect();          //Make sure we stay connected to the mqtt broker
  button.tick();            //Has a button been pressed?

  //Check the timers
  eyesLED_onTime.update();
  eyesLED_offTime.update();        //Blink eye
  eyesLED_dim.update();            //Dim eye

  menu();
  syncCheck();              //Check the sync status.
  eyes_DIM();

}
