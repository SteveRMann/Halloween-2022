// --------------- General functions ---------------
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

// --------------- Function to display a string for debugging. ---------------
void dbugs(const char *s, const char *v) {
  //Show a string variable. Enter with the string description and the string.
  //Example dbugs("My String= ",myString);
  Serial.print(s);
  Serial.print (F("\""));
  Serial.print(v);
  Serial.println(F("\""));
}



// ********************************************
// --------------- my functions ---------------
// --------------- Unique to this sketch ---------------
void forward(int duration) {
  digitalWrite (MOTOR1, LOW);
  digitalWrite (MOTOR2, HIGH);
  delay (duration);
}

void stop(int duration) {
  digitalWrite (MOTOR1, LOW);
  digitalWrite (MOTOR2, LOW);
  delay (duration);
}

void reverse(int duration) {
  digitalWrite (MOTOR1, HIGH);
  digitalWrite (MOTOR2, LOW);
  delay (duration);
}

void forwardSlow(int pwm, int duration) {
  analogWrite (MOTOR1, pwm);
  digitalWrite (MOTOR2, LOW);
  delay (duration);
}

void reverseSlow(int pwm, int duration) {
  digitalWrite (MOTOR1, LOW);
  analogWrite (MOTOR2, pwm);
  delay (duration);
}

void rampUp() {
  digitalWrite (MOTOR2, LOW);
  for (int i = 0; i < 100; i++) {
    analogWrite (MOTOR1, i);
    delay(10);
  }
  delay (1000);
}

void wag(int count) {
  for (int i = 0; i < count; i++) {
    forwardSlow(300, 100);                  // (int pwm, int duration)
    //delay(100);
    stop(125);
    reverseSlow(300, 100);
    //delay(100);
    stop(200);
  }
}

void twitch(int count) {
  for (int i = 0; i < count; i++) {
    forwardSlow(100, 25);                   // (int pwm, int duration)
    //delay(100);
    stop(500);
    reverseSlow(100, 25);
    //delay(100);
    stop(200);
  }
}

void largeTwitch(int count) {
  for (int i = 0; i < count; i++) {
    forwardSlow(40, 750);                   // (int pwm, int duration)
    stop(300);
    reverseSlow(40, 750);
    stop(200);
  }
}

void slowWag(int count) {
  for (int i = 0; i < count; i++) {
    forwardSlow(30, 150);                   // (int pwm, int duration)
    //delay(100);
    stop(225);
    reverseSlow(30, 150);
    //delay(100);
    stop(225);
  }
}

// ---------- button functions ----------
void singleClick() {
  Serial.println(F("singleClick=twitch(1)"));
  twitch(1);
}

void doubleclick() {
  Serial.println(F("doubleClick=largeTwitch(1)"));
  largeTwitch(1);
}

void longPress() {
  Serial.println(F("longPress=wag(2)"));
  wag(2);
}


// ---------- noDelay functions ----------
void oneWag() {
  wag(1);
}

void oneTwitch() {
  twitch(1);
}

void oneLargeTwitch() {
  largeTwitch(1);
}

void oneSlowWag() {
  Serial.println(F("oneSlowWag()"));
  slowWagTime.stop();
  slowWag(1);
  //Reset the timer for another wag.
  slowWagTime.setdelay(random(5000, 10000));    //Wag will repeat for this time.
  slowWagTime.start();
}
