/*
   NoDelay-Function-Experiments.ino

   This test is simulating the peek and blink functions for my
   Halloween monster box
*/


/* To create a NoDelay object:
   noDelay object(1000);                    //Makes an object of given time in ms
   noDelay object(1000, function_to_call);  //Makes an object in ms that will call the given function
   noDelay object(1000,false);              //Makes an object of given time in ms but keeps it from running
   noDelay object(1000, function, false);   //Makes object in ms that will call function but keep it from running

    Methods
    update() : When called it will check if the amount of time set has passed.
    setdelay() : This function is used to adjust the amount of time it takes for NoDelay to wait for.
    start() : Start is used to reset the timer or to start NoDelay again when it has been stopped.
    stop() : This function will keep NoDelay from returning true or running a function when calling update().
*/

#include <NoDelay.h>

//---------- prototypes ----------
void peek_ON();
void peek_OFF();
void eyes_ON();
void eyes_OFF();
void eyes_DIM();


//Create noDelay objects
noDelay peekLED_onTime(1000, peek_ON , false);
noDelay peekLED_offTime(1000, peek_OFF, false);
noDelay eyesLED_onTime(1000, eyes_ON , false);
noDelay eyesLED_offTime(1000, eyes_OFF, false);
noDelay eyesLED_dim(20, eyes_DIM , true);           //How fast to dim the LED. Lower is faster

const int LED_ON = 1;
const int LED_OFF = 0;
const int LED_PEEK_PIN = D2;
const int LED_EYE_PIN = D1;


int eyeVal = 0;
const int EYES_MIN = 5;            //Eye will dim to this value in loop
const int EYES_MAX = 100;          //peek_ON will bring eye back to this level.


// ---------- setup ----------
void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(F("NoDelay-Function-Experiments.ino"));
  Serial.println();

  pinMode(LED_PEEK_PIN, OUTPUT);
  pinMode(LED_EYE_PIN, OUTPUT);
  digitalWrite(LED_PEEK_PIN, LED_OFF);
  digitalWrite(LED_EYE_PIN, LED_OFF);


  //Start the LED timers
  peek_ON();                     //The ON functions will start OFF functions.
  eyes_ON();
}


// ---------- loop ----------
void loop() {
  peekLED_onTime.update();        //If time has past, run set function
  peekLED_offTime.update();
  eyesLED_onTime.update();
  eyesLED_offTime.update();        //Blink eye
  eyesLED_dim.update();            //Dim eye

}


void peek_ON() {
  //The peek ON timer has dinged.
  //Turn on the LED, stop the ON timer then start the OFF timer.
  digitalWrite(LED_PEEK_PIN, LED_ON);                   //Turn on the peek LED
  peekLED_onTime.stop();                                //Stop the ON timer
  peekLED_offTime.setdelay(random(1000, 5000));         //LED will be on for this time.
  peekLED_offTime.start();                              //Start the OFF timer
  eyeVal = EYES_MAX;
}

void peek_OFF() {
  digitalWrite(LED_PEEK_PIN, LED_OFF);                 //Turn off the peek LED
  peekLED_offTime.stop();                              //Stop the OFF timer
  peekLED_onTime.setdelay(random(1000, 6000));         //LED will be off for this time.
  peekLED_onTime.start();                              //Start the ON timer
}

void eyes_ON() {
  analogWrite(LED_EYE_PIN, eyeVal);
  eyesLED_onTime.stop();                                //Stop the ON timer
  eyesLED_offTime.setdelay(random(1500, 4000));         //LED will be on for this time.
  eyesLED_offTime.start();                              //Start the OFF timer
}

void eyes_OFF() {
  digitalWrite(LED_EYE_PIN, LED_OFF);                   //Turn off the eye LED
  eyesLED_offTime.stop();                                //Stop the OFF timer
  eyesLED_onTime.setdelay(random(100, 150));             //LED will be off for this time.
  eyesLED_onTime.start();                                //Start the ON timer
}

void eyes_DIM() {
  //Fade the eyeVal
  if (eyeVal > EYES_MIN) {
    eyeVal -= 1;
    analogWrite(LED_EYE_PIN, eyeVal);
  }
}
