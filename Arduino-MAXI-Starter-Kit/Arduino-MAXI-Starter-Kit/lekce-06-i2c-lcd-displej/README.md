# Lekce 6: I2C LCD displej

## Úvod

Jak jistě všichni víme, LCD a další obrazovky výrazně obohacují naší interakci s přístroji, avšak mají i jednu nevýhodu. Pokud jsou připojeny ke kontroleru, bude obsazeno několik IO portů, kterých je omezený počet. A právě z těchto důvodů byl vyvinut převodník se I2C sběrnicí pro 1602 a 2004 LCD displej, který daný problém vyřešil.

I²C (anglicky Inter-Integrated Circuit, čteme I-squared-C, nesprávně I-two-C) je multi-masterová počítačová sériová sběrnice vyvinutá firmou Philips, která je používána k připojování nízkorychlostních periferií k základní desce, mikrokontroléru, aj. Praktická identická sběrnice se skrývá i pod zkratkou TWI (Two Wire Interface - dvoudrátové rozhraní), kterou používá firma Atmel a další výrobci, namísto chráněné značky I2C. Modrý potenciometr na převodníky se používá k nastavení podsvícení. I²C používá pouze dva obousměrné kanály - datový kanál SDA a hodinový signál SCL s pull-up rezistory. Používá se napětí +5 V nebo +3,3 V, povoleny jsou však i systémy s jiným napětím.

<p align="center"><img src="img/obr-01.png" width="100%" alt=""></p>

## Komponenty

- Arduino
- LCD displej
- USB kabel
- Kabely Dupont samec-samice
## Princip

V tomto pokusu necháme I2C LCD1602 displej zobrazit “Laskarduino” a “Zdravim bastlire!" pomocí programování.

## Postup experimentu

**Krok 1:** Vytvoř obvod

Spojení I2C mezi LCD1602 a Arduino:

| I2C LCD1602 | UNO R3 / UNO R4 WiFi | Arduino Mega |
|---|---|---|
| GND | GND | GND |
| VCC | 5V | 5V |
| SDA | A4 | 20 |
| SCL | A5 | 21 |

Poznámka: Vedení I2C LCD1602 bude stejné ve všech následujících lekcích.

Na desce UNO R4 WiFi i UNO R3 můžeš místo A4/A5 použít také piny SDA a SCL vedle pinu AREF – jsou propojené. Na Arduino Mega se displej připojuje na piny 20 (SDA) a 21 (SCL), případně SDA/SCL vedle AREF.

<p align="center"><img src="img/obr-02.png" width="98%" alt=""></p>

**Krok 2:** Napiš kód do Arduino IDE

**Kód** – soubor `I2C_LCD_displej.ino`:

<!-- kod: I2C_LCD_displej/I2C_LCD_displej.ino -->
```cpp
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
```
<!-- /kod -->

**Krok 3:** Nainstaluj knihovnu LiquidCrystal I2C (autor Frank de Brabander) přes Správce knihoven – postup najdeš v kapitole Instalace knihoven na začátku návodu. Pak kód zkompiluj.

**Krok 4:** Nahraj sketch do Arduina

Nyní bys na svém displeji měl vidět „Laskarduino“ a „Zdravim bastlire!“.

**Pokud na displeji nic nevidíš, zkontroluj nastavení odporového trimru pro řízení kontrastu na převodníku. Může se stát, že je nastavený na minimum a tudíž na displeji není nic vidět.** Otáčením si nastav správný kontrsat, tak aby byl nápis na displeji co nejlépe čitelný.

<p align="center"><img src="img/obr-03.jpg" width="42%" alt=""></p>
