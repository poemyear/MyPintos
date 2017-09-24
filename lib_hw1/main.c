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

int ToInt(char *str) {
	int num;
	sscanf(str, "%d", &num);
	return num;
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
	int idx, begin, end, num, cnt, i;
	char *subcmd = GetArg();
	char *arg1 = GetArg(), *arg2 = GetArg(), *arg3 = GetArg(), *arg4 = GetArg(), *arg5 = GetArg();
	struct list_elem *elem, *next;
	struct list * list_ptr, * list_ptr2;

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
		if (arg2 == NULL || arg3 == NULL)
			return ;
		idx = ToInt(arg2);
		num = ToInt(arg3);
		list_insert(list_index_of(list_ptr, idx), CreateListElem(num));
	}
	else if (strcmp(subcmd,"splice")==0) {
		if (arg2 == NULL || arg3 == NULL || arg4 == NULL || arg5 == NULL)
			return ;
		list_ptr2 = FindList(arg3);
		if (list_ptr2 == NULL)
			return ;
		idx = ToInt(arg2);
		begin = ToInt(arg4);
		end = ToInt(arg5);

		if (idx < 0 || idx >= list_size(list_ptr))
			return ;
		if (begin < 0 || begin >= list_size(list_ptr2))
			return ;
		if (end < 0 || end >= list_size(list_ptr2))
			return ;

		list_splice(
				list_index_of(list_ptr, idx)
				, list_index_of(list_ptr2, begin)
				, list_index_of(list_ptr2, end)
				);
	}
	else if (strcmp(subcmd,"push_front")==0) {
		if (arg2 == NULL)
			return ;
		list_push_front(list_ptr, CreateListElem(ToInt(arg2)));
	}
	else if (strcmp(subcmd,"push_back")==0) {
		if (arg2 == NULL)
			return ;
		list_push_back(list_ptr, CreateListElem(ToInt(arg2)));
	}
	else if (strcmp(subcmd,"remove")==0) {
		if (arg2 == NULL)
			return ;
		idx = ToInt(arg2);
		if (idx < 0 || idx >= list_size(list_ptr)) {
			printf("[remove index is not valid!!]\n");
			return ;
		}
		list_remove(list_index_of(list_ptr, idx));
	}
	else if (strcmp(subcmd,"pop_front")==0) {
		list_pop_front(list_ptr);
	}
	else if (strcmp(subcmd,"pop_back")==0) {
		list_pop_back(list_ptr);
	}
	else if (strcmp(subcmd,"front")==0) {
		elem = list_front(list_ptr);
		printf("%d\n", GET_LIST_DATA(elem));
	}
	else if (strcmp(subcmd,"back")==0) {
		elem = list_back(list_ptr);
		printf("%d\n", GET_LIST_DATA(elem));
	}
	else if (strcmp(subcmd,"size")==0) {
		printf("%d\n", list_size(list_ptr));
	}
	else if (strcmp(subcmd,"empty")==0) {
		if (list_empty(list_ptr))
			printf("true\n");
		else
			printf("false\n");
	}
	else if (strcmp(subcmd,"reverse")==0) {
		list_reverse(list_ptr);
	}
	else if (strcmp(subcmd,"sort")==0) {
		list_sort(list_ptr, llf, NULL);
	}
	else if (strcmp(subcmd,"insert_ordered")==0) {
		if (arg2 == NULL)
			return ;
		list_insert_ordered(list_ptr, CreateListElem(ToInt(arg2)), llf, NULL);
	}
	else if (strcmp(subcmd,"unique")==0) {
		list_unique(list_ptr, FindList(arg2), llf, NULL);
	}
	else if (strcmp(subcmd,"max")==0) {
		printf("%d\n", GET_LIST_DATA(list_max(list_ptr, llf, NULL)));
	}
	else if (strcmp(subcmd,"min")==0) {
		printf("%d\n", GET_LIST_DATA(list_min(list_ptr, llf, NULL)));
	}
	else if (strcmp(subcmd,"swap")==0) {
		if (arg2 == NULL || arg3 == NULL)
			return ;
		list_swap(
				list_index_of(list_ptr, ToInt(arg2))
				, list_index_of(list_ptr, ToInt(arg3)));
	}
	else if (strcmp(subcmd,"shuffle")==0) {
		list_shuffle(list_ptr);
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
	if (name == NULL)
		return NULL;
	for (i=0; i<list_idx+1; i++) {
		if (strcmp(name, my_list[i].name)==0)
			return &(my_list[i].os_list);
	}
	printf("Np such list!\n");
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
		printf("%d ", GET_LIST_DATA(e));
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

struct list_elem * CreateListElem(int data) {
	struct list_item *new_item = (struct list_item*)malloc(sizeof(struct list_item));
	new_item->data = data;
	return &(new_item->elem);
}

bool llf (const struct list_elem *a, const struct list_elem *b, void *aux) {
	if (GET_LIST_DATA(a) >= GET_LIST_DATA(b) )return false;
	else return true;
}
