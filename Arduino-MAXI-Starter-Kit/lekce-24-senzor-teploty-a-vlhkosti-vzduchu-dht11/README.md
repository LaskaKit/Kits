# Lekce 24: Senzor teploty a vlhkosti vzduchu DHT11

## Úvod

DHT11 je senzor, který obsahuje rezistivní čidlo vlhkosti, NTC teplotní senzor a 8bitový převodník. Právě díky převodníku jsme schopni ze senzoru dostat hotová digitální data místo surového analogového výstupu, který jsme museli zpracovávat např. v lekci 11. 

## Komponenty

- Arduino
- USB kabel
- Teplotní modul DHT11
- LCD displej
- Breadboard vodiče

<p align="center"><img src="img/obr-01.png" width="31%" alt=""></p>

<p align="center"><img src="img/obr-02.png" width="37%" alt=""></p>

## Princip

Čidlo má pouze 3 piny: VCC, GND a DATA. Komunikace začíná posláním startovacího signálu do DHT11, který signál přijme a vrátí odpověď. Hostitel (Arduino) poté začne přijímat 40bitový balíček dat (16 bitů pro vlhkost (8 pro celá čísla a 8 pro desetinná) + 16 bitů pro teplotu (8 pro celá čísla a 8 pro desetinná) + 8 bitů pro kontrolu správnosti dat).

## Postup projektu

| I2C LCD1602 | Arduino |
|---|---|
| GND | GND |
| VCC | 5V |
| SDA | A4 (Mega: 20) |
| SCL | A5 (Mega: 21) |

**Krok 1:** Vytvoř obvod

| DHT11 modul | Arduino |
|---|---|
| - | GND |
| + | 5V |
| S | 4 |

<p align="center"><img src="img/obr-03.png" width="66%" alt=""></p>

**Krok 2:** Napiš kód do Arduino IDE

> **Poznámka:** Potřebuješ knihovny DHT sensor library (Adafruit) a LiquidCrystal I2C – viz kapitola Instalace knihoven.

**Kód** – soubor `Senzor_teploty_a_vlhkosti_DHT11.ino`:

<!-- kod: Senzor_teploty_a_vlhkosti_DHT11/Senzor_teploty_a_vlhkosti_DHT11.ino -->
```cpp
/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 24: Senzor teploty a vlhkosti vzduchu DHT11
 *
 * Čidlo DHT11 měří teplotu a relativní vlhkost vzduchu.
 * Hodnoty se zobrazují na displeji I2C LCD1602 a v sériovém monitoru.
 * DHT11 je pomalé čidlo – nová hodnota je k dispozici zhruba každé 2 s.
 *
 * Zapojení:
 *   DHT11 modul: – na GND, + na 5V, S na pin 4
 *   I2C LCD1602: GND–GND, VCC–5V, SDA/SCL podle lekce 6
 *
 * Knihovny: DHT sensor library (Adafruit) + Adafruit Unified Sensor, LiquidCrystal I2C – Správce knihoven
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

const int dhtPin = 4;
DHT dht(dhtPin, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("DHT11 start...");
  delay(2000);  // čidlo potřebuje chvíli po zapnutí
  lcd.clear();
}

void loop() {
  float vlhkost = dht.readHumidity();
  float teplota = dht.readTemperature();  // ve °C

  if (isnan(vlhkost) || isnan(teplota)) {
    // čtení se nepovedlo – nejčastěji špatně zapojený pin S
    lcd.setCursor(0, 0);
    lcd.print("Chyba cteni DHT ");
    lcd.setCursor(0, 1);
    lcd.print("Zkontroluj pin 4");
    Serial.println("Chyba cteni z DHT11");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Teplota: ");
    lcd.print(teplota, 1);
    lcd.print((char)223);
    lcd.print("C ");
    lcd.setCursor(0, 1);
    lcd.print("Vlhkost: ");
    lcd.print(vlhkost, 0);
    lcd.print(" %   ");

    Serial.print("Teplota: ");
    Serial.print(teplota, 1);
    Serial.print(" C, vlhkost: ");
    Serial.print(vlhkost, 0);
    Serial.println(" %");
  }
  delay(2000);
}
```
<!-- /kod -->

**Krok 3:** Připoj desku k počítači

**Krok 4:** Vyber desku a port

**Krok 5:** Zkompiluj a nahraj sketch do Arduina (Ctrl+U)

Teď uvidíš aktuální vlhkost a teplotu na displeji.
