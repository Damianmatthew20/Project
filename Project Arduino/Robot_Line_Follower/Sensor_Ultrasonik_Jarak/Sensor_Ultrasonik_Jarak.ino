#define echo_kanan 6
#define trig_kanan 7
#define echo_kiri 10
#define trig_kiri 11


unsigned long duration_right;
unsigned long distance_right;
unsigned long duration_left;
unsigned long distance_left;


void setup()
{
  Serial.begin(9600);
  pinMode(echo_kanan,INPUT);
  pinMode(trig_kanan,OUTPUT);
  pinMode(echo_kiri,INPUT);
  pinMode(trig_kiri,OUTPUT);
}

void loop()
{
  ultrasonik_kanan();
  ultrasonik_kiri();
  delay(1000);
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
