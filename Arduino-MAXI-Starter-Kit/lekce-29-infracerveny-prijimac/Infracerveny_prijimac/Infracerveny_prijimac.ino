/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 29: Infračervený přijímač
 *
 * Přijímač HX1838 čte kódy z dálkového ovladače a vypisuje je do
 * sériového monitoru (9600 Bd). Tlačítko „Play/Pause“ (►||) rozsvítí
 * LED na pinu 13, jakékoli jiné tlačítko ji zhasne.
 * Kódy dalších tlačítek zjistíš v sériovém monitoru.
 *
 * Zapojení:
 *   IR přijímač: S–2, – na GND, + na 5V
 *   LED: vestavěná LED „L“ na pinu 13
 *
 * Knihovny: IRremote (Armin Joachimsmeyer) verze 4.x – Správce knihoven
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

#include <IRremote.hpp>

const int irPin = 2;
const int ledPin = 13;
const uint8_t KOD_PLAY = 0x43;  // tlačítko ►|| na ovladači ze stavebnice

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  IrReceiver.begin(irPin, DISABLE_LED_FEEDBACK);  // spustit příjem
  Serial.println("Mackej tlacitka na ovladaci...");
}

void loop() {
  if (IrReceiver.decode()) {
    // Opakovaný kód (tlačítko držíš) ignorujeme
    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
      uint8_t kod = IrReceiver.decodedIRData.command;

      Serial.print("Protokol: ");
      Serial.print(getProtocolString(IrReceiver.decodedIRData.protocol));
      Serial.print(", kod tlacitka: 0x");
      Serial.println(kod, HEX);

      if (kod == KOD_PLAY) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    }
    IrReceiver.resume();  // připravit se na další kód
  }
}
