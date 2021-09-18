#define SKETCH "ServoSweep.ino"

const int servoPin = D1;

#include <Servo.h>
Servo myservo;

void setup() {
  /*
    Specs in https://www.servocity.com/hs-645mg-servo/
    pin: the number of the pin that the servo is attached to
    min: pulse width, in us, corresponding to the 0 degree angle on the servo (defaults to 544)
    max: pulse width, in us, corresponding to the 180 degree angle on the servo (defaults to 2400)

    Use ServoManualSweep.ino to calibrate these end points.
  */
  myservo.attach(servoPin, 400, 2400);    //PWM range.

  myservo.write(0);                       //Start at zero
  delay(1000);
}


void loop() {
  //Sweep 0 to 180 degrees.
  myservo.write(180);
  delay(2000);
  myservo.write(0);
  delay(3000);
}
