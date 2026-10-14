/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 13: Senzor plamene
 *
 * Infračervený senzor plamene reaguje na plamen (zapalovač, svíčku).
 * Když hodnota překročí práh, rozsvítí se LED na pinu 13.
 * Hodnoty sleduj v sériovém monitoru (9600 Bd) a podle nich si
 * uprav konstantu „prah“.
 *
 * Zapojení:
 *   Senzor plamene (IR dioda): kratší nožička (katoda) na 5V,
 *   delší nožička (anoda) na A0
 *   Odpor 10 kΩ: mezi A0 a GND
 *   LED: vestavěná LED „L“ na pinu 13
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int plamenPin = A0;
const int ledPin = 13;
const int prah = 30;  // práh detekce, uprav podle sériového monitoru

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int hodnota = analogRead(plamenPin);
  Serial.println(hodnota);

  if (hodnota > prah) {
    digitalWrite(ledPin, HIGH);  // plamen detekován
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(200);
}
