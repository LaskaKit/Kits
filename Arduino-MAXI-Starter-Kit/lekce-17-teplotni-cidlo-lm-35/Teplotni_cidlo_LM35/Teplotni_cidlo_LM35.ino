/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 17: Teplotní čidlo LM35
 *
 * Změří teplotu čidlem LM35 a zobrazí ji na displeji I2C LCD1602.
 * LM35 dává 10 mV na každý °C (25 °C = 250 mV).
 * Program průměruje 20 měření, aby údaj neskákal.
 *
 * Zapojení:
 *   LM35 (plochou stranou k sobě, zleva): +Vs na 5V, Vout na A0, GND na GND
 *   I2C LCD1602: GND–GND, VCC–5V, SDA/SCL podle lekce 6
 *
 * Knihovny: LiquidCrystal I2C (Frank de Brabander) – Správce knihoven
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int lm35Pin = A0;
const int pocetMereni = 20;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(6, 0);
  lcd.print("LM35");
}

void loop() {
  // průměr z několika měření potlačí šum
  long soucet = 0;
  for (int i = 0; i < pocetMereni; i++) {
    soucet += analogRead(lm35Pin);
    delay(5);
  }
  float prumer = soucet / (float)pocetMereni;

  float napeti_mV = prumer * 5000.0 / 1023.0;  // převod na milivolty
  float teplota = napeti_mV / 10.0;            // 10 mV = 1 °C

  lcd.setCursor(0, 1);
  lcd.print("Teplota: ");
  lcd.print(teplota, 1);
  lcd.print((char)223);  // znak stupně °
  lcd.print("C ");
  delay(500);
}
