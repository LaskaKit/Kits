# Lekce 21: RGB LED

## Úvod

RGB LED jsou svítivé diody, které obsahují 3 základní barvy na jednom komponentu. Tyto barvy jsou červená, zelená a modrá. Diody bývají zalité v průhledném nebo poloprůhledném plastovém pouzdře se čtyřmi vývody. Pokud si pamatuješ výuku z prvního stupně, tak určitě víš, že z červené, zelené a modré lze míchat a vytvářet všechny druhy barev pomocí aditivního míchání, takže si můžeš udělat RGB LED vyzařující barevné světlo. Stejný způsob míchání barev využívají víceméně všechny plnobarevné monitory, televize a obrazovky na světě.

## Komponenty

- Arduino
- USB kabel
- RGB LED modul
- Breadboard vodiče

<p align="center"><img src="img/obr-01.png" width="37%" alt=""></p>

## Princip

V tomto experimentu budeme používat technologii PWM pro ovládání jasu RGB LED. Už jsme to popsali v lekci 2 tohoto kitu. Pokud si potřebuješ osvěžit paměť, klidně si tu lekci projdi ještě jednou.

Každý ze tří kanálů má 256 stupňů jasu (0–255). Pokud jsou všechny tři základní barvy na 0, LED zhasne. Pokud jsou všechny 255, LED bude svítit nejjasnější možnou bílou. Různé barvy pak namícháme tak, že do kolíků pustíme hodnoty mezi 0 a 255.

RGB LED se dělí na dva typy: se společnou anodou a se společnou katodou. V tomto experimentu budeme používat RGB LED se společnou katodou.

## Postup experimentu

**Krok 1:** Vytvoř obvod

<p align="center"><img src="img/obr-02.png" width="56%" alt=""></p>

| RGB LED modul | Arduino |
|---|---|
| R | 11 |
| G | 10 |
| B | 9 |
| - | GND |

**Krok 2:** Napiš kód do Arduino IDE

**Kód** – soubor `RGB_LED.ino`:

<!-- kod: RGB_LED/RGB_LED.ino -->
```cpp
/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 21: RGB LED
 *
 * RGB LED postupně svítí červeně, zeleně a modře a pak míchá další
 * barvy – oranžovou, žlutou, indigo a fialovou. Jas každé složky
 * se řídí přes PWM.
 *
 * Zapojení:
 *   RGB LED modul: R–11, G–10, B–9, – na GND
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int cervenaPin = 11;
const int zelenaPin = 10;
const int modraPin = 9;

void setup() {
  pinMode(cervenaPin, OUTPUT);
  pinMode(zelenaPin, OUTPUT);
  pinMode(modraPin, OUTPUT);
}

void loop() {
  barva(255, 0, 0);     // červená
  delay(1000);
  barva(0, 255, 0);     // zelená
  delay(1000);
  barva(0, 0, 255);     // modrá
  delay(1000);
  barva(237, 109, 0);   // oranžová
  delay(1000);
  barva(255, 215, 0);   // žlutá
  delay(1000);
  barva(0, 46, 90);     // indigo
  delay(1000);
  barva(128, 0, 128);   // fialová
  delay(1000);
  barva(0, 0, 0);       // zhasnuto
  delay(500);
}

// nastaví jas jednotlivých složek 0–255
void barva(int r, int g, int b) {
  analogWrite(cervenaPin, r);
  analogWrite(zelenaPin, g);
  analogWrite(modraPin, b);
}
```
<!-- /kod -->

**Krok 3:** Připoj desku k počítači

**Krok 4:** Vyber desku a port

**Krok 5:** Zkompiluj a nahraj sketch do Arduina (Ctrl+U)

Nyní můžeš vidět, že RGB LED bliká červeně, zeleně, modře, oranžově, žlutě, fialově a barvou indigo.
