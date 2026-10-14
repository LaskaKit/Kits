# LaskaKit – stavebnice

<p align="center"><img src="_build/assets/logo.jpg" width="40%" alt="LaskaKit"></p>

Návody a programy ke stavebnicím [LaskaKit](https://www.laskakit.cz). Hotové PDF návody najdeš u produktu na e-shopu v Souvisejících souborech nebo v sekci [Releases](../../releases).

## Stavebnice

| Stavebnice | Verze návodu | Desky |
|---|---|---|
| [LaskaKit Arduino MAXI Starter kit](Arduino-MAXI-Starter-Kit/README.md) | 3.0 (říjen 2026) | Pro Arduino UNO R3, UNO R4 WiFi a Mega 2560 |

## Jak je repozitář uspořádaný

- Každá stavebnice má vlastní složku, v ní je každá lekce ve své podsložce: `README.md` (text), `img/` (obrázky) a složka se sketchem `.ino`.
- Kód se do `README.md` vkládá automaticky ze souboru `.ino` – **opravuj vždy jen soubor `.ino`**.
- `<stavebnice>/_kit/kit.json` – název, verze, datum a texty titulní strany.
- `_build/` – společný sestavovací skript, styl PDF, fonty a logo.

## Sestavení PDF

```bash
python3 _build/build.py                            # všechny stavebnice
python3 _build/build.py Arduino-MAXI-Starter-Kit   # jedna stavebnice
```

Výsledek je v `<stavebnice>/vystup/`. Potřebuješ `pandoc`, Python s `playwright` (`pip install playwright && playwright install chromium`) a `poppler-utils`; fonty z `_build/fonts` nainstaluj do systému.

PDF a ZIP se sestavují i automaticky na GitHubu (Actions) při každé změně; po vytvoření tagu `v*` se přiloží k vydání v Releases.
