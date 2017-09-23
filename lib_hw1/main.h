#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "hash.h"
#include "bitmap.h"

#define QUIT                    0
#define CREATE                  1
#define DELETE                  2
#define DUMPDATA                3
#define LIST                    4
#define HASH                    5
#define BITMAP                  6


void GetString(char *);
char* GetArg();
int GetCommand();

void DoCreate();
void DoDelete();
void DoDumpdata();
void DoList();
void DoHash();
void DoBitmap();


