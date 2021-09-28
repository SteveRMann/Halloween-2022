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
  analogWrite(motorPin, motorPwm);            //Turn on the motor to motorPwm
  delay(100);                                 //Give the motor time to move past the stop switch.
  Serial.print(F("openSwitch= "));
  Serial.println(digitalRead(openSwitch));
  Serial.print(F("closedSwitch= "));
  Serial.println(digitalRead(closedSwitch));
}

// ---------- Open the lid ----------
void openTheLid() {
  startTheMotor();
  analogWrite(motorPin, 100);        //Slow it down
  while (digitalRead(openSwitch)) yield();    //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.print(F("motor off"));
  Serial.println(F("OPEN"));
}


// ---------- Slow Open the lid ----------
void slowOpen() {
  startTheMotor();
  analogWrite(motorPin, 80);                  //Slow it down
  while (digitalRead(openSwitch)) yield();    //Wait for the open switch closes (==0)
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.print(F("motor off"));
  Serial.println(F("OPEN"));
}


// ---------- Fast Open the lid ----------
void fastOpen() {
  startTheMotor();
  analogWrite(motorPin, 250);                 //Speed it up
  while (digitalRead(openSwitch)) yield();    //Wait for the open switch closes (==0)
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.print(F("motor off"));
  Serial.println(F("OPEN"));
}

// ---------- Close the lid ----------
void closeTheLid() {
  startTheMotor();
  analogWrite(motorPin, 100);        //Slow it down
  while (digitalRead(closedSwitch)) yield();  //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.print(F("motor off"));
  Serial.println(F("CLOSED"));
}

// ---------- Slow close the lid ----------
void slowClose() {
  startTheMotor();
  analogWrite(motorPin, 80);        //Slow it down
  while (digitalRead(closedSwitch)) yield();  //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.print(F("motor off"));
  Serial.println(F("CLOSED"));
}



//=============== motorOn ===============
//Function called by the ticker.
void motorOn() {
  //Serial.println(F("Tick"));
  flagMotorOn = true;
  lidState += 1;
  if (lidState > 2) lidState = 0;
}
