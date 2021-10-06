// -------------- beginSerial() --------------
void beginSerial() {
  while (!Serial);
  Serial.begin( 115200 );
  Serial.println();
  Serial.println();
  Serial.print(SKETCH);
  Serial.print(".ino, Version ");
  Serial.println(VERSION);
  Serial.println(F("++++++++++++++++++ +"));
}

// *********** Function to display a string for debugging. ***********
void dbugs(const char *s, const char *v) {
  //Show a string variable. Enter with the string description and the string.
  //Example dbugs("My String= ",myString);
  Serial.print(s);
  Serial.print (F("\""));
  Serial.print(v);
  Serial.println(F("\""));
}

// *********** Function to blink the WiFi status LED ***********
void blueTick() {
  //toggle state
  int state = digitalRead(BLUE_LED_PIN);            // get the current state of GPIO pin
  digitalWrite(BLUE_LED_PIN, !state);               // set pin to the opposite state
}


//Functions for this sketch
// -------------- dropEgg() --------------
void dropEgg(int howMany) {
  eyes = eyesMax;                     //Every time we drop an egg, turn the eyes up to max.
  analogWrite(EYES_PIN, eyes);

  printf("\nDropping\n");
  if (servo1Position != 90) {        //Make sure we're closed.
    dropServoClose();
    loadServoClose();
    delay(500);
  }
  while (howMany > 0) {
    howMany--;
    printf(" egg# %d.\n", howMany);
    dropServoOpen();                            //Exit
    digitalWrite (servo1LedPin, ledON);
    delay(dropDelay);
    dropServoClose();
    digitalWrite (servo1LedPin, ledOFF);
    delay(dropDelay);                   //Let 'drop' close before 'load' opens

    loadServoOpen();                            //Load
    digitalWrite (servo2LedPin, ledON);
    delay(loadDelay);
    loadServoClose();
    digitalWrite (servo2LedPin, ledOFF);

    if (howMany > 1) delay(2000);               //Time between eggs
  }
}

// -------------- dropServoOpen() --------------
void dropServoOpen() {                          //Open the exit
  servoOne.write(1);
  servo1Position = 0;
}

// -------------- dropServoClose() --------------
void dropServoClose() {                         //Close the exit
  servoOne.write(90);
  servo1Position = 90;
}

// -------------- loadServoOpen() --------------
void loadServoOpen() {                          //Open the preload servo
  servoTwo.write(0);
  servo2Position = 0;
}

// -------------- loadServoClose() --------------
void loadServoClose() {                         //Close the preload
  servoTwo.write(90);
  servo2Position = 90;
}

// -------------- stress() --------------
void stress() {
  //Drop an egg every STRESS_PERIOD
  if (millis() - lastTimeChecked >= STRESS_PERIOD) {
    dropEgg(1);
    lastTimeChecked = millis();
  }
}

// ---------- button functions ----------
void singleClick() {
  //Drop one egg
  dropEgg(1);
}

void doubleclick() {
  //Flush-Open both servos.
  dropServoOpen();
  loadServoOpen();
}

void longPress() {
  //Reset-Close both servos
  dropServoClose();
  loadServoClose();
}
