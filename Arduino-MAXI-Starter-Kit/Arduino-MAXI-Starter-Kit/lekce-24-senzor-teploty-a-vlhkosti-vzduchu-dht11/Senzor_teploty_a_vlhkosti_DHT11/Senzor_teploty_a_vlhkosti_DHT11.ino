/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 24: Senzor teploty a vlhkosti vzduchu DHT11
 *
 * Čidlo DHT11 měří teplotu a relativní vlhkost vzduchu.
 * Hodnoty se zobrazují na displeji I2C LCD1602 a v sériovém monitoru.
 * DHT11 je pomalé čidlo – nová hodnota je k dispozici zhruba každé 2 s.
 *
 * Zapojení:
 *   DHT11 modul: – na GND, + na 5V, S na pin 4
 *   I2C LCD1602: GND–GND, VCC–5V, SDA/SCL podle lekce 6
 *
 * Knihovny: DHT sensor library (Adafruit) + Adafruit Unified Sensor, LiquidCrystal I2C – Správce knihoven
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const int dhtPin = 4;
DHT dht(dhtPin, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("DHT11 start...");
  delay(2000);  // čidlo potřebuje chvíli po zapnutí
  lcd.clear();
}

void loop() {
  float vlhkost = dht.readHumidity();
  float teplota = dht.readTemperature();  // ve °C

  if (isnan(vlhkost) || isnan(teplota)) {
    // čtení se nepovedlo – nejčastěji špatně zapojený pin S
    lcd.setCursor(0, 0);
    lcd.print("Chyba cteni DHT ");
    lcd.setCursor(0, 1);
    lcd.print("Zkontroluj pin 4");
    Serial.println("Chyba cteni z DHT11");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Teplota: ");
    lcd.print(teplota, 1);
    lcd.print((char)223);
    lcd.print("C ");
    lcd.setCursor(0, 1);
    lcd.print("Vlhkost: ");
    lcd.print(vlhkost, 0);
    lcd.print(" %   ");

    Serial.print("Teplota: ");
    Serial.print(teplota, 1);
    Serial.print(" C, vlhkost: ");
    Serial.print(vlhkost, 0);
    Serial.println(" %");
  }
  delay(2000);
}
