from pathlib import Path
import os
import re
import markdown as _markdown_lib
from urllib.parse import quote
import html

# TODO: import markdown requires you to install markdown package

FolderInput = Path("D:\\create\\2026-03-23 create website compiler\\i")
FolderWebsite = Path("D:\\create\\2026-03-23 create website compiler")
TemplatePath = Path("D:\\create\\2026-03-23 create website compiler\\i\\template.html")


def ConvertMarkdownToHTML(FolderA, FolderB):

    InputFolder = Path(FolderA)
    OutputFolder = Path(FolderB)
    if not InputFolder.exists() or not InputFolder.is_dir():
        raise FileNotFoundError(f"Input folder not found: {InputFolder}")
    OutputFolder.mkdir(parents=True, exist_ok=True)

    md_exts = {".md", ".markdown"}
    wiki_img_re = re.compile(r'!\[\[([^\]\|]+?)(?:\|([^\]]*?))?\]\]')
    wiki_link_re = re.compile(r'(?<!!)\[\[([^\]\|]+?)(?:\|([^\]]*?))?\]\]')

    for md_path in InputFolder.rglob("*"):
        if not md_path.is_file() or md_path.suffix.lower() not in md_exts:
            continue
        rel = md_path.relative_to(InputFolder)
        out_path = (OutputFolder / rel).with_suffix(".html")
        out_path.parent.mkdir(parents=True, exist_ok=True)

        text = md_path.read_text(encoding="utf-8")

        # Replace Obsidian-style image embeds ![[path/to/image.png|alt]] with HTML <img>
        def _replace_wiki_image(m):
            img_ref = m.group(1).strip()
            alt = (m.group(2) or "").strip().replace('"', "&quot;")
            # Resolve image path relative to the markdown file location first
            img_source = (md_path.parent / img_ref)
            try:
                img_rel_to_input = img_source.relative_to(InputFolder)
            except Exception:
                # If the image path is not under the input folder, use the raw reference
                img_rel_to_input = Path(img_ref)
            img_output = (OutputFolder / img_rel_to_input).resolve()
            try:
                src = os.path.relpath(img_output, start=out_path.parent)
            except Exception:
                src = str(img_output)
            src = src.replace(os.path.sep, "/")
            return f'<img src="{src}" alt="{alt}">'

        # Replace wiki-links [[page|display]] -> site path like page.html (no /w/ prefix)
        def _replace_wiki_link(m):
            raw = m.group(1).strip()
            display = (m.group(2) or "").strip()
            # separate anchor if present
            anchor = ""
            if "#" in raw:
                raw, anchor = raw.split("#", 1)
            # strip markdown extension if present
            rp = Path(raw)
            if rp.suffix.lower() in md_exts:
                raw = str(rp.with_suffix(""))
            # build quoted path preserving subfolders
            segments = [quote(seg) for seg in raw.split("/") if seg != ""]
            url_path = "/".join(segments)
            # produce relative path like "page.html" or "sub/page.html" (no /w/ prefix)
            href = f"{url_path}.html" if url_path else ".html"
            if anchor:
                href += "#" + quote(anchor)
            if not display:
                display = rp.stem if rp.name else raw
            display = html.escape(display)
            return f'<a href="{href}">{display}</a>'

        text = wiki_img_re.sub(_replace_wiki_image, text)
        text = wiki_link_re.sub(_replace_wiki_link, text)

        body_html = _markdown_lib.markdown(text, extensions=["extra", "toc"])
        html_doc = (
            "<!doctype html>\n"
            "<html>\n<head>\n<meta charset=\"utf-8\">\n"
            f"<title>{md_path.stem}</title>\n</head>\n<body>\n"
            f"{body_html}\n</body>\n</html>"
        )
        out_path.write_text(html_doc, encoding="utf-8")

def CopyFileTypeFromFolderAToFolderB(FolderA, FolderB, FileTypes):
    FolderA = Path(FolderA)
    FolderB = Path(FolderB)
    if not FolderA.exists() or not FolderA.is_dir():
        raise FileNotFoundError(f"Folder A not found: {FolderA}")
    FolderB.mkdir(parents=True, exist_ok=True)

    for file_path in FolderA.rglob("*"):
        if not file_path.is_file() or file_path.suffix.lower() not in FileTypes:
            continue
        rel = file_path.relative_to(FolderA)
        out_path = FolderB / rel
        out_path.parent.mkdir(parents=True, exist_ok=True)
        out_path.write_bytes(file_path.read_bytes())

def AddTemplateToHTMLFiles(FolderB, TemplatePath):
    # adds template to the top of the html files in FolderB, but skip the template file itself
    FolderB = Path(FolderB)
    TemplatePath = Path(TemplatePath)
    if not FolderB.exists() or not FolderB.is_dir():
        raise FileNotFoundError(f"Folder B not found: {FolderB}")
    if not TemplatePath.exists() or not TemplatePath.is_file():
        raise FileNotFoundError(f"Template file not found: {TemplatePath}")

    template = TemplatePath.read_text(encoding="utf-8")
    placeholder = "{{content}}"
    template_resolved = TemplatePath.resolve()

    for html_path in FolderB.rglob("*.html"):
        if not html_path.is_file():
            continue
        try:
            if html_path.resolve() == template_resolved:
                continue  # skip the template file itself
        except Exception:
            pass

        html_text = html_path.read_text(encoding="utf-8")
        # extract inner body if present
        m = re.search(r'(?is)<body.*?>(.*?)</body>', html_text)
        body_inner = m.group(1) if m else html_text

        if placeholder in template:
            out_html = template.replace(placeholder, body_inner)
        else:
            # insert before closing </body> (case-insensitive), or append if not found
            if re.search(r'(?i)</body>', template):
                out_html = re.sub(r'(?i)</body>', body_inner + "\n</body>", template, count=1)
            else:
                out_html = template + "\n" + body_inner

        html_path.write_text(out_html, encoding="utf-8")


print("converting markdown to html")
ConvertMarkdownToHTML(FolderInput, FolderWebsite)

print("copying png and css files")
CopyFileTypeFromFolderAToFolderB(FolderInput, FolderWebsite, {".png", ".css", ".html", ".ico"})

print("applying template to html files")
AddTemplateToHTMLFiles(FolderWebsite, TemplatePath)

print("finished")
