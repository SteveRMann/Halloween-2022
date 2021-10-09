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
  Serial.println(F("motor on"));
  analogWrite(motorPin, 255);                 //Turn on the motor
  delay(100);                                 //Give the motor time to move past the stop switch.
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
  startTheMotor();
  analogWrite(motorPin, 200);        //Slow it down
  while (digitalRead(openSwitch)) yield();    //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.println(F("OPEN"));
  client.publish (statusTopic, "Open");
}

// ---------- Close the lid ----------
void closeTheLid() {
  startTheMotor();
  analogWrite(motorPin, 200);        //Slow it down
  while (digitalRead(closedSwitch)) yield();  //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.println(F("CLOSED"));
  client.publish (statusTopic, "Closed");
}


//=============== eyesOn ===============
void eyesOn() {
  digitalWrite(LEDS_PIN, 1);
  client.publish (statusTopic, "Eyes On");
}

//=============== eyesOff ===============
void eyesOff() {
  digitalWrite(LEDS_PIN, 0);
  client.publish (statusTopic, "Eyes Off");
}

//=============== fanOn ===============
void fanOn() {
  analogWrite(FAN_PIN, 250);
  client.publish (statusTopic, "Fan On");
}

//=============== fanOff ===============
void fanOff() {
  analogWrite(FAN_PIN, 0);
  client.publish (statusTopic, "Fan Off");
}


// ---------- button functions ----------
void singleClick() {
  Serial.println(F("singleClick"));
  //Open the lid for one second
  eyesOn();
  fanOn();
  openTheLid();
  delay(1000);
  closeTheLid();
  eyesOff();
  fanOff();
}

void doubleclick() {
  Serial.println(F("doubleClick"));
}

void longPress() {
  Serial.println(F("longPress"));
  //Mayhem
  eyesOn();
  fanOn();
  for (int i = 0; i < 10; i++) {
    openTheLid();
    delay(100);
    closeTheLid();
  }
  eyesOff();
  fanOff();
}
