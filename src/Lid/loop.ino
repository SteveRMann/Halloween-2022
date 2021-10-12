//=============== loop ===============
void loop() {
  ArduinoOTA.handle();
  mqttReconnect();          //Make sure we stay connected to the mqtt broker
  button.tick();            //Has a button been pressed?
  menu();

  //Blink the eyes
  eyesLED_onTime.update();
  eyesLED_offTime.update();        //Blink eye

  //Fade the eyes
  eyesLED_dim.update();     //Dim the eyes

  //sync();                   //Check the sync status.

  /*
    TO DO- Open the lid at random times.
    peek();                 //Check the peek status.

      eyes??
      openTheLid();
      delay(250);
      closeTheLid();

  */
}
