#define ldr A0
#define sensorSM A1
#define sensorWL A2
#define pushbutton 3
#define led 4
#define lampu 5
#define pompa 6

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int kelembapan;
int cahaya;
int tinggiAir;
int buttonState;

void setup()
{
  Serial.begin (9600);
  lcd.init();
  lcd.backlight();
  
  for (int i = 1; i <= 3; i++)
  {
    lcd.setCursor (1,0);
    lcd.print ("AUTO  WATERING");
    lcd.setCursor (5,1);
    lcd.print ("SYSTEM");
    delay (2000);
    lcd.clear();
    delay (1000);
  }
  
  for (int i = 1; i <= 3; i++)
  {
    lcd.setCursor(2,0);
    lcd.print("AWAS PROGRAM");
    lcd.setCursor(1,1);
    lcd.print("IS NOW LOADING");
    delay (800);
    lcd.clear();
    delay (400);
  }
  lcd.noBacklight();
  
  pinMode (ldr,INPUT);
  pinMode (sensorSM,INPUT);
  pinMode (sensorWL,INPUT);
  pinMode (pushbutton,INPUT_PULLUP);
  pinMode (led,OUTPUT);
  pinMode (lampu,OUTPUT);
  pinMode (pompa,OUTPUT);
}

void loop()
{
  //Kelembapan Tanah
  kelembapan = analogRead (sensorSM);
  kelembapan = map(kelembapan, 0, 1023, 0, 255);
  kelembapan = kelembapan*100/255;
  Serial.print("Kelembapan Tanah = ");
  Serial.print(kelembapan);
  Serial.println(" %");
    
  if (kelembapan >= 60)
  {
    digitalWrite (pompa,LOW);
  }
  
  else
  {
    digitalWrite (pompa,HIGH);
  }
  
  //Intensitas Cahaya
  cahaya = analogRead (ldr);
  cahaya = map (cahaya, 0, 1023, 0, 255);
  cahaya = cahaya*100/255;
  Serial.print ("Intensitas Cahaya = ");
  Serial.println (cahaya);
  
  if (cahaya >40 && cahaya < 60)
  {
    digitalWrite (lampu,HIGH);
  }
   
  else
  {
    digitalWrite (lampu,LOW);
  }
  
  //Ketinggian Air
  tinggiAir = analogRead (sensorWL)/7.3;
  Serial.print("Tinggi Air = ");
  Serial.print(tinggiAir);
  Serial.println(" %");

  if (tinggiAir < 40)
  {
    digitalWrite (led,HIGH);
  }
  
  else
  {
    digitalWrite (led,LOW);
  }
  
  //LCD
  buttonState = digitalRead (pushbutton);
  Serial.print("Kondisi Pushbutton = ");
  Serial.println(buttonState);
  if (buttonState == LOW)
  {
    lcd.display();
    lcd.backlight();
    lcd.setCursor (0,0);
    lcd.print ("Kelembapan");
    lcd.setCursor (0,1);
    lcd.print ("Tanah = ");
    lcd.setCursor (8,1);
    lcd.print (kelembapan);
    lcd.setCursor (11,1);
    lcd.print ("%");
    delay (3000);
    lcd.clear();
    delay(500);
    lcd.setCursor (0,0);
    lcd.print ("Intensitas");
    lcd.setCursor (0,1);
    lcd.print ("Cahaya = ");
    lcd.setCursor (9,1);
    lcd.print (cahaya);
    lcd.setCursor (12,1);
    lcd.print ("%");
    delay (3000);
    lcd.clear();
    delay(500);
    lcd.setCursor (0,0);
    lcd.print ("Ketinggian");
    lcd.setCursor (0,1);
    lcd.print ("Air = ");
    lcd.setCursor (6,1);
    lcd.print (tinggiAir);
    lcd.setCursor (9,1);
    lcd.print ("%");
    delay (3000);
    lcd.clear();
    delay(500);
    lcd.noBacklight();
  }
  Serial.println();
}
