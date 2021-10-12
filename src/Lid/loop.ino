//=============== loop ===============
void loop() {
  ArduinoOTA.handle();
  mqttReconnect();          //Make sure we stay connected to the mqtt broker
  button.tick();            //Has a button been pressed?
  menu();

/*
  //Blink the eyes
  eyesLED_onTime.update();
  eyesLED_offTime.update();        //Blink eye

  //Fade the eyes
  eyesLED_dim.update();     //Dim the eyes

  //Open the lid at random times.
  peekOnTime.update();        //If time has past, run set function
  peekOffTime.update();
*/  
  //syncCheck();                   //Check the sync status.

}
