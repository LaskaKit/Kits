/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 19: Stopky – 4místný sedmisegmentový displej
 *
 * Na 4místném displeji běží čítač, který se každou sekundu zvýší o 1
 * (0000 až 9999). Číslice se rozsvěcí rychle po sobě (multiplex),
 * oko je proto vidí všechny najednou.
 * Program nepotřebuje žádnou knihovnu – čas měří funkcí millis(),
 * takže funguje na UNO R3, UNO R4 WiFi i Mega.
 * Podle typu displeje nastav řádek SPOLECNA_ANODA.
 *
 * Zapojení:
 *   Segmenty přes odpor 220 Ω: a–2, b–3, c–4, d–5, e–6, f–7, g–8, p–9
 *   Číslice: D1–10, D2–11, D3–12, D4–13 (D1 je číslice úplně vlevo)
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

// true = displej se společnou anodou (CA), false = se společnou katodou (CC)
const bool SPOLECNA_ANODA = true;

const int segmentPiny[7] = {2, 3, 4, 5, 6, 7, 8};  // a, b, c, d, e, f, g
const int teckaPin = 9;
const int cislicePiny[4] = {10, 11, 12, 13};       // D1, D2, D3, D4

const byte vzory[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 1, 1}   // 9
};

int cislo = 0;                   // zobrazovaná hodnota 0–9999
unsigned long posledniZmena = 0;

void setup() {
  for (int i = 0; i < 7; i++) pinMode(segmentPiny[i], OUTPUT);
  pinMode(teckaPin, OUTPUT);
  for (int i = 0; i < 4; i++) pinMode(cislicePiny[i], OUTPUT);
  zhasniVse();
}

void loop() {
  // každou sekundu přičíst 1
  if (millis() - posledniZmena >= 1000) {
    posledniZmena += 1000;
    cislo++;
    if (cislo > 9999) cislo = 0;
  }

  // rozložit číslo na tisíce, stovky, desítky a jednotky
  int rad[4] = {cislo / 1000, (cislo / 100) % 10, (cislo / 10) % 10, cislo % 10};

  // multiplex: každou číslici rozsvítit na 4 ms
  for (int pozice = 0; pozice < 4; pozice++) {
    zhasniVse();
    nastavSegmenty(rad[pozice]);
    zapniCislici(pozice);
    delay(4);
  }
}

void nastavSegmenty(int hodnota) {
  for (int i = 0; i < 7; i++) {
    bool sviti = vzory[hodnota][i];
    // u CA svítí segment při LOW, u CC při HIGH
    digitalWrite(segmentPiny[i], (sviti != SPOLECNA_ANODA) ? HIGH : LOW);
  }
}

void zapniCislici(int pozice) {
  // u CA se číslice zapíná HIGH (anoda), u CC LOW (katoda)
  digitalWrite(cislicePiny[pozice], SPOLECNA_ANODA ? HIGH : LOW);
}

void zhasniVse() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(cislicePiny[i], SPOLECNA_ANODA ? LOW : HIGH);
  }
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPiny[i], SPOLECNA_ANODA ? HIGH : LOW);
  }
  digitalWrite(teckaPin, SPOLECNA_ANODA ? HIGH : LOW);
}
