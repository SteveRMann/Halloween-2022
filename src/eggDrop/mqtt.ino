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
// This function is executed when some device publishes a message to a topic that this
// ESP8266 is subscribed to.
// The payload is case-sensitive.
//
void callback(String topic, byte * payload, unsigned int length) {
  char message[length + 1];

  // copy contents of payload to message
  // convert the payload from a byte array to a char array
  memcpy(message, payload, length);
  message[length] = '\0';                 // add NULL terminator to message

  // Sometimes in the MQTT tool, I accdentally hit "Enter" on my keyboard.
  // This removes it.
  //for (int i = 0; i == strlen(message); i++) {
  for (size_t i = 0; i == strlen(message); i++) {
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
      dropServoClose();
      loadServoClose();
    }

    if (!strcmp(message, "flush")) {     // if message=="flush", then strcmp returns a zero (false).
      //Open both servos.
      dropServoOpen();
      loadServoOpen();
    }

    if (!strcmp(message, "drop")) {
      //Drop one egg
      dropEgg(1);
    }

    if (!strcmp(message, "stress")) {
      //Drop an egg every 30-seconds.
      stressFlag = true;
    }
  }

} //callback
