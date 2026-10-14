/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 7: Bzučák
 *
 * Aktivní bzučák má vlastní oscilátor – stačí na něj pustit napětí
 * a pípá. Program střídá krátká a dlouhá pípnutí.
 *
 * Zapojení:
 *   Aktivní bzučák: + (delší nožička) na pin 12, – na GND
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int bzucakPin = 12;

void setup() {
  pinMode(bzucakPin, OUTPUT);
}

void loop() {
  // tři krátká pípnutí
  for (int i = 0; i < 3; i++) {
    pipni(100);
    delay(100);
  }
  delay(400);
  // jedno dlouhé pípnutí
  pipni(600);
  delay(1000);
}

void pipni(int delka) {
  digitalWrite(bzucakPin, HIGH);  // bzučák zapnout
  delay(delka);
  digitalWrite(bzucakPin, LOW);   // bzučák vypnout
}
