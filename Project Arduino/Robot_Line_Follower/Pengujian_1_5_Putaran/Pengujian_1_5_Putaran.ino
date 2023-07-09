#define RE 2
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

unsigned int counter;
unsigned int count = 0;
unsigned int rotation = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(RE,INPUT_PULLUP);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(RE), kecepatan, CHANGE);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop()
{
  maju();
  
  if (count >= 30)
  {
    berhenti();
  }

  Serial.print("Count: ");
  Serial.println(count);
}

void kecepatan()
{
  count++;
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
