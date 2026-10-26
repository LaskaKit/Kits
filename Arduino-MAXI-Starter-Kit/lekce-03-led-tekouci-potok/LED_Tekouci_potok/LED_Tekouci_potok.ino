/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 3: LED tekoucí potok
 *
 * Osm LED se postupně rozsvěcí a zhasíná jedna po druhé,
 * jako by světlem tekla voda – tam a zpátky.
 *
 * Zapojení:
 *   8× LED přes rezistor 220 Ω na piny 2, 3, 4, 5, 6, 7, 8, 9
 *   Katody (kratší nožičky) všech LED na GND
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int prvniPin = 2;     // pin první LED
const int posledniPin = 9;  // pin poslední LED
const int pauza = 100;      // rychlost efektu v ms

void setup() {
  for (int pin = prvniPin; pin <= posledniPin; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  // rozsvítit zleva doprava
  for (int pin = prvniPin; pin <= posledniPin; pin++) {
    digitalWrite(pin, HIGH);
    delay(pauza);
  }
  // zhasnout zprava doleva
  for (int pin = posledniPin; pin >= prvniPin; pin--) {
    digitalWrite(pin, LOW);
    delay(pauza);
  }
  // rozsvítit zprava doleva
  for (int pin = posledniPin; pin >= prvniPin; pin--) {
    digitalWrite(pin, HIGH);
    delay(pauza);
  }
  // zhasnout zleva doprava
  for (int pin = prvniPin; pin <= posledniPin; pin++) {
    digitalWrite(pin, LOW);
    delay(pauza);
  }
}
