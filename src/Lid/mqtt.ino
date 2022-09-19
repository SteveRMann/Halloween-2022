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

  strcpy(syncTopic, "roar");

  dbugs("cmndTopic= ", cmndTopic);
  dbugs("statusTopic= ", statusTopic);
  dbugs("rssiTopic= ", rssiTopic);
  dbugs("syncTopic= ", syncTopic);
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
  // create client ID from mac address
  byte mac[5];
  WiFi.macAddress(mac); // get mac address
  String clientID = String(mac[0]) + String(mac[4]) ; // use mac address to create clientID

  client.setServer(mqttServer, mqttPort); //Call the setServer method
  while (!client.connected()) {
    Serial.print(F("MQTT connecting..."));
    if (client.connect(clientID.c_str())) {
      ////    if (client.connect(hostName)) {
      Serial.println(F("connected"));
      Serial.print(F("clientID: "));
      Serial.print(clientID);
      Serial.println();
      client.setCallback(callback);

      //Subscriptions:
      client.subscribe(cmndTopic);
      Serial.print(F("Subscribing to "));
      Serial.println(cmndTopic);

      client.subscribe(syncTopic);
      Serial.print(F("Subscribing to "));
      Serial.println(syncTopic);

    } else {
      Serial.print(F("failed, rc="));
      Serial.print(client.state());
      Serial.println(F("- trying again in 5-seconds."));
      delay(5000);
    }
  }
}
