/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 6: I2C LCD displej
 *
 * Na displeji postupně „přiběhnou“ zprava texty
 * „Laskarduino“ a „Zdravim bastlire!“.
 * Pokud displej nic neukazuje: otoč trimrem kontrastu na zadní straně
 * převodníku a ověř adresu skenerem z lekce 5.
 *
 * Zapojení:
 *   I2C LCD1602: GND–GND, VCC–5V
 *   UNO R3 / UNO R4 WiFi: SDA–A4, SCL–A5
 *   Mega 2560: SDA–20, SCL–21
 *
 * Knihovny: LiquidCrystal I2C (Frank de Brabander) – Správce knihoven
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Adresa displeje 0x27, 16 znaků, 2 řádky.
// Pokud skener (lekce 5) ukázal jinou adresu, např. 0x3F, přepiš ji zde.
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char text1[] = " Laskarduino              ";  // 26 znaků
const char text2[] = " Zdravim bastlire!        ";  // 26 znaků
const int delkaTextu = 26;
const int pauza = 500;  // rychlost posunu v ms

void setup() {
  lcd.init();       // inicializace displeje
  lcd.backlight();  // zapnout podsvícení
}

void loop() {
  bezText(text1, 0);  // první řádek
  bezText(text2, 1);  // druhý řádek
}

// Text „vjíždí“ zprava: znak vypíšeme a celý obsah posuneme doleva
void bezText(const char *text, int radek) {
  lcd.clear();
  lcd.setCursor(15, radek);
  for (int i = 0; i < delkaTextu; i++) {
    lcd.scrollDisplayLeft();
    lcd.print(text[i]);
    delay(pauza);
  }
}
