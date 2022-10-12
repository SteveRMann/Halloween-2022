#define SKETCH "AnalogInput"
#define VERSION "1.00"

/*
  Analog Photoresistor detector
  Used in the Halloween project- tail to detect when the tail wag motor makes one revolution.
  This program prints the LDR va

*/

#define LEDOFF LOW
#define LEDON HIGH
#define LEDPIN D4

int sensorPin = A0;
//int sensorValue = 0;
int threshold=800;


void beginSerial() {
  while (!Serial);
  Serial.begin( 115200 );
  Serial.println();
  Serial.println();
  Serial.print(SKETCH);
  Serial.print(".ino, Version ");
  Serial.println(VERSION);
  Serial.println(F("++++++++++++++++++ +"));
}


void setup() {
  beginSerial();
  pinMode(LEDPIN, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

  if (sensorValue  <= threshold) {
    digitalWrite(LEDPIN, LEDOFF);    //Turn off the LED
    delay(500);
  }
  else {
    //White spot detected.
    digitalWrite(LEDPIN, LEDON);   //Turn on the LED
    delay(500);
  }

} //loop
