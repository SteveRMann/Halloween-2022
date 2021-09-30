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

    if (!strcmp(message, "fanon")) {
      //Turn on the mist fan.
      Serial.println(F("Fan On"));
      analogWrite(FAN_PIN, 250);
    }

    if (!strcmp(message, "fanoff")) {
      //Turn on the mist fan.
      Serial.println(F("Fan Off"));
      analogWrite(FAN_PIN, 0);
    }

    if (!strcmp(message, "eyeson")) {
      //Turn on the eyes
      Serial.println(F("Eyes On"));
      digitalWrite(LEDS_PIN, 1);
    }

    if (!strcmp(message, "eyesoff")) {
      //Turn off the eyes
      Serial.println(F("Eyes Off"));
      digitalWrite(LEDS_PIN, 0);
    }

    if (!strcmp(message, "slowopen")) {
      //Open the lid
      Serial.println(F("Open the lid"));
      slowOpen();
    }

    if (!strcmp(message, "slowclose")) {
      //Close the lid
      Serial.println(F("Close the lid"));
      slowClose();
    }

    if (!strcmp(message, "help")) {
      client.publish (statusTopic, "MQTT commands: fanon fanoff eyeson eyesoff slowopen slowclose");
      //Print the available commands
      //Serial.println(F("Commands: "));
      //Serial.println(F("fanOn -  Turn on the mist fan."));
      //Serial.println(F("fanOff - Turn off the mist fan."));
      //Serial.println(F("eyesOn - Turn on the eyes LEDs."));
      //Serial.println(F("eyesOff - Turn off the eyes LEDs."));
      //Serial.println(F("slowOpen - Open the lid."));
      //Serial.println(F("slowClose - Close the lid."));
    }

  }

} //callback
