#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home();
  lcd.setCursor(0 , 0);
  lcd.print("Home Automation");
  delay(1000);

}

void loop() {
  
  lcd.setCursor(2 , 1);
  lcd.print("temp");
  delay(1000);
  lcd.setCursor(2, 1);
  lcd.print("erature");
  delay(1000);
}