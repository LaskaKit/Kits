#!/usr/bin/env python3
"""
Sestavení návodů ke stavebnicím LaskaKit z Markdownu.

  python3 _build/build.py                          # všechny stavebnice
  python3 _build/build.py Arduino-MAXI-Starter-Kit # jen jedna

Pro každou stavebnici:
  1. vloží kód z .ino souborů do README.md jednotlivých lekcí,
  2. vytvoří README.md stavebnice (obsah s odkazy) a README.md repozitáře,
  3. vytvoří PDF návod a ZIP s programy do <stavebnice>/vystup/.

Stavebnice = složka v kořeni, která obsahuje _kit/kit.json.
Kapitoly = podsložky s README.md (řazené podle názvu), titulek = první řádek „# …“.

Potřebuje: pandoc, python3 + playwright (Chromium), poppler-utils (pdftotext, pdfunite, pdfinfo)
a fonty Montserrat, Lato a JetBrains Mono (jsou v _build/fonts, nainstaluj je do systému).
"""
import base64, html, json, os, re, subprocess, sys, zipfile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
B = os.path.join(REPO, '_build')


# ------------------------------------------------------------ pomocné
def kits():
    return sorted(d for d in os.listdir(REPO)
                  if os.path.isfile(os.path.join(REPO, d, '_kit', 'kit.json')))


def load_kit(name):
    root = os.path.join(REPO, name)
    cfg = json.load(open(os.path.join(root, '_kit', 'kit.json'), encoding='utf-8'))
    chapters = []
    for d in sorted(os.listdir(root)):
        p = os.path.join(root, d, 'README.md')
        if d.startswith(('_', '.')) or not os.path.isfile(p):
            continue
        first = open(p, encoding='utf-8').readline().strip()
        chapters.append({'folder': d, 'title': first.lstrip('# ').strip()})
    return root, cfg, chapters


def md_to_html(md):
    r = subprocess.run(['pandoc', '-f', 'gfm', '-t', 'html5', '--highlight-style=pygments', '--wrap=none'],
                       input=md, capture_output=True, text=True, check=True)
    return r.stdout


def uri(path):
    return 'file://' + path.replace(' ', '%20')


# ------------------------------------------------------------ 1) kódy do README
CODE = re.compile(r'(<!-- kod: (.+?) -->\n)(.*?)(<!-- /kod -->)', re.S)


def sync_code(root, chapters):
    for ch in chapters:
        p = os.path.join(root, ch['folder'], 'README.md')
        txt = open(p, encoding='utf-8').read()

        def repl(m):
            src = open(os.path.join(root, ch['folder'], m.group(2)), encoding='utf-8').read().rstrip('\n')
            return f'{m.group(1)}```cpp\n{src}\n```\n{m.group(4)}'
        new = CODE.sub(repl, txt)
        if new != txt:
            open(p, 'w', encoding='utf-8').write(new)


# ------------------------------------------------------------ 2) README soubory
def kit_readme(root, cfg, chapters):
    lines = [f'# {cfg["nazev"]} – návod', '',
             '<p align="center"><img src="_kit/titulka.png" width="45%" alt=""></p>', '',
             f'Verze {cfg["verze"]} ({cfg["datum"]}). Návod a programy ke stavebnici '
             f'[{cfg["nazev"]}]({cfg["produkt"]}) – {cfg["popis"]}', '',
             f'{cfg["desky"]}.', '', '## Obsah', '']
    for ch in chapters:
        lines.append(f'- [{ch["title"]}]({ch["folder"]}/README.md)')
    about = os.path.join(root, '_kit', 'about.md')
    if os.path.exists(about):
        lines += ['', '---', '', open(about, encoding='utf-8').read().strip()]
    open(os.path.join(root, 'README.md'), 'w', encoding='utf-8').write('\n'.join(lines) + '\n')


