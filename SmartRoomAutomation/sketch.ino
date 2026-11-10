#include <DHT.h>

// Konfigurasi pin
#define DHT_PIN 15
#define DHT_TYPE DHT22

#define LDR_PIN 34
#define LED_PIN 2
#define BUZZER_PIN 18

// Batas otomatisasi
#define BATAS_SUHU 30.0
#define BATAS_CAHAYA 1800

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("SMART ROOM AUTOMATION");
  Serial.println("Sistem dimulai...");
}

void loop() {

  // Membaca sensor DHT22
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();

  // Membaca sensor LDR
  int cahaya = analogRead(LDR_PIN);

  // Memeriksa apakah pembacaan DHT valid
  if (isnan(suhu) || isnan(kelembapan)) {
    Serial.println("Gagal membaca DHT22!");
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    delay(2000);
    return;
  }

  // Menampilkan data sensor
  Serial.println("====================");
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println(" C");

  Serial.print("Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  Serial.print("Nilai cahaya: ");
  Serial.println(cahaya);

  // Otomatisasi lampu
  // Asumsi nilai ADC rendah berarti gelap
  if (cahaya < BATAS_CAHAYA) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Lampu: MENYALA");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Lampu: MATI");
  }

  // Otomatisasi peringatan suhu
  if (suhu >= BATAS_SUHU) {
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Peringatan: SUHU PANAS!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Suhu: NORMAL");
  }

  delay(2000);
}
