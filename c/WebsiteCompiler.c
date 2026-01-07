
// TODO
// x MAKE NEW FOLDER CALLED "w"
// x SCAN FOLDERS "i" & "t" FOR FILES TO PUT IN "w"
// - SCAN "i" FOLDER FOR .MD FILES
// - CONVERT THAT INTO .HTML FILES
// - ADD THOSE TO FOLDER "w"

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <windows.h>









// - MAKE NEW FOLDER CALLED "w"
int MakeFolder()
{
  struct stat st = {0};

  if (stat("D:\\create projects\\2025-09-19 create website compiler\\w", &st) == -1)
  {
    mkdir("D:\\create projects\\2025-09-19 create website compiler\\w");
    return 0;
  }
  return 1;
}

// - SCAN FOLDERS "i" & "t" FOR FILES TO PUT IN "w"
int LookForThisInHereToPutThere(const char* ThingWeAreLookingFor, const char  *SourceFolder, const char *DestinationFolder)
{
  // THIS SEARCHES FOR FILES
  WIN32_FIND_DATA findFileData;
  HANDLE hFind = INVALID_HANDLE_VALUE;

  // SEARCHES FOLDER FOR ANYTHING THAT ENDS WITH .PNG
  char searchPath[MAX_PATH];
  snprintf(searchPath, MAX_PATH, ThingWeAreLookingFor, SourceFolder);

  // STARTS SEARCHING FOR PNG FILES
  hFind = FindFirstFile(searchPath, &findFileData);
  if (hFind == INVALID_HANDLE_VALUE)
  {
    printf("no CSS files found or folder issue.\n");
    return 1;
  }

  do
  {
    if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
      char sourceFile[MAX_PATH];
      char destFile[MAX_PATH];

      // BUILDS PATH TO LOCATION
      snprintf(sourceFile, MAX_PATH, "%s\\%s", SourceFolder, findFileData.cFileName);
      snprintf(destFile, MAX_PATH, "%s\\%s", DestinationFolder, findFileData.cFileName);

      // COPY FILE
      if (CopyFile(sourceFile, destFile, FALSE)) {
        printf("Copied: %s\n", findFileData.cFileName);
      } else {
        printf("Failed to copy: %s (Error %lu)\n", findFileData.cFileName, GetLastError());
      }
    }

  } while (FindNextFile(hFind, &findFileData) != 0);

  FindClose(hFind);

  printf("finished moving all CSS files to w.\n");
  return 0;
}




int From_MD_Make_HTML()
{
  // search for MD file
  DIR *dir;
  struct dirent *entry;
  dir = opendir("D:\\create projects\\2025-09-19 create website compiler\\i");

  // ERROR CASE
  if (dir == NULL)
  {
    perror("unable to open directory");
    return 1;
  }

  printf("searching for files \n");
  while ((entry = readdir(dir)) != NULL)
  {
    char *ext = strrchr(entry->d_name, '.');

    if (ext != NULL && strcmp(ext, ".md") == 0)
    {
      *ext = '\0';
      printf("%s\n", entry->d_name);
      strcat(entry->d_name, ".html");
      printf("%s\n", entry->d_name);



// ISSUE ==========================================================================================
// TODO this makes a file, with the correct name in the incorrect folder location.
// ideally it should use something like: fopen(directory location + entry->d_name, "w")
// but i'm  sure if i do that it'll just cause some other issue.


      char FullPath[512];

      snprintf(FullPath, sizeof(FullPath), "D:\\create projects\\2025-09-19 create website compiler\\w\\%s.html", entry->d_name);



      // make new file suffix HTML
      FILE *fptr = fopen(FullPath, "w");
      if (fptr == NULL)
      {
        perror("error creating file\n");
        return 1;
      }

      fprintf(fptr, "<html><body>content from %s</body></html>", ext);
      fclose(fptr);

      printf("created: %s\n", ext);





    }
  }

  closedir(dir);


  // syntax conversion


  return 0;

}










int main()
{
  // VARIABLES
  const char *PNGFiles = "%s\\*.png";
  const char *ICOFiles = "%s\\*.ico";
  const char *CSSFiles = "%s\\*.css";
  const char *MDFiles = "%s\\*.md";

  const char *FolderInput = "D:\\create projects\\2025-09-19 create website compiler\\i";
  const char *FolderTemplate = "D:\\create projects\\2025-09-19 create website compiler\\t";
  const char *FolderWebsite = "D:\\create projects\\2025-09-19 create website compiler\\w";



  // 1) MAKE FOLDER w
  MakeFolder();

  // 2) COPY PNG, ICO, CSS FILES TO FOLDER w
  // LookForThisInHereToPutThere(ThingWeAreLookingFor, SourceFolder, DestinationFolder)
  LookForThisInHereToPutThere(PNGFiles, FolderTemplate, FolderWebsite);
  LookForThisInHereToPutThere(ICOFiles, FolderTemplate, FolderWebsite);
  LookForThisInHereToPutThere(CSSFiles, FolderTemplate, FolderWebsite);
  LookForThisInHereToPutThere(PNGFiles, FolderInput, FolderWebsite);


  From_MD_Make_HTML();





  return 0;


}
