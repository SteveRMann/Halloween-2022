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
  ///Serial.println(F("motor on"));
  analogWrite(motorPin, 255);                 //Turn on the motor
  while (!digitalRead(openSwitch) || !digitalRead(openSwitch)) yield(); //Wait until motor is past the stop switces.
  analogWrite(motorPin, 150);        //Slow it down
  
  /*
    Serial.print(F("Limit Switches (open,close)= ("));
    Serial.print(digitalRead(openSwitch));
    Serial.print(F("), ("));
    Serial.print(digitalRead(closedSwitch));
    Serial.print(F(")"));
  */
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
  ///client.publish (statusTopic, "Open");
}

// ---------- Close the lid ----------
void closeTheLid() {
  analogWrite(FAN_PIN, FAN_MIN);
  startTheMotor();
  while (digitalRead(closedSwitch)) yield();  //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.println(F("CLOSED"));
  ///client.publish (statusTopic, "Closed");
}



void eyes_ON() {
  analogWrite(EYES_PIN, eyesVal);
  eyesLED_onTime.stop();                                //Stop the ON timer
  eyesLED_offTime.setdelay(random(2500, 6000));         //LED will be on for this time.
  eyesLED_offTime.start();                              //Start the OFF timer
}

void eyes_OFF() {
  digitalWrite(EYES_PIN, LED_OFF);                       //Turn off the eyes LED
  eyesLED_offTime.stop();                                //Stop the OFF timer
  eyesLED_onTime.setdelay(random(200, 350));             //LED will be off for this time.
  eyesLED_onTime.start();                                //Start the ON timer
}


// Function to dim the eyes
void eyes_DIM() {
  //Fade eyesVal.
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
  //Open the lid for one second
  openTheLid();
  delay(1000);
  closeTheLid();
}

void doubleclick() {
  Serial.println(F("doubleClick- Stop the peek timer"));
  ///peekOnTime.stop();
  ///peekOffTime.stop();
}

void longPress() {
  Serial.println(F("longPress"));
  syncFlag = true;
}


// ---------- sync ----------
void syncCheck() {
  if (syncFlag) {
    if (millis() - syncStart > T1OPEN && t1OpenFlag) {    //If T1 has expired and the t1OpenFlag flag is true,
      Serial.println(F("open T1"));
      openTheLid();
      t1OpenFlag = false;
      syncCount += 1;
    }
    if (millis() - syncStart > T2OPEN && t2OpenFlag) {
      Serial.println(F("open T2"));
      openTheLid();
      t1OpenFlag = false;
      syncCount += 1;
    }
    if (millis() - syncStart > T3OPEN && t3OpenFlag) {
      Serial.println(F("open T3"));
      openTheLid();
      t1OpenFlag = false;
      syncCount += 1;
    }
    if (millis() - syncStart > T4OPEN && t4OpenFlag) {
      Serial.println(F("open T4"));
      openTheLid();
      t1OpenFlag = false;
      syncCount += 1;
    }
    if (millis() - syncStart > T5OPEN && t5OpenFlag) {
      Serial.println(F("open T5"));
      openTheLid();
      t1OpenFlag = false;
      syncCount += 1;
    }

    if (millis() - syncStart > T1CLOSE && t1CloseFlag) {    //If T1 has expired and the t1CloseFlag flag is true,
      Serial.println(F("close T1"));
      closeTheLid();                                           //close the lid
      t1CloseFlag = false;
      syncCount += 1;
    }
    if (millis() - syncStart > T2CLOSE && t2CloseFlag) {
      Serial.println(F("close T2"));
      closeTheLid();
      t1CloseFlag = false;
      syncCount += 1;
    }
    if (millis() - syncStart > T3CLOSE && t3CloseFlag) {
      Serial.println(F("close T3"));
      closeTheLid();
      t1CloseFlag = false;
      syncCount += 1;
    }
    if (millis() - syncStart > T4CLOSE && t4CloseFlag) {
      Serial.println(F("close T4"));
      closeTheLid();
      t1CloseFlag = false;
      syncCount += 1;
    }
    if (millis() - syncStart > T5CLOSE && t5CloseFlag) {
      Serial.println(F("close T5"));
      closeTheLid();
      t1CloseFlag = false;
      syncCount += 1;
    }
    if (syncCount == 10)
      //All lid peratons are finished.
      Serial.println(F("syncFlag=false"));
    syncFlag = false;
  }
}
