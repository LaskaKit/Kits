/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 1: Řízení LED tlačítkem
 *
 * Dokud držíš tlačítko, svítí LED na desce Arduino (pin 13).
 * Po puštění tlačítka LED zhasne.
 *
 * Zapojení:
 *   Tlačítko: jeden vývod na 5V, druhý na pin 12
 *   Odpor 10 kΩ: mezi pin 12 a GND (drží vstup v klidu na LOW)
 *   LED: vestavěná LED „L“ na pinu 13 (nic nezapojuješ)
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int tlacitkoPin = 12;  // pin, na kterém je tlačítko
const int ledPin = 13;       // vestavěná LED na desce

void setup() {
  pinMode(tlacitkoPin, INPUT);  // tlačítko je vstup
  pinMode(ledPin, OUTPUT);      // LED je výstup
}

void loop() {
  // Při stisku je na pinu 12 napětí 5 V, tedy HIGH
  if (digitalRead(tlacitkoPin) == HIGH) {
    digitalWrite(ledPin, HIGH);  // rozsvítit LED
  } else {
    digitalWrite(ledPin, LOW);   // zhasnout LED
  }
}
