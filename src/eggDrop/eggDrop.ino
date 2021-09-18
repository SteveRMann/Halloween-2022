#define SKETCH "eggDrop.ino"

const int servo1Pin = D1;
const int servo2Pin = D2;

#include <Servo.h>
Servo servoOne;
Servo servoTwo;

int servo1Position;
int servo2Position;
const int dropDelay = 700;          //How long the drop servo is open.
const int loadDelay = 450;          //How long the load servo is open.

void setup() {
  while (!Serial);
  Serial.begin( 115200 );
  Serial.println();
  Serial.println();
  Serial.println(SKETCH);
  Serial.println(F("+++++++++++++++++++"));

  /*
    Specs in https://www.servocity.com/hs-645mg-servo/
    pin: the number of the pin that the servo is attached to
    min: pulse width, in us, corresponding to the 0 degree angle on the servo (defaults to 544)
    max: pulse width, in us, corresponding to the 180 degree angle on the servo (defaults to 2400)

    Use ServoManualSweep.ino to calibrate these end points.
  */
  //servoOne.attach(servo1Pin, 400, 2400);    //PWM range for HS-645MG servos
  servoOne.attach(servo1Pin, 625, 2600);    //PWM range for SG90 servos
  servoTwo.attach(servo2Pin, 625, 2600);    //PWM range for SG90 servos

  dropServoClose();
  loadServoClose();
  delay(1000);
}


void loop() {
  bool isValidInput;

  // draw a menu on the serial port
  Serial.println(F( "-----------------------------" ));
  Serial.println(F( "MENU:" ));
  Serial.println(F( "1) Close both" ));
  Serial.println(F( "2) Open both" ));
  Serial.println(F( "3) Drop one egg" ));
  Serial.println(F( "4) Drop six eggs" ));
  Serial.println(F( "5) Drop ten eggs" ));
  Serial.println(F( "8) Preload" ));
  //Serial.println(F( "9) 180° sweep" ));
  Serial.println(F( "-----------------------------" ));

  do {
    byte c;
    // get the next character from the serial port
    Serial.print( "? " );
    while ( !Serial.available() ) ;
    c = Serial.read();

    switch ( c )
    {
      case '1':                                   // Close Both
        Serial.println(F("1- Close Both"));
        dropServoClose();
        loadServoClose();
        isValidInput = true;
        break;

      case '2':                                   // Open both
        Serial.println(F("1- Open both"));
        dropServoOpen();
        loadServoOpen();
        isValidInput = true;
        break;

      case '3':                                   // Drop one egg
        dropEgg(1);
        isValidInput = true;
        break;

      case '4':                                   // Drop six eggs
        dropEgg(6);
        //delay(500);
        isValidInput = true;
        break;

      case '5':                                   // Drop 10 eggs
        dropEgg(10);
        //delay(500);
        isValidInput = true;
        break;

      case '8':                                   // Preload
        Serial.println(F("8- Preload"));
        dropServoClose();
        loadServoOpen();
        isValidInput = true;
        break;

      /*
            case '9':                                   // Sweep 0-180ºuntil any alpha key is entered.
              Serial.println(F("9- Sweep. Reset to stop"));
              while (isValidInput == true) {
                servoOne.write(180);
                servoTwo.write(180);
                delay(2000);
                servoOne.write(0);
                servoTwo.write(0);
                delay(2000);
              }
              isValidInput = true;
              break;
      */

      default:
        // wrong character! display the menu again!
        isValidInput = false;
        break;
    }
  } while ( isValidInput == true );


}

void dropEgg(int howMany) {
  printf("\nDropping\n");
  if (servo1Position != 90) {            //Make sure we're closed.
    dropServoClose();
    loadServoClose();
    delay(500);
  }
  while (howMany > 0) {
    howMany--;
    printf(" egg# %d.\n", howMany);
    dropServoOpen();                            //Exit
    delay(dropDelay);
    dropServoClose();
    delay(dropDelay);                   //Let 'drop' close before 'load' opens


    loadServoOpen();                            //Load
    delay(loadDelay);
    loadServoClose();

    delay(2000);                     //Time between eggs
  }
}

void dropServoOpen() {                          //Open the exit
  servoOne.write(0);
  servo1Position = 0;
}

void dropServoClose() {                         //Close the exit
  servoOne.write(90);
  servo1Position = 90;
}

void loadServoOpen() {                          //Open the preload servo
  servoTwo.write(0);
  servo2Position = 0;
}

void loadServoClose() {                         //Close the preload
  servoTwo.write(90);
  servo2Position = 90;
}
