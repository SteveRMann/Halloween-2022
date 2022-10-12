// --------------- setup ---------------
void setup() {
  //configure GPIO pins
  pinMode (BUTTON_PIN, INPUT_PULLUP);
  pinMode (BLUE_LED_PIN, OUTPUT);

  //Start the tickers
  wagTicker.attach_ms(tickerInterval, myTicker::periodicWag);
  blueTicker.attach(0.2, myTicker::blueTick);

  myFunctions::beginSerial();
  myWifiMulti::setup_wifiMulti();       // MUST be before setupMqtt()
  blueTicker.detach();                  // Stop blueTick() after WiFi connects
  myOTA::start_OTA();
  
  randomSeed(analogRead(0));

  button.attachDoubleClick(doubleclick);
  button.attachClick(singleClick);
  button.attachLongPressStop(longPress);

  wag(1);
  drawMenu();
}
