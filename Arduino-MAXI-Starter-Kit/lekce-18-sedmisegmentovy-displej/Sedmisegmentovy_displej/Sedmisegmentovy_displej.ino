/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 18: Sedmisegmentový displej
 *
 * Na jednomístném sedmisegmentovém displeji se postupně zobrazují
 * číslice 0 až 9.
 * Displej může mít společnou katodu (CC) nebo společnou anodu (CA) –
 * jak to zjistit, popisuje návod. Podle typu nastav řádek SPOLECNA_ANODA.
 *
 * Zapojení:
 *   Segmenty přes odpor 220 Ω: a–7, b–6, c–5, d–11, e–10, f–8, g–9, dp–4
 *   Společný vývod (prostřední pin): CC displej na GND, CA displej na 5V
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

// false = displej se společnou katodou (CC), true = se společnou anodou (CA)
const bool SPOLECNA_ANODA = false;

// piny segmentů v pořadí a, b, c, d, e, f, g
const int segmentPiny[7] = {7, 6, 5, 11, 10, 8, 9};
const int dpPin = 4;

// které segmenty svítí pro číslice 0–9 (pořadí a b c d e f g)
const byte cislice[10][7] = {
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

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPiny[i], OUTPUT);
  }
  pinMode(dpPin, OUTPUT);
  nastavSegment(dpPin, false);  // desetinnou tečku necháme zhasnutou
}

void loop() {
  for (int c = 0; c <= 9; c++) {
    zobraz(c);
    delay(1000);
  }
}

void zobraz(int c) {
  for (int i = 0; i < 7; i++) {
    nastavSegment(segmentPiny[i], cislice[c][i]);
  }
}

// U CA displeje segment svítí při LOW, u CC při HIGH
void nastavSegment(int pin, bool sviti) {
  if (SPOLECNA_ANODA) {
    digitalWrite(pin, sviti ? LOW : HIGH);
  } else {
    digitalWrite(pin, sviti ? HIGH : LOW);
  }
}
