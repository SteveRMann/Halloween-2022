// --------------- General functions ---------------
// --------------- Unique to this sketch ---------------

const int SPEED = 24;
const int HALFSPEED = SPEED / 2;
const int QUARTERSPEED = HALFSPEED / 2;
const int FASTSPEED = SPEED * 2;;


void motorRun(int pwm, int duration) {
  motor1.setSpeed(pwm);
  delay (duration);
  motor1.setSpeed(0);     // Motor 1 stops.
}


void wag(int count) {
  for (int i = 0; i < count; i++) {
    motorRun(SPEED, 500 );               //(int pwm, int duration)
    stop(500);                              //Stop then pause
    motorRun(-SPEED, 500);
    stop(500);
  }
  motor1.setSpeed(0);
}

void twitch(int count) {
  for (int i = 0; i < count; i++) {
    motorRun(SPEED, 100 );               //(int pwm, int duration)
    stop(100);                             //Stop then pause
    motorRun(-SPEED, 100 );               //(int pwm, int duration)
  }
  motor1.setSpeed(0);
}

void stop(int duration) {
  motor1.setSpeed(0);     // Motor 1 stops.
  delay (duration);
}

/*
  void rampUp() {
  motor1.setSpeed(0);     // Motor 1 stops.
  for (int i = 0; i < 128; i++) {
    motor1.setSpeed(i);   // Motor 1 runs forward
    delay(10);
  }
  motor1.setSpeed(0);     // Motor 1 stops.
  }
*/


// ---------- button functions ----------
void singleClick() {
  Serial.println(F("singleClick=twitch(5)"));
  twitch(5);
}

void doubleclick() {
  Serial.println(F("doubleClick=largeTwitch(1)"));
  //largeTwitch(1);
}

void longPress() {
  Serial.println(F("longPress=wag(5)"));
  wag(5);
}
