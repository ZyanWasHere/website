#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <windows.h>




int MakeFolder(const char *FolderOutput)
{
  printf("creating website folder...\n");
  struct stat st = {0}; //stat is used to read and manipulate system data
  if (stat(FolderOutput, &st) == -1) // if folder output doesn't exist
  {
    mkdir(FolderOutput);
    printf("website folder has been created\n");
  }
  printf("folder already created\n");
}

int ChangeNameOfFileFromFolder(char *FileName)
{
  printf("changing name of %s\n", FileName);
  char *dot = strrchr(FileName, '.'); // find the suffix
  if (dot != NULL)
  {
    strcpy(dot, ".html");
    printf("name changed to %s\n", FileName);
    return 0;
  }
}

int CreateNewFileInFolder(char *FileName, const char *FolderDir)
{
  printf("creating path in %s\n", FolderDir);
  char FullPath[512]; // temp buffer
  FILE *fptr;
  // why does this look harder than it needs to be. stupid C.
  // TLDR: add dir + filename = buffer

  snprintf(FullPath, sizeof(FullPath), "%s/%s", FolderDir, FileName);
  fptr = fopen(FullPath, "w"); // try to make file in location
  fclose(fptr);
  printf("created: %s\n", FullPath);
  return 0;
}

int GetDataFromFile(char *StoreDataHere, const char *FileDir)
{
  printf("copying data from %s\n", FileDir);
  FILE *fptr; // get file location
  fptr = fopen(FileDir, "r");

  // TODO: HOPEFULLY ITS ENOUGH???
  char line[1024]; // TMP storage to store each line

  StoreDataHere[0] = '\0'; // reset string

  while (fgets(line, sizeof(line), fptr)) // read each line and put it in StoreDataHere
  {
      strcat(StoreDataHere, line);
  }
  printf("copied data from in %s\n", FileDir);
  printf("pasted data local variable"); // NOTE: can't printf the var name, vars names don't exist when code is compiled?...
  fclose(fptr);
  return 0;
}

int PutDataFromThisOntoThat(char *ThisData, char *IntoThatFile)
{
  printf("copy data from local variable \n");
  FILE *fptr;
  fptr = fopen(IntoThatFile, "w");
  printf("pasted it onto: %s\n", IntoThatFile);

  // TODO: this might give error. apperantly this runs then tests function. i don't trust it.
  if (fputs(ThisData, fptr) == EOF)
  {
      fclose(fptr);
      return -1;
  }

  fclose(fptr);
  return 0;
}









int main()
{
  const char *FolderInput = "D:\\create projects\\2025-09-19 create website compiler\\i";
  const char *FolderTemplate = "D:\\create projects\\2025-09-19 create website compiler\\t";
  const char *FolderWebsite = "D:\\create projects\\2025-09-19 create website compiler\\w";

  char File1[128];
  char HoldData[2048]; // THIS SHOULD... I HOPE... HOLD A NOTEPAD FULL OF DATA???

  const char *PNGFiles = "%s\\*.png";
  const char *ICOFiles = "%s\\*.ico";
  const char *CSSFiles = "%s\\*.css";
  const char *MDFiles = "%s\\*.md";

  MakeFolder(FolderWebsite);
  CopyFilesOfThisTypeFromSourceDirToOutputDir(PNGFiles, FolderInput, FolderWebsite);
}
