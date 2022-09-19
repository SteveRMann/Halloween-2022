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
    Serial.println(F("Shouldn't get here"));
  }
}

// ==================================  mqttConnect ==================================
void mqttConnect() {
  // create client ID from mac address
  // Fixed: "failed, rc=-2"
  byte mac[5];
  WiFi.macAddress(mac); // get mac address
  String clientID = String(mac[0]) + String(mac[4]) ; // use mac address to create clientID

  client.setServer(mqttServer, mqttPort); //Call the setServer method
  while (!client.connected()) {
    Serial.print(F("MQTT connecting..."));
    if (client.connect(clientID.c_str())) {    //Was hostName
      Serial.println(F("connected"));
      Serial.print(F("clientID: "));
      Serial.print(clientID);
      Serial.println();
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
  for (size_t i = 0; i == strlen(message); i++) {
    if (message[i] == 10) {
      message[i] = '\0';
      break;
    }
  }

  // If the message terminates in a line-feed, make it the terminating null char.
  int j = strlen(message) - 1;
  if (message[j] == 10) message[j] = '\0';

  // --------- Command ---------
  if (topic == cmndTopic) {                    // Process incoming commands
    Serial.print(F("received message on cmdTopic: '"));
    Serial.print(message);
    Serial.println(F("'"));

    //Handle the command
    if (!strcmp(message, "1")) {
      Serial.println(F("Play Track 1"));
      pulse(TRACK1_PIN);
      return;
    }

    if (!strcmp(message, "2")) {
      Serial.println(F("Play Track 2"));
      pulse(TRACK2_PIN);
      return;
    }

    if (!strcmp(message, "3")) {
      Serial.println(F("Loop Track 1"));
      hold(TRACK1_PIN);
      return;
    }

    if (!strcmp(message, "4")) {
      Serial.println(F("Loop Track 2"));
      hold(TRACK2_PIN);
      return;
    }

    if (!strcmp(message, "5")) {
      Serial.println(F("Play/Pause"));
      pulse(PLAY_PAUSE_PIN);
      return;
    }

    if (!strcmp(message, "6")) {
      Serial.println(F("Previous Track"));
      pulse(PREV_VOLdn_PIN);
      return;
    }

    if (!strcmp(message, "7")) {
      Serial.println(F("Next Track"));
      pulse(NEXT_VOLup_PIN);
      return;
    }

    if (!strcmp(message, "-")) {
      Serial.println(F("Volume Down"));
      hold(PREV_VOLdn_PIN);
      return;
    }

    if (!strcmp(message, "+")) {
      Serial.println(F("Volume Up"));
      hold(NEXT_VOLup_PIN);
      return;
    }

    //Catch all:
    Serial.println();
    Serial.print(F("Message arrived on topic: "));
    Serial.println(topic);

    Serial.print("message: ");
    Serial.println(message);
    //  Serial.print(F("Length= "));
    //  Serial.print(strlen(message));
    Serial.println();

  }
} //callback
