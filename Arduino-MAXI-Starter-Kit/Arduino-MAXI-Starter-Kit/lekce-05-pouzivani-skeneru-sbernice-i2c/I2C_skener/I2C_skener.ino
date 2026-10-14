/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 5: Skener sběrnice I²C
 *
 * Projde všechny adresy na sběrnici I²C a vypíše do sériového
 * monitoru ty, na kterých odpovědělo nějaké zařízení.
 * Hodí se, když LCD displej nic neukazuje – zjistíš jeho skutečnou
 * adresu (obvykle 0x27, někdy 0x3F).
 * Sériový monitor nastav na 9600 Bd.
 *
 * Zapojení:
 *   I2C LCD1602: GND–GND, VCC–5V
 *   UNO R3 / UNO R4 WiFi: SDA–A4, SCL–A5 (nebo piny SDA/SCL u AREF)
 *   Mega 2560: SDA–20, SCL–21
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) { }  // u některých desek počkat na otevření monitoru
  Serial.println();
  Serial.println("I2C skener");
}

void loop() {
  int pocetZarizeni = 0;
  Serial.println("Skenuji...");

  for (byte adresa = 1; adresa < 127; adresa++) {
    // Zařízení, které na adrese existuje, potvrdí přenos (výsledek 0)
    Wire.beginTransmission(adresa);
    byte vysledek = Wire.endTransmission();

    if (vysledek == 0) {
      Serial.print("Nalezeno I2C zarizeni na adrese 0x");
      if (adresa < 16) Serial.print("0");
      Serial.println(adresa, HEX);
      pocetZarizeni++;
    } else if (vysledek == 4) {
      Serial.print("Neznama chyba na adrese 0x");
      if (adresa < 16) Serial.print("0");
      Serial.println(adresa, HEX);
    }
  }

  if (pocetZarizeni == 0) {
    Serial.println("Zadne I2C zarizeni nenalezeno. Zkontroluj zapojeni.");
  } else {
    Serial.println("Hotovo.");
  }
  Serial.println();
  delay(5000);  // další sken za 5 sekund
}
