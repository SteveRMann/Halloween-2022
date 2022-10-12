/* myTicker.h
   Declarations and callback functions for the ticker.h library

   Once a ticker is started, the callback is executed until the ticker object is detached.

   Start the ticker in setup()
   void setup() {
     wagTicker.attach_ms(tickerInterval, periodicWag);

*/


// --------------- ticker declarations ---------------
// for LED status
#include <Ticker.h>
Ticker blueTicker;              //Ticker object for the WiFi Connecting LED
const int BLUE_LED_PIN = D4;    //LED_BUILTIN is on GPIO2, D4

Ticker wagTicker;
int tickerInterval = 1000;      //Time between wags?
bool wagFlag = false;

Ticker motorTicker;             //Ticket to time the motor on duration
bool motorFlag = false;



namespace myTicker {
// =============== Ticker callback functions ===============
// ----- Function to blink the WiFi status LED -----
void blueTick() {
  //toggle state
  int state = digitalRead(BLUE_LED_PIN);            // get the current state of GPIO pin
  digitalWrite(BLUE_LED_PIN, !state);               // set pin to the opposite state
}


// ----- Function to randomize wags -----
void periodicWag() {
  wagFlag = true;                                   //We can't put wag() here in a callback because it uses delay()
  tickerInterval = random(1000, 6000);
  Serial.print(F("tickerInterval= "));
  Serial.println(tickerInterval);
  wagTicker.detach();
  wagTicker.attach_ms(tickerInterval, periodicWag);
}


// ----- Callback function to stop the motor -----
void motorStop() {
  motorFlag=true;
}
} //namespace
