/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 9: Kvízový bzučák
 *
 * Tlačítkem 4 moderátor spustí kolo (rozsvítí se LED 4).
 * Kdo z hráčů 1–3 stiskne tlačítko jako první, tomu se rozsvítí LED
 * a zazní bzučák. Ostatní tlačítka se ignorují, dokud moderátor
 * znovu nestiskne tlačítko 4.
 *
 * Zapojení:
 *   Tlačítka 1, 2, 3, 4: piny 2, 3, 4, 9 – druhý vývod tlačítek na GND
 *   LED 1, 2, 3, 4: přes rezistor 220 Ω na piny 6, 7, 8, 10, katody na GND
 *   Aktivní bzučák: + na pin 5, – na GND
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int tlacitka[] = {2, 3, 4};  // tlačítka hráčů 1–3
const int ledky[]    = {6, 7, 8};  // LED hráčů 1–3
const int tlacitkoModerator = 9;   // tlačítko 4
const int ledModerator = 10;       // LED 4
const int bzucakPin = 5;

bool koloBezi = false;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(tlacitka[i], INPUT_PULLUP);  // stisk = LOW
    pinMode(ledky[i], OUTPUT);
  }
  pinMode(tlacitkoModerator, INPUT_PULLUP);
  pinMode(ledModerator, OUTPUT);
  pinMode(bzucakPin, OUTPUT);
  zhasniVse();
}

void loop() {
  // Moderátor spouští nové kolo
  if (digitalRead(tlacitkoModerator) == LOW) {
    zhasniVse();
    digitalWrite(ledModerator, HIGH);
    koloBezi = true;
    delay(200);
  }

  if (koloBezi) {
    for (int i = 0; i < 3; i++) {
      if (digitalRead(tlacitka[i]) == LOW) {  // tento hráč byl první
        koloBezi = false;
        digitalWrite(ledModerator, LOW);
        digitalWrite(ledky[i], HIGH);
        pipni();
        break;
      }
    }
  }
}

void zhasniVse() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledky[i], LOW);
  }
  digitalWrite(ledModerator, LOW);
}

void pipni() {
  digitalWrite(bzucakPin, HIGH);
  delay(600);
  digitalWrite(bzucakPin, LOW);
}
