#include <Countimer.h>
Countimer timer;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


#define potensio A0
#define pb_up 4
#define pb_down 5
#define pb_reset 6
#define pb_enter_set 7
#define led 8
#define buzzer 9
#define R_PWM 10
#define L_PWM 11

unsigned int status_up;
unsigned int status_down;
unsigned int status_reset;
unsigned int status_enter_set;
unsigned int kecepatan_potensio;
unsigned int kecepatan_motor;
unsigned int opsi = 1;
unsigned int menu_value;

unsigned int s = 0;
unsigned int m = 0;
unsigned int h = 0;

bool condition;
bool condition_pb = false;


void start_menu();
void menu1();
void menu2();
void menu3();
void menu4();
void main_menu();
void refresh_time();
void time_second();
void time_minute();
void time_hour();
void complete();


void setup()
{
  pinMode(potensio,INPUT);
  pinMode(pb_up,INPUT_PULLUP);
  pinMode(pb_down,INPUT_PULLUP);
  pinMode(pb_reset,INPUT_PULLUP);
  pinMode(pb_enter_set,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(R_PWM,OUTPUT);
  pinMode(L_PWM,OUTPUT);

  lcd.init();
  lcd.backlight();

  start_menu();
  delay(200);
  lcd.clear();

  analogWrite(R_PWM,0);
  analogWrite(L_PWM,0);
}

void loop()
{
  condition = true;
  home_menu();
  lcd.clear();
  delay(100);
  
  condition = true;
  main_menu();
  lcd.clear();
  delay(100);
  
  condition = true;
  time_second();
  lcd.clear();
  delay(100);
  
  condition = true;
  time_minute();
  lcd.clear();
  delay(100);
  
  condition = true;
  time_hour();
  lcd.clear();
  delay(100);

  timer.setCounter(h,m,s,timer.COUNT_DOWN,complete);
  timer.setInterval(refresh_time,1000);
  lcd.setCursor(1,0);
  lcd.print("SETELAN WAKTU:");
  lcd.setCursor(4,1);
  lcd.print(timer.getCurrentTime());

  condition = true;
  while(condition)
  {
    timer.run();

    status_enter_set = digitalRead(pb_enter_set);
    status_reset = digitalRead(pb_reset);
    kecepatan_potensio = analogRead(potensio);

    kecepatan_motor = map(kecepatan_potensio,0,1024,0,255);
    kecepatan_motor = map(kecepatan_motor,0,255,0,75);
    
    if(status_enter_set == LOW)
    {
      condition_pb = !condition_pb;
      delay(100);
    }
    else if (status_reset == LOW)
    {
      digitalWrite(led,LOW);
      analogWrite(R_PWM,0);
      analogWrite(L_PWM,0);
      break;
      home_menu();
    }

    if(condition_pb == true)
    {
      timer.start();
      digitalWrite(led,HIGH);
      analogWrite(R_PWM,kecepatan_motor);
      analogWrite(L_PWM,0);
    }
    else if(condition_pb == false)
    {
      timer.pause();
      digitalWrite(led,LOW);
      analogWrite(R_PWM,0);
      analogWrite(L_PWM,0);
    }
    
    delay(100);
  }
  
  lcd.clear();
  delay(100);
}
