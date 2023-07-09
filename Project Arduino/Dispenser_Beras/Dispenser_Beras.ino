#include <Servo.h>
#include <HX711.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);


const byte ROW1 = 4;
const byte COL1 = 3;
const byte ROW2 = 4;
const byte COL2 = 4;

char key1 [ROW1][COL1]=
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

char key2 [ROW2][COL2]=
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// NC 1 2 3 4 5 6 7 8 NC
byte rowPin1 [ROW1] = {8, 9, 10, 11}; // 4 5 6 7
byte colPin1 [COL1] = {4, 5, 6}; // 1 2 3
byte rowPin2 [ROW2] = {8, 9, 10, 11}; // 5 6 7 8
byte colPin2 [COL2] = {4, 5, 6, 7}; // 1 2 3 4

Keypad customKeypad1 = Keypad (makeKeymap (key1), rowPin1, colPin1, ROW1, COL1);
Keypad customKeypad2 = Keypad (makeKeymap (key2), rowPin2, colPin2, ROW2, COL2);


#define pinR 14
#define pinG 15
#define pinB 16
#define buzzer 12
#define pompa 13
#define DOUT 2
#define CLK 3

HX711 scale;
Servo servoku;

float faktor_kalibrasi = 34.20;
float satuan;
float total;
char mode;
char jumlah;
int menu = 1;
int nilai;

void setup()
{
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pompa, OUTPUT);
  pinMode(buzzer, OUTPUT);
  servoku.attach(17);
  
  digitalWrite(buzzer, HIGH);
  digitalWrite(pompa, HIGH);
  RGB_color (255, 0, 0);
  servoku.write(0);

  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  long zero_factor = scale.read_average();
  
  lcd.init();
  lcd.backlight();

  /*
  for (int a = 1; a <= 3; a++)
  {
    lcd.display();
    lcd.setCursor (7,1);
    lcd.print ("DISBOX");
    delay (1000);
    lcd.noDisplay();
    delay(1000);
  }
  
  lcd.clear();
  
  for (int a = 1; a <= 3; a++)
  {
    lcd.display();
    lcd.setCursor (4,1);
    lcd.print ("NOW");
    lcd.setCursor (6,2);
    lcd.print ("LOADING...");
    delay (500);
    lcd.noDisplay();
    delay(500);
  }
  */
  lcd.clear();
  lcd.noBacklight();
  delay(1000);
}

void loop()
{
  lcd.backlight();
  lcd.display();

  // Set Up Menu
  if (menu == 1)
  {
    menu1();
  }
  else if (menu == 2)
  {
    menu2();
  }
  else if (menu == 3)
  {
    menu3();
  }
  
  lcd.clear();
}


void RGB_color (int red, int green, int blue)
{
  analogWrite (pinR, red);
  analogWrite (pinG, green);
  analogWrite (pinB, blue);
}

