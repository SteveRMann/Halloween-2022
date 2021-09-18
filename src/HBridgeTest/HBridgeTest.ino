/*
  HG7881_Motor_Driver_Example - Arduino sketch

  This example shows how to drive a motor with using HG7881 (L9110) Dual
  Channel Motor Driver Module.  For simplicity, this example shows how to
  drive a single motor.  Both channels work the same way.

*/

#define SKETCH "HBridgeTest.ino"
#define MOTOR_PWM D1          // Motor PWM Speed
#define MOTOR_DIR D2          // Motor Direction

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 500           // arbitrary slow speed PWM duty cycle
#define PWM_FAST 1023          // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000        // brief delay for abrupt motor changes

void stopMotors() {
  digitalWrite( MOTOR_DIR, LOW );
  digitalWrite( MOTOR_PWM, LOW );
  delay( DIR_DELAY );
}


// ------------ setup() ------------
void setup()
{
  Serial.begin( 115200 );
  Serial.println();
  Serial.println(SKETCH);
  pinMode( MOTOR_DIR, OUTPUT );
  pinMode( MOTOR_PWM, OUTPUT );
  stopMotors();
}


// ------------ loop() ------------
void loop()
{
  bool isValidInput;

  // draw a menu on the serial port
  Serial.println(F( "-----------------------------" ));
  Serial.println(F( "MENU:" ));
  Serial.println(F( "1) Forward" ));
  Serial.println(F( "2) Reverse" ));
  Serial.println(F( "3) Fast forward" ));
  Serial.println(F( "4) Forward" ));
  Serial.println(F( "5) Soft stop (coast)" ));
  Serial.println(F( "6) Reverse" ));
  Serial.println(F( "7) Fast reverse" ));
  Serial.println(F( "8) Hard stop (brake)" ));
  Serial.println(F( "-----------------------------" ));

  do {
    byte c;
    // get the next character from the serial port
    Serial.print( "?" );
    while ( !Serial.available() ) ;
    c = Serial.read();

    switch ( c )
    {
      case '1':                                   // Fast forward
        Serial.println(F("H-L..."));
        stopMotors();                             // Stop motors briefly before abrupt changes
        digitalWrite( MOTOR_DIR, HIGH );          // direction = forward
        analogWrite( MOTOR_PWM, LOW);
        isValidInput = true;
        break;

      case '2':                                   // Fast forward
        Serial.println(F("L-H..."));
        stopMotors();                             // Stop motors briefly before abrupt changes
        digitalWrite( MOTOR_DIR, LOW );          // direction = forward
        analogWrite( MOTOR_PWM, HIGH);
        isValidInput = true;
        break;

      case '3':                                   // Fast forward
        Serial.println(F("Fast forward..."));
        stopMotors();                             // Stop motors briefly before abrupt changes
        digitalWrite( MOTOR_DIR, HIGH );          // direction = forward
        analogWrite( MOTOR_PWM, PWM_FAST );
        isValidInput = true;
        break;

      case '4':                                   // 2= Forward
        Serial.println( "Forward..." );
        stopMotors();
        digitalWrite( MOTOR_DIR, HIGH );          // direction = forward
        analogWrite( MOTOR_PWM, PWM_SLOW ); // PWM speed = slow
        isValidInput = true;
        break;

      case '5':                                   // 3= Soft stop (preferred)
        Serial.println( "Soft stop (coast)..." );
        stopMotors();
        isValidInput = true;
        break;

      case '6':                                   // 4) Reverse
        Serial.println( "Fast forward..." );
        stopMotors();
        digitalWrite( MOTOR_DIR, LOW );           // direction = reverse
        analogWrite( MOTOR_PWM, PWM_SLOW );       // PWM speed = slow
        isValidInput = true;
        break;

      case '7':                                   // 5= Fast reverse
        Serial.println( "Fast forward..." );
        digitalWrite( MOTOR_DIR, LOW );           // direction = reverse
        analogWrite( MOTOR_PWM, PWM_FAST );       // PWM speed = fast
        isValidInput = true;
        break;

      case '8':                                   // 6= Hard stop (use with caution)
        Serial.println( "Hard stop (brake)..." );
        digitalWrite( MOTOR_DIR, HIGH );
        digitalWrite( MOTOR_PWM, HIGH );
        isValidInput = true;
        break;

      default:
        // wrong character! display the menu again!
        isValidInput = false;
        break;
    }
  } while ( isValidInput == true );
}
