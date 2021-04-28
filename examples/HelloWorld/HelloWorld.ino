#include "LCD_101x64.h"

LCD lcd(5, 4, 2, 8, 6);

void setup() {
  lcd.init();
  delay(500);
  lcd.clear();
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HELLO WORLD");
  lcd.setCursor(1,0);
  lcd.print(analogRead(0));
  delay(500);
}
