#define IR A1
#define LDR A0

unsigned int IN1;
unsigned int IN2;


void setup()
{
  Serial.begin(9600);
  pinMode(IR, INPUT);
  pinMode(LDR, INPUT);
}

void loop()
{
  IN1 = analogRead(LDR);
  IN2 = analogRead(IR);

  Serial.print("LDR INPUT = ");
  Serial.println(IN1);
  Serial.print("IR INPUT = ");
  Serial.println(IN2);
  Serial.println("");
  delay(1500);
}
