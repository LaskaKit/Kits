/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 30: RFID vstupní ochranný systém
 *
 * 2. část lekce: po přiložení povolené karty se na displeji ukáže její
 * ID a pozdrav a na 2 s sepne relé (např. elektrický zámek).
 * Neznámá karta relé nesepne.
 * ID svých karet zjistíš programem RFID_zjisti_ID a zapíšeš je
 * do pole povoleneKarty níže.
 *
 * Zapojení:
 *   RFID RC522: 3.3V–3,3V (NE 5V!), GND–GND, RST–9, SDA (SS)–10, IRQ nezapojuj
 *   UNO R3 / UNO R4 WiFi: MOSI–11, MISO–12, SCK–13
 *   Mega 2560: MOSI–51, MISO–50, SCK–52
 *   Modul relé: S–8, +–5V, ––GND (viz lekce 25)
 *   I2C LCD1602: GND–GND, VCC–5V, SDA/SCL podle lekce 6
 *
 * Knihovny: MFRC522 (GithubCommunity), LiquidCrystal I2C – Správce knihoven
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int ssPin = 10;
const int rstPin = 9;
const int relePin = 8;
const int RELE_ZAPNUTO = HIGH;  // u modulů spínaných nulou změň na LOW

MFRC522 ctecka(ssPin, rstPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Sem zapiš ID svých karet (4 bajty z programu RFID_zjisti_ID)
const int pocetKaret = 2;
const byte povoleneKarty[pocetKaret][4] = {
  {0xD0, 0xE7, 0xC2, 0x80},  // karta 1
  {0x4B, 0xE6, 0xD1, 0x3B}   // karta 2 (přívěsek)
};
const char *pozdravy[pocetKaret] = {
  "Zdravim bastlire",
  "  Ahoj Kosto!   "
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  ctecka.PCD_Init();

  pinMode(relePin, OUTPUT);
  digitalWrite(relePin, !RELE_ZAPNUTO);  // relé vypnuté

  lcd.init();
  lcd.backlight();
  zobrazVitej();
}

void loop() {
  if (!ctecka.PICC_IsNewCardPresent() || !ctecka.PICC_ReadCardSerial()) {
    return;
  }

  // 1. řádek: ID karty
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ID: ");
  for (byte i = 0; i < 4; i++) {
    if (ctecka.uid.uidByte[i] < 0x10) lcd.print("0");
    lcd.print(ctecka.uid.uidByte[i], HEX);
  }

  // 2. řádek: pozdrav podle karty
  int karta = najdiKartu();
  lcd.setCursor(0, 1);
  if (karta >= 0) {
    lcd.print(pozdravy[karta]);
    digitalWrite(relePin, RELE_ZAPNUTO);   // otevřít
    delay(2000);
    digitalWrite(relePin, !RELE_ZAPNUTO);  // zavřít
  } else {
    lcd.print(" Ahoj cizince!  ");
    delay(2000);
  }

  ctecka.PICC_HaltA();
  zobrazVitej();
}

// vrátí pořadí povolené karty, nebo -1 pro neznámou kartu
int najdiKartu() {
  for (int k = 0; k < pocetKaret; k++) {
    bool shoda = true;
    for (byte i = 0; i < 4; i++) {
      if (ctecka.uid.uidByte[i] != povoleneKarty[k][i]) {
        shoda = false;
        break;
      }
    }
    if (shoda) return k;
  }
  return -1;
}

void zobrazVitej() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("     Vitej!     ");
  lcd.setCursor(0, 1);
  lcd.print(" Priloz kartu...");
}
