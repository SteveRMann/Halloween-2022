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
      pulse(D5);
      c = '0';
    }

    if (c == '2') {
      pulse(D6);
      c = '0';
    }

    if (c == '3') {
      pulse(D7);
      c = '0';
    }

    if (c == '4') {
      pulse(D8);
      c = '0';
    }
  }
}

void pulse(int d) {
  digitalWrite(d, 0);
  delay(100);
  digitalWrite(d, 1);
}

void drawMenu() {
  // draw a menu on the serial port
  Serial.println(F( "-----------------------------" ));
  Serial.println(F( "MENU:" ));
  Serial.println(F( "1) D5 (Segment 1)" ));
  Serial.println(F( "2) D6 (Segment 2)" ));
  Serial.println(F( "3) D7 (Pause/Play)" ));
  Serial.println(F( "4) D8 (Next)" ));
  Serial.println(F( "-----------------------------" ));
  Serial.print( "? " );
}
