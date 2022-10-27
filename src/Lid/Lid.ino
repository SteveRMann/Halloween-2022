#define SKETCH "lid.ino"
#define VERSION "7.0"
#define NODENAME "lid"


//Version 6.5- Made eyes blink
//Version 6.6- Using nodelay.h for dimming the eyes
//Version 6.7- Synchronizing with sounds.
//             Starts when MQTT topic lid/cmnd + message "roar" is received.
//Version 6.8- WIP Removed all sync functions to simplify the code.
//Version 7.0- Use interrupt for buttons.

/*
   Using Wemos D1 Mini
   Project is a monster box. The motor slightly opens the box periodically
   and randomly.
*/


const int LED_ON = 1;
const int LED_OFF = 0;
int sensorPin = A0;    // potentiometer used in motortest (seup.ino)
int sensorValue = 0;

const int closedSwitch = D1;              //Limit pin, stops the motor. (yellow)
const int openSwitch = D2;                //Limit pin, stops the motor. (pink)
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



//--------------- WiFiMulti declarations ---------------
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;

// WiFi connect timeout per AP. Increase when connecting takes longer.
const uint32_t connectTimeoutMs = 5000;

// setup_wifi vars
char macBuffer[24];       // Holds the last three digits of the MAC, in hex.
char hostNamePrefix[] = NODENAME;
char hostName[12];        // Holds hostNamePrefix + the last three bytes of the MAC address.



//--------------- OTA declarations ---------------
#include <ArduinoOTA.h>



//--------------- MQTT declarations ---------------
#include "Kaywinnet.h"
#include <ESP8266WiFi.h>        // Connect (and reconnect) an ESP8266 to the a WiFi network.
#include <PubSubClient.h>       // connect to a MQTT broker and publish/subscribe messages in topics.
// Declare an object of class WiFiClient
// Declare an object of class PubSubClient, which receives as input of the constructor the previously defined WiFiClient.
// The constructor MUST be unique on the network. (Does it?)
WiFiClient monsterBoxLid;
PubSubClient client(monsterBoxLid);

// Make the MQTT topics
// Declare strings for the topics. Topics will be created in setup_mqtt().
char statusTopic[20];
char cmndTopic[20];
char rssiTopic[20];

const char *mqttServer = MQTT_SERVER;         // Local broker defined in Kaywinnet.h
const int mqttPort = 1883;



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