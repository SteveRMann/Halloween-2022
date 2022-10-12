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
      Serial.println(F("1- One wag"));
      wag(1);
      c = '0';
    }
  }
}

void drawMenu() {
  // draw a menu on the serial port
  Serial.println(F( "-----------------------------" ));
  Serial.println(F( "MENU:" ));
  Serial.println(F( "1) One wag" ));
  Serial.println(F( "2) One twitch" ));
  Serial.println(F( "3) One slow wag" ));
  Serial.println(F( "-----------------------------" ));
  Serial.print( "? " );
}
