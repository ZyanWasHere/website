#importing libraries
import os
import glob
import markdown
import shutil
import re



# if folder don't exist >> make folder
if os.path.isdir("converted") == False:
    os.makedirs("converted")


# gather every md in website folder
gatheredtext = glob.glob("website/*.md")

for x in gatheredtext:
    # header name
    newname = x.replace("website\\" , "")
    newname = newname.replace(".md", "")

    # convert .md to .html & put it in "converted" folder
    newfile = x.replace(".md", ".html")
    newfile = newfile.replace("website\\", "converted\\")

    # make new file, & paste header in a variable
    with open(newfile, "a") as file:
        textfile = open(x)
        with open("template/templateheader.md", "r") as file:
            htmlfile = file.read()

    # replace header template name, with .md name
    # and write header to html & add markdowned text file to html.
    with open(newfile, "a") as file:
        htmlfile = htmlfile.replace("TEMPLATE", newname)
        file.write(htmlfile)
        file.write(markdown.markdown(textfile.read()))

    # replaces image
    with open(newfile, 'r') as file:
        content = file.read()

        def replaceimage(match):
            linkimage = match.group(1)
            return f'<img src ="{linkimage}" class="thumbnail">'

        replacehyperlinkfile = re.sub(r"!\[\[([^\]]+)\]\]", replaceimage, content)

    # html compatible
    with open(newfile, 'w') as file:
        file.write(replacehyperlinkfile)

    # replaces hyperlink
    with open(newfile, 'r') as file:
        content = file.read()

        def replacelink(match):
            linkwebsite = match.group(1)
            return f'<a href="{linkwebsite}.html">{linkwebsite}</a>'
        replacehyperlinkfile = re.sub(r"(?<!\!)\[\[([^\]]+)\]\]", replacelink, content)

        # html compatible
        with open(newfile, 'w') as file:
            file.write(replacehyperlinkfile)

# get png, jpg, ico, & css
gatheredimages = glob.glob("template/*.png")
gatheredimages += glob.glob("template/*.ico")
gatheredimages += glob.glob("template/*.css")
gatheredimages += glob.glob("template/*.jpg")
gatheredimages += glob.glob("template/*.pdf")

gatheredimages += glob.glob("website/*.png")
gatheredimages += glob.glob("website/*.ico")
gatheredimages += glob.glob("website/*.css")
gatheredimages += glob.glob("website/*.jpg")
gatheredimages += glob.glob("website/*.pdf")

for x in gatheredimages:
    shutil.copy(x, "converted\\")
