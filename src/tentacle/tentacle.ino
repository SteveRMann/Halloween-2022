#define SKETCH "tentacle"
#define VERSION "1.0"

#define LEDOFF LOW
#define LEDON HIGH
//#define LEDPIN D4               //LED_BUILTIN on most boards
#define LEDPIN D6
#define LIMITPIN D5

int motorState = 0;
bool motorDirection = false;

const int SPEED = 48;
int motorSpeed = SPEED;

// Configure the motor driver.
#include "CytronMotorDriver.h"
CytronMD motor1(PWM_PWM, D1, D2);   // PWM 1A = Pin D1, PWM 1B = Pin D2.



// --------------- ticker declarations ---------------
#include <Ticker.h>
Ticker wagTicker;
int tickerInterval = 1000;      //Time between wags?
bool wagFlag = false;


// --------------- Limit Switch Interrupt Handler ---------------
IRAM_ATTR void limitSwitchHandler() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 20ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 20) {
    //Not a bounce, do your thing
    motorState = 2;
  }
  last_interrupt_time = interrupt_time;
}


// ----- Function to randomize wags -----
void periodicWag() {
  wagFlag = true;                                   //We can't put wag() here in a callback because it uses delay()
  tickerInterval = random(1000, 6000);
  Serial.print(F("tickerInterval= "));
  Serial.println(tickerInterval);
  wagTicker.detach();
  wagTicker.attach_ms(tickerInterval, periodicWag); //Start the timer to the next wag.
}



void setup() {
  // -------------- beginSerial() --------------
  while (!Serial);
  Serial.begin( 115200 );
  Serial.println();
  Serial.println();
  Serial.print(SKETCH);
  Serial.print(".ino, Version ");
  Serial.println(VERSION);
  Serial.println(F("++++++++++++++++++ +"));

  //Setup the GPIO pins
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LEDOFF);
  pinMode(LIMITPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LIMITPIN), limitSwitchHandler, FALLING);

  motorState = 0;
}



void motorStart(int speed) {
  //Start the motor long enough to get past the limit switch
  motor1.setSpeed(speed);         //Turn on the motor
  delay(100);                      //Let the motor turn past the limit switch
  motor1.setSpeed(speed / 2);     //Slow the motor down
}


void loop() {
  switch (motorState) {
    case (0):
      //Motor is stopped, start it and move to case 1
      motorStart(motorSpeed);
      motorState = 1;
      break;
    case (1):
      //Start the motor running, waiting for interrupt to set state to 2
      digitalWrite(LEDPIN, LEDON);
      break;
    case (2):
      //Interrupt happened. Stop the motor and move to state 3
      motor1.setSpeed(0);         //Stop motor
      delay(500);
      motorState = 3;
      break;
    case (3):
      //Delay ended, toggle direction and move to state 3
      motorSpeed = motorSpeed * -1;
      motorState = 4;             //Start over in the opposite direction
      break;
    case (4):
      //Delay between wags then go back to state 0 to start over.
      delay(1000);
      motorState = 0;
      break;
  }
}
