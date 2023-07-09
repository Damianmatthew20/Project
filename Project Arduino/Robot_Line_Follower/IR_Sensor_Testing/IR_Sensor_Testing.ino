#define DO 4
#define AO

int analog;
int digital;

void setup()
{
  Serial.begin(9600);
  pinMode(DO,INPUT);
  pinMode(AO,INPUT);
}

void loop()
{
  analog = analogRead(AO);
  digital = digitalRead(DO);
  Serial.print("Analog = ");
  Serial.println(analog);
  Serial.print("Digital = ");
  Serial.println(digital);
  delay(500);
}
