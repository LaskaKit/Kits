/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 25: Modul relé
 *
 * Relé každou sekundu sepne a rozepne – uslyšíš cvakání
 * a na modulu bliká kontrolka.
 * Většina modulů relé spíná při HIGH. Pokud tvůj modul spíná obráceně
 * (kontrolka svítí, když má být relé vypnuté), změň RELE_ZAPNUTO na LOW.
 *
 * Zapojení:
 *   Modul relé: S (IN) na pin 8, + (VCC) na 5V, – (GND) na GND
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int relePin = 8;
const int RELE_ZAPNUTO = HIGH;  // u modulů spínaných nulou změň na LOW
const int RELE_VYPNUTO = !RELE_ZAPNUTO;

void setup() {
  pinMode(relePin, OUTPUT);
  digitalWrite(relePin, RELE_VYPNUTO);
}

void loop() {
  digitalWrite(relePin, RELE_ZAPNUTO);  // sepnout
  delay(1000);
  digitalWrite(relePin, RELE_VYPNUTO);  // rozepnout
  delay(1000);
}
