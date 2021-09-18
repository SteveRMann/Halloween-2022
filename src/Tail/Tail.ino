#define SKETCH "Tail.ino"

//Motor Pins
int Motor1 = D1;
int Motor2 = D2;


// --------------- functions ---------------
void forward(int duration) {
  digitalWrite (Motor1, LOW);
  digitalWrite (Motor2, HIGH);
  delay (duration);
}

void stop(int duration) {
  digitalWrite (Motor1, LOW);
  digitalWrite (Motor2, LOW);
  delay (duration);
}

void reverse(int duration) {
  digitalWrite (Motor1, HIGH);
  digitalWrite (Motor2, LOW);
  delay (duration);
}

void forwardSlow(int pwm, int duration) {
  analogWrite (Motor1, pwm);
  digitalWrite (Motor2, LOW);
  delay (duration);
}

void reverseSlow(int pwm, int duration) {
  digitalWrite (Motor1, LOW);
  analogWrite (Motor2, pwm);
  delay (duration);
}

void rampUp() {
  digitalWrite (Motor2, LOW);
  for (int i = 0; i < 100; i++) {
    analogWrite (Motor1, i);
    delay(10);
  }
  delay (1000);
}


// --------------- setup ---------------
void setup() {
  Serial.begin( 115200 );
  Serial.println();
  Serial.println(SKETCH);
  //configure pins as outputs
  pinMode (Motor1, OUTPUT);
  pinMode (Motor2, OUTPUT);


  forwardSlow(300, 100);
  delay(100);
  stop(25);
  reverseSlow(300, 100);
  delay(100);

  //reverse();
  stop(100);
  //rampUp();
  //stop();

}

//--------------- loop ---------------
void loop() {
}
