#define SKETCH "dfplayer2"
#define VERSION "1.0"

//Version 1.0, Simplified clone of dfplayer.ino

/*
  Control the DFPlayer ADKEY1 pin through GPIO ports.
*/

const int TRACK1_PIN = D5;
const int TRACK2_PIN = D3;
const int PLAY_PAUSE_PIN = D6;
const int PREV_VOLdn_PIN = D1;
const int NEXT_VOLup_PIN = D2;


//--------------- ticker declarations ---------------
//for WiFi status
#include <Ticker.h>
Ticker blueTicker;                       //Ticker object for the WiFi Connecting LED
const int BLUE_LED_PIN = D4;             //D4 is LED_BUILTIN on Wemos D1 Mini

//--------------- WiFi declarations ---------------
// WiFi declarations
#include <ESP8266WiFi.h>        // Not needed if also using the Arduino OTA Library...
#include <Kaywinnet.h>          // WiFi credentials
char macBuffer[24];             // Holds the last three digits of the MAC, in hex.
char hostName[24];              // Holds nodeName + the last three bytes of the MAC address.
char nodeName[] = SKETCH;       // Give this node a name

//--------------- OTA declarations ---------------
#include <ArduinoOTA.h>
