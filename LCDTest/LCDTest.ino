int RSpin = 2;
int ENpin = 3;
int DB4pin = 4;
int DB5pin = 5;
int DB6pin = 6;
int DB7pin = 7;

#include <LiquidCrystal.h>

LiquidCrystal lcd(7,8,9,10,11,12);

void setup(){
 
  
  lcd.begin(16, 2);
  
  lcd.print("phil is fake");
}

void loop(){
  lcd.setCursor(0, 1);
}



