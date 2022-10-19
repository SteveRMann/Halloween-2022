/*
 * Ticker functions
*/

// --------------- Function to blink the WiFi status LED ---------------
// --------------- called from wifi.ino ---------------
void blueTick() {
  //toggle state
  int state = digitalRead(BLUE_LED_PIN);            // get the current state of GPIO pin
  digitalWrite(BLUE_LED_PIN, !state);               // set pin to the opposite state
}
