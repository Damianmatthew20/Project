void time_second()
{
  while(condition)
  {
    lcd.setCursor(0,0);
    lcd.print("DETIK:");
    lcd.setCursor(0,1);
    lcd.print(s);

    status_up = digitalRead(pb_up);
    status_down = digitalRead(pb_down);
    status_enter_set = digitalRead(pb_enter_set);
  
    if(status_up == LOW)
    {
      s += 1;

      if(s > 59)
      {
        s = 0;
      }

      lcd.clear();
    }
    else if(status_down == LOW)
    {
      s -= 1;

      if(s < 0)
      {
        s = 59;
      }
    
      lcd.clear();
    }
    else if(status_enter_set == LOW)
    {
      condition = false;
    }
  
    delay(100);
  }

  return s;
}


void time_minute()
{
  while(condition)
  {
    lcd.setCursor(0,0);
    lcd.print("MENIT:");
    lcd.setCursor(0,1);
    lcd.print(m);

    status_up = digitalRead(pb_up);
    status_down = digitalRead(pb_down);
    status_enter_set = digitalRead(pb_enter_set);
  
    if(status_up == LOW)
    {
      m += 1;

      if(m > 59)
      {
        m = 0;
      }

      lcd.clear();
    }
    else if(status_down == LOW)
    {
      m -= 1;

      if(m < 0)
      {
        m = 59;
      }
    
      lcd.clear();
    }
    else if(status_enter_set == LOW)
    {
      condition = false;
    }
  
    delay(100);
  }

  return m;
}


void time_hour()
{
  while(condition)
  {
    lcd.setCursor(0,0);
    lcd.print("JAM:");
    lcd.setCursor(0,1);
    lcd.print(h);

    status_up = digitalRead(pb_up);
    status_down = digitalRead(pb_down);
    status_enter_set = digitalRead(pb_enter_set);
  
    if(status_up == LOW)
    {
      h += 1;

      if(h > 24)
      {
        h = 0;
      }

      lcd.clear();
    }
    else if(status_down == LOW)
    {
      h -= 1;

      if(h < 0)
      {
        h = 24;
      }
    
      lcd.clear();
    }
    else if(status_enter_set == LOW)
    {
      condition = false;
    }
  
    delay(100);
  }

  return h;
}


void refresh_time()
{
  lcd.setCursor(1,0);
  lcd.print("WAKTU TERSISA:");
  lcd.setCursor(4,1);
  lcd.print(timer.getCurrentTime());
}


void complete()
{
  condition = false;

  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("WAKTU TERSISA:");
  lcd.setCursor(4,1);
  lcd.print("00:00:00");

  digitalWrite(led,LOW);
  analogWrite(R_PWM,0);
  analogWrite(L_PWM,0);
   
  while(true)
  {
    status_enter_set = digitalRead(pb_enter_set);
    
    if(status_enter_set == LOW)
    {
      digitalWrite(buzzer,LOW);
      digitalWrite(led,LOW);
      break;
    }
  
    digitalWrite(buzzer,HIGH);
    digitalWrite(led,HIGH);
    delay(300);
    digitalWrite(buzzer,LOW);
    digitalWrite(led,LOW);
  }
}
