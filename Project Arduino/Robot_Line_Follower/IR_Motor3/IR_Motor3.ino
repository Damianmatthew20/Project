#define RE_KA 2
#define RE_KI 3
#define IR_tengah 4
#define IN1 8
#define IN2 9
#define ENA 10
#define ENB 11
#define IN3 12
#define IN4 13
#define IR_ki2 A2
#define IR_ki1 A3
#define IR_ka1 A4
#define IR_ka2 A5


unsigned int countKA = 0;
unsigned int countKI = 0;
unsigned int RT;
unsigned int RKI2;
unsigned int RKI1;
unsigned int RKA1;
unsigned int RKA2;


void setup()
{
  Serial.begin(9600);
  pinMode(RE_KA,INPUT);
  pinMode(RE_KI,INPUT);
  pinMode(IR_tengah,INPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  //pinMode(ENA,OUTPUT);
  //pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(IR_ki2,INPUT);
  pinMode(IR_ki1,INPUT);
  pinMode(IR_ka1,INPUT);
  pinMode(IR_ka2,INPUT);
  
  attachInterrupt(digitalPinToInterrupt(RE_KA), kecepatan_kanan, RISING);
  attachInterrupt(digitalPinToInterrupt(RE_KI), kecepatan_kiri, RISING);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void loop()
{
  RT = digitalRead(IR_tengah);
  RKI1 = digitalRead(IR_ki1);
  RKA1 = digitalRead(IR_ka1);
  RKI2 = digitalRead(IR_ki2);
  RKA2 = digitalRead(IR_ka2);

  if (RT == HIGH && RKI1 == HIGH && RKI2 == HIGH && RKA1 == HIGH && RKA2 == HIGH)
  {
    berhenti();
  }
  else if(RT == LOW && RKI1 == LOW && RKI2 == LOW && RKA1 == LOW && RKA2 == LOW)
  {
    kiri_dikit(); 
  }
  else if(RT == HIGH && RKI1 == LOW && RKI2 == LOW && RKA1 == LOW && RKA2 == LOW)
  {
    maju(); 
  }
  else if(RT == LOW && RKI1 == HIGH && RKI2 == LOW && RKA1 == LOW && RKA2 == LOW)
  {
    kiri_dikit(); 
  }
  else if(RT == LOW && RKI1 == LOW && RKI2 == LOW && RKA1 == HIGH && RKA2 == LOW)
  {
    kanan_dikit(); 
  }
}


void kecepatan_kanan()
{
  countKA++;
}

void kecepatan_kiri()
{
  countKI++;
}

void maju()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void kanan_dikit()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void kiri_dikit()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void berhenti()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
