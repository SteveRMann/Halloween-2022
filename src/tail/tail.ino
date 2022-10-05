#define SKETCH "tail"
#define VERSION "3.0"

#include "myFunctions.h"
#include "myOTA.h"
#include "myWiFiMulti.h"
#include "myMqtt.h"

// Configure the motor driver.
#include "CytronMotorDriver.h"
CytronMD motor1(PWM_PWM, D1, D2);   // PWM 1A = Pin D1, PWM 1B = Pin D2.

#ifndef nodeNameD
#define nodeNameD
char nodeName[] = SKETCH;
#endif


//GPIO Pins
const int BUTTON_PIN = D3;



// --------------- ticker declarations ---------------
// for LED status
#include <Ticker.h>
Ticker blueTicker;
const int BLUE_LED_PIN = D4;


// --------------- button declarations ---------------
#include "OneButton.h"
OneButton button(BUTTON_PIN);
