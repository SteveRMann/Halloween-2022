// ==================================  mqtt callback ==================================
// This function is executed when some device publishes a message to a topic that this ESP8266 is subscribed to.
// The MQTT payload is the filename of the message to play when the phone is picked up.  The payload is case-sensitive.
//
void callback(String topic, byte * payload, unsigned int length) {
  char message[length + 1];

  // copy contents of payload to message
  // convert the payload from a byte array to a char array
  memcpy(message, payload, length);
  message[length] = '\0';                 // add NULL terminator to message

  // Sometimes in the MQTT tool, I accdentally hit "Enter" on my keyboard.
  // This removes it.
  for (size_t i = 0; i == strlen(message); i++) {
    if (message[i] == 10) {
      message[i] = '\0';
      break;
    }
  }


  Serial.println();
  Serial.println();
  Serial.print(F("Message arrived on topic: "));
  Serial.print(topic);
  Serial.println(F("."));

  Serial.print("message: ");
  Serial.println(message);
  Serial.print(F("Length= "));
  Serial.print(strlen(message));
  Serial.println();

  // If the message terminates in a line-feed, make it the terminating null char.
  int j = strlen(message) - 1;
  if (message[j] == 10) message[j] = '\0';



  // --------- Command ---------
  if (topic == cmndTopic) {                    // Process incoming commands
    Serial.print(F("received message on cmdTopic: '"));
    Serial.print(message);
    Serial.println(F("'"));

    if (!strcmp(message, "play1")) {
      Serial.println(F("Play Track One"));
      pulse(TRACK1_PIN);
    }

    if (!strcmp(message, "loop1")) {
      Serial.println(F("Loop Track One"));
      hold(TRACK1_PIN);
    }

    if (!strcmp(message, "play2")) {
      Serial.println(F("Play Track Two"));
      pulse(TRACK2_PIN);
    }

    if (!strcmp(message, "loop2")) {
      Serial.println(F("Loop Track Two"));
      hold(TRACK2_PIN);
    }

    if (!strcmp(message, "play")) {
      Serial.println(F("Play/Pause"));
      pulse(PLAY_PAUSE_PIN);
    }

    if (!strcmp(message, "pause")) {
      Serial.println(F("Play/Pause"));
      pulse(PLAY_PAUSE_PIN);
    }

    if (!strcmp(message, "prev")) {
      Serial.println(F("Previous"));
      pulse(PREV_VOLdn_PIN);
    }

    if (!strcmp(message, "next")) {
      Serial.println(F("Next"));
      pulse(NEXT_VOLup_PIN);
    }

    if (!strcmp(message, "volup")) {
      Serial.println(F("Volume Up"));
      hold(NEXT_VOLup_PIN);
    }

    if (!strcmp(message, "voldn")) {
      Serial.println(F("Volume Down"));
      hold(PREV_VOLdn_PIN);
    }

    if (!strcmp(message, "roar")) {
      pulse(TRACK2_PIN);                    //PLay track 2.
      Serial.println(F("ROAR- play track 2"));
      //Since there's no feedback from the DFPlayer module,
      //this is approximately the length of track1
      delay (9000);
      hold(TRACK1_PIN);                    //Restart track1
      Serial.println(F("loop track 1"));
    }



  }

  // --------- syncTopic ---------
  if (topic == syncTopic) {
    pulse(TRACK2_PIN);                    //PLay track 2.
    Serial.println(F("ROAR- play track 2"));
    //Since there's no feedback from the DFPlayer module,
    //this is approximately the length of track1
    delay (9000);
    hold(TRACK1_PIN);                    //Restart track1
    Serial.println(F("loop track 1"));
  }

} //callback