void menu1()
{
  lcd.setCursor(0,0);
  lcd.print("Mode Beras:");
  lcd.setCursor(0,1);
  lcd.print("A) Nasi");
  lcd.setCursor(0,2);
  lcd.print("B) Bubur");
  lcd.setCursor(0,3);
  lcd.print("C) Manual");

  mode = customKeypad2.getKey();
  if (mode != NO_KEY)
  {
    if (mode == 'A')
    {
      digitalWrite(buzzer, LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      menu = 2;
    }
    else if (mode == 'B')
    {
      digitalWrite(buzzer, LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      menu = 2;
    }
    else if (mode == 'C')
    {
      digitalWrite(buzzer, LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      menu = 3;
    }
    else
    {
      lcd.clear();
      lcd.setCursor(4,1);
      lcd.print("PILIH TOMBOL");
      lcd.setCursor(3,2);
      lcd.print("YANG SESUAI!!!");
      for (int i = 1; i <= 3; i++)
      {
        digitalWrite(buzzer, LOW);
        delay(100);
        digitalWrite(buzzer, HIGH);
        delay(100);
      }
      delay(900);
      menu = 1;
    }
  }
  delay(300);
}

void menu2()
{
  lcd.setCursor(0,0);
  lcd.print("Jumlah Porsi(MAX=9):");
  lcd.setCursor(2,1);
  lcd.print("porsi");
  lcd.setCursor(1,3);
  lcd.print("Back(*) | Enter(#)");
  
  jumlah = customKeypad1.getKey();
  if (jumlah == '*')
  {
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    menu = 1;
  }
  else if (jumlah == '0' | jumlah == '#')
  {
    menu2();
  }
  else if (jumlah)
  {
    lcd.setCursor(0,1);
    lcd.print(jumlah);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    nilai = jumlah - 48;
      
    while (true)
    {
      jumlah = customKeypad1.getKey();
      if (jumlah == '#')
      {
        for (int i = 1; i <= 2; i++)
        {
          digitalWrite(buzzer, LOW);
          delay(100);
          digitalWrite(buzzer, HIGH);
          delay(100);
        }

        satuan = scale.get_units(), 1;
        total = nilai * 300;

        if (satuan <= (total + 20))
        {
          servoku.write(180);
          
        }
        else if (satuan >= (total + 20))
        {
          servoku.write(0);
          lcd.setCursor(0,1);
          lcd.print("Proses Sudah Selesai");
          delay(2000);
          lcd.clear();
          lcd.setCursor(2,1);
          lcd.print("Keluarkan Wadah");
          lcd.setCursor(3,2);
          lcd.print("Lalu Cuci Beras");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("Setelah Itu,");
          lcd.setCursor(1,2);
          lcd.print("Taruh Wadah Kembali");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("Tekan Tombol Apa Pun");
          lcd.setCursor(1,2);
          lcd.print("Untuk Melanjutkan!");
          
          customKeypad1.waitForKey();

          lcd.clear();
          lcd.setCursor(1,0);
          lcd.print("Wadah Akan Diisi Air");
          delay(1000);
          lcd.clear();
          digitalWrite(pompa, LOW);
          lcd.setCursor(1,1);
          lcd.print("Wadah Sedang Diisi");
          delay(3000);
          digitalWrite(pompa, HIGH);
          lcd.setCursor(0,6);
          lcd.print("Pengisian Air");
          lcd.setCursor(1,1);
          lcd.print("Sudah Selesai!");
          lcd.setCursor(3,3);
          lcd.print("Ambil Wadah!");
          
          break;
        }
      }
      else if (jumlah == '*')
      {
        digitalWrite(buzzer, LOW);
        delay(100);
        digitalWrite(buzzer, HIGH);
        delay(100);
        menu = 1;
        break;
      }
    }
  } 
  delay(300);
}

void menu3()
{
  lcd.setCursor(0,0);
  lcd.print("Berat(MAX=900 gr):");
  lcd.setCursor(4, 1);
  lcd.print("gram");
  lcd.setCursor(10,1);
  lcd.print("(1=100 gr)");
  lcd.setCursor(1,3);
  lcd.print("Back(*) | Enter(#)");

  jumlah = customKeypad1.getKey();
  if (jumlah == '*')
  {
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    menu = 1;
  }
  else if (jumlah == '#')
  {
    menu3();
  }
  else if (jumlah)
  {
    lcd.setCursor(0,1);
    lcd.print(jumlah);
    lcd.setCursor(1,1);
    lcd.print("00");
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    nilai = (jumlah - 48) * 100;
    
    while(true)
    {
      jumlah = customKeypad1.getKey();
      if (jumlah == '#')
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter is Pressed");
        for (int i = 1; i <= 2; i++)
        {
          digitalWrite(buzzer, LOW);
          delay(100);
          digitalWrite(buzzer, HIGH);
          delay(100);
        }
        break;
      }
      else if (jumlah == '*')
      {
        digitalWrite(buzzer, LOW);
        delay(100);
        digitalWrite(buzzer, HIGH);
        delay(100);
        menu = 1;
        break;
      }
    }
  }
  delay(300);
}
