#define SKETCH "lid2.ino"
#define VERSION "1.0"

//Version 1.0- Simplified from lid 2021 for 2022.

/*
   Using Wemos D1 Mini
   Project is a monster box. The motor slightly opens the box periodically
   and randomly.

   TO DO - Eyes need to blink when on.
*/


const int LED_ON = 1;
const int LED_OFF = 0;
int sensorPin = A0;    // potentiometer used in motortest (seup.ino)
int sensorValue = 0;

const int CLOSED_SWITCH = D1;              //Limit pin, stops the motor. (yellow)
const int OPEN_SWITCH = D2;                //Limit pin, stops the motor. (pink)
const int MOTOR_PIN = D3;                 //Controls the motor. (violet)
const int BUTTON_PIN = D4;                //Action button (Also LED_BUILTIN)
const int EYES_PIN = D5;                  //Eyes
const int FAN_PIN = D6;                   //Mist fan
const int BLUE_LED_PIN = D8;              //WiFi Status
const int LOOP_PIN = D7;                  //Loop button

int maxTorque = 255;
int runTorque = 165;



const long int MINUTES = 60000;           //ms per minute
const long int SECONDS = 1000;            //ms per second
//bool motorOnFlag = false;
const int MIN_PWM = 200;                  //Anything lower and the motor won't start
int motorPwm = MIN_PWM;                   //PWM value for motor on.
// (not used) int lidState;
// (not used) int bounceCount = 0;
bool randomFlag = false;                  //Set true to open/close untill stopped.


// --------------- noDelay ---------------
#include <NoDelay.h>

// prototypes (noDelay callbacks)
void eyes_ON();
void eyes_OFF();
void eyes_DIM();
void lidRandom();
void closeTheLid();


//Create noDelay objects
// objName(time,callback,isEnabled);
noDelay eyesLED_onTime(1000, eyes_ON , false);
noDelay eyesLED_offTime(1000, eyes_OFF, false);
noDelay eyesLED_dim(200, eyes_DIM , true);           //How fast to dim the LED. Lower is faster
noDelay lidOpenTime(1000, lidRandom, false);
noDelay lidCloseTime(2000, closeTheLid, false);



// --------------- button declarations ---------------
volatile bool buttonFlag = false;         //True when sction button is pressed
volatile bool loopFlag = false;           //True when loop button is pressed



//--------------- ticker ---------------
//for LED status
#include <Ticker.h>
Ticker blueTicker;                       //Ticker object for the WiFi Connecting LED




// --------------- Global stuff ---------------
int eyesVal = 0;
const int EYES_MIN = 5;            //Eye will dim to this value in loop
const int EYES_MAX = 100;          //open() will bring eye back to this level.

const int FAN_MAX = 255;
const int FAN_MIN = 128;
const int FAN_OFF = 0;
