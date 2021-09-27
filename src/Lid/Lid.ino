#define SKETCH "Lid"
#define VERSION "6.1"

/*
   Brushed Motor Speed Control
   Using Wemos D1 Mini

   Project is a monster box. The motor slightly opens the box periodically
   and randomly. Inside the box will be a second motor that spins a chain
   to make noise.
*/

#define TENSEC 10000
#define FIVESEC 5000

const int motorPin = D1;                  //Controls the motor. (red)
const int startSwitch = D2;               //Starts the motor. (blue)
const int closedSwitch = D3;              //Limit pin, stops the motor. (orange)
const int openSwitch = D4;                //Limit pin, stops the motor. (yellow)
const int ledPin = D5;                    //Control for the LED "eyes". (green)
const int tailPin = D6;                   //Control for the tail movement. (violet)

const long int Minutes = 60000;           //ms per minute
const long int Seconds = 1000;            //ms per second
bool flagMotorOn = false;
const int MIN_PWM = 200;                  //Anything lower and the motor won't start
int motorPwm = MIN_PWM;                   //PWM value for motor on.
int lidState;
int bounceCount = 0;
int motorState = 0;



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
const int BLUE_LED_PIN = LED_BUILTIN;    //D4 is LED_BUILTIN on Wemos D1 Mini
//for LED status
#include <Ticker.h>
Ticker blueTicker;                       //Ticker object for the WiFi Connecting LED
