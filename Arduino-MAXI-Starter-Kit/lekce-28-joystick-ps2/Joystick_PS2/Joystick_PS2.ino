/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 28: Joystick PS2
 *
 * V sériovém monitoru (9600 Bd) vidíš polohu joysticku v osách X a Y
 * (0–1023, ve středu kolem 512) a stav tlačítka Z (0 = stisknuto).
 *
 * Zapojení:
 *   Joystick: GND–GND, +5V–5V, VRx–A0, VRy–A1, SW–8
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int xPin = A0;
const int yPin = A1;
const int tlacitkoPin = 8;

void setup() {
  pinMode(tlacitkoPin, INPUT_PULLUP);  // tlačítko spíná na GND
  Serial.begin(9600);
}

void loop() {
  Serial.print("X: ");
  Serial.print(analogRead(xPin));
  Serial.print(" | Y: ");
  Serial.print(analogRead(yPin));
  Serial.print(" | Z: ");
  Serial.println(digitalRead(tlacitkoPin));
  delay(200);
}
