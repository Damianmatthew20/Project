#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define pushbutton 4
#define sensorMD 5
#define led 6
#define buzzer 7
#define RST_PIN 9
#define SS_PIN 10

int buttonState;
bool kondisiPintu;
bool sensorStateCurrent;
bool sensorStatePrevious;

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servoku;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode (pushbutton,INPUT_PULLUP);
  pinMode (sensorMD,INPUT_PULLUP);
  pinMode (led,OUTPUT);
  pinMode (buzzer,OUTPUT);
  
  servoku.attach(3);
  servoku.write(130);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor (3,0);
  lcd.print ("TIM IMPALA");
  delay (3000);
  lcd.clear();
  for (int a = 1; a <= 3; a++) //membuat tulisan "Now Loading" berkedip sebanyak 3 kali
  {
    lcd.setCursor (2,0);
    lcd.print ("NOW");
    lcd.setCursor (4,1);
    lcd.print ("LOADING...");
    delay (500);
    lcd.clear();
    delay (500);
  }
  
  lcd.noBacklight();
  digitalWrite (led,HIGH);
}

void loop() 
{
  buttonState = digitalRead (pushbutton);
  
  if (buttonState == LOW) // kondisi pada saat pintu dibuka dari dalam
  {
    BukaTutupPintu();
  }
  
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) //apabila tidak ada kartu yang terdeteksi, maka akan kembali ke program void loop awal
  {
    return;
  }

  // Verify if the UID has been readed
  if (!mfrc522.PICC_ReadCardSerial()) //apabila tidak ada kode kartu yang terdeteksi, maka akan kembali ke program void loop awal
  {
    return;
  }
  
  Serial.println ("UID tag :");
  //                    
  String content = ("");
  byte letter;
  for (byte i=0; i < mfrc522.uid.size; i++)
  {
    Serial.print (mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "); 
    Serial.print (mfrc522.uid.uidByte[i], HEX);
    content.concat (String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat (String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  
  if (content.substring(1) == "DA CC C1 80") // kondisi pada saat pintu dibuka dari luar
  {
    BukaTutupPintu();
  }
  
  else // kondisi pada saat kode kartu yang terbaca salah atau tidak sesuai
  {
    digitalWrite (led,LOW);
    lcd.backlight();
    lcd.display();
    lcd.setCursor (0,0);
    lcd.print ("ACCESS DENIED");
    lcd.setCursor (0,1);
    lcd.print ("WRONG CARD");
    for (int b=1; b<=3; b++) // buzzer akan berbunyi sebanyak 3 kali
    {
      tone (buzzer,5000);
      delay (100);
      noTone (buzzer);
      delay (100);
    }
    delay (1000);
    lcd.clear();
    lcd.noBacklight();
    digitalWrite (led,HIGH);
  }
}

void BukaTutupPintu()
{
  kondisiPintu = true;
  digitalWrite (led,LOW);
  tone (buzzer,5000);
  delay (100);
  noTone (buzzer);
  delay (100);
  lcd.backlight();
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print("ACCESS GRANTED");
  lcd.setCursor(0,1);
  lcd.print("DOOR OPEN");
  servoku.write(180);
  
  while (kondisiPintu == true)
  {
    sensorStateCurrent = digitalRead (sensorMD);
          
    if (sensorStatePrevious == HIGH && sensorStateCurrent == LOW)
    {
      kondisiPintu = false;
      delay (1000);
      servoku.write(130);
      digitalWrite (led,HIGH);
      lcd.clear();
      lcd.noBacklight();
    }
    sensorStatePrevious = sensorStateCurrent;
  }
}
