/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 12: Ovládání zvuku pomocí světla
 *
 * Bzučák pípá tím pomaleji, čím víc světla dopadá na fotorezistor.
 * Ve tmě pípá rychle.
 *
 * Zapojení:
 *   Fotorezistor: jeden vývod na 5V, druhý na A0
 *   Rezistor 10 kΩ: mezi A0 a GND
 *   Aktivní bzučák: + na pin 9, – na GND
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int fotoPin = A0;
const int bzucakPin = 9;

void setup() {
  pinMode(bzucakPin, OUTPUT);
}

void loop() {
  int svetlo = analogRead(fotoPin);  // 0–1023
  int pauza = map(svetlo, 0, 1023, 20, 1000);

  digitalWrite(bzucakPin, HIGH);  // pípnutí
  delay(30);
  digitalWrite(bzucakPin, LOW);
  delay(pauza);                   // čím víc světla, tím delší pauza
}
