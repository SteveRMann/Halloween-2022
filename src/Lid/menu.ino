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
      Serial.println(F("2- Slow open-close"));
      //slowWag(1);
      c = '0';
    }

    if (c == '4') {
      Serial.println(F("2- Fast open-close"));
      //slowWag(1);
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
  Serial.println(F( "3) Slow open-close" ));
  Serial.println(F( "4) Fast open-close" ));
  Serial.println(F( "-----------------------------" ));
  Serial.print( "? " );
}
