/*
  SG90 360 Degree Test Program
  Simply runs servo in one direction and then reverses direction
  Uses built-in Servo.h library
*/
#include "Servo.h"
#define SERVO_PIN D4

Servo servo;          // creates servo object used to control the servo motor

void setup()
{
  servo.attach(SERVO_PIN); // assigns PWM pin to the servo object
}


void loop()
{
  servo.write(0);   //Spin in one direction
  delay(1000);
  servo.write(90);  //Stop
  delay(1000);
  servo.write(180); //opposite direction
  delay(1000);
  servo.write(90);  //Stop
  delay(100);
}
