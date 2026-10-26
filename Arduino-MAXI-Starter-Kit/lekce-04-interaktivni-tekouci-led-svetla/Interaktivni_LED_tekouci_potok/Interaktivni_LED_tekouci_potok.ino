/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 4: Interaktivní tekoucí LED světla
 *
 * Světlo běhá po osmi LED tam a zpět.
 * Potenciometrem měníš rychlost běhu.
 *
 * Zapojení:
 *   8× LED přes rezistor 220 Ω na piny 2 až 9, katody na GND
 *   Potenciometr: krajní vývody na 5V a GND, prostřední vývod na A0
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const byte ledPiny[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int pocetLed = sizeof(ledPiny);
const int potPin = A0;

int aktualniLed = 0;
int smer = 1;                    // 1 = doprava, -1 = doleva
unsigned long casZmeny = 0;

void setup() {
  for (int i = 0; i < pocetLed; i++) {
    pinMode(ledPiny[i], OUTPUT);
  }
}

void loop() {
  // hodnota 0–1023 z potenciometru = pauza v milisekundách
  unsigned long pauza = analogRead(potPin);

  // millis() vrací čas od zapnutí; LED přepneme, až uplyne pauza
  if (millis() - casZmeny >= pauza) {
    casZmeny = millis();
    posunLed();
  }
}

void posunLed() {
  for (int i = 0; i < pocetLed; i++) {
    digitalWrite(ledPiny[i], LOW);         // zhasnout všechny
  }
  digitalWrite(ledPiny[aktualniLed], HIGH); // rozsvítit aktuální

  aktualniLed += smer;
  if (aktualniLed == pocetLed - 1 || aktualniLed == 0) {
    smer = -smer;                           // na konci obrátit směr
  }
}
