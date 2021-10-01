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
      pulse(D5);          //Play track 1
      c = '0';
    }

    if (c == '2') {
      pulse(D7);          //Play track 5
      c = '0';
    }

    if (c == '3') {
      pulse(D6);          //Pause/Play
      c = '0';
    }

    if (c == '4') {
      pulse(D1);          //Previous
      c = '0';
    }

    if (c == '5') {
      pulse(D2);          //Next
      c = '0';
    }
    if (c == '6') {
      hold(D5);          //Loop track 1
      c = '0';
    }

    if (c == '7') {
      hold(D7);          //Loop track 5
      c = '0';
    }

    if (c == '8') {
      pulse(D3);          //Play track 2
      c = '0';
    }

    if (c == '9') {
      hold(D3);          //Loop track 2
      c = '0';
    }


    if (c == '-') {
      hold(D1);           //Volume Down
      c = '0';
    }

    if (c == '+') {
      hold(D2);           //Volume Up
      c = '0';
    }

  }
}


void pulse(int d) {
  pinMode(d, OUTPUT);
  digitalWrite(d, 0);
  delay(100);
  pinMode(d, INPUT);
}

void hold(int d) {
  pinMode(d, OUTPUT);
  digitalWrite(d, 0);
  delay(2000);
  pinMode(d, INPUT);
}


void drawMenu() {
  // draw a menu on the serial port
  Serial.println(F( "-----------------------------" ));
  Serial.println(F( "MENU:" ));
  Serial.println(F( "1) Track 1 (D5)" ));
  Serial.println(F( "2) Track 5 (D7)" ));
  Serial.println(F( "3) Pause/Play (D6)" ));
  Serial.println(F( "4) Previous (D1)" ));
  Serial.println(F( "5) Next (D2)" ));
  Serial.println(F( "6) Loop Track 1 (D5)" ));
  Serial.println(F( "7) Loop Track 5 (D7)" ));
  Serial.println(F( "8) Track 2 (D3)" ));
  Serial.println(F( "9) Loop Track 2 (D3)" ));
  Serial.println(F( "-) Volume Down (hold D1)" ));
  Serial.println(F( "+) Volume Up (hold D2)" ));
  Serial.println(F( "-----------------------------" ));
  Serial.print( "? " );
}
