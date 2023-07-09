#include <Servo.h>

#define servoPin 5
Servo servo1;


void setup()
{
  Serial.begin(9600);
  servo1.attach(servoPin);
  servo1.write(80);
}

void loop()
{
  servo1.write(80);
  delay(1000);
  servo1.write(150);
  delay(2000);
}
