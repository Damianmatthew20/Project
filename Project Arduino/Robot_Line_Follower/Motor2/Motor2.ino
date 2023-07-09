#define RE_KA 2
#define RE_KI 3
#define IN1 8
#define IN2 9
#define IN3 12
#define IN4 13


unsigned int countKA = 0;
unsigned int countKI = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(RE_KA,INPUT);
  pinMode(RE_KI,INPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(RE_KA), kecepatan_kanan, RISING);
  attachInterrupt(digitalPinToInterrupt(RE_KI), kecepatan_kiri, RISING);

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void loop()
{
  maju();
  
  if (countKA >= 15 && countKI >= 17)
  {
    berhenti();
  }

  Serial.print("Count Kanan: ");
  Serial.print(countKA);
  Serial.print(" |||| ");
  Serial.print("Count Kiri: ");
  Serial.println(countKI);
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

void berhenti()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
