/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 11: Fotorezistor
 *
 * Čím víc světla dopadá na fotorezistor, tím víc LED svítí.
 * Ve tmě nesvítí žádná. Naměřenou hodnotu vidíš i v sériovém monitoru
 * (9600 Bd) – podle ní si můžeš upravit konstantu „tma“.
 *
 * Zapojení:
 *   Fotorezistor: jeden vývod na 5V, druhý na A0
 *   Odpor 10 kΩ: mezi A0 a GND
 *   8× LED přes odpor 220 Ω na piny 5 až 12, katody na GND
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int ledPiny[] = {5, 6, 7, 8, 9, 10, 11, 12};
const int pocetLed = 8;
const int fotoPin = A0;
const int tma = 300;  // hodnota, pod kterou nesvítí žádná LED

void setup() {
  for (int i = 0; i < pocetLed; i++) {
    pinMode(ledPiny[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int svetlo = analogRead(fotoPin);  // 0 (tma) až 1023 (světlo)
  Serial.println(svetlo);

  // převést rozsah tma..1023 na počet LED 0..8
  int pocetSvitich = map(svetlo, tma, 1023, 0, pocetLed);
  pocetSvitich = constrain(pocetSvitich, 0, pocetLed);

  for (int i = 0; i < pocetLed; i++) {
    digitalWrite(ledPiny[i], i < pocetSvitich ? HIGH : LOW);
  }
  delay(50);
}
