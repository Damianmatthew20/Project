#define RE_KA 2
#define RE_KI 3
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11


unsigned int countKA = 0;
unsigned int countKI = 0;


void setup()
{
  pinMode(IN1,OUTPUT); // Roda motor A
  pinMode(IN2,OUTPUT); // Roda motor A
  pinMode(IN3,OUTPUT); // Roda motor B
  pinMode(IN4,OUTPUT); // Roda motor B
  
  attachInterrupt(digitalPinToInterrupt(RE_KA), kecepatan_kanan, RISING);
  attachInterrupt(digitalPinToInterrupt(RE_KI), kecepatan_kiri, RISING);
}

void loop()
{
  if (countKA <= 10 && countKI <= 10)
  {
    kiri();
  }
  else
  {
    berhenti();
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

void berhenti()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void kiri()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void kanan()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
