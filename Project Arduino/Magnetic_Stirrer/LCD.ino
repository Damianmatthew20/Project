void start_menu()
{
  digitalWrite(led,HIGH);
  
  for(int i = 0;i < 18;i++)
  {
    lcd.setCursor(18,0);
    lcd.print("MAGNETIC STIRRER");
    lcd.setCursor(20,1);
    lcd.print("BY YEHESKIEL");
    lcd.scrollDisplayLeft();
    delay(350);
  }
  delay(1200);
  lcd.clear();
  delay(100);
  
  for (int a = 1; a <= 3; a++)
  {
    lcd.setCursor(2,0);
    lcd.print("NOW");
    lcd.setCursor(4,1);
    lcd.print("LOADING...");
    delay(500);
    lcd.clear();
    delay(500);
  }
  lcd.clear();
  delay(100);
  digitalWrite(led,LOW);
}


void home_menu()
{
  while(condition)
  {
    status_enter_set = digitalRead(pb_enter_set);

    if(status_enter_set == LOW)
    {
      condition = false;
    }
    
    lcd.display();
    lcd.setCursor(0,0);
    lcd.print("START:");
    lcd.setCursor(0,1);
    lcd.print("> PRESS ENTER");

    delay(100);
  }
  
}

void menu1()
{
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print("Ukuran Magnet:");
  lcd.setCursor(0,1);
  lcd.print("> 20 mm");
  menu_value = 20;
}


void menu2()
{
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print("Ukuran Magnet:");
  lcd.setCursor(0,1);
  lcd.print("> 30 mm");
  menu_value = 30;
}


void menu3()
{
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print("Ukuran Magnet:");
  lcd.setCursor(0,1);
  lcd.print("> 40 mm");
  menu_value = 40;
}


void menu4()
{
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print("Ukuran Magnet:");
  lcd.setCursor(0,1);
  lcd.print("> 50 mm");
  menu_value = 50;
}


void main_menu()
{
  while(condition)
  {
    status_up = digitalRead(pb_up);
    status_down = digitalRead(pb_down);
    status_enter_set = digitalRead(pb_enter_set);
  
    if(status_up == LOW)
    {
      opsi += 1;

      if(opsi >= 4)
      {
        opsi = 4;
      }

      lcd.clear();
    }
    else if(status_down == LOW)
    {
      opsi -= 1;

      if(opsi <= 1)
      {
        opsi = 1;
      }
    
      lcd.clear();
    }
    else if(status_enter_set == LOW)
    {
      condition = false;
    }
  
    switch(opsi)
    {
      case 1:
      menu1();
      break;

      case 2:
      menu2();
      break;
    
      case 3:
      menu3();
      break;
    
      case 4:
      menu4();
      break;
    }

    delay(100);
  }

  return menu_value;
}
