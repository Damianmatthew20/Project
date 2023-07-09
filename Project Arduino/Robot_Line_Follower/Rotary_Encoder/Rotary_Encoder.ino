#define RE 3

unsigned int counter;
unsigned int count = 0;
unsigned int rotation = 0;


void setup()
{
  Serial.begin(9600);
  pinMode (RE,INPUT);
}

void loop()
{
  counter = digitalRead(RE);

  if (counter == 1)
  {
    count++;
  }

  rotation = (count/20);
  Serial.print("Count: ");
  Serial.println(rotation);
}
