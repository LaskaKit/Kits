# Lekce 26: Krokový motor

## Úvod

Krokové motory, díky své jedinečné konstrukci, mohou být ovládány s vysokou přesností a bez jakýchkoli mechanismů zpětné vazby. Na hřídeli krokového motoru je namontována série magnetů, řízená pomocí elektromagnetických cívek, které jsou buzeny elektrickými impulzy. Díky tomuto mechanickému zpracování se krokové motory dokážou přesně otáčet dopředu a dozadu v malých „krocích“. Dokonce se dokážou otočit i o půlkrok nebo čtvrtkrok.

Existují dva typy krokových motorů – unipolární a bipolární. Je velmi důležité vědět, s jakým typem pracuješ. V tomto experimentu použijeme unipolární krokový motor.

Arduino desky nebo kontrolery nemohou přímo řídit krokové motory. Je tedy nezbytný řadič krokového motoru (jako je ukázáno na následujícím obrázku).

## Komponenty

- Arduino
- USB kabel
- Potenciometr
- Krokový motor
- Řadič krokového motoru
- Breadboard vodiče
- Breadboard

<p align="center"><img src="img/obr-01.jpg" width="29%" alt=""></p>

<p align="center"><img src="img/obr-02.png" width="26%" alt=""></p>

## Princip

Uvnitř krokového motoru je otočný magnet (rotor) a kolem něj čtyři cívky, zde fungující jako elektromagnety. Když pustíš proud do jedné cívky, přitáhne si magnet k sobě a rotor se k ní natočí. Když pak proud přepneš do sousední cívky, rotor se posune o kousek dál. Tomuto posunu se říká krok.

<p align="center"><img src="img/obr-03.png" width="47%" alt=""></p>

Když cívky zapínáš jednu po druhé ve správném pořadí (A, B, C, D, A…), rotor se otáčí krok za krokem. Opačné pořadí ho roztočí na druhou stranu a rychlost přepínání určuje rychlost otáčení. Motor udělá přesně tolik kroků, kolik mu pošleš, takže vždy víš, kde je jeho hřídel, a to bez jakéhokoli čidla (na rozdíl od serv).

Motor 28BYJ-48 ze stavebnice má navíc převodovku, takže jedna otáčka hřídele odpovídá 2048 krokům. Díky tomu se dá natáčet velmi jemně, ale otáčí se pomalu (nejvýš asi 15 otáček za minutu).

Cívky potřebují větší proud, než dokáže dát pin Arduina. Proto je mezi Arduinem a motorem řadič ULN2003: Arduino mu jen říká, kterou cívku zapnout, a řadič ji sepne. Kontrolky na řadiči ukazují, která cívka je právě zapnutá. Pořadí přepínání cívek za tebe řeší knihovna Stepper, takže v programu stačí říct, o kolik kroků se má motor otočit.

## Postup projektu

**Krok 1:** Vytvoř obvod

Zapojení mezi řadičem krokového motoru a Arduinem:

<p align="center"><img src="img/obr-04.png" width="65%" alt=""></p>

| Řadič ULN2003 | Arduino |
|---|---|
| IN1 | 8 |
| IN2 | 9 |
| IN3 | 10 |
| IN4 | 11 |
| GND | GND |
| VCC | 5V |

**Krok 2:** Napiš kód do Arduino IDE

> **Poznámka:** Knihovna Stepper je součástí Arduino IDE. V programu jsou piny v pořadí 8, 10, 9, 11 – to není chyba, motor 28BYJ-48 je tak potřebuje, jinak se jen chvěje na místě.

**Kód** – soubor `Krokovy_motor.ino`:

<!-- kod: Krokovy_motor/Krokovy_motor.ino -->
```cpp
/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 26: Krokový motor
 *
 * Hřídel krokového motoru 28BYJ-48 sleduje natočení potenciometru:
 * celý rozsah potenciometru odpovídá jedné otáčce hřídele.
 * Motor má s převodovkou 2048 kroků na otáčku. Knihovna Stepper
 * potřebuje u řadiče ULN2003 piny v pořadí IN1, IN3, IN2, IN4.
 *
 * Zapojení:
 *   Řadič ULN2003: IN1–8, IN2–9, IN3–10, IN4–11, – na GND, + na 5V
 *   Motor: bílý konektor do řadiče
 *   Potenciometr: krajní vývody na 5V a GND, prostřední na A0
 *
 * Knihovny: Stepper (součást Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <Stepper.h>

const int krokuNaOtacku = 2048;  // 28BYJ-48 s převodovkou

// Pořadí pinů 8, 10, 9, 11 (IN1, IN3, IN2, IN4) je pro 28BYJ-48 nutné,
// jinak motor jen cuká na místě.
Stepper motor(krokuNaOtacku, 8, 10, 9, 11);

const int potPin = A0;
int predchoziPoloha = 0;

void setup() {
  motor.setSpeed(10);  // otáčky za minutu (28BYJ-48 zvládne max. cca 15)
  predchoziPoloha = map(analogRead(potPin), 0, 1023, 0, krokuNaOtacku);
}

void loop() {
  // poloha potenciometru převedená na kroky motoru
  int poloha = map(analogRead(potPin), 0, 1023, 0, krokuNaOtacku);
  int rozdil = poloha - predchoziPoloha;

  // malé změny ignorujeme, aby motor necukal kvůli šumu
  if (abs(rozdil) > 8) {
    motor.step(rozdil);
    predchoziPoloha = poloha;
  }
}
```
<!-- /kod -->

**Krok 3:** Připoj desku k počítači

**Krok 4:** Vyber desku a port

**Krok 5:** Zkompiluj a nahraj sketch do Arduina (Ctrl+U)

Nyní otáčej potenciometrem a hřídel motoru ho bude následovat – celý rozsah potenciometru odpovídá jedné otáčce hřídele.

<p align="center"><img src="img/obr-05.jpg" width="67%" alt=""></p>
