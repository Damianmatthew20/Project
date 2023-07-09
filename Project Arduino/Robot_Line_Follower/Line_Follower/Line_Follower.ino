#include <Servo.h>


//#define echo_kanan 0
//#define trig_kanan 1
#define RE_kanan 2
#define RE_kiri 3
#define IR_tengah 4
#define capit 5
#define echo_kanan 6
#define trig_kanan 7
#define echo_kiri 8
#define trig_kiri 9
#define IN1 10
#define IN2 11
//#define ENA 10
//#define ENB 11
#define IN3 12
#define IN4 13
#define ldr A0
#define IR_analog A1
#define IR_ki2 A2
#define IR_ki1 A3
#define IR_ka1 A4
#define IR_ka2 A5


Servo servo;


unsigned int countKA = 0;
unsigned int countKI = 0;
unsigned long duration_right;
unsigned long distance_right;
unsigned long duration_left;
unsigned long distance_left;


void setup()
{
  pinMode(echo_kanan,INPUT);
  pinMode(trig_kanan,OUTPUT);
  pinMode(RE_kanan,INPUT);
  pinMode(RE_kiri,INPUT);
  pinMode(IR_tengah,INPUT);
  servo.attach(capit);
  pinMode(echo_kiri,INPUT);
  pinMode(trig_kiri,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ldr,INPUT);
  pinMode(IR_analog,INPUT);
  //pinMode(IR_ki2,INPUT);
  //pinMode(IR_ki1,INPUT);
  //pinMode(IR_ka1,INPUT);
  //pinMode(IR_ka2,INPUT);

  attachInterrupt(digitalPinToInterrupt(RE_kanan), kecepatan_kanan, RISING);
  attachInterrupt(digitalPinToInterrupt(RE_kiri), kecepatan_kiri, RISING);

  servo.write(0);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void loop()
{
  
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
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
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
