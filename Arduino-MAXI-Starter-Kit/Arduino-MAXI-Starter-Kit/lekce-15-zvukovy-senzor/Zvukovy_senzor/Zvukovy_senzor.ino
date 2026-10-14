/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 15: Zvukový senzor
 *
 * Program měří, jak moc se mění signál z mikrofonu (rozkmit), a když
 * je zvuk dost hlasitý (tleskni, promluv), rozsvítí na 2 s LED na pinu 13.
 * Rozkmit vidíš v sériovém monitoru (9600 Bd) – podle něj si nastav
 * konstantu „prah“.
 *
 * Zapojení:
 *   Zvukový senzor: AO–A0, G–GND, + na 3,3V (výstup DO nezapojuješ)
 *   LED: vestavěná LED „L“ na pinu 13
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int ledPin = 13;
const int zvukPin = A0;
const int prah = 50;          // citlivost – menší číslo = citlivější
const int oknoMeren = 50;     // délka měření v ms

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Během 50 ms najdeme nejmenší a největší hodnotu signálu.
  // Rozdíl (rozkmit) odpovídá hlasitosti zvuku.
  int minimum = 1023;
  int maximum = 0;
  unsigned long start = millis();
  while (millis() - start < oknoMeren) {
    int hodnota = analogRead(zvukPin);
    if (hodnota < minimum) minimum = hodnota;
    if (hodnota > maximum) maximum = hodnota;
  }
  int rozkmit = maximum - minimum;
  Serial.println(rozkmit);

  if (rozkmit > prah) {
    digitalWrite(ledPin, HIGH);
    delay(2000);  // LED svítí 2 sekundy
    digitalWrite(ledPin, LOW);
  }
}
