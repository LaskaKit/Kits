/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 30: RFID vstupní ochranný systém – zjištění ID karty
 *
 * 1. část lekce: přilož kartu nebo přívěsek ke čtečce a v sériovém
 * monitoru (9600 Bd) uvidíš jeho ID. ID si opiš – v programu
 * RFID_pristupovy_system ho pak zadáš jako povolený klíč.
 *
 * Zapojení:
 *   RFID RC522: 3.3V–3,3V (NE 5V!), GND–GND, RST–9, SDA (SS)–10, IRQ nezapojuj
 *   UNO R3 / UNO R4 WiFi: MOSI–11, MISO–12, SCK–13
 *   Mega 2560: MOSI–51, MISO–50, SCK–52
 *
 * Knihovny: MFRC522 (GithubCommunity) – Správce knihoven
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <SPI.h>
#include <MFRC522.h>

const int ssPin = 10;   // SDA (SS)
const int rstPin = 9;   // RST
MFRC522 ctecka(ssPin, rstPin);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  ctecka.PCD_Init();
  Serial.println("Priloz kartu nebo privesek ke ctecce...");
}

void loop() {
  // čekáme na novou kartu a přečteme její sériové číslo
  if (!ctecka.PICC_IsNewCardPresent() || !ctecka.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Typ: ");
  Serial.println(ctecka.PICC_GetTypeName(ctecka.PICC_GetType(ctecka.uid.sak)));

  Serial.print("ID karty: ");
  for (byte i = 0; i < ctecka.uid.size; i++) {
    if (ctecka.uid.uidByte[i] < 0x10) Serial.print("0");
    Serial.print(ctecka.uid.uidByte[i], HEX);
    Serial.print(i < ctecka.uid.size - 1 ? " " : "");
  }
  Serial.println();

  Serial.print("Pro program pristupoveho systemu: {");
  for (byte i = 0; i < 4; i++) {
    Serial.print("0x");
    if (ctecka.uid.uidByte[i] < 0x10) Serial.print("0");
    Serial.print(ctecka.uid.uidByte[i], HEX);
    if (i < 3) Serial.print(", ");
  }
  Serial.println("}");
  Serial.println();

  ctecka.PICC_HaltA();  // uspat kartu, aby se nečetla pořád dokola
  delay(500);
}
