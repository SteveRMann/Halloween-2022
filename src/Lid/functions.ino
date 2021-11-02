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
  ///Serial.println(F("in startTheMotor()"));
  ///Serial.print(F("openSwitch= "));
  ///Serial.println(digitalRead(openSwitch));
  ///Serial.print(F("closedSwitch= "));
  ///Serial.println(digitalRead(closedSwitch));
  analogWrite(motorPin, 255);        //Turn on the motor (max torque)

#ifndef simulation
  //While either switch is closed, wait until motor is past the stop switches.
  while (!digitalRead(openSwitch) || !digitalRead(closedSwitch)) {
    yield();
    Serial.print(F(":"));
  }
#endif

  analogWrite(motorPin, 150);        //Slow it down
  ///Serial.println(F("end of startTheMotor()"));
}


// ---------- Open the lid ----------
void openTheLid() {
  ///Serial.println(F("in openTheLid()"));
  analogWrite(FAN_PIN, FAN_MAX);      //Every time we open the lid, turn the fan and eyes up to max.
  eyesVal = EYES_MAX;
  analogWrite(EYES_PIN, eyesVal);

  startTheMotor();

#ifndef simulation
  while (digitalRead(openSwitch)) yield();    //Wait for the limit switch to close (=0)
#endif

  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.println(F("OPEN"));
}

// ---------- Close the lid ----------
void closeTheLid() {
  analogWrite(FAN_PIN, FAN_MIN);
  startTheMotor();

#ifndef simulation
  while (digitalRead(closedSwitch)) yield();  //Wait for the limit switch
#endif

  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.println(F("CLOSED"));
}



// ---------- eyes (blink)----------
void eyes_ON() {
  analogWrite(EYES_PIN, eyesVal);
  eyesLED_onTime.stop();                           //Stop the ON timer
  eyesLED_offTime.setdelay(random(5000, 8000));    //LED will be on for this time.
  eyesLED_offTime.start();                         //Start the OFF timer
}

void eyes_OFF() {
  analogWrite(EYES_PIN, 0);                        //Turn off the eyes LED
  eyesLED_offTime.stop();                          //Stop the OFF timer
  eyesLED_onTime.setdelay(random(100, 200));       //LED will be off for this time.
  eyesLED_onTime.start();                          //Start the ON timer
}


// Function to dim the eyes
void eyes_DIM() {
  static long int dimTime;
  if (eyesVal > EYES_MIN) {
    //millis() - lastTimeChecked >= elapsed time
    if (millis() - dimTime  > 50) {               //Once every 1/25 of a second
      eyesVal -= 1;                               //Dim the lights slightly
      analogWrite(EYES_PIN, eyesVal);
      dimTime = millis();
    }
  }
}


// ---------- peek ----------
void peek_ON() {
  //The peek ON timer has dinged.
  //Open the lid, stop the ON timer then start the OFF timer.
  openTheLid();
  client.publish ("tail/cmnd", "wag");
  peekOnTime.stop();                                //Stop the ON timer
  peekOffTime.setdelay(random(1000, 5000));         //Lid will be open for this time.
  peekOffTime.start();                              //Start the OFF timer
}

void peek_OFF() {
  closeTheLid();
  client.publish ("tail/cmnd", "slowwag");
  peekOffTime.stop();                              //Stop the OFF timer
  peekOnTime.setdelay(random(15000UL, 30000UL));   //Lid will be closed for this time.
  peekOnTime.start();                              //Start the ON timer
}




// ---------- button functions ----------
void singleClick() {
  Serial.println(F("singleClick"));
  //Open the lid for one second
  openTheLid();
  delay(1000);
  closeTheLid();
}

void doubleclick() {
  //Start a sync to the sound
  //Same as ROAR

  Serial.println(F("Start a sync to the sound."));
  Serial.print(F("Num of elements in syncTbl= "));
  Serial.println(tblN);
  for (int i = 0; i < tblN; i++) {                      //For debugging, show the time points
    Serial.print(syncTbl[i]);
    Serial.print(F(", "));
  }
  Serial.println();


  //Tell the dfPlayer to start.
  client.publish ("dfplayer/cmnd", "roar");
  client.publish ("tail/cmnd", "wag");
  //Start the open/close sequence
  syncClose();
  //Start the tail twitching
  client.publish ("tail/cmnd", "slowwag");
}



void longPress() {
  Serial.println(F("longPress"));
}


// ---------- sync ----------
//When started, this function cycles through the sync timer table, syncTbl[]
//The sequence is started by calling syncClose().
void syncOpen() {
  sync_open_timer.stop();
  openTheLid();
  Serial.print(F("Open at point# "));
  Serial.print(syncPtr);
  Serial.print(F(", "));
  Serial.print(syncTbl[syncPtr]);
  Serial.println(F(" ms."));
  sync_close_timer.setdelay(syncTbl[syncPtr++]);
  sync_close_timer.start();

  if (syncPtr > tblN) {         //When we run out of time points, stop the timers.
    sync_open_timer.stop();
    sync_close_timer.stop();
    syncPtr = 0;
  }
}

void syncClose() {
  sync_close_timer.stop();
  closeTheLid();
  Serial.print(F("Close at point# "));
  Serial.print(syncPtr);
  Serial.print(F(", "));
  Serial.print(syncTbl[syncPtr]);
  Serial.println(F(" ms."));
  sync_open_timer.setdelay(syncTbl[syncPtr++]);
  sync_open_timer.start();

  if (syncPtr > tblN) {         //When we run out of time points, stop the timers.
    sync_open_timer.stop();
    sync_close_timer.stop();
    syncPtr = 0;
  }
}
