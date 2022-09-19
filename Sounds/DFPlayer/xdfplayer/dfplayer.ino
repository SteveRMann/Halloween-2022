#define SKETCH "dfplayer"
#define VERSION "1.0"

/*
  Control the DFPlayer ADKEY1 pin through a GPIO port.
*/

const int TRACK1_PIN = D5;
const int TRACK2_PIN = D3;
const int PLAY_PAUSE_PIN = D6;
const int PREV_VOLdn_PIN = D1;
const int NEXT_VOLup_PIN = D2;
//const int TX_PIN = D7;
//const int RX_PIN = D8;


//--------------- WiFi declarations ---------------
// WiFi declarations
#include <ESP8266WiFi.h>        // Not needed if also using the Arduino OTA Library...
#include <Kaywinnet.h>          // WiFi credentials
char macBuffer[24];             // Holds the last three digits of the MAC, in hex.
char hostName[24];              // Holds nodeName + the last three bytes of the MAC address.
char nodeName[] = SKETCH;       // Give this node a name


//--------------- ticker declarations ---------------
//for WiFi status
#include <Ticker.h>
Ticker blueTicker;                       //Ticker object for the WiFi Connecting LED
const int BLUE_LED_PIN = D4;             //D4 is LED_BUILTIN on Wemos D1 Mini


//--------------- MQTT declarations ---------------
#include <ESP8266WiFi.h>        // Connect (and reconnect) an ESP8266 to the a WiFi network.
#include <PubSubClient.h>       // connect to a MQTT broker and publish/subscribe messages in topics.
// Declare an object of class WiFiClient, which allows to establish a connection to a specific IP and port
// Declare an object of class PubSubClient, which receives as input the constructor previously defined with WiFiClient.
// The constructor MUST be unique on the network. (Does it?)
WiFiClient dfplayer;
PubSubClient client(dfplayer);

const char *mqttServer = MQTT_SERVER;         // Local broker defined in Kaywinnet.h
const int mqttPort = 1883;

// Declare strings for the topics. Topics will be created in setup_mqtt().
char statusTopic[20];
char cmndTopic[20];
char rssiTopic[20];

//--------------- OTA declarations ---------------
#include <ArduinoOTA.h>
