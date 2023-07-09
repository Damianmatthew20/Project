#define IR_tengah 4
#define IR_ki2 A2
#define IR_ki1 A3
#define IR_ka1 A4
#define IR_ka2 A5


unsigned int RT;
unsigned int RKI2;
unsigned int RKI1;
unsigned int RKA1;
unsigned int RKA2;


void setup()
{
  Serial.begin(9600);
  pinMode(IR_tengah,INPUT);
  pinMode(IR_ki2,INPUT);
  pinMode(IR_ki1,INPUT);
  pinMode(IR_ka1,INPUT);
  pinMode(IR_ka2,INPUT);
}

void loop()
{
  RT = digitalRead(IR_tengah);
  RKI2 = digitalRead(IR_ki2);
  RKI1 = digitalRead(IR_ki1);
  RKA1 = digitalRead(IR_ka1);
  RKA2 = digitalRead(IR_ka2);
  Serial.print("Digital Read Middle = ");
  Serial.println(RT);
  Serial.print("Digital Read Left 2 = ");
  Serial.println(RKI2);
  Serial.print("Digital Read Left 1 = ");
  Serial.println(RKI1);
  Serial.print("Digital Read Right 1 = ");
  Serial.println(RKA1);
  Serial.print("Digital Read Right 2 = ");
  Serial.println(RKA2);
  Serial.println("");
  Serial.println("");
  delay(2000);
}
