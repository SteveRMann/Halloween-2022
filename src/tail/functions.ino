// --------------- General functions ---------------
// --------------- Unique to this sketch ---------------

const int SPEED = 24;
const int HALFSPEED = SPEED / 2;
const int QUARTERSPEED = HALFSPEED / 2;
const int FASTSPEED = SPEED * 2;;



//A wag starts here
void wag(int count) {
  for (int i = 0; i < count; i++) {
    pwm = SPEED;
    duration = 800;         //How long a wag lasts
    motorRun();
  }
}

void motorRun() {
  //Start the ticker
  motorTicker.attach_ms(duration, myTicker::motorStop);
  motor1.setSpeed(pwm);               //Turn on the motor
  motorFlag = false;
  motorState = 1;
}




// ---------- button functions ----------
void singleClick() {
  Serial.println(F("singleClick=twitch(5)"));
//  twitch(5);
}

void doubleclick() {
  Serial.println(F("doubleClick=largeTwitch(1)"));
//  largeTwitch(1);
}

void longPress() {
  Serial.println(F("longPress=wag(5)"));
  wag(5);
}
