#define RE_kanan 2
#define RE_kiri 3
#define echo_kanan 6
#define trig_kanan 7
#define IN1 8
#define IN2 9
#define echo_kiri 10
#define trig_kiri 11
#define IN3 12
#define IN4 13


unsigned int countKA = 0;
unsigned int countKI = 0;
unsigned long duration_right;
unsigned long distance_right;
unsigned long duration_left;
unsigned long distance_left;


void setup()
{
  Serial.begin(9600);
  pinMode(IN1,OUTPUT); // Roda motor A
  pinMode(IN2,OUTPUT); // Roda motor A
  pinMode(IN3,OUTPUT); // Roda motor B
  pinMode(IN4,OUTPUT); // Roda motor B
  pinMode(RE_kanan,INPUT);
  pinMode(RE_kiri,INPUT);
  pinMode(echo_kanan,INPUT);
  pinMode(trig_kanan,OUTPUT);
  pinMode(echo_kiri,INPUT);
  pinMode(trig_kiri,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(RE_kanan), kecepatan_kanan, RISING);
  attachInterrupt(digitalPinToInterrupt(RE_kiri), kecepatan_kiri, RISING);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop()
{
  ultrasonik_kanan();
  ultrasonik_kiri();
  
  if(distance_right <= 20)
  {
    kanan();
    if (countKA == 10 && countKI == 10)
    {
      berhenti();
    }
    
    delay(5000);
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
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
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

void ultrasonik_kanan()
{
  digitalWrite(trig_kanan,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_kanan,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_kanan,LOW);
  
  duration_right = pulseIn(echo_kanan,HIGH);
  distance_right = duration_right*0.034/2;
  Serial.print("Distance Right: ");
  Serial.print(distance_right);
  Serial.print(" CM ");
  Serial.print(" || ");
}

void ultrasonik_kiri()
{
  digitalWrite(trig_kiri,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_kiri,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_kiri,LOW);
  
  duration_left = pulseIn(echo_kiri,HIGH);
  distance_left = duration_left*0.034/2;
  Serial.print("Distance Left: ");
  Serial.print(distance_left);
  Serial.println(" CM ");
}
