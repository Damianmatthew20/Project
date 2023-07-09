#include <Servo.h>


#define LDR A0
#define IR A1
#define servoPin 5


Servo servo1;


unsigned int sensor_ldr;
unsigned int sensor_ir;


void setup()
{
  Serial.begin(9600);
  pinMode(IR, INPUT);
  pinMode(LDR, INPUT);
  servo1.attach(servoPin);
  
  servo1.write(80);
}

void loop()
{
  sensor_ldr = analogRead(LDR);
  sensor_ir = analogRead(IR);
  
  Serial.print("LDR INPUT = ");
  Serial.println(sensor_ldr);
  Serial.print("IR INPUT = ");
  Serial.println(sensor_ir);
  Serial.println("");
  delay(1500);

  if (sensor_ldr >= 480 && sensor_ir >= 680)
  {
    servo1.write(170);
  }
}
