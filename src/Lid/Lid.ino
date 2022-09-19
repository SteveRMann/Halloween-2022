#define SKETCH "lid.ino"
#define VERSION "6.8"
//Version 6.5- Made eyes blink
//Version 6.6- Using nodelay.h for dimming the eyes
//Version 6.7- Synchronizing with sounds.
//             Starts when MQTT topic lid/cmnd + message "roar" is received.
//Version 6.8- WIP Removed all sync functions to simplify the code.

/*
   Using Wemos D1 Mini
   Project is a monster box. The motor slightly opens the box periodically
   and randomly.
*/


const int LED_ON = 1;
const int LED_OFF = 0;

const int motorPin = D3;                  //Controls the motor. (violet)
const int closedSwitch = D1;              //Limit pin, stops the motor. (yellow)
const int openSwitch = D2;                //Limit pin, stops the motor. (pink)
//const int buttonPin = D4;
const int EYES_PIN = D5;
const int FAN_PIN = D6;

const long int Minutes = 60000;           //ms per minute
const long int Seconds = 1000;            //ms per second
bool flagMotorOn = false;
const int MIN_PWM = 200;                  //Anything lower and the motor won't start
int motorPwm = MIN_PWM;                   //PWM value for motor on.
int lidState;
int bounceCount = 0;


// --------------- noDelay ---------------
#include <NoDelay.h>

// prototypes (noDelay callbacks)
void eyes_ON();
void eyes_OFF();
void eyes_DIM();
void syncOpen();
void syncClose();


//Create noDelay objects
noDelay eyesLED_onTime(1000, eyes_ON , false);
noDelay eyesLED_offTime(1000, eyes_OFF, false);
noDelay eyesLED_dim(200, eyes_DIM , true);           //How fast to dim the LED. Lower is faster
noDelay sync_open_timer(100, syncOpen , false);
noDelay sync_close_timer(100, syncClose , false);



// --------------- lid sync timing ---------------
// These are the time points for the lid state change
// Odd is open, even is close.
const int t0 = 0;         //cmnd received
const int t1 = 467;       //ms until first open
const int t2 = 1067;
const int t3 = 2102;
const int t4 = 2702;
const int t5 = 3470;
const int t6 = 4070;
const int t7 = 5038;
const int t8 = 5638;
const int t9 = 6673;
const int t10 = 7273;

unsigned int syncTbl[] = {t1 - t0, t2 - t1, t3 - t2, t4 - t3, t5 - t4, t6 - t5, t7 - t6, t8 - t7, t9 - t8, t10 - t9};
int syncTblPtr = 0;
int syncPtr=0;
int tblN;


// --------------- button declarations ---------------
const int BUTTON_PIN = D4;
#include "OneButton.h"
OneButton button(BUTTON_PIN);


//--------------- WiFi declarations ---------------
// WiFi declarations
#include <ESP8266WiFi.h>        // Not needed if also using the Arduino OTA Library...
#include <Kaywinnet.h>          // WiFi credentials
char macBuffer[24];             // Holds the last three digits of the MAC, in hex.
char hostName[24];              // Holds nodeName + the last three bytes of the MAC address.
char nodeName[] = SKETCH;       // Give this node a name



//--------------- OTA declarations ---------------
#include <ArduinoOTA.h>



//--------------- MQTT declarations ---------------
#include <ESP8266WiFi.h>        // Connect (and reconnect) an ESP8266 to the a WiFi network.
#include <PubSubClient.h>       // connect to a MQTT broker and publish/subscribe messages in topics.
// Declare an object of class WiFiClient
// Declare an object of class PubSubClient, which receives as input of the constructor the previously defined WiFiClient.
// The constructor MUST be unique on the network. (Does it?)
WiFiClient monsterBoxLid;
PubSubClient client(monsterBoxLid);

// Declare strings for the topics. Topics will be created in setup_mqtt().
char statusTopic[20];
char cmndTopic[20];
char rssiTopic[20];
char syncTopic[20];

const char *mqttServer = MQTT_SERVER;         // Local broker defined in Kaywinnet.h
const int mqttPort = 1883;



//--------------- ticker ---------------
const int BLUE_LED_PIN = D7;             //D4 is LED_BUILTIN on Wemos D1 Mini
//for LED status
#include <Ticker.h>
Ticker blueTicker;                       //Ticker object for the WiFi Connecting LED




// --------------- Global stuff ---------------
int eyesVal = 0;
const int EYES_MIN = 5;            //Eye will dim to this value in loop
const int EYES_MAX = 100;          //open() will bring eye back to this level.

const int FAN_MAX = 255;
const int FAN_MIN = 255;
