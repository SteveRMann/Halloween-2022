// ==================================  setup_mqtt ==================================
// Create topic names
void setup_mqtt() {
  //MUST follow setupWiFi()
  strcpy(cmndTopic, NODENAME);            //nodeName is defined in the wifi tab.
  strcat(cmndTopic, "/cmnd");             //Incoming commands, payload is a command.
  strcpy(statusTopic, NODENAME);
  strcat(statusTopic, "/stat");
  strcpy(rssiTopic, NODENAME);
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
    Serial.println(F("Should not get here"));
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
      Serial.println(clientID);
      Serial.print(F("RSSI: "));
      Serial.println(WiFi.RSSI());
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
      Serial.print(F("RSSI: "));
      Serial.println(WiFi.RSSI());
      delay(5000);
    }
  }
}
