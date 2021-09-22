#define SKETCH "eggDrop"
#define VERSION "2.0"

const int servo1Pin = D1;           //Drop servo
const int servo2Pin = D2;           //Preload servo
const int servo1LedPin = D3;
const int servo2LedPin = D4;

bool stressFlag = false;
const int STRESS_PERIOD = 10000;    //How long between stress cycles
unsigned int lastTimeChecked = 0;
unsigned long loopMillis = 0;

#define ledON 1
#define ledOFF 0

#include <ArduinoOTA.h>

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



// -------------- setup() --------------
void setup() {
  beginSerial();
  setup_wifi();                   // MUST be before setupMqtt()
  start_OTA();                    // If using OTA
  setup_mqtt();                   // Generate the topics

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

  pinMode(servo1LedPin, OUTPUT);
  pinMode(servo2LedPin, OUTPUT);

  dropServoClose();
  loadServoClose();
  stressFlag = false;

  delay(1000);
}


// -------------- loop() --------------
void loop() {
  ArduinoOTA.handle();
  mqttReconnect();         //Make sure we stay connected to the mqtt broker
  loopMillis = millis();

  if (stressFlag) stress();
}


// -------------- dropEgg() --------------
void dropEgg(int howMany) {
  printf("\nDropping\n");
  if (servo1Position != 90) {            //Make sure we're closed.
    dropServoClose();
    loadServoClose();
    delay(500);
  }
  while (howMany > 0) {
    howMany--;
    printf(" egg# %d.\n", howMany);
    dropServoOpen();                            //Exit
    digitalWrite (servo1LedPin, ledON);
    delay(dropDelay);
    dropServoClose();
    digitalWrite (servo1LedPin, ledOFF);
    delay(dropDelay);                   //Let 'drop' close before 'load' opens


    loadServoOpen();                            //Load
    digitalWrite (servo2LedPin, ledON);
    delay(loadDelay);
    loadServoClose();
    digitalWrite (servo2LedPin, ledOFF);

    delay(2000);                     //Time between eggs
  }
}

// -------------- dropServoOpen() --------------
void dropServoOpen() {                          //Open the exit
  servoOne.write(0);
  servo1Position = 0;
}

// -------------- dropServoClose() --------------
void dropServoClose() {                         //Close the exit
  servoOne.write(90);
  servo1Position = 90;
}

// -------------- loadServoOpen() --------------
void loadServoOpen() {                          //Open the preload servo
  servoTwo.write(0);
  servo2Position = 0;
}

// -------------- loadServoClose() --------------
void loadServoClose() {                         //Close the preload
  servoTwo.write(90);
  servo2Position = 90;
}

// -------------- stress() --------------
void stress() {
  //Drop an egg every STRESS_PERIOD
  if (millis() - lastTimeChecked >= STRESS_PERIOD) {
    dropEgg(1);
    lastTimeChecked = millis();
  }
}


// -------------- beginSerial() --------------
void beginSerial() {
  while (!Serial);
  Serial.begin( 115200 );
  Serial.println();
  Serial.println();
  Serial.print(SKETCH);
  Serial.print(".ino, Version ");
  Serial.println(VERSION);
  Serial.println(F("++++++++++++++++++ +"));
}

// ********************** Function to display a string for debugging. **********************
void dbugs(const char *s, const char *v) {
  //Show a string variable. Enter with the string description and the string.
  //Example dbugs("My String= ",myString);
  Serial.print(s);
  Serial.print (F("\""));
  Serial.print(v);
  Serial.println(F("\""));
}
