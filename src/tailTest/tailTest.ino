#define SKETCH "tail"
#define VERSION "5.0"

#define LEDOFF LOW
#define LEDON HIGH
#define LEDPIN D4               //LED_BUILTIN on most boards
#define LIMITPIN D5

bool motorState = false;

const int SPEED = 24;
const int HALFSPEED = SPEED / 2;
const int QUARTERSPEED = HALFSPEED / 2;
const int FASTSPEED = SPEED * 2;;

// Configure the motor driver.
#include "CytronMotorDriver.h"
CytronMD motor1(PWM_PWM, D1, D2);   // PWM 1A = Pin D1, PWM 1B = Pin D2.


IRAM_ATTR void limitSwitchHandler() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) {
    //Not a bounce, do your thing
    motorState = !motorState;                //Limit switch is closed, stop the motor
  }
  last_interrupt_time = interrupt_time;
}


// --------------- ticker declarations ---------------
#include <Ticker.h>
Ticker wagTicker;
int tickerInterval = 1000;      //Time between wags?
bool wagFlag = false;


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

  //Setup the limit pin interrupt
  pinMode(LEDPIN, OUTPUT);
  pinMode(LIMITPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LIMITPIN), limitSwitchHandler, FALLING);

  wagFlag = true;                   //Wag as long as this is true.
}



void loop() {
  Serial.print(F("motorState= "));
  Serial.println(motorState);

  //Run the motor until the limit switch is closed.
  if (motorState) {                //If the motor is not moving...
    motor1.setSpeed(0);            //Turn off the motor
  }
  else {
    motor1.setSpeed(SPEED);         //Turn on the motor
    delay(100);                     //Let the motor turn past the limit switch
    motor1.setSpeed(SPEED / 2);     //Slow the motor down
  }
}