def repo_readme():
    lines = ['# LaskaKit – stavebnice', '',
             '<p align="center"><img src="_build/assets/logo.jpg" width="40%" alt="LaskaKit"></p>', '',
             'Návody a programy ke stavebnicím [LaskaKit](https://www.laskakit.cz). '
             'Hotové PDF návody najdeš u produktu na e-shopu v Souvisejících souborech '
             'nebo v sekci [Releases](../../releases).', '',
             '## Stavebnice', '',
             '| Stavebnice | Verze návodu | Desky |', '|---|---|---|']
    for k in kits():
        _, cfg, _ = load_kit(k)
        lines.append(f'| [{cfg["nazev"]}]({k}/README.md) | {cfg["verze"]} ({cfg["datum"]}) | {cfg["desky"]} |')
    lines += ['', '## Jak je repozitář uspořádaný', '',
              '- Každá stavebnice má vlastní složku, v ní je každá lekce ve své podsložce: '
              '`README.md` (text), `img/` (obrázky) a složka se sketchem `.ino`.',
              '- Kód se do `README.md` vkládá automaticky ze souboru `.ino` – **opravuj vždy jen soubor `.ino`**.',
              '- `<stavebnice>/_kit/kit.json` – název, verze, datum a texty titulní strany.',
              '- `_build/` – společný sestavovací skript, styl PDF, fonty a logo.', '',
              '## Sestavení PDF', '', '```bash',
              'python3 _build/build.py                            # všechny stavebnice',
              'python3 _build/build.py Arduino-MAXI-Starter-Kit   # jedna stavebnice', '```', '',
              'Výsledek je v `<stavebnice>/vystup/`. Potřebuješ `pandoc`, Python s `playwright` '
              '(`pip install playwright && playwright install chromium`) a `poppler-utils`; '
              'fonty z `_build/fonts` nainstaluj do systému.', '',
              'PDF a ZIP se sestavují i automaticky na GitHubu (Actions) při každé změně; '
              'po vytvoření tagu `v*` se přiloží k vydání v Releases.', '']
    open(os.path.join(REPO, 'README.md'), 'w', encoding='utf-8').write('\n'.join(lines))


# ------------------------------------------------------------ 3) HTML + PDF
def page(body, title):
    css = open(os.path.join(B, 'style.css'), encoding='utf-8').read()
    fonts = os.path.join(B, 'fonts')
    face = ''.join(
        f"@font-face{{font-family:'{fam}';src:url('{uri(os.path.join(fonts, f))}');font-weight:{w};font-style:{s}}}"
        for fam, f, w, s in [('Montserrat', 'Montserrat.ttf', '100 900', 'normal'),
                             ('Lato', 'Lato-Regular.ttf', '400', 'normal'), ('Lato', 'Lato-Bold.ttf', '700', 'normal'),
                             ('Lato', 'Lato-Italic.ttf', '400', 'italic'), ('Lato', 'Lato-BoldItalic.ttf', '700', 'italic'),
                             ('JetBrains Mono', 'JetBrainsMono[wght].ttf', '100 800', 'normal'),
                             ('JetBrains Mono', 'JetBrainsMono-Italic[wght].ttf', '100 800', 'italic')])
    return (f'<!doctype html><html lang="cs"><head><meta charset="utf-8"><title>{html.escape(title)}</title>'
            f'<style>{face}{css}</style></head><body>{body}</body></html>')


def chapter_html(root, chapters):
    parts = []
    for ch in chapters:
        md = open(os.path.join(root, ch['folder'], 'README.md'), encoding='utf-8').read()
        md = re.sub(r'<!-- /?kod.*?-->\n?', '', md)
        h = md_to_html(md)
        h = h.replace('src="img/', f'src="{uri(os.path.join(root, ch["folder"]))}/img/')
        h = re.sub(r'<h1[^>]*>', f'<h1 id="{ch["folder"]}">', h, count=1)
        parts.append(f'<section class="chapter">{h}</section>')
    return '\n'.join(parts)


