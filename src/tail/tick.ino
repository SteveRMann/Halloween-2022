/*
 * Ticker functions
 * 
// --------------- ticker declarations ---------------
// for LED status
#include <Ticker.h>
Ticker blueTicker;
const int BLUE_LED_PIN = D6;
*/


// --------------- Function to blink the WiFi status LED ---------------
void blueTick() {
  //toggle state
  int state = digitalRead(BLUE_LED_PIN);            // get the current state of GPIO pin
  digitalWrite(BLUE_LED_PIN, !state);               // set pin to the opposite state
}
