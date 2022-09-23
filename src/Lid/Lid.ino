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

const int MOTOR_PIN = D3;                  //Controls the motor. (violet)
const int closedSwitch = D1;              //Limit pin, stops the motor. (yellow)
const int openSwitch = D2;                //Limit pin, stops the motor. (pink)
const int EYES_PIN = D5;
const int FAN_PIN = D6;
const int maxTorque = 255;
#define SIMULATION
#ifdef SIMULATION                         //The simulation motor needs more torque to start
const int runTorque = maxTorque;
#else
const int runTorque = 150;
#endif


const long int Minutes = 60000;           //ms per minute
const long int Seconds = 1000;            //ms per second
bool flagMotorOn = false;
const int MIN_PWM = 200;                  //Anything lower and the motor won't start
int motorPwm = MIN_PWM;                   //PWM value for motor on.
int lidState;
int bounceCount = 0;
bool randomFlag=false;                    //Set true to open/close untill stopped.

// --------------- noDelay ---------------
#include <NoDelay.h>

// prototypes (noDelay callbacks)
void eyes_ON();
void eyes_OFF();
void eyes_DIM();
void lidRandom();



//Create noDelay objects
// objName(time,callback,isEnabled);
noDelay eyesLED_onTime(1000, eyes_ON , false);
noDelay eyesLED_offTime(1000, eyes_OFF, false);
noDelay eyesLED_dim(200, eyes_DIM , true);           //How fast to dim the LED. Lower is faster
noDelay lidOpenTime(1000, lidRandom, false);
noDelay lidCloseTime(2000, closeTheLid, false);



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
