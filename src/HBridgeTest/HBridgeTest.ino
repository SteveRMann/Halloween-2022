/*******************************************************************************
   THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
   IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
   IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
   DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
   DESCRIPTION:

   This example shows how to drive 2 motors using 4 PWM pins (2 for each motor)
   with 2-channel motor driver.


   CONNECTIONS:

   Arduino D3  - Motor Driver PWM 1A Input
   Arduino D9  - Motor Driver PWM 1B Input
   Arduino D10 - Motor Driver PWM 2A Input
   Arduino D11 - Motor Driver PWM 2B Input
   Arduino GND - Motor Driver GND


   AUTHOR   : Kong Wai Weng
   COMPANY  : Cytron Technologies Sdn Bhd
   WEBSITE  : www.cytron.io
   EMAIL    : support@cytron.io

 *******************************************************************************/

#include "CytronMotorDriver.h"


// Configure the motor driver.
CytronMD motor1(PWM_PWM, D1, D2);   // PWM 1A = Pin D1, PWM 1B = Pin D2.
//CytronMD motor2(PWM_PWM, D3, D4);   // PWM 2A = Pin 10, PWM 2B = Pin 11.


// The setup routine runs once when you press reset.
void setup() {

}


// The loop routine runs over and over again forever.
// SPEED can be 1-256
void loop() {
  const int SPEED = 16;

  motor1.setSpeed(SPEED);   // Motor 1 runs forward
  delay(1000);

  motor1.setSpeed(0);     // Motor 1 stops.
  delay(1000);

  motor1.setSpeed(-SPEED);  // Motor 1 runs backward
  delay(1000);

  motor1.setSpeed(0);     // Motor 1 stops.
  delay(1000);
}
