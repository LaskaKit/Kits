# Lekce 2: Řízení LED PWMkou

## Úvod

Pojďme zkusit v této lekci něco trochu jednoduššího – postupně budeme měnit jas LEDky pomocí kódů. Vzhledem k tomu, že pulzující světlo vypadá jako dýchání, dali jsme mu magické jméno – dýchající LEDka. Dosáhneme tohoto efektu pomocí pulzně šířkové modulace (PWM)

## Komponenty

- Arduino
- Breadboard
- Breadboard vodiče
- 1x LED
- Odpor (220Ω)
- USB kabel

<p align="center"><img src="img/obr-01.png" width="51%" alt=""></p>

## Princip

Pulzně šířková modulace neboli PWM (Pulse Width Modulation) je diskrétní modulace pro přenos analogového signálu pomocí dvouhodnotového signálu. Jako dvouhodnotová veličina může být použito např. napětí. Signál je přenášen pomocí střídy. Vzhledem ke svým vlastnostem je pulsně šířková modulace často využívána ve výkonové elektronice pro řízení velikosti napětí.

<p align="center"><img src="img/obr-02.png" width="61%" alt=""></p>

Přenosový signál, který nese informaci o přenášené hodnotě, může nabývat hodnot zapnuto/vypnuto tj. log.1/log.0 (5V a 0V v našem případě). Hodnota přenášeného signálu je v přenosu "zakódována" jako poměr mezi stavy zapnuto/vypnuto. Tomuto poměru se říká střída. Cyklu, kdy dojde k přenosu jedné střídy, se říká perioda. Omezením pro PWM je to, že přenos informace je vždy omezen na relativní vyjádření a to 0 - 100 %. To znamená, že musí být znám poměr mezi skutečnou hodnotou a procentuálním vyjádřením. Časové hodnoty střídy se pohybují v sekundách nebo v milisekundách pro přesnější řízení. Perioda je vždy součtem doby zapnuto a vypnuto.

Musíš zopakovat periodu dostatečně rychle s LED, aby nebylo vidět, že LEDka bliká, ale trvale svítí.

Z oscilogramu je patrné, že amplituda napětí výstupu je 5V. Skutečné výstupní napětí je pouze 3.75V pomocí PWM, protože 5V trvá pouze 75% střídy (duty cycle).

Tři základní parametry PWM:

- Střída (duty cycle) je poměr mezi stavy zapnuto/vypnuto.
- Perioda je součtem doby zapnuto a vypnuto.
- Amplituda napětí je zde 0V-5V.
## Postup experimentu

**Krok 1:** Vytvoř obvod

<p align="center"><img src="img/obr-03.png" width="27%" alt=""> <img src="img/obr-04.png" width="38%" alt=""></p>

**Krok 2:** Napiš kód do Arduino IDE

**Kód** – soubor `Rizeni_LED_PWM.ino`:

<!-- kod: Rizeni_LED_PWM/Rizeni_LED_PWM.ino -->
```cpp
/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 2: Řízení LED pomocí PWM
 *
 * „Dýchající“ LED – plynule se rozsvěcí a zase zhasíná.
 * Jas se řídí pulzně šířkovou modulací (PWM) funkcí analogWrite().
 *
 * Zapojení:
 *   LED (anoda, delší nožička) přes odpor 220 Ω na pin 9
 *   LED (katoda, kratší nožička) na GND
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int ledPin = 9;  // pin s podporou PWM (na desce označený ~)

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Rozsvěcování: jas od 0 do 255
  for (int jas = 0; jas <= 255; jas++) {
    analogWrite(ledPin, jas);
    delay(8);
  }
  // Zhasínání: jas od 255 do 0
  for (int jas = 255; jas >= 0; jas--) {
    analogWrite(ledPin, jas);
    delay(8);
  }
  delay(800);  // krátká pauza mezi „nádechy“
}
```
<!-- /kod -->

**Krok 3:** Zkompiluj kód

**Krok 4:** Nahraj sketch do Arduina

Tady bys měl vidět, jak se LEDka stává jasnější a tmavší, a tak pořád dokola.
