/*
   servoCalibrate.ino
   Use a 10K pot on A0 (3v3 to ground) to determine the physical limits of a servo.
   The SG90 hobby servo goes from 0 to 90 degrees.
*/

#include <Servo.h>
Servo servo;

const int SERVO_PIN = D4;
const int ANALOG_PIN = A0;
const int MAX = 180;

void setup()
{
  Serial.begin(115200);
  Serial.println(F("servoCalibrate.ino"));
  servo.attach(SERVO_PIN);       //GPIO2
}


void loop()
{
  int potValue = analogRead(ANALOG_PIN);
  int angle = map(potValue, 0, 1023, 0, MAX);  //Convert 0-1023 to degrees
  servo.write(angle);                          //Sets the servo angle in degrees.

  Serial.print(F("A0= "));
  Serial.print(potValue);
  Serial.print(F(",  Angle= "));
  Serial.println(angle);
}
