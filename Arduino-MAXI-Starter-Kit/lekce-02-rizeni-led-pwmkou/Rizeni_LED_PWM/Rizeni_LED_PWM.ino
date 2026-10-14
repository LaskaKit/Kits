/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 2: Řízení LED pomocí PWM
 *
 * „Dýchající“ LED – plynule se rozsvěcí a zase zhasíná.
 * Jas se řídí pulzně šířkovou modulací (PWM) funkcí analogWrite().
 *
 * Zapojení:
 *   LED (anoda, delší nožička) přes odpor 220 Ω na pin 9
 *   LED (katoda, kratší nožička) na GND
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int ledPin = 9;  // pin s podporou PWM (na desce označený ~)

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Rozsvěcování: jas od 0 do 255
  for (int jas = 0; jas <= 255; jas++) {
    analogWrite(ledPin, jas);
    delay(8);
  }
  // Zhasínání: jas od 255 do 0
  for (int jas = 255; jas >= 0; jas--) {
    analogWrite(ledPin, jas);
    delay(8);
  }
  delay(800);  // krátká pauza mezi „nádechy“
}
