#define SKETCH "lid"
#define VERSION "6.4"
//Version 6.4 added button.h functions

/*
   Brushed DC Motor Control
   Using Wemos D1 Mini

   Project is a monster box. The motor slightly opens the box periodically
   and randomly. Inside the box will be a second motor that spins a chain
   to make noise.
*/

#define TENSEC 10000
#define FIVESEC 5000

const int motorPin = D3;                  //Controls the motor. (violet)
const int closedSwitch = D1;              //Limit pin, stops the motor. (yellow)
const int openSwitch = D2;                //Limit pin, stops the motor. (pink)
//const int buttonPin = D4;
const int LEDS_PIN = D5;
const int FAN_PIN = D6;

const long int Minutes = 60000;           //ms per minute
const long int Seconds = 1000;            //ms per second
bool flagMotorOn = false;
const int MIN_PWM = 200;                  //Anything lower and the motor won't start
int motorPwm = MIN_PWM;                   //PWM value for motor on.
int lidState;
int bounceCount = 0;


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
Ticker eyesTicker;           //Testing

//--------------- lid timing ---------------
/* This is the timing of opens (even) and closes (odds).
  The numbers are millisceonds from the start of track1.mp3
  as played from dfplayer.ino.
  The sequence is started when an MQTT message is received
  on topic: lid/cmnd/sync
*/
const int T0 = 0;
const int T1 = 4862;
const int T2 = 5965;
const int T3 = 9517;
const int T4 = 9965;
const int T5 = 16862;
const int T6 = 17793;
const int T7 = 21586;
const int T8 = 22275;
const int T9 = 23000;
const int T10 = 23965;
const int T11 = 25000;
