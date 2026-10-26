/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 22: Řízení sedmisegmentového displeje s 74HC595
 *
 * Posuvný registr 74HC595 ovládá všech 8 segmentů displeje pomocí
 * pouhých 3 pinů Arduina. Na displeji se postupně zobrazí znaky 0 až F.
 * Podle typu displeje nastav řádek SPOLECNA_ANODA.
 *
 * Zapojení:
 *   74HC595: DS (14)–11, SH_CP (11)–8, ST_CP (12)–12,
 *   VCC (16) a MR (10) na 5V, GND (8) a OE (13) na GND
 *   Výstupy Q0–Q7 přes rezistor 220 Ω na segmenty podle schématu v návodu
 *   Společný vývod displeje: CC na GND, CA na 5V
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

// false = společná katoda (CC), true = společná anoda (CA)
const bool SPOLECNA_ANODA = false;

const int latchPin = 12;  // ST_CP
const int clockPin = 8;   // SH_CP
const int dataPin = 11;   // DS

// kódy znaků 0,1,2,3,4,5,6,7,8,9,A,b,C,d,E,F pro zapojení podle schématu
const byte znaky[16] = {250, 96, 220, 244, 102, 182, 190, 224,
                        254, 246, 238, 62, 154, 124, 158, 142};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 16; i++) {
    byte data = znaky[i];
    if (SPOLECNA_ANODA) {
      data = ~data;  // u CA displeje svítí segment při LOW -> bity obrátit
    }
    digitalWrite(latchPin, LOW);                     // začátek zápisu
    shiftOut(dataPin, clockPin, MSBFIRST, data);     // poslat 8 bitů
    digitalWrite(latchPin, HIGH);                    // přenést na výstupy
    delay(1000);
  }
}
