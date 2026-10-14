/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 26: Krokový motor
 *
 * Hřídel krokového motoru 28BYJ-48 sleduje natočení potenciometru:
 * celý rozsah potenciometru odpovídá jedné otáčce hřídele.
 * Motor má s převodovkou 2048 kroků na otáčku. Knihovna Stepper
 * potřebuje u řadiče ULN2003 piny v pořadí IN1, IN3, IN2, IN4.
 *
 * Zapojení:
 *   Řadič ULN2003: IN1–8, IN2–9, IN3–10, IN4–11, – na GND, + na 5V
 *   Motor: bílý konektor do řadiče
 *   Potenciometr: krajní vývody na 5V a GND, prostřední na A0
 *
 * Knihovny: Stepper (součást Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <Stepper.h>

const int krokuNaOtacku = 2048;  // 28BYJ-48 s převodovkou

// Pořadí pinů 8, 10, 9, 11 (IN1, IN3, IN2, IN4) je pro 28BYJ-48 nutné,
// jinak motor jen cuká na místě.
Stepper motor(krokuNaOtacku, 8, 10, 9, 11);

const int potPin = A0;
int predchoziPoloha = 0;

void setup() {
  motor.setSpeed(10);  // otáčky za minutu (28BYJ-48 zvládne max. cca 15)
  predchoziPoloha = map(analogRead(potPin), 0, 1023, 0, krokuNaOtacku);
}

void loop() {
  // poloha potenciometru převedená na kroky motoru
  int poloha = map(analogRead(potPin), 0, 1023, 0, krokuNaOtacku);
  int rozdil = poloha - predchoziPoloha;

  // malé změny ignorujeme, aby motor necukal kvůli šumu
  if (abs(rozdil) > 8) {
    motor.step(rozdil);
    predchoziPoloha = poloha;
  }
}
