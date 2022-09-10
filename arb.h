/* Anton Dumitrita 324CB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifndef ARBORE_BINAR
#define ARBORE_BINAR

struct Dir;
struct File;

typedef struct Dir {
    char *name;
    struct Dir* parent;
    struct File* files;
    struct Dir* directories;
    struct Dir* left;
    struct Dir* right;
} Dir;

typedef struct File {
    char *name;
    struct Dir* parent;
    struct File* left;
    struct File* right;
} File;

Dir* alocDir(char * name);
File* alocFile(char * name);
Dir* searchHelperDir(Dir * dir, char * name);
Dir* searchHelperFile(File * file, char * name);
int searchDir(Dir* dir, char* name);
int searchFile(File* file, char* name);
void InsertFile(File *file, char * name);
void InsertDir(Dir *dir, char * name);
void printFiles(File * file);
void printDirs(Dir * dir);
File * minFile(File * file);
Dir * minDir(Dir * dir);
File * deleteFile(File* file, char * name);
Dir* deleteDir(Dir* dir, char* name);
void freeDir(Dir** dir);
void freeFile(File** file);
void freeTreeDir(Dir** dir);
void freeTreeFile(File** file);

#endif
 