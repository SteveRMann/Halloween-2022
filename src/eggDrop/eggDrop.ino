#define SKETCH "eggDrop"
#define VERSION "2.0"

const int servo1Pin = D1;           //Drop servo
const int servo2Pin = D2;           //Preload servo
const int servo1LedPin = D3;
const int servo2LedPin = D4;
const int BUTTON_PIN = D5;
const int BLUE_LED_PIN = D6;
const int EYES_PIN = D7;

bool stressFlag = false;
const int STRESS_PERIOD = 10000;    //How long between stress cycles
unsigned int lastTimeChecked = 0;
unsigned long loopMillis = 0;

#define ledON 1
#define ledOFF 0

#include <ArduinoOTA.h>

//for LED status
#include <Ticker.h>
Ticker blueTicker;                //Ticker object for the WiFi Connecting LED

//--------------- WiFi declarations ---------------
// WiFi declarations
#include <ESP8266WiFi.h>        // Not needed if also using the Arduino OTA Library...
#include <Kaywinnet.h>          // WiFi credentials
char macBuffer[24];             // Holds the last three digits of the MAC, in hex.
char hostName[24];              // Holds nodeName + the last three bytes of the MAC address.
char nodeName[] = SKETCH;       // Give this node a name


#include <Servo.h>
Servo servoOne;                     // Exit servo
Servo servoTwo;                     // Preload servo

int servo1Position;
int servo2Position;
const int dropDelay = 700;          // How long the drop servo is open.
const int loadDelay = 450;          // How long the load servo is open.


//--------------- MQTT declarations ---------------
#include <ESP8266WiFi.h>        // Connect (and reconnect) an ESP8266 to the a WiFi network.
#include <PubSubClient.h>       // connect to a MQTT broker and publish/subscribe messages in topics.
// Declare an object of class WiFiClient, which allows to establish a connection to a specific IP and port
// Declare an object of class PubSubClient, which receives as input of the constructor the previously defined WiFiClient.
// The constructor MUST be unique on the network. (Does it?)
WiFiClient eggdrop;
PubSubClient client(eggdrop);

// Declare strings for the topics. Topics will be created in setup_mqtt().
char statusTopic[20];
char cmndTopic[20];
char rssiTopic[20];

const char *mqttServer = MQTT_SERVER;         // Local broker defined in Kaywinnet.h
const int mqttPort = 1883;

const int eyesMax = 255;
const int eyesMin = 25;
int eyes = 100;                       //Eyes intensity

// -------------- setup() --------------
void setup() {
  pinMode(servo1LedPin, OUTPUT);
  pinMode(servo2LedPin, OUTPUT);
  pinMode(EYES_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);      // Must be before calling setup_wifi
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  beginSerial();
  setup_wifi();                       // MUST be before setupMqtt()
  start_OTA();                        // If using OTA
  setup_mqtt();                       // Generate the topics

  // Call the setServer method on the PubSubClient object
  client.setServer(mqttServer, mqttPort);
  mqttConnect();


  /*
    Specs in https://www.servocity.com/hs-645mg-servo/
    pin: the number of the pin that the servo is attached to
    min: pulse width, in us, corresponding to the 0 degree angle on the servo (defaults to 544)
    max: pulse width, in us, corresponding to the 180 degree angle on the servo (defaults to 2400)

    Use ServoManualSweep.ino to calibrate these end points.
  */
  //servoOne.attach(servo1Pin, 400, 2400);    //PWM range for HS-645MG servos
  servoOne.attach(servo1Pin, 625, 2600);    //PWM range for SG90 servos
  servoTwo.attach(servo2Pin, 625, 2600);    //PWM range for SG90 servos

  dropServoClose();
  loadServoClose();
  stressFlag = false;

  //digitalWrite(BLUE_LED_PIN, ledON);
  analogWrite(BLUE_LED_PIN, 50);            //Leave it on, but dim.


  //Cycle through the eyes' LED intensity.
  for (int j = 0; j < 4; j++) {
    for (int i = 10; i < 255; i++) {
      analogWrite(EYES_PIN, i);
      delay(2);
    }
    for (int i = 255; i > 10; i--) {
      analogWrite(EYES_PIN, i);
      delay(2);
    }
  }
  eyes = eyesMin;
  analogWrite(EYES_PIN, eyes);
  delay(1000);
}


// -------------- loop() --------------
void loop() {
  ArduinoOTA.handle();
  mqttReconnect();         //Make sure we stay connected to the mqtt broker
  loopMillis = millis();

  if (stressFlag) stress();
  int i = digitalRead(BUTTON_PIN);
  if (i == 0) dropEgg(1);

  if (eyes > eyesMin) {
    eyes -= 1;
    analogWrite(EYES_PIN, eyes);
    delay(10);
  }
}
