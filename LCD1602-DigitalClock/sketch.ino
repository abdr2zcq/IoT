#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;
const int daylightOffset_sec = 0;
void setup() {
Serial.begin(115200);
Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("DIGITAL CLOCK");
  lcd.setCursor(3, 1);
  lcd.print("ESP32 LCD");
delay(2000);
  lcd.clear();
  lcd.print("Connecting WiFi");
  WiFi.begin(ssid, password, 6);
  while (WiFi.status() != WL_CONNECTED) {
delay(500);
}
  lcd.clear();
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print("Syncing Time...");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
delay(500);
}
  lcd.clear();
}
void loop() {
struct tm timeinfo;
if (!getLocalTime(&timeinfo)) {
  lcd.setCursor(0, 0);
  lcd.print("Time Error");
return;
}
char tanggal[17];
strftime(tanggal, sizeof(tanggal), "Tgl: %d/%m/%Y", &timeinfo);
  lcd.setCursor(0, 0);
  lcd.print(tanggal);
char jam[17];
strftime(jam, sizeof(jam), "Jam: %H:%M:%S", &timeinfo);
  lcd.setCursor(0, 1);
  lcd.print(jam);
delay(1000);
}
