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

/////////////// Functions unique to this sketch ////////////////

// ========= Start the motor =========
void startTheMotor() {
  Serial.println(F("motor on"));
  analogWrite(motorPin, motorPwm);            //Turn on the motor to motorPwm
  motorState = 1;                             //Just used to print debug statements only once.
  delay(100);                                 //Give the motor time to move past the stop switch.
  Serial.print(F("openSwitch= "));
  Serial.println(digitalRead(openSwitch));
  Serial.print(F("closedSwitch= "));
  Serial.println(digitalRead(closedSwitch));
  
}

// ---------- Open the lid ----------
void openTheLid() {
  startTheMotor();
  while (digitalRead(openSwitch)) yield();    //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.print(F("motor off"));
  if (motorState == 1) {                      //Just print once
    Serial.println(F("OPEN"));
    motorState = 0;
  }
}

// ---------- Close the lid ----------
void closeTheLid() {
  startTheMotor();
  while (digitalRead(closedSwitch)) yield();  //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.print(F("motor off"));
  if (motorState == 1) {                      //Just print once
    Serial.println(F("CLOSED"));
    motorState = 0;
  }
}


//=============== motorOn ===============
//Function called by the ticker.
void motorOn() {
  //Serial.println(F("Tick"));
  flagMotorOn = true;
  lidState += 1;
  if (lidState > 2) lidState = 0;
}
