/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 27: Servo
 *
 * Servo se pomalu otáčí z 0° do 180° a zpět.
 *
 * Zapojení:
 *   Servo: hnědý vodič na GND, červený na 5V, oranžový (signál) na pin 9
 *
 * Knihovny: Servo (součást Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <Servo.h>

Servo servo;
const int servoPin = 9;

void setup() {
  servo.attach(servoPin);
}

void loop() {
  for (int uhel = 0; uhel <= 180; uhel++) {  // tam
    servo.write(uhel);
    delay(15);  // počkat, než servo dojede
  }
  for (int uhel = 180; uhel >= 0; uhel--) {  // a zpět
    servo.write(uhel);
    delay(15);
  }
}
