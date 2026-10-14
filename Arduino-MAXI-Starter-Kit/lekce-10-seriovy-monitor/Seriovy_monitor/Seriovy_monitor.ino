/*
 * LaskaKit Arduino MAXI Starter kit – Lekce 10: Sériový monitor
 *
 * Do sériového monitoru napiš barvu a stiskni Enter:
 * „cervena“, „zluta“ nebo „modra“ – rozsvítí se příslušná LED.
 * Jiný text všechny LED zhasne.
 * Funguje s jakýmkoli nastavením konce řádku v sériovém monitoru.
 *
 * Zapojení:
 *   Modrá LED přes odpor 220 Ω na pin 2
 *   Žlutá LED přes odpor 220 Ω na pin 3
 *   Červená LED přes odpor 220 Ω na pin 4
 *   Katody všech LED na GND
 *
 * Knihovny: žádné (jen Arduino IDE)
 * Desky:    Arduino UNO R3, Arduino UNO R4 WiFi, Arduino Mega 2560
 *
 * Verze návodu 3.0 (10/2026)
 * LaskaKit | https://www.laskakit.cz | podpora@laskakit.cz
 */

const int modraPin = 2;
const int zlutaPin = 3;
const int cervenaPin = 4;

void setup() {
  pinMode(modraPin, OUTPUT);
  pinMode(zlutaPin, OUTPUT);
  pinMode(cervenaPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Napis barvu LED (cervena, zluta, modra) a stiskni Enter:");
}

void loop() {
  if (Serial.available() > 0) {
    // přečíst celý řádek a odstranit mezery a znaky konce řádku
    String prikaz = Serial.readStringUntil('\n');
    prikaz.trim();
    prikaz.toLowerCase();
    Serial.print("Prijato: ");
    Serial.println(prikaz);

    // nejdřív všechny LED zhasnout, pak rozsvítit tu správnou
    digitalWrite(modraPin, LOW);
    digitalWrite(zlutaPin, LOW);
    digitalWrite(cervenaPin, LOW);

    if (prikaz == "cervena") {
      digitalWrite(cervenaPin, HIGH);
    } else if (prikaz == "zluta") {
      digitalWrite(zlutaPin, HIGH);
    } else if (prikaz == "modra") {
      digitalWrite(modraPin, HIGH);
    } else {
      Serial.println("Neznama barva - vsechny LED zhasnuty.");
    }
  }
}
