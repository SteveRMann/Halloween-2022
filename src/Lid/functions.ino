// ********************** Function to display a string for debugging. **********************
void dbugs(const char *s, const char *v) {
  //Show a string variable. Enter with the string description and the string.
  //Example dbugs("My String= ",myString);
  Serial.print(s);
  Serial.print (F("\""));
  Serial.print(v);
  Serial.println(F("\""));
}


void beginSerial() {
  Serial.begin(115200);
  delay(1);
  Serial.println();
  Serial.println();
  Serial.print(F("Sketch Name: "));
  Serial.println(F(SKETCH));
  Serial.print(F("Sketch Version: "));
  Serial.println(F(VERSION));
  Serial.println();
  delay(2500);
}

// ---------- Functions unique to this sketch ----------
// ========= Start the motor =========
void startTheMotor() {
  analogWrite(MOTOR_PIN, maxTorque);          //Turn on the motor (max torque) to get it started.
  delay(1);
  ///while (!digitalRead(openSwitch) || !digitalRead(openSwitch)) yield(); //Wait until motor is not on a stop switch.
  analogWrite(MOTOR_PIN, runTorque);          //Slow it down
}



// ---------- Open the lid ----------
void openTheLid() {
  // Turn on bubbles sound
  client.publish ("dfplayer/cmnd", "1");
  Serial.print(F("dfplayer/cmnd, "));
  Serial.println(F("1"));

  analogWrite(FAN_PIN, FAN_MAX);      //Every time we open the lid, turn the fan and eyes up to max.
  delay(100);
  analogWrite(FAN_PIN, FAN_MIN);
  eyesVal = EYES_MAX;
  analogWrite(EYES_PIN, eyesVal);

  startTheMotor();

  while (digitalRead(openSwitch)) yield();     //Wait for the limit switch
  analogWrite(MOTOR_PIN, 0);                   //Stop the motor

  Serial.println(F("OPEN"));
}

// ---------- Close the lid ----------
void closeTheLid() {
  // Turn off bubbles
  // Bubbles are using the fan pin


  lidCloseTime.stop();                              //Make sure the random timer is off
  analogWrite(FAN_PIN, FAN_OFF);
  startTheMotor();
  while (digitalRead(closedSwitch)) yield();        //Wait for the limit switch
  analogWrite(MOTOR_PIN, 0);                        //Stop the motor
  Serial.println(F("CLOSED"));
}


// ---------- Open lid for a random time ----------
void lidRandom() {
  int openTime = random(2500, 6000);
  Serial.print(F("Opening lid for "));
  Serial.print(openTime);
  Serial.println(F(" ms"));
  openTheLid();
  delay(openTime);
  closeTheLid();
}


// ---------- eyes ----------
void eyes_ON() {
  analogWrite(EYES_PIN, eyesVal);
  eyesLED_onTime.stop();                           //Stop the ON timer
  eyesLED_offTime.setdelay(random(2000, 5000));    //LED will be on for this time.
  eyesLED_offTime.start();                         //Start the OFF timer
}

void eyes_OFF() {
  analogWrite(EYES_PIN, 0);                        //Turn off the eyes LED
  eyesLED_offTime.stop();                          //Stop the OFF timer
  eyesLED_onTime.setdelay(random(150, 300));       //LED will be off for this time.
  eyesLED_onTime.start();                          //Start the ON timer
}


// Function to dim the eyes
void eyes_DIM() {
  if (eyesVal > EYES_MIN) {
    eyesVal -= 1;
    analogWrite(EYES_PIN, eyesVal);
  }
}





// ---------- button handlers ----------

// Action Button Interrupt Handler
IRAM_ATTR void actionButtonHandler() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  //Debounce
  if (interrupt_time - last_interrupt_time > 250)
  {
    buttonFlag = true;
  }
  last_interrupt_time = interrupt_time;
}

// Loop Button Interrupt Handler
IRAM_ATTR void loopButtonHandler() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  //Debounce
  if (interrupt_time - last_interrupt_time > 250)
  {
    loopFlag = true;
  }
  last_interrupt_time = interrupt_time;
}


/*
  void singleClick() {
  randomFlag = false;                      //Stop random opens
  Serial.println(F("singleClick"));

  // Turn on bubbles
  //Sound
  client.publish ("dfplayer/cmnd", "1");
  Serial.print(F("dfplayer/cmnd, "));
  Serial.println(F("1"));

  //Open the lid for one second
  openTheLid();
  delay(1000);
  closeTheLid();

  // Turn off bubbles
  //client.publish ("dfplayer/cmnd", "5");
  //Serial.println('"dfplayer/cmnd", "5"');

  }


  void doubleclick() {
  randomFlag = false;                      //Stop random opens
  //Tell the dfPlayer to start.
  //client.publish ("dfplayer/cmnd", "1");
  client.publish ("dfplayer/cmnd", "1");
  Serial.print(F("dfplayer/cmnd, "));
  Serial.println(F("1"));
  //Start the sequence
  }



  void longPress() {
  randomFlag = true;
  Serial.println(F("longPress"));
  lidRandom();                                      //Open the lid for a random time
  }
*/

void dbgLoopFlg() {
  Serial.print(F("loopFlag= "));
  Serial.println(loopFlag);
}
