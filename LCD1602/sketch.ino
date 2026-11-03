#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Halo Dunia!");
  lcd.setCursor(1, 1);
  lcd.print("SELAMAT DATANG");
}

void loop() {
 
}
