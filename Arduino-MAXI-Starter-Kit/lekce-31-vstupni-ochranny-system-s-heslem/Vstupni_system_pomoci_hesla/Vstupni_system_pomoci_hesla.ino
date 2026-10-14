/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 31: Vstupní ochranný systém s heslem
 *
 * Stiskni „*“, zadej šestimístné heslo (výchozí 123456) a potvrď „#“.
 * Při správném hesle se na displeji ukáže „Spravne!“ a na 2 s sepne
 * relé. Při chybném hesle se ukáže „Chyba!“.
 * Klávesy jsou v programu očíslované po řádcích (1 2 3 4 / 5 6 7 8 /
 * 9 A B C / D * 0 #), když máš klávesnici vývody nahoru.
 *
 * Zapojení:
 *   Klávesnice 4×4: řádky R1–11, R2–10, R3–9, R4–8,
 *   sloupce C1–7, C2–6, C3–5, C4–4
 *   Modul relé: S–13, +–5V, ––GND
 *   I2C LCD1602: GND–GND, VCC–5V, SDA/SCL podle lekce 6
 *
 * Knihovny: Keypad (Mark Stanley, Alexander Brevig), LiquidCrystal I2C – Správce knihoven
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int relePin = 13;
const int RELE_ZAPNUTO = HIGH;  // u modulů spínaných nulou změň na LOW

const byte RADKY = 4;
const byte SLOUPCE = 4;
char klavesy[RADKY][SLOUPCE] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'A', 'B', 'C'},
  {'D', '*', '0', '#'}
};
byte radkyPiny[RADKY] = {11, 10, 9, 8};
byte sloupcePiny[SLOUPCE] = {7, 6, 5, 4};
Keypad klavesnice = Keypad(makeKeymap(klavesy), radkyPiny, sloupcePiny, RADKY, SLOUPCE);

const char heslo[] = "123456";      // tajné heslo
const byte delkaHesla = sizeof(heslo) - 1;
char zadano[delkaHesla + 1];
byte pozice = 0;
bool zadavani = false;

void setup() {
  pinMode(relePin, OUTPUT);
  digitalWrite(relePin, !RELE_ZAPNUTO);
  lcd.init();
  lcd.backlight();
  zobrazVitej();
}

void loop() {
  char klavesa = klavesnice.getKey();
  if (!klavesa) return;  // nic nestisknuto

  if (klavesa == '*') {                 // začátek zadávání
    pozice = 0;
    zadavani = true;
    lcd.clear();
    lcd.print("Zadej heslo:");
    lcd.setCursor(0, 1);
  } else if (klavesa == '#') {          // potvrzení
    if (zadavani) over();
  } else if (zadavani && pozice < delkaHesla) {
    zadano[pozice] = klavesa;
    pozice++;
    lcd.print('*');                     // heslo na displeji schovat
  }
}

void over() {
  zadano[pozice] = '\0';
  zadavani = false;
  lcd.clear();
  if (pozice == delkaHesla && strcmp(zadano, heslo) == 0) {
    lcd.print("    Spravne!    ");
    lcd.setCursor(0, 1);
    lcd.print("     Vstup      ");
    digitalWrite(relePin, RELE_ZAPNUTO);
    delay(2000);
    digitalWrite(relePin, !RELE_ZAPNUTO);
  } else {
    lcd.print("     Chyba!     ");
    lcd.setCursor(0, 1);
    lcd.print(" Zkus to znovu  ");
    delay(2000);
  }
  zobrazVitej();
}

void zobrazVitej() {
  lcd.clear();
  lcd.print("     Vitej!     ");
  lcd.setCursor(0, 1);
  lcd.print("Stiskni *");
}
