//=============== loop ===============
void loop() {
  ArduinoOTA.handle();
  mqttReconnect();          //Make sure we stay connected to the mqtt broker
  button.tick();            //Has a button been pressed?
  menu();

  //Fade the eyes
  if (eyes > EYES_MIN) {
    eyes -= 1;
    analogWrite(EYES_PIN, eyes);
    delay(10);
  }

  blinker();                //Blink the eyes
  sync();                   //Check the sync status.

  /*
    TO DO- Open the lid at random times.
    peek();                 //Check the peek status.

      eyes??
      openTheLid();
      delay(250);
      closeTheLid();

  */
}
