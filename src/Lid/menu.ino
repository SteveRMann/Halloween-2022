/*
   menu
   NOTE- THIS IS A BLOCKING FUNCTION
   This provides a menu template
*/
void menu() {
  static byte c = '?';

  // get the next character from the serial port
  if (Serial.available() ) {
    c = Serial.read();

    if (c == '?') {
      // draw a menu on the serial port
      drawMenu();
      c = '0';
    }

    if (c == '1') {
      Serial.println(F("1- Open"));
      openTheLid();
      c = '0';
    }

    if (c == '2') {
      Serial.println(F("2- Close"));
      closeTheLid();
      c = '0';
    }

if (c == '3') {
      Serial.println(F("3- Eyes On"));
      digitalWrite(LEDS_PIN, 1);
      c = '0';
    }

if (c == '4') {
      Serial.println(F("4- Eyes Off"));
      digitalWrite(LEDS_PIN, 0);
      c = '0';
    }

if (c == '5') {
      Serial.println(F("5- Fan On"));
      analogWrite(FAN_PIN, 255);
      c = '0';
    }
    
if (c == '6') {
      Serial.println(F("6- Fan Off"));
      analogWrite(FAN_PIN, 0);
      c = '0';
    }
    

    
  }
}

void drawMenu() {
  // draw a menu on the serial port
  Serial.println(F( "-----------------------------" ));
  Serial.println(F( "MENU:" ));
  Serial.println(F( "1) Open" ));
  Serial.println(F( "2) Close" ));
  Serial.println(F( "3) Eyes ON" ));
  Serial.println(F( "4) Eyes OFF" ));
  Serial.println(F( "5) Fan ON" ));
  Serial.println(F( "6) Fan Off" ));
  Serial.println(F( "-----------------------------" ));
  Serial.print( "? " );
}
