#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <cmark.h>


int MakeFolder(const char *FolderName)
{
    if (CreateDirectory(FolderName, NULL))
    {
        return 0;
    }
    else
    {
        printf("failed to create: %s\n", FolderName);
        return 0;
    }
}

int CopyFolder(const char *FolderA, const char *FolderB)
{
    char Command[1024];
    snprintf(Command, sizeof(Command), "copy \"%s\" \"%s\"", FolderA, FolderB);
    system(Command);
    return 0;
}

int MoveFiles(const char *FolderA, const char *FolderB)
{
    char Command[1024];
    snprintf(Command, sizeof(Command), "move \"%s\\*\" \"%s\"", FolderA, FolderB);
    system(Command);
    return 0;
}

int DeleteFolder(const char *FolderName)
{
    char Command[1024];
    snprintf(Command, sizeof(Command), "rmdir \"%s\"", FolderName);
    system(Command);
    return 0;
}

const char *OutputString()
{
    const char *TestMarkdown = "# Hello World\nThis is a test markdown file.";
    char *html_output = cmark_markdown_to_html(TestMarkdown, strlen(TestMarkdown), CMARK_OPT_DEFAULT);
    return html_output;
}




int main()
{
    const char *Output = "C:\\Users\\a\\Desktop\\virtual machine\\Output";
    const char *FolderA = "C:\\Users\\a\\Desktop\\virtual machine\\FolderA";
    const char *FolderB = "C:\\Users\\a\\Desktop\\virtual machine\\FolderB";


    printf(OutputString());

    return 0;

}
