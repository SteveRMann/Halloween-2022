#include <Servo.h>
Servo servo;

const int SERVO_PIN = D4;
const int ANALOG_PIN = A0;
const int SERVO_MIN = 0;
const int SERVO_MAX = 180;
const int SERVO_STEP = 30;

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Servo.ino"));
  servo.attach(SERVO_PIN);       //GPIO2
}


void loop()
{
  int pos;
  int potValue = analogRead(ANALOG_PIN);
  Serial.println(potValue);

  for (pos = SERVO_MIN; pos < SERVO_MAX; pos += SERVO_STEP)
  {
    servo.write(pos);
    delay(random(10, 50));                //Speed of the servo
  }
  delay(random(100, 200));                //Time between directions

  for (pos = SERVO_MAX; pos > SERVO_MIN; pos -= SERVO_STEP)
  {
    servo.write(pos);
    delay(random(10, 50));
  }
  delay(random(100, 500));
}
