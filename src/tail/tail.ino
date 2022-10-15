

#define SKETCH "tail"
#define VERSION "4.0"

//Version 4.0 - Added a LDR sensor to detect the motor turns
#define LEDOFF LOW
#define LEDON HIGH
#define LEDPIN D4
#define LDRPIN A0
int threshold = 800;


#include "myFunctions.h"
#include "myOTA.h"
#include "myWifiMulti.h"
#include "myTicker.h"


// Configure the motor driver.
#include "CytronMotorDriver.h"
CytronMD motor1(PWM_PWM, D1, D2);   // PWM 1A = Pin D1, PWM 1B = Pin D2.

#ifndef nodeNameD
#define nodeNameD
char nodeName[] = SKETCH;
#endif


//GPIO Pins
const int BUTTON_PIN = D3;

int endTime = 0;                      // Used in the random wag



// --------------- Button declarations ---------------
#include "OneButton.h"
OneButton button(BUTTON_PIN);


// --------------- Motor declarations ---------------
int motorState=0;
int pwm;
int duration;
