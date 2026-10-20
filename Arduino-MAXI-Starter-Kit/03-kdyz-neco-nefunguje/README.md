# Když něco nefunguje

- Chyba „No such file or directory“ u řádku #include – chybí knihovna, nainstaluj ji podle kapitoly Instalace knihoven.
- Nahrávání selže – zkontroluj vybranou desku a port a zavři jiné programy (internetový prohlížeč, jiná ArduinoIDE okna,...), které mohou port používat.
- LCD svítí, ale nic neukazuje – otoč trimrem kontrastu na zadní straně a skenerem z lekce 5 ověř adresu displeje (obvykle 0x27, někdy 0x3F).
- Sériový monitor ukazuje nesmyslné znaky – nastav rychlost 9600 baud.
- Sériový monitor nic nezobrazuje u Arduino UNO R4 – přidej `delay(100);` po `Serial.begin(9600)`
- Obvod zapojuj vždy bez napájení. USB kabel připoj, až když je vše zapojené.
- Pořád nic? Napiš nám na podpora@laskakit.cz – pošli fotku zapojení a text chyby.
