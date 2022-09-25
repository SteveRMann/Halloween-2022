//=============== loop ===============
void loop() {
  ArduinoOTA.handle();

 mqttReconnect();          //Make sure we stay connected to the mqtt broker

  //Check the timers
  eyesLED_onTime.update();
  eyesLED_offTime.update();        //Blink eye
  eyesLED_dim.update();            //Dim eye
  lidOpenTime.update();
  lidCloseTime.update();

  if (buttonFlag) {
    Serial.println(F("Action button pressed"));
    buttonFlag = false;
    loopFlag = false;
    lidRandom();
  }


  if (loopFlag) {
    Serial.println(F("Loop button pressed"));
    int closeTime = random(2500, 6000);
    Serial.print(F("Closing lid for "));
    Serial.print(closeTime);
    Serial.println(F(" ms"));
    closeTheLid();
    delay(closeTime);
    lidRandom();                    //Open the lid for a random time
  }



  menu();
  eyes_DIM();



}
