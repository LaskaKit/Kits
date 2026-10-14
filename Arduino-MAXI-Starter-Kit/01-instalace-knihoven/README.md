# Instalace knihoven

Některé lekce potřebují knihovny, které nejsou přímo součástí Arduino IDE. Všechny se instalují stejně, přes Správce knihoven:

- V Arduino IDE klikni v levém panelu na ikonu knih (Správce knihoven), případně zvol Nástroje > Spravovat knihovny…
- Do vyhledávání napiš název knihovny z tabulky níže.
- U správné knihovny (zkontroluj autora) klikni na Instalovat. Když se IDE zeptá na instalaci závislostí, zvol Instalovat vše.

| Knihovna (název ve Správci) | Autor | Lekce |
|---|---|---|
| LiquidCrystal I2C | Frank de Brabander | 6, 14, 16, 17, 23, 24, 30, 31 |
| Rtc by Makuna | Michael C. Miller | 23 |
| DHT sensor library | Adafruit | 24 |
| Adafruit Unified Sensor | Adafruit | 24 (IDE ji nabídne samo) |
| IRremote | shirriff, z3t0, ArminJo | 29 |
| MFRC522 | GithubCommunity | 30 |
| Keypad | Mark Stanley, Alexander Brevig | 31 |
| Servo, Stepper | Arduino | 26, 27 (součást IDE) |

Hotové programy ke všem lekcím najdeš v souboru „LaskaKit MAXI kody“ v Souvisejících souborech u produktu na laskakit.cz. Archiv rozbal a program otevři přes Soubor > Otevřít.

> **Poznámka:** Na UNO R4 WiFi vypíše IDE u knihovny LiquidCrystal I2C oranžové upozornění, že je určená pro architekturu AVR. Upozornění můžeš ignorovat, knihovna funguje.

> **Poznámka:** Pokud máš ze starší verze návodu ve složce Arduino/libraries nakopírované knihovny (IRremote, DS1302RTC, RFID, TimerOne…), smaž je. Staré verze by se pletly s novými.
