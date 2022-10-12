//--------------- loop ---------------
void loop() {
  int ldrValue;                     //Motor rotation detector

  ArduinoOTA.handle();
  button.tick();
  menu();

  //----- Look at the rotation sensor.
  ldrValue = analogRead(LDRPIN);
  //Serial.println(ldrValue);

  if (ldrValue  <= threshold) {
    digitalWrite(LEDPIN, LEDOFF);    //Turn off the LED
  }
  else {
    //White spot detected.
    digitalWrite(LEDPIN, LEDON);   //Turn on the LED
  }


  if (wagFlag) {                    //The wag interval timer calls for a wag.
    wagFlag = false;
    wag(1);
  }


  /*
     Motor state machine. How this works
     motorRun()
       starts the motor and attaches the motorTicker for duration ms.
       Set motorState=1
     MotorTicker times out
       detach the ticker timer
       Next action depends on the motorState
       motorState=1
         The motor was moving forward. It stopped when entering here
         attach the timer for 500ms
         set motorState=2
       motorState=2
         The motor has been stopped for 500ms
         run motor backwards
         motorState=3
       motorState=3
         The motor has been running in reverse
         attach the timer for 500ms
         set motorState=0
       motorState=9
         The ticker timer has timed out
         Stop the motor
  */

  if (motorFlag) {            //Set true anytime the ticker timer ends.
    motor1.setSpeed(0);       //Motor 1 stops.
    motorTicker.detach();     //Stop the timer

    switch (motorState) {
      case 0:
        //Do nothing
        break;
      case 1:   //Motor is moving forward, stop for 500ms
        motorTicker.attach_ms(500, myTicker::motorStop);
        motorFlag = false;
        motorState = 2;
        break;
      case 2:   //Motor has stopped for 500ms, run the motor in reverse.
        motorTicker.attach_ms(duration, myTicker::motorStop);
        motor1.setSpeed(-pwm);               //Turn on the motor
        motorFlag = false;
        motorState = 3;
        break;
      case 3:   //Motor is moving in reverse, stop for 500ms
        motorTicker.attach_ms(500, myTicker::motorStop);
        motorFlag = false;
        motorState = 4;
        break;
      case 4:   //Motor stoped 500 ms after the reverse.
        break;
      default:
        Serial.print(F("CANNOT BE HERE, motorState= "));
        Serial.println(motorState);
        break;
    }
  }
} //loop
