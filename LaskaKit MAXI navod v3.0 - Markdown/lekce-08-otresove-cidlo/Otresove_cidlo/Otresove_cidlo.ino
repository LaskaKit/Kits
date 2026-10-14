/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 8: Otřesové čidlo
 *
 * Když čidlem pohneš nebo ho nakloníš, kulička uvnitř spojí kontakty
 * a rozsvítí se LED na desce Arduino (pin 13).
 * Vstup používá vnitřní pull-up odpor, žádný další odpor není potřeba.
 *
 * Zapojení:
 *   Otřesové čidlo: jeden vývod na pin 2, druhý na GND
 *   LED: vestavěná LED „L“ na pinu 13
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int ledPin = 13;   // vestavěná LED
const int cidloPin = 2;  // otřesové čidlo

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(cidloPin, INPUT_PULLUP);  // zapnout vnitřní pull-up odpor
}

void loop() {
  // Sepnuté čidlo spojí pin 2 se zemí -> čteme LOW
  if (digitalRead(cidloPin) == LOW) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(50);  // krátká pauza proti zákmitům kontaktů
}
