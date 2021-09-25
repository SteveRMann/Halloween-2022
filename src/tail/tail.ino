#define SKETCH "tail"
#define VERSION "2.0"

//GPIO Pins
const int MOTOR1 = D1;
const int MOTOR2 = D2;
const int BUTTON_PIN = D3;


#include <ArduinoOTA.h>

//--------------- WiFi declarations ---------------
// WiFi declarations
#include <ESP8266WiFi.h>        // Not needed if also using the Arduino OTA Library...
#include <Kaywinnet.h>          // WiFi credentials
char macBuffer[24];             // Holds the last three digits of the MAC, in hex.
char hostName[24];              // Holds nodeName + the last three bytes of the MAC address.
char nodeName[] = SKETCH;       // Give this node a name


// --------------- ticker declarations ---------------
// for LED status
#include <Ticker.h>
Ticker blueTicker;
const int BLUE_LED_PIN = D4;


//--------------- MQTT declarations ---------------
#include <ESP8266WiFi.h>        // Connect (and reconnect) an ESP8266 to the a WiFi network.
#include <PubSubClient.h>       // connect to a MQTT broker and publish/subscribe messages in topics.
// Declare an object of class WiFiClient, which allows to establish a connection to a specific IP and port
// Declare an object of class PubSubClient, which receives as input the constructor previously defined with WiFiClient.
// The constructor MUST be unique on the network. (Does it?)
WiFiClient tail;
PubSubClient client(tail);

const char *mqttServer = MQTT_SERVER;         // Local broker defined in Kaywinnet.h
const int mqttPort = 1883;

// Declare strings for the topics. Topics will be created in setup_mqtt().
char statusTopic[20];
char cmndTopic[20];
char rssiTopic[20];


// --------------- button declarations ---------------
#include "OneButton.h"
OneButton button(BUTTON_PIN);
