/*
   menu
   NOTE- THIS IS A BLOCKING FUNCTION
   This provides a menu template

  TRACK1_PIN = D5;
  TRACK2_PIN = D3;
  PLAY_PAUSE_PIN = D6;
  PREV_VOLdn_PIN = D1;
  NEXT_VOLup_PIN = D2;
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

    if (c == '1') {               //Play track 1
      pulse(TRACK1_PIN);
      c = '0';
    }

    if (c == '2') {               //Play track 2
      pulse(TRACK2_PIN);
      c = '0';
    }

    if (c == '3') {               //Loop track 1
      hold(TRACK1_PIN);
      c = '0';
    }

    if (c == '4') {               //Loop track 2
      hold(TRACK2_PIN);
      c = '0';
    }

    //Note about pause/play
    //Press Pause/Play, and no other buttons will work until the sound file completes.
    if (c == '5') {               //Pause/Play
      pulse(PLAY_PAUSE_PIN);
      c = '0';
    }

    if (c == '6') {               //Previous
      pulse(PREV_VOLdn_PIN);
      c = '0';
    }

    if (c == '7') {               //Next
      pulse(NEXT_VOLup_PIN);
      c = '0';
    }

    if (c == '-') {               //Volume Down
      hold(PREV_VOLdn_PIN);
      c = '0';
    }

    if (c == '+') {               //Volume Up
      hold(NEXT_VOLup_PIN);
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
  Serial.println(F( "MENU:"));
  Serial.println(F( "1) Track 1" ));
  Serial.println(F( "2) Track 2" ));
  Serial.println(F( "3) Loop Track 1" ));
  Serial.println(F( "4) Loop Track 2" ));
  Serial.println(F( "5) Pause/Play" ));
  Serial.println(F( "6) Previous" ));
  Serial.println(F( "7) Next"));
  Serial.println(F( "-) Volume Down" ));
  Serial.println(F( "+) Volume Up" ));
  Serial.println(F( "-----------------------------" ));
  Serial.print( "? " );
}
