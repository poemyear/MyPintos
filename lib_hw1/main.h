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

#define DELIM_COMMAND			"_ \t"
#define DELIM_ARG				" \t"

#define MAX_COMMAND_LENGTH		100
#define MAX_NAME_LENGTH   		30
#define MAX_STRUCTURE_CNT		10

#define INT_32_MAX_VALUE		4294967295

typedef unsigned long elem_type;
struct bitmap
{
	size_t bit_cnt;     /* Number of bits. */
	elem_type *bits;    /* Elements that represent bits. */
};


struct MyList {
	struct list os_list;
	char name[MAX_NAME_LENGTH];
};

struct MyHash {
	struct hash os_hash;
	char name[MAX_NAME_LENGTH];
};

struct MyBitmap {
	struct bitmap* os_bitmap;
	char name[MAX_NAME_LENGTH];
};

struct MyList my_list[MAX_STRUCTURE_CNT];
struct MyHash my_hash[MAX_STRUCTURE_CNT];
struct MyBitmap my_bitmap[MAX_STRUCTURE_CNT];

int list_idx=-1;
int hash_idx=-1;
int bitmap_idx=-1;

#define IF_NULL_EXIT(VARS_TO_BE_NOT_NULL) \
	if (!(VARS_TO_BE_NOT_NULL))	return

#define CMP(VAR, STR) \
	strcmp(VAR, STR)==0
#define TYPE(STR) \
	CMP(type, STR)
#define CMD(STR) \
	CMP(ptr, STR)
#define SUBCMD(STR) \
	CMP(subcmd, STR)
#define TYPE_IS_LIST\
	TYPE("list")
#define TYPE_IS_HASH\
	TYPE("hashtable")
#define TYPE_IS_BITMAP\
	TYPE("bitmap")

char *subcmd, *type, *name, *arg1, *arg2, *arg3, *arg4;

struct list * FindList(char *);
struct hash * FindHash(char *);
struct bitmap * FindBitmap(char *);

void DumpList(struct list *);
void DumpHash(struct hash *);
void DumpBitmap(struct bitmap *);

void DoCreate();
void DoDelete();
void DoDumpdata();
void DoList();
void DoHash();
void DoBitmap();

typedef void list_iterate_func(struct list_elem *);
void IterateList(struct list *, list_iterate_func *);
void PrintListItem(struct list_elem *);
void FreeListItem(struct list_elem *);

#define GET_LIST_ITEM(LIST_ELEM) \
	list_entry(LIST_ELEM, struct list_item, elem)
#define GET_LIST_DATA(LIST_ELEM) \
	GET_LIST_ITEM(LIST_ELEM)->data
struct list_elem * CreateListElem(int);
bool llf (const struct list_elem *,
		const struct list_elem *, 
		void *);

#define GET_HASH_ITEM(HASH_ELEM) \
	hash_entry(HASH_ELEM, struct hash_item, elem)
#define GET_HASH_DATA(HASH_ELEM) \
	GET_HASH_ITEM(HASH_ELEM)->data

struct hash_elem * CreateHashElem(int);
unsigned hhf (const struct hash_elem *,
		void *);
bool hlf (const struct hash_elem *,
		const struct hash_elem *, 
		void *);
void haf (struct hash_elem *, void *);
void haf_square (struct hash_elem *, void *);
void haf_triple (struct hash_elem *, void *);
void haf_free_item (struct hash_elem *, void *);

void PrintInt(int);
void PrintBool(bool);
void PrintSizeT(size_t);

int ToInt(char *);
bool ToBool(char *);
void GetString(char *);
char* GetArg();
int GetCommand();
