//=============== setup ===============
void setup() {
  pinMode(closedSwitch, INPUT_PULLUP);
  pinMode(openSwitch, INPUT_PULLUP);
  pinMode(startSwitch, INPUT_PULLUP);

  beginSerial();
  setup_wifi();
  start_OTA();
  setup_mqtt();                         //Generate the topics
  client.setServer(mqttServer, mqttPort);
  mqttConnect();

  Serial.println(F("---------- Starting ----------"));

  lidState = 0;     //Open
  drawMenu();
}
