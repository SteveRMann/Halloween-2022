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
  analogWrite(motorPin, 255);        //Turn on the motor (max torque)
  while (!digitalRead(openSwitch) || !digitalRead(openSwitch)) yield(); //Wait until motor is past the stop switces.
  analogWrite(motorPin, 150);        //Slow it down
}


// ---------- Open the lid ----------
void openTheLid() {
  analogWrite(FAN_PIN, FAN_MAX);      //Every time we open the lid, turn the fan and eyes up to max.
  eyesVal = EYES_MAX;
  analogWrite(EYES_PIN, eyesVal);

  startTheMotor();

  while (digitalRead(openSwitch)) yield();    //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor

  Serial.println(F("OPEN"));
}

// ---------- Close the lid ----------
void closeTheLid() {
  analogWrite(FAN_PIN, FAN_MIN);
  startTheMotor();
  while (digitalRead(closedSwitch)) yield();  //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.println(F("CLOSED"));
}



void eyes_ON() {
  analogWrite(EYES_PIN, eyesVal);
  eyesLED_onTime.stop();                           //Stop the ON timer
  eyesLED_offTime.setdelay(random(2500, 6000));    //LED will be on for this time.
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


void peek_ON() {
  //The peek ON timer has dinged.
  //Turn on the LED, stop the ON timer then start the OFF timer.
  ///openTheLid();
  ///peekOnTime.stop();                                //Stop the ON timer
  ///peekOffTime.setdelay(random(1000, 5000));         //Lid will be open for this time.
  ///peekOffTime.start();                              //Start the OFF timer
}

void peek_OFF() {
  ///closeTheLid();
  ///peekOffTime.stop();                              //Stop the OFF timer
  ///peekOnTime.setdelay(random(1000, 6000));         //Lid will be closed for this time.
  ///peekOnTime.start();                              //Start the ON timer
}




// ---------- button functions ----------
void singleClick() {
  Serial.println(F("singleClick"));

  // Turn on bubbles
  //Sound
  client.publish ("dfplayer/cmnd", "1");
  Serial.print(F("MQTT Publish: "));
  Serial.print(F("dfplayer/cmnd, "));
  Serial.println(F("1"));

  //Open the lid for one second
  openTheLid();
  delay(1000);
  closeTheLid();

  // Turn off bubbles
  //client.publish ("dfplayer/cmnd", "5");
  //Serial.print(F("MQTT Publish: "));
  //Serial.println('"dfplayer/cmnd", "5"');
  
}


void doubleclick() {
  //Start a sync to the sound
/*  
  Serial.println(F("Start a sync to the sound."));
  Serial.print(F("Num of elements in syncTbl= "));
  Serial.println(tblN);
  for (int i = 0; i < tblN; i++) {                      //For debugging, show the time points
    Serial.print(syncTbl[i]);
    Serial.print(F(", "));
  }
  Serial.println();
*/

  //Tell the dfPlayer to start.
  client.publish ("dfplayer/cmnd", "1");
  client.publish ("dfplayer/cmnd", "1");
  Serial.print(F("MQTT Publish: "));
  Serial.print(F("dfplayer/cmnd, "));
  Serial.println(F("1"));
  //Start the sequence
  syncClose();
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