def toc_html(root, cfg, chapters, pages):
    items = []
    for i, ch in enumerate(chapters):
        if i == cfg.get('uvodnich_kapitol', 0) and i:
            items.append('<li class="part">Lekce</li>')
        items.append(f'<li><a href="#{ch["folder"]}">{html.escape(ch["title"])}</a>'
                     f'<span class="dots"></span><span class="pg">{pages.get(ch["folder"], "")}</span></li>')
    about = os.path.join(root, '_kit', 'about.md')
    about_html = md_to_html(open(about, encoding='utf-8').read()) if os.path.exists(about) else ''
    return (f'<section class="toc"><h1>Obsah</h1><ol>{"".join(items)}</ol>'
            f'<div style="margin-top:8mm;color:#5b7680;font-size:9pt">{about_html}</div></section>')


def cover_html(root, cfg):
    img = os.path.join(root, '_kit', 'titulka.png')
    logo = os.path.join(B, 'assets', 'logo.jpg')
    body = f'''
<div style="height:247mm;display:flex;flex-direction:column;align-items:center;justify-content:space-between;text-align:center">
  <img src="{uri(logo)}" style="width:62mm;margin-top:2mm">
  <img src="{uri(img)}" style="width:140mm;max-height:140mm;object-fit:contain">
  <div>
    <div style="font-family:Montserrat;font-weight:700;font-size:30pt;color:#009BAA;line-height:1.1">{cfg["titulek"]}</div>
    <div style="font-family:Montserrat;font-weight:500;font-size:14pt;color:#FF873C;margin-top:4mm">{cfg["podtitulek"]}</div>
  </div>
  <div style="font-size:10pt;color:#5b7680;margin-bottom:2mm">
    {cfg["desky"]}<br>Verze {cfg["verze"]} · {cfg["datum"]} · www.laskakit.cz
  </div>
</div>'''
    return page(body, cfg['nazev']).replace('</style>', '@page{margin:22mm 18mm 18mm 18mm}</style>', 1)


def header_footer():
    logo = base64.b64encode(open(os.path.join(B, 'assets', 'logo.jpg'), 'rb').read()).decode()
    header = (f'<div style="width:100%;padding:0 18mm 0 20mm;display:flex;justify-content:flex-end;'
              f'-webkit-print-color-adjust:exact"><img src="data:image/jpeg;base64,{logo}" style="height:11mm"></div>')
    footer = ('<div style="width:100%;padding:0 18mm 0 14mm;display:flex;align-items:flex-end;'
              'justify-content:space-between;font-family:Lato;-webkit-print-color-adjust:exact">'
              '<div style="display:flex;align-items:flex-end;gap:4mm">'
              '<span class="pageNumber" style="font-family:Montserrat;font-size:15pt;color:#114655;min-width:8mm"></span>'
              '<span style="font-size:6.5pt;color:#009BAA;line-height:1.35">'
              '<b style="color:#FF873C">t.</b> +420 <b>499 111 222</b> <b style="color:#FF873C">+</b> <b>objednavky@laskakit.cz</b><br>'
              'Jiráskova 2009, 516 01 Rychnov nad Kněžnou, Česká republika<br>'
              '<b style="color:#FF873C">IČ:</b> 176 08 007 <b style="color:#FF873C">DIČ:</b> CZ17608007</span></div>'
              '<div style="text-align:right;font-family:Montserrat;font-size:10pt;color:#009BAA;line-height:1.25">'
              'Bastli s láskou<br>na <span style="color:#FF873C">www.laskakit.cz</span></div></div>')
    return header, footer


def print_pdf(html_path, pdf_path, with_hf=True):
    from playwright.sync_api import sync_playwright
    header, footer = header_footer()
    with sync_playwright() as p:
        br = p.chromium.launch()
        pg = br.new_page()
        pg.goto(uri(html_path), wait_until='networkidle')
        pg.evaluate('document.fonts.ready')
        opts = dict(path=pdf_path, format='A4', print_background=True, prefer_css_page_size=True)
        if with_hf:
            opts.update(display_header_footer=True, header_template=header, footer_template=footer)
        pg.pdf(**opts)
        br.close()


def find_pages(pdf, chapters):
    info = subprocess.run(['pdfinfo', pdf], capture_output=True, text=True).stdout
    n = int(re.search(r'Pages:\s+(\d+)', info).group(1))
    pages = {}
    for i in range(1, n + 1):
        t = subprocess.run(['pdftotext', '-f', str(i), '-l', str(i), pdf, '-'], capture_output=True, text=True).stdout
        flat = ' '.join(t.split())
        if sum(ch['title'][:25] in flat for ch in chapters) >= 3:
            continue  # stránka obsahu
        head = flat[:160]
        for ch in chapters:
            if ch['folder'] not in pages and head.startswith(ch['title'][:25]):
                pages[ch['folder']] = i
    return pages


def build_pdf(root, cfg, chapters):
    out = os.path.join(root, 'vystup')
    tmp = os.path.join(out, 'tmp')
    os.makedirs(tmp, exist_ok=True)
    body = chapter_html(root, chapters)
    body_html, body_pdf = os.path.join(tmp, 'body.html'), os.path.join(tmp, 'body.pdf')
    pages = {}
    for _ in range(2):  # 1. průchod zjistí čísla stran, 2. je vypíše do obsahu
        open(body_html, 'w', encoding='utf-8').write(page(toc_html(root, cfg, chapters, pages) + body, cfg['nazev']))
        print_pdf(body_html, body_pdf)
        pages = find_pages(body_pdf, chapters)
    missing = [c['title'] for c in chapters if c['folder'] not in pages]
    if missing:
        print('  VAROVÁNÍ – v PDF nenalezeny kapitoly:', missing)
    cover = os.path.join(tmp, 'cover.html')
    open(cover, 'w', encoding='utf-8').write(cover_html(root, cfg))
    cover_pdf = os.path.join(tmp, 'cover.pdf')
    print_pdf(cover, cover_pdf, with_hf=False)
    final = os.path.join(out, f'{cfg["nazev"]} v{cfg["verze"]}.pdf')
    subprocess.run(['pdfunite', cover_pdf, body_pdf, final], check=True)
    print('  PDF:', final)


def build_zip(root, cfg, chapters):
    top = f'{cfg["zip_kody"]} v{cfg["verze"]}'
    z = os.path.join(root, 'vystup', top + '.zip')
    with zipfile.ZipFile(z, 'w', zipfile.ZIP_DEFLATED) as zf:
        for ch in chapters:
            m = re.match(r'lekce-(\d+)', ch['folder'])
            if not m:
                continue
            d = os.path.join(root, ch['folder'])
            lesson = f'Lekce_{m.group(1)} {ch["title"].split(": ", 1)[-1]}'
            for sub in sorted(os.listdir(d)):
                sp = os.path.join(d, sub)
                if os.path.isdir(sp) and sub != 'img':
                    for f in sorted(os.listdir(sp)):
                        if f.endswith(('.ino', '.h', '.cpp')):
                            zf.write(os.path.join(sp, f), f'{top}/{lesson}/{sub}/{f}')
        cti = os.path.join(root, '_kit', 'CTI_ME.txt')
        if os.path.exists(cti):
            zf.write(cti, f'{top}/CTI_ME.txt')
    print('  ZIP:', z)


if __name__ == '__main__':
    selected = sys.argv[1:] or kits()
    for k in selected:
        print(k)
        root, cfg, chapters = load_kit(k)
        sync_code(root, chapters)
        kit_readme(root, cfg, chapters)
        build_pdf(root, cfg, chapters)
        build_zip(root, cfg, chapters)
    repo_readme()
