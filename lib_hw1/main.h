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



typedef unsigned long elem_type;
struct bitmap
{
	size_t bit_cnt;     /* Number of bits. */
	elem_type *bits;    /* Elements that represent bits. */
};


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

struct list * FindList(char *);
struct hash * FindHash(char *);
struct bitmap * FindBitmap(char *);

void DumpList(struct list *);
void DumpHash(struct hash *);
void DumpBitmap(struct bitmap *);

void PrintBool(bool);
void PrintSizeT(size_t);

int ToInt(char *);
bool ToBool(char *);
void GetString(char *);
char* GetArg();
int GetCommand();

void DoCreate();
void DoDelete();
void DoDumpdata();
void DoList();
void DoHash();
void DoBitmap();

#define GET_LIST_DATA(LIST_ELEM) \
	list_entry(LIST_ELEM, struct list_item, elem)->data
struct list_elem * CreateListElem(int);
bool llf (const struct list_elem *,
		const struct list_elem *, 
		void *);

#define GET_HASH_DATA(HASH_ELEM) \
	hash_entry(HASH_ELEM, struct hash_item, elem)->data

struct hash_elem * CreateHashElem(int);
unsigned hhf (const struct hash_elem *,
		void *);
bool hlf (const struct hash_elem *,
		const struct hash_elem *, 
		void *);
void haf (struct hash_elem *, 
		void *);
void haf_square (struct hash_elem *, 
		void *);
void haf_triple (struct hash_elem *, 
		void *);

void FreeAll();
