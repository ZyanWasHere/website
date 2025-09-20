	last updated: 2025-07-18
# i made my first website!

![[i made my first website 1.png]]
## background
in 2024 i had the idea to create my first ever website! having absolutely no knowledge of how to do just that. i ended up never making a website... the information overload was too much, and the logistics just didn't make sense. plus - i was so inexpirienced, i somehow managed to lose my domain - yep... i was grumpy at it (and still am to this day) and have only barely managed to get it back.

making a website is a spectrum, ranging from stupidly simple to stupidly cheap. you want to make a website for free? well you used to be able to on an ancient platform called [geocities](https://en.wikipedia.org/wiki/GeoCities) and i think that's a beautiful thing. a similar platform exists today called [neocities](https://neocities.org/). i've even seen some artists use [itch.io](https://itch.io/)! if you want more professional and expensive options, there's [obsidian publish](https://obsidian.md/publish) which takes your [obsidian md](https://obsidian.md/) vault, and uploads that to the web! further down the ladder you get [wix](https://www.wix.com/) and [squarespace](https://www.squarespace.com/) and so forth.

i wanted full creative control over the formatting and presentation of the site, inspired by [hundreds of rabbits](https://100r.co/site/home.html), artists who publish a lot of their process. their website is a wiki coded by them, made in c89 (which appears to be a version of c - the programming language?). the second site came from [lemmino](https://www.lemmi.no/) who made their website with plane html, css & javascript. and i similarly wanted to follow suit. i wanted to make a website purely in html & css! and i would ideally, like to not have to pay a limb in order to publish the site.

## why
now, you might be thinking to yourself "yeah cool story zyan, no one cares. and because no one cares why did you do it?" - because lets be honest? when was the last time you went to someone's personal website? this isn't the 90's anymore! half of you weren't even alive back then! and if you are you should feel worse!

here's what i think: on the very surface level you have "content" - you have youtube, and tiktok feeds recommending you posts, things that are made FOR THE SOLE PURPOSE of being consumed. it's like a TV show or a podcast or a movie. there's an agreement that - time will be spent purposefully to entertain.

then lower on the list is social media: i.e twitter and instagram and facebook - where you can still get content. and a lot of those posts are designed to "be consumed", but a lot of that content is also personal. it's "here's what i think about THAT thing" and "i can't believe that THIS is happening?!"

and then on the bottom there's blogs. there's articles that people write that few people will read, articles which take their time. there's a funnel from "attention grabbing media sensation" to "personalized conversations" and then below that bottom, there's the floor. which is personal websites. places which statistically: will have the least amount of traffic. places where you can share things you're interested in KNOWING that it will get little traffic. and yet they're charming to me SOLEY for that fact. its like writing a book VS a letter to a penpal. that's what this is to me.
## how my site specifically works

![[i made my first website 2.png]]

1. every page on the site is actually a text document. that's right! everything you're lookin' at is made with good ol' markdown!
2. all the pages (and the images that they use) are in a "website folder" and all the css, icon files, the html for the header are all in a "template folder"
3. a python script grabs all the assets from the website & template folder, and places it into a "converted folder". then the python script slaps a header on top of the text files, and converts them into an html file!
4. finally, you can simply upload the entire "converted" folder straight onto [github pages](https://pages.github.com/).

as of 2025-06-05 i did not want to impliment any javascript or node.js or anything of that sort onto the site! i wanted a simple static site, which could run efficiently, and being able to modify it simply was the objective. as of now i know i don't have the skills (and don't want the responsibility) of handeling any transactions or handeling sensitive data. if i were to handle any transactions, they would go on another website ([patreon](https://www.patreon.com/zyanwashere), and etsy come to mind). at best they would link to those sites.

## python code

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
