/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 21: RGB LED
 *
 * RGB LED postupně svítí červeně, zeleně a modře a pak míchá další
 * barvy – oranžovou, žlutou, indigo a fialovou. Jas každé složky
 * se řídí přes PWM.
 *
 * Zapojení:
 *   RGB LED modul: R–11, G–10, B–9, – na GND
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int cervenaPin = 11;
const int zelenaPin = 10;
const int modraPin = 9;

void setup() {
  pinMode(cervenaPin, OUTPUT);
  pinMode(zelenaPin, OUTPUT);
  pinMode(modraPin, OUTPUT);
}

void loop() {
  barva(255, 0, 0);     // červená
  delay(1000);
  barva(0, 255, 0);     // zelená
  delay(1000);
  barva(0, 0, 255);     // modrá
  delay(1000);
  barva(237, 109, 0);   // oranžová
  delay(1000);
  barva(255, 215, 0);   // žlutá
  delay(1000);
  barva(0, 46, 90);     // indigo
  delay(1000);
  barva(128, 0, 128);   // fialová
  delay(1000);
  barva(0, 0, 0);       // zhasnuto
  delay(500);
}

// nastaví jas jednotlivých složek 0–255
void barva(int r, int g, int b) {
  analogWrite(cervenaPin, r);
  analogWrite(zelenaPin, g);
  analogWrite(modraPin, b);
}
