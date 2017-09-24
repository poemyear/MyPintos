#include "main.h"

int main (void) {
	char cmd[255]={0, };
	char *ptr;
	int i;
	bool quit=false;

	while (!quit) {
		GetString(cmd);
		switch (GetCommand(cmd)) {
			case QUIT:
				quit=true;
				break;
			case CREATE:
				DoCreate();
				break;
			case DELETE:
				DoDelete();
				break;
			case DUMPDATA:
				DoDumpdata();
				break;
			case LIST:
				DoList();
				break;
			case HASH:
				DoHash();
				break;
			case BITMAP:
				DoBitmap();
				break;
			default:
				break;
		}
	}
	return 0;
}

void GetString(char *str) {
	int i;
	for(i=0;i<100;i++)
	{
		scanf("%c",&str[i]);
		if(str[i] == '\n')
		{
			str[i]='\0';
			break;
		}
	}
}

char* GetArg() {
	return strtok (NULL,  " \t");
}

int GetCommand(char *cmd) {
	char * ptr = strtok (cmd, "_ \t");
	if (cmd[0]=='\0')
		return -1;
	if (strcmp(ptr, "quit") == 0)
		return QUIT;
	if (strcmp(ptr, "create") == 0)
		return CREATE;
	if (strcmp(ptr, "delete") == 0)
		return DELETE;
	if (strcmp(ptr, "dumpdata") == 0)
		return DUMPDATA;
	if (strcmp(ptr, "list") == 0)
		return LIST;
	if (strcmp(ptr, "hash") == 0)
		return HASH;
	if (strcmp(ptr, "bitmap") == 0)
		return BITMAP;
	return -1;
}

void DoCreate() {
	char *arg = GetArg();
	char *name = GetArg();
	int idx=0;
	int num=0;
	if (arg == NULL)
		return ;
	if (strcmp(arg, "list")==0) {
		idx = ++list_idx;
		strcpy(my_list[idx].name, name);
		list_init(&(my_list[idx].os_list));
	} else if (strcmp(arg, "hashtable")==0) {
		idx = ++hash_idx;
		//		strcpy(my_hash[idx].name, name);
		//		hash_init(&(my_hash[idx].os_hash));
	} else if (strcmp(arg, "bitmap")==0) {
		idx = ++bitmap_idx;
		sscanf(GetArg(),"%d", &num);

		printf("%s %d\n", name, num);
		//		strcpy(my_bitmap[idx].name, name);
		//		bitmap_init(&(my_bitmap[idx].os_bitmap));
	}
}

void DoDelete() {
	char *arg = GetArg();
	if (arg == NULL)
		return ;
}

void DoDumpdata() {
	int idx=0;
	char *arg = GetArg();
	if (arg == NULL)
		return ;
	DumpList(FindList(arg));
	DumpHash(FindHash(arg));
	DumpBitmap(FindBitmap(arg));
}

void DoList() {
	int num=0;
	char *subcmd = GetArg();
	char *arg1 = GetArg();
	char *arg2 = GetArg();
	struct list_item * new_item;
	struct list * list_ptr;

	// sub command
	if (subcmd == NULL)
		return ;
	// argument 1
	if (arg1 == NULL)
			return ;
	// check list name exsists
	list_ptr = FindList(arg1);
	if (list_ptr == NULL) 
		return ;
	if (strcmp(subcmd,"insert")==0) {
	}
	else if (strcmp(subcmd,"splice")==0) {
	}
	else if (strcmp(subcmd,"push_front")==0) {
		if (arg2 == NULL)
			return ;
		new_item = (struct list_item*)malloc(sizeof(struct list_item));
		sscanf(arg2,"%d", &(new_item->data));
		list_push_front(list_ptr, &(new_item->elem));
	}
	else if (strcmp(subcmd,"push_back")==0) {
		if (arg2 == NULL)
			return ;
		new_item = (struct list_item*)malloc(sizeof(struct list_item));
		sscanf(arg2,"%d", &(new_item->data));
		list_push_back(list_ptr, &(new_item->elem));
	}
	else if (strcmp(subcmd,"remove")==0) {
	}
	else if (strcmp(subcmd,"pop_front")==0) {
	}
	else if (strcmp(subcmd,"pop_back")==0) {
	}
	else if (strcmp(subcmd,"front")==0) {
	}
	else if (strcmp(subcmd,"back")==0) {
	}
	else if (strcmp(subcmd,"size")==0) {
	}
	else if (strcmp(subcmd,"empty")==0) {
	}
	else if (strcmp(subcmd,"reverse")==0) {
	}
	else if (strcmp(subcmd,"sort")==0) {
	}
	else if (strcmp(subcmd,"insert_ordered")==0) {
	}
	else if (strcmp(subcmd,"unique")==0) {
	}
	else if (strcmp(subcmd,"max")==0) {
	}
	else if (strcmp(subcmd,"min")==0) {
	}
	else if (strcmp(subcmd,"swap")==0) {
	}
	else if (strcmp(subcmd,"shuffle")==0) {
	}
}

