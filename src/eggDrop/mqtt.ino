
/* ================================== mqttConnect() =================================
  Include at the top of the main ino file:

  //--------------- MQTT declarations ---------------
  #include <ESP8266WiFi.h>        // Connect (and reconnect) an ESP8266 to the a WiFi network.
  #include <PubSubClient.h>       // connect to a MQTT broker and publish/subscribe messages in topics.
  // Declare an object of class WiFiClient, which allows to establish a connection to a specific IP and port
  // Declare an object of class PubSubClient, which receives as input of the constructor the previously defined WiFiClient.
  // The constructor MUST be unique on the network. (Does it?)
  WiFiClient xyzzy;
  PubSubClient client(xyzzy);

  // Declare strings for the topics. Topics will be created in setup_mqtt().
  char statusTopic[20];
  char cmndTopic[20];                           // Incoming commands, payload is a command.
  char rssiTopic[20];
  // Other topics as needed

  const char *mqttServer = MQTT_SERVER;         // Local broker defined in Kaywinnet.h
  const int mqttPort = 1883;
  //--------------- End of MQTT declarations ---------------



  // --------------- Example setup: ---------------
  void setup() {
    beginSerial();
    setup_wifi();                   // MUST be before setupMqtt()
    start_OTA();                    // Ifusing OTA
    setup_mqtt();                   // Generate the topics

    // Call the setServer method on the PubSubClient object
    client.setServer(mqttServer, mqttPort);
    mqttConnect();
  //-------------------------------------------------



  //----------
  //IN LOOP()
  mqttReconnect();         //Make sure we stay connected to the mqtt broker

*/



// ==================================  setup_mqtt ==================================
// Create topic names
void setup_mqtt() {
  //MUST follow setupWiFi()
  strcpy(cmndTopic, nodeName);            //nodeName is defined in the wifi tab.
  strcat(cmndTopic, "/cmnd");             //Incoming commands, payload is a command.
  strcpy(statusTopic, nodeName);
  strcat(statusTopic, "/stat");
  strcpy(rssiTopic, nodeName);
  strcat(rssiTopic, "/rssi");

  dbugs("cmndTopic= ", cmndTopic);
  dbugs("statusTopic= ", statusTopic);
  dbugs("rssiTopic= ", rssiTopic);
}


// ==================================  mqttReconnect ==================================
void mqttReconnect() {
  //mqttConnect
  //Make sure we stay connected to the mqtt broker
  if (!client.connected()) {
    mqttConnect();
  }
  if (!client.loop()) {
    client.connect(hostName);
  }
}

// ==================================  mqttConnect ==================================
void mqttConnect() {
  client.setServer(mqttServer, mqttPort); //Call the setServer method
  while (!client.connected()) {
    Serial.print(F("MQTT connecting..."));
    if (client.connect(hostName)) {
      Serial.println(F("connected"));

      client.setCallback(callback);

      //Subscriptions:
      client.subscribe(cmndTopic);
      Serial.print(F("Subscribing to "));
      Serial.println(cmndTopic);
    } else {
      Serial.print(F("failed, rc="));
      Serial.print(client.state());
      Serial.println(F("- trying again in 5-seconds."));
      delay(5000);
    }
  }
}



// ==================================  mqtt callback ==================================
/*
  This function is executed when some device publishes a message to a topic that this
  ESP8266 is subscribed to.  The payload is case-sensitive.
*/
/*******
  void callback(String topic, byte * message, unsigned int length) {

  Serial.println();
  Serial.print(F("Message arrived on topic: "));
  Serial.println(topic);


  // Convert the character array to a string
  String messageString;
  for (unsigned int i = 0; i < length; i++) {
    messageString += (char)message[i];
  }
  messageString.trim();
  messageString.toUpperCase();          //Make the string upper-case


  Serial.print("messageString: ");
  Serial.print(messageString);
  Serial.println();



  if (topic == cmndTopic) {
    //Handle the command
  }
*******/
// ==================================  mqtt callback ==================================
// This function is executed when some device publishes a message to a topic that this ESP8266 is subscribed to.
// The MQTT payload is the filename of the message to play when the phone is picked up.  The payload is case-sensitive.
//
void callback(String topic, byte * payload, unsigned int length) {
  char message[length + 1];

  // copy contents of payload to message
  // convert the payload from a byte array to a char array
  memcpy(message, payload, length);
  message[length] = '\0';                 // add NULL terminator to message

  // Sometimes in the MQTT tool, I accdentally hit "Enter" on my keyboard.
  // This removes it.
  for (int i = 0; i == strlen(message); i++) {
    if (message[i] == 10) {
      message[i] = '\0';
      break;
    }
  }


  Serial.println();
  Serial.println();
  Serial.print(F("Message arrived on topic: "));
  Serial.print(topic);
  Serial.println(F("."));

  Serial.print("message: ");
  Serial.println(message);
  Serial.print(F("Length= "));
  Serial.print(strlen(message));
  Serial.println();

  // If the message terminates in a line-feed, make it the terminating null char.
  int j = strlen(message) - 1;
  if (message[j] == 10) message[j] = '\0';



  // --------- Command ---------
  if (topic == cmndTopic) {                    // Process incoming commands
    Serial.print(F("received message on cmdTopic: '"));
    Serial.print(message);
    Serial.println(F("'"));
    stressFlag = false;                 //Just in case we're in a stress test

    if (!strcmp(message, "reset")) {
      //Close both servos.
      Serial.println(F("Close both servos"));
      dropServoClose();
      loadServoClose();
    }

    if (!strcmp(message, "flush")) {     // if message=="flush", then strcmp returns a zero (false).
      //Open both servos.
      Serial.println(F("Open both servos"));
      dropServoOpen();
      loadServoOpen();
    }

    if (!strcmp(message, "drop")) {
      //Drop one egg
      Serial.println(F("Drop one egg"));
      dropEgg(1);
    }

    if (!strcmp(message, "stress")) {
      //Drop an egg every 30-seconds.
      Serial.println(F("Drop an egg every 30-seconds."));
      stressFlag = true;
      //  lastTimeChecked = millis();

      //stressFlag = true;
      //stress();
    }

  }

} //callback