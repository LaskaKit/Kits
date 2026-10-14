#!/usr/bin/env python3
"""
Sestavení návodu LaskaKit Arduino MAXI Starter kit z Markdownu.

  python3 _build/build.py          # vloží kódy do README, vytvoří README obsahu, PDF a ZIP s kódy

Potřebuje: pandoc, python3 + playwright (Chromium), poppler-utils (pdftotext, pdfunite).
Fonty Montserrat, Lato a JetBrains Mono jsou ve složce _build/fonts (nainstaluj je do systému).
"""
import base64, html, json, os, re, shutil, subprocess, sys, tempfile, zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
B = os.path.join(ROOT, '_build')
OUT = os.path.join(ROOT, 'vystup')
VERZE = '3.0'
DATUM = 'říjen 2026'
NAZEV = 'LaskaKit Arduino MAXI Starter kit'

chapters = json.load(open(os.path.join(B, 'chapters.json'), encoding='utf-8'))


# ------------------------------------------------------------ 1) kódy do README
def sync_code():
    pat = re.compile(r'(<!-- kod: (.+?) -->\n)(.*?)(<!-- /kod -->)', re.S)
    for ch in chapters:
        p = os.path.join(ROOT, ch['folder'], 'README.md')
        txt = open(p, encoding='utf-8').read()

        def repl(m):
            src = open(os.path.join(ROOT, ch['folder'], m.group(2)), encoding='utf-8').read().rstrip('\n')
            return f'{m.group(1)}```cpp\n{src}\n```\n{m.group(4)}'
        new = pat.sub(repl, txt)
        if new != txt:
            open(p, 'w', encoding='utf-8').write(new)


# ------------------------------------------------------------ 2) README.md v kořeni (GitHub)
def root_readme():
    lines = [
        f'# {NAZEV} – návod',
        '',
        '<p align="center"><img src="_build/assets/titulka.png" width="45%" alt=""></p>',
        '',
        f'Verze {VERZE} ({DATUM}). Návod a programy ke stavebnici '
        '[LaskaKit Arduino MAXI Starter kit, RFID](https://www.laskakit.cz/laskkit-arduino-maxi-starter-kit--rfid/) '
        '– 31 lekcí od blikání LED až po RFID zámek.',
        '',
        'Programy fungují na deskách **Arduino UNO R3**, **Arduino UNO R4 WiFi** a **Arduino Mega 2560**.',
        '',
        '## Obsah',
        '',
    ]
    for ch in chapters:
        lines.append(f'- [{ch["title"]}]({ch["folder"]}/README.md)')
    lines += [
        '',
        '## Jak je repozitář uspořádaný',
        '',
        '- Každá lekce má vlastní složku: `README.md` (text lekce), `img/` (obrázky) a složku se sketchem `.ino`.',
        '- Kód v `README.md` se do textu vkládá automaticky ze souboru `.ino` – opravuj vždy jen soubor `.ino`.',
        '- `_build/build.py` vytvoří PDF návod a ZIP s kódy do složky `vystup/`.',
        '',
        '## Sestavení PDF',
        '',
        '```bash',
        'python3 _build/build.py',
        '```',
        '',
        'Potřebuješ `pandoc`, Python s balíčkem `playwright` (Chromium) a `poppler-utils`. '
        'Fonty Montserrat, Lato a JetBrains Mono jsou ve složce `_build/fonts`.',
        '',
        '---',
        '',
        open(os.path.join(B, 'about.md'), encoding='utf-8').read().strip(),
        '',
    ]
    open(os.path.join(ROOT, 'README.md'), 'w', encoding='utf-8').write('\n'.join(lines))


# ------------------------------------------------------------ 3) HTML
def md_to_html(md):
    r = subprocess.run(['pandoc', '-f', 'gfm', '-t', 'html5', '--highlight-style=pygments', '--wrap=none'],
                       input=md, capture_output=True, text=True, check=True)
    return r.stdout


def chapter_html():
    parts = []
    for ch in chapters:
        md = open(os.path.join(ROOT, ch['folder'], 'README.md'), encoding='utf-8').read()
        md = re.sub(r'<!-- /?kod.*?-->\n?', '', md)
        h = md_to_html(md)
        h = h.replace('src="img/', f'src="file://{ROOT}/{ch["folder"]}/img/')
        h = re.sub(r'<h1[^>]*>', f'<h1 id="{ch["folder"]}">', h, count=1)
        parts.append(f'<section class="chapter">{h}</section>')
    return '\n'.join(parts)


def toc_html(pages):
    items = []
    for i, ch in enumerate(chapters):
        if i == 4:
            items.append('<li class="part">Lekce</li>')
        pg = pages.get(ch['folder'], '')
        items.append(f'<li><a href="#{ch["folder"]}">{html.escape(ch["title"])}</a>'
                     f'<span class="dots"></span><span class="pg">{pg}</span></li>')
    about = md_to_html(open(os.path.join(B, 'about.md'), encoding='utf-8').read())
    return (f'<section class="toc"><h1>Obsah</h1><ol>{"".join(items)}</ol>'
            f'<div style="margin-top:8mm;color:#5b7680;font-size:9pt">{about}</div></section>')


def page(body, title):
    css = open(os.path.join(B, 'style.css'), encoding='utf-8').read()
    return (f'<!doctype html><html lang="cs"><head><meta charset="utf-8"><title>{title}</title>'
            f'<style>{css}</style></head><body>{body}</body></html>')


def cover_html():
    img = os.path.join(B, 'assets', 'titulka.png')
    logo = os.path.join(B, 'assets', 'logo.jpg')
    body = f'''
<div style="height:247mm;display:flex;flex-direction:column;align-items:center;justify-content:space-between;text-align:center">
  <img src="file://{logo}" style="width:62mm;margin-top:2mm">
  <img src="file://{img}" style="width:140mm">
  <div>
    <div style="font-family:Montserrat;font-weight:700;font-size:30pt;color:#009BAA;line-height:1.1">Arduino MAXI<br>Starter kit</div>
    <div style="font-family:Montserrat;font-weight:500;font-size:14pt;color:#FF873C;margin-top:4mm">Návod k použití · 31 lekcí</div>
  </div>
  <div style="font-size:10pt;color:#5b7680;margin-bottom:2mm">
    Pro Arduino UNO R3, UNO R4 WiFi a Mega 2560<br>Verze {VERZE} · {DATUM} · www.laskakit.cz
  </div>
</div>'''
    css = '@page{size:A4;margin:22mm 18mm 18mm 18mm} body{margin:0;font-family:Lato;color:#114655}'
    return f'<!doctype html><html lang="cs"><head><meta charset="utf-8"><style>{css}</style></head><body>{body}</body></html>'


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
        pg.goto('file://' + html_path, wait_until='networkidle')
        pg.evaluate('document.fonts.ready')
        opts = dict(path=pdf_path, format='A4', print_background=True, prefer_css_page_size=True)
        if with_hf:
            opts.update(display_header_footer=True, header_template=header, footer_template=footer)
        pg.pdf(**opts)
        br.close()


def find_pages(pdf):
    """strana, na které začíná každá kapitola (číslováno od 1 v těle)"""
    n = int(re.search(r'Pages:\s+(\d+)', subprocess.run(['pdfinfo', pdf], capture_output=True, text=True).stdout).group(1))
    pages = {}
    for i in range(1, n + 1):
        t = subprocess.run(['pdftotext', '-f', str(i), '-l', str(i), '-layout', pdf, '-'],
                           capture_output=True, text=True).stdout
        head = ' '.join(t.split())[:200]
        for ch in chapters:
            if ch['folder'] in pages:
                continue
            title = ch['title']
            if head.startswith(title[:25]) or (' ' + title[:25]) in head[:120]:
                pages[ch['folder']] = i
    return pages


def build_pdf():
    os.makedirs(OUT, exist_ok=True)
    tmp = os.path.join(B, 'tmp')
    os.makedirs(tmp, exist_ok=True)
    chapters_part = chapter_html()
    body_html = os.path.join(tmp, 'body.html')
    body_pdf = os.path.join(tmp, 'body.pdf')
    pages = {}
    for _ in range(2):  # 1. průchod zjistí čísla stran, 2. je vypíše do obsahu
        open(body_html, 'w', encoding='utf-8').write(page(toc_html(pages) + chapters_part, NAZEV))
        print_pdf(body_html, body_pdf)
        pages = find_pages(body_pdf)
    missing = [c['title'] for c in chapters if c['folder'] not in pages]
    if missing:
        print('VAROVÁNÍ – nenalezené strany:', missing)
    cover_path = os.path.join(tmp, 'cover.html')
    open(cover_path, 'w', encoding='utf-8').write(cover_html())
    cover_pdf = os.path.join(tmp, 'cover.pdf')
    print_pdf(cover_path, cover_pdf, with_hf=False)
    final = os.path.join(OUT, f'{NAZEV} v{VERZE}.pdf')
    subprocess.run(['pdfunite', cover_pdf, body_pdf, final], check=True)
    print('PDF:', final)
    return final


def build_zip():
    z = os.path.join(OUT, f'LaskaKit MAXI kody v{VERZE}.zip')
    top = f'LaskaKit MAXI kody v{VERZE}'
    with zipfile.ZipFile(z, 'w', zipfile.ZIP_DEFLATED) as zf:
        for ch in chapters:
            d = os.path.join(ROOT, ch['folder'])
            for sub in sorted(os.listdir(d)):
                sp = os.path.join(d, sub)
                if os.path.isdir(sp) and sub != 'img':
                    for f in sorted(os.listdir(sp)):
                        if f.endswith('.ino') or f.endswith('.h') or f.endswith('.cpp'):
                            n = re.match(r'lekce-(\d+)', ch['folder']).group(1)
                            zf.write(os.path.join(sp, f), f'{top}/Lekce_{n} {ch["title"].split(": ", 1)[1]}/{sub}/{f}')
        cti = os.path.join(B, 'CTI_ME.txt')
        if os.path.exists(cti):
            zf.write(cti, f'{top}/CTI_ME.txt')
    print('ZIP:', z)


if __name__ == '__main__':
    sync_code()
    root_readme()
    build_pdf()
    build_zip()
