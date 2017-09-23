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


struct MyList {
	struct list os_list;
	char name[30];
};

struct MyHash {
	struct hash os_hash;
	char name[30];
};

struct MyBitmap {
	struct bitmap* os_bitmap;
	char name[30];
};

struct MyList my_list[10];
struct MyHash my_hash[10];
struct MyBitmap my_bitmap[10];

int list_idx=-1;
int hash_idx=-1;
int bitmap_idx=-1;

int FindList(char *);
int FindHash(char *);
int FindBitmap(char *);

void DumpList(struct list *);
void DumpHash(struct hash *);
void DumpBitmap(struct bitmap *);

void GetString(char *);
char* GetArg();
int GetCommand();

void DoCreate();
void DoDelete();
void DoDumpdata();
void DoList();
void DoHash();
void DoBitmap();
