#define IN1 8
#define IN2 9
//#define ENA 10
//#define ENB 11
#define IN3 12
#define IN4 13


/*
Kecepatan bisa bervariasi dari 0-255 (0V-6V)

Cara:
#define ENA
#define ENB
pinMode(ENA,OUTPUT);
pinMode(ENB,OUTPUT);
digitalWrite(ENA, 255); untuk mengatur kecepatan motor A
digitalWrite(ENB, 255); untuk mengatur kecepatan motor B

Apabila:
> ENA dan ENB dijumper, maka kecepatan selalu maksimum
> ENA dan ENB dihubungkan ke arduino, maka kecepatan bisa diatur
> ENA dan ENB tidak dihubungkan kedua pinnya, maka ENA dan ENB tidak aktif
*/


void setup()
{
  pinMode(IN1,OUTPUT); // Roda motor A
  pinMode(IN2,OUTPUT); // Roda motor A
  //pinMode(ENA,OUTPUT);
  //pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT); // Roda motor B
  pinMode(IN4,OUTPUT); // Roda motor B

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void maju()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //digitalWrite(ENA,200);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //digitalWrite(ENB,60);
}

void mundur()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
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
