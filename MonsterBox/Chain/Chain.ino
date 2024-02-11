/*
   Brushed Motor Speed Control
   Using Wemos D1 Mini
*/

#define Sketch "Chain"

int motorPin = D1;
int maxPwm = 1023;                     //0-1023 for ESP, 0-255 for Arduino
int potPin = A0;
int potValue = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println(Sketch);
  Serial.println();
  delay(1500);
}



void loop() {
  /*
    analogWrite(motorPin, 1023);        //Start
    delay(10);
    analogWrite(motorPin, 256);
    delay(5000);
  */
  int i = getPotValue();
  analogWrite(motorPin, i);
  delay(100);
}


int getPotValue() {
  int potV = analogRead(potPin);
  //int motorV = map(potV, 0, 1023, 0, 255);  //For Arduino boards (0-255)
  int motorV = potV;                        //For ESP8266 (0-1023)
  Serial.print(F("pot= "));
  Serial.print(potV);
  Serial.print(F("   "));
  Serial.print(F("motor= "));
  Serial.println(motorV);
  return motorV;
}
