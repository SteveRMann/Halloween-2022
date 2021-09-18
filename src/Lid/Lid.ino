#define SKETCH_NAME "Lid.ino"
#define SKETCH_VERSION "6.0"

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
char nodeName[] = SKETCH_NAME;  // Give this node a name



//--------------- OTA declarations ---------------
#include <ArduinoOTA.h>



//--------------- MQTT declarations ---------------
#include <ESP8266WiFi.h>        // Connect (and reconnect) an ESP8266 to the a WiFi network.
#include <PubSubClient.h>       // connect to a MQTT broker and publish/subscribe messages in topics.
// Declare an object of class WiFiClient
// Declare an object of class PubSubClient, which receives as input of the constructor the previously defined WiFiClient.
// The constructor MUST be unique on the network. (Does it?)
WiFiClient monsterBox;
PubSubClient client(monsterBox);

// Declare strings for the topics. Topics will be created in setup_mqtt().
char statusTopic[20];
char cmndTopic[20];
char rssiTopic[20];
const char *mqttServer = MQTT_SERVER;         // Local broker defined in Kaywinnet.h
const int mqttPort = 1883;



//--------------- ticker ---------------
//Function prototype must precede the ticker init
//void motorStart();

//#include <Ticker.h>
//Ticker motorTimer;



//=============== setup ===============
void setup() {
  beginSerial();
  setup_wifi();
  start_OTA();
  setup_mqtt();                         //Generate the topics
  client.setServer(mqttServer, mqttPort);
  mqttConnect();


  Serial.println(F("---------- Starting ----------"));

  pinMode(closedSwitch, INPUT_PULLUP);
  pinMode(openSwitch, INPUT_PULLUP);
  pinMode(startSwitch, INPUT_PULLUP);

  // Start the motor periodically
  //  motorTimer.attach(8.0, motorOn);

  lidState = 0;     //Open
}


//=============== loop ===============
void loop() {
  ArduinoOTA.handle();
  mqttReconnect();         //Make sure we stay connected to the mqtt broker

  closeTheLid();
  delay(FIVESEC);
  openTheLid();
  delay(FIVESEC);

  /*
  closeTheLid();
  delay(6000);

  //Thrash the lid
  motorPwm = 200;                   //Fast
  for (int i = 0; i < 5; i++) {
    openTheLid();
    closeTheLid();
  }
  motorPwm = MIN_PWM;               //Default speed
  delay(15000);
  */
}


// ========= Start the motor =========
void startTheMotor() {
  Serial.println(F("motor on"));
  analogWrite(motorPin, motorPwm);            //Turn on the motor to motorPwm
  motorState = 1;                             //Just used to print debug statements only once.
  delay(100);                                 //Give the motor time to move past the stop switch.
  Serial.print(F("openSwitch= "));
  Serial.println(digitalRead(openSwitch));
  Serial.print(F("closedSwitch= "));
  Serial.println(digitalRead(closedSwitch));
  
}

// ---------- Open the lid ----------
void openTheLid() {
  startTheMotor();
  while (digitalRead(openSwitch)) yield();    //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.print(F("motor off"));
  if (motorState == 1) {                      //Just print once
    Serial.println(F("OPEN"));
    motorState = 0;
  }
}

// ---------- Close the lid ----------
void closeTheLid() {
  startTheMotor();
  while (digitalRead(closedSwitch)) yield();  //Wait for the limit switch
  analogWrite(motorPin, 0);                   //Stop the motor
  Serial.print(F("motor off"));
  if (motorState == 1) {                      //Just print once
    Serial.println(F("CLOSED"));
    motorState = 0;
  }
}



//=============== motorOn ===============
//Function called by the ticker.
void motorOn() {
  //Serial.println(F("Tick"));
  flagMotorOn = true;
  lidState += 1;
  if (lidState > 2) lidState = 0;
}
