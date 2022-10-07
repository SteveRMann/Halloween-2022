// --------------- setup ---------------
void setup() {
  //configure GPIO pins
  pinMode (BUTTON_PIN, INPUT_PULLUP);
  pinMode (BLUE_LED_PIN, OUTPUT);

  myFunctions::beginSerial();
  myWifiMulti::setup_wifiMulti();       // MUST be before setupMqtt()
  myOTA::start_OTA();
  myMqtt::setup_mqtt();                 // Generate the topics


  button.attachDoubleClick(doubleclick);
  button.attachClick(singleClick);
  button.attachLongPressStop(longPress);

  wag(1);
  drawMenu();
}