void DoHash() {
	char *subcmd = GetArg();
	if (subcmd == NULL)
		return ;
	if (strcmp(subcmd,"insert")==0) {
	}
	else if (strcmp(subcmd,"replace")==0) {
	}
	else if (strcmp(subcmd,"find")==0) {
	}
	else if (strcmp(subcmd,"delete")==0) {
	}
	else if (strcmp(subcmd,"clear")==0) {
	}
	else if (strcmp(subcmd,"size")==0) {
	}
	else if (strcmp(subcmd,"empty")==0) {
	}
	else if (strcmp(subcmd,"apply")==0) {
	}
}

void DoBitmap() {
	char *subcmd = GetArg();
	if (subcmd == NULL)
		return ;
	if (strcmp(subcmd,"size")==0) {
	}
	else if (strcmp(subcmd,"set")==0) {
	}
	else if (strcmp(subcmd,"mark")==0) {
	}
	else if (strcmp(subcmd,"reset")==0) {
	}
	else if (strcmp(subcmd,"flip")==0) {
	}
	else if (strcmp(subcmd,"test")==0) {
	}
	else if (strcmp(subcmd,"set_all")==0) {
	}
	else if (strcmp(subcmd,"set_multiple")==0) {
	}
	else if (strcmp(subcmd,"count")==0) {
	}
	else if (strcmp(subcmd,"contains")==0) {
	}
	else if (strcmp(subcmd,"any")==0) {
	}
	else if (strcmp(subcmd,"none")==0) {
	}
	else if (strcmp(subcmd,"all")==0) {
	}
	else if (strcmp(subcmd,"scan")==0) {
	}
	else if (strcmp(subcmd,"scan_and_flip")==0) {
	}
	else if (strcmp(subcmd,"dump")==0) {
	}
	else if (strcmp(subcmd,"expand")==0) {
	}
}

struct list * FindList(char *name) {
	int i=0;
	for (i=0; i<list_idx+1; i++) {
		if (strcmp(name, my_list[i].name)==0)
			return &(my_list[i].os_list);
	}
	return NULL;
}

struct hash * FindHash(char *name) {
	int i=0;
	for (i=0; i<hash_idx+1; i++) {
		if (strcmp(name, my_hash[i].name)==0)
			return &(my_hash[i].os_hash);
	}
	return NULL;
}

struct bitmap ** FindBitmap(char *name) {
	int i=0;
	for (i=0; i<bitmap_idx+1; i++) {
		if (strcmp(name, my_bitmap[i].name)==0)
			return &(my_bitmap[i].os_bitmap);
	}
	return NULL;
}

void DumpList(struct list *target) {
	struct list_elem *e;
	if (target == NULL) 
		return ;
	for(e = list_begin(target); e != list_end(target); e = list_next(e)){
		struct list_item *item = list_entry(e, struct list_item, elem);
		printf("%d ", item->data);
	}
	printf("\n");
}

void DumpHash(struct hash *target) {
	if (target == NULL) 
		return ;
}

void DumpBitmap(struct bitmap **target) {
	if (target == NULL) 
		return ;

}
