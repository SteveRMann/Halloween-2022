#define SKETCH "ServoManualSweep.ino"

#include <Servo.h>
Servo myservo;

const int servoPin = D1;
const int potPin = A0;



void setup() {
  Serial.begin(115200);
  while (!Serial);
  printf("\nSketch: %s\n", SKETCH);


  /*
    Specs in https://www.servocity.com/hs-645mg-servo/
    pin: the number of the pin that the servo is attached to
    min: pulse width, in us, corresponding to the 0 degree angle on the servo (defaults to 544)
    max: pulse width, in us, corresponding to the 180 degree angle on the servo (defaults to 2400)
  */
  myservo.attach(servoPin, 400, 2400);    //PWM range.
  //myservo.attach(servoPin);


  //Start at zero
  myservo.write(0);
  delay(1000);
}


void loop() {
  int pwmVal = analogRead(potPin);
  int servoVal = map(pwmVal, 0, 1023, 0, 180);     // scale it to use it with the servo library (value between 0 and 180)
  myservo.write(servoVal);
  printf("servoVal= %d, pwmVal= %d\n", servoVal, pwmVal);
  delay(25);
}
