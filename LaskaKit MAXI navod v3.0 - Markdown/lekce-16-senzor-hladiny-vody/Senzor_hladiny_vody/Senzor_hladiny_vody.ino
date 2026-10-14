/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 16: Senzor hladiny vody
 *
 * Čím hlouběji ponoříš senzor do vody, tím vyšší hodnotu uvidíš
 * na displeji I2C LCD1602. Hodnota je bez jednotek (0–1023).
 * Senzor neponořuj nad vyznačenou čáru – elektronika nesmí do vody.
 *
 * Zapojení:
 *   Senzor hladiny vody: – na GND, + na 5V, S na A0
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
const int senzorPin = A0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Hladina vody  ");
}

void loop() {
  int hodnota = analogRead(senzorPin);
  lcd.setCursor(0, 1);
  lcd.print("                ");  // smazat druhý řádek
  lcd.setCursor(6, 1);
  lcd.print(hodnota);
  delay(300);
}
