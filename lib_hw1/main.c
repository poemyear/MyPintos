#include "main.h"

int main (void) {
	char cmd[255]={0, };
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
	for(i=0;i<MAX_COMMAND_LENGTH;i++) {
		scanf("%c",&str[i]);
		if(str[i] == '\n') {
			str[i]='\0';
			break;
		}
	}
}

char* GetArg() {
	return strtok (NULL,  DELIM_ARG);
}

int GetCommand(char *cmd) {
	char * ptr = strtok (cmd, DELIM_COMMAND);
	if (cmd[0]=='\0')
		return -1;
	if (CMD("quit"))
		return QUIT;
	if (CMD("create")) {
		type = GetArg();
		name = GetArg();
		if (!type || !name)
			return -1;
		return CREATE;
	}
	if (CMD("delete")) {
		name = GetArg();
		if (name == NULL)
			return -1;
		return DELETE;
	}
	if (CMD("dumpdata")) {
		name = GetArg();
		if (name == NULL)
			return -1;
		return DUMPDATA;
	}
	subcmd = GetArg();
	name = GetArg();
	arg1 = GetArg();
	arg2 = GetArg();
	arg3 = GetArg();
	arg4 = GetArg();
	if (!subcmd || !name)
		return -1;
	if (CMD("list"))
		return LIST;
	if (CMD("hash"))
		return HASH;
	if (CMD("bitmap"))
		return BITMAP;
	return -1;
}

void DoCreate() {
	int idx=0;
	if (TYPE_IS_LIST) {
		idx = ++list_idx;
		strcpy(my_list[idx].name, name);
		list_init(&(my_list[idx].os_list));
	} else if (TYPE_IS_HASH) {
		idx = ++hash_idx;
		strcpy(my_hash[idx].name, name);
		hash_init(&(my_hash[idx].os_hash), hhf, hlf, NULL);
	} else if (TYPE_IS_BITMAP) {
		idx = ++bitmap_idx;
		strcpy(my_bitmap[idx].name, name);
		my_bitmap[idx].os_bitmap = bitmap_create(ToInt(GetArg()));
	}
}

void DoDelete() {
	struct list *list_ptr = FindList(name);
	if (list_ptr) {
		IterateList(list_ptr, FreeListItem);
	}
	struct hash *hash_ptr = FindHash(name);
	if (hash_ptr) {
		hash_destroy(hash_ptr, haf_free_item);
	}
	struct bitmap *bitmap_ptr = FindBitmap(name);
	if (bitmap_ptr) {
		bitmap_destroy(bitmap_ptr);
	}
}

void DoDumpdata() {
	DumpList(FindList(name));
	DumpHash(FindHash(name));
	DumpBitmap(FindBitmap(name));
}

void DoList() {
	int idx, begin, end;
	struct list * list_ptr, * list_ptr2;

	list_ptr = FindList(name);
	IF_NULL_EXIT(list_ptr);
	if (SUBCMD("insert")) {
		IF_NULL_EXIT(arg1 && arg2);
		idx = ToInt(arg1);
		list_insert(list_index_of(list_ptr, idx), CreateListElem(ToInt(arg2)));
	} else if (SUBCMD("splice")) {
		IF_NULL_EXIT(arg1 && arg2 && arg3 && arg4);
		list_ptr2 = FindList(arg2);
		IF_NULL_EXIT(list_ptr2);
		idx = ToInt(arg1);
		begin = ToInt(arg3);
		end = ToInt(arg4);

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
	} else if (SUBCMD("push_front")) {
		IF_NULL_EXIT(arg1);
		list_push_front(list_ptr, CreateListElem(ToInt(arg1)));
	} else if (SUBCMD("push_back")) {
		IF_NULL_EXIT(arg1);
		list_push_back(list_ptr, CreateListElem(ToInt(arg1)));
	} else if (SUBCMD("remove")) {
		IF_NULL_EXIT(arg1);
		idx = ToInt(arg1);
		if (idx < 0 || idx >= list_size(list_ptr))
			return ;
		list_remove(list_index_of(list_ptr, idx));
	} else if (SUBCMD("pop_front")) {
		list_pop_front(list_ptr);
	} else if (SUBCMD("pop_back")) {
		list_pop_back(list_ptr);
	} else if (SUBCMD("front")) {
		PrintInt(GET_LIST_DATA(list_front(list_ptr)));
	} else if (SUBCMD("back")) {
		PrintInt(GET_LIST_DATA(list_back(list_ptr)));
	} else if (SUBCMD("size")) {
		PrintInt(list_size(list_ptr));
	} else if (SUBCMD("empty")) {
		PrintBool(list_empty(list_ptr));
	} else if (SUBCMD("reverse")) {
		list_reverse(list_ptr);
	} else if (SUBCMD("sort")) {
		list_sort(list_ptr, llf, NULL);
	} else if (SUBCMD("insert_ordered")) {
		IF_NULL_EXIT(arg1);
		list_insert_ordered(list_ptr, CreateListElem(ToInt(arg1)), llf, NULL);
	} else if (SUBCMD("unique")) {
		list_unique(list_ptr, FindList(arg1), llf, NULL);
	} else if (SUBCMD("max")) {
		PrintInt(GET_LIST_DATA(list_max(list_ptr, llf, NULL)));
	} else if (SUBCMD("min")) {
		PrintInt(GET_LIST_DATA(list_min(list_ptr, llf, NULL)));
	} else if (SUBCMD("swap")) {
		IF_NULL_EXIT(arg1 && arg2);
		list_swap(
				list_index_of(list_ptr, ToInt(arg1))
				, list_index_of(list_ptr, ToInt(arg2)));
	} else if (SUBCMD("shuffle")) {
		list_shuffle(list_ptr);
	}
}

void DoHash() {
	struct hash *hash_ptr;
	struct hash_elem *elem_ptr;

	hash_ptr = FindHash(name);
	IF_NULL_EXIT(hash_ptr);
	if (SUBCMD("insert")) {
		IF_NULL_EXIT(arg1);
		hash_insert(hash_ptr, CreateHashElem(ToInt(arg1)));
	} else if (SUBCMD("replace")) {
		IF_NULL_EXIT(arg1);
		hash_replace(hash_ptr, CreateHashElem(ToInt(arg1)));
	} else if (SUBCMD("find")) {
		IF_NULL_EXIT(arg1);
		elem_ptr = hash_find(hash_ptr, CreateHashElem(ToInt(arg1)));
		IF_NULL_EXIT(elem_ptr);
		PrintInt(GET_HASH_DATA(elem_ptr));
	} else if (SUBCMD("delete")) {
		IF_NULL_EXIT(arg1);
		hash_delete(hash_ptr, CreateHashElem(ToInt(arg1)));
	} else if (SUBCMD("clear")) {
		hash_clear(hash_ptr, haf);
	} else if (SUBCMD("size")) {
		PrintInt(hash_size(hash_ptr));
	} else if (SUBCMD("empty")) {
		PrintBool(hash_empty(hash_ptr));
	} else if (SUBCMD("apply")) {
		IF_NULL_EXIT(arg1);
		if (CMP(arg1, "square")) {
			hash_apply(hash_ptr, haf_square);
		} else if (CMP(arg1, "triple")) {
			hash_apply(hash_ptr, haf_triple);
		} else {
			hash_apply(hash_ptr, haf);
		}
	}
}

void DoBitmap() {
	struct bitmap *bitmap_ptr;

	bitmap_ptr = FindBitmap(name);
	IF_NULL_EXIT(bitmap_ptr);
	if (SUBCMD("size")) {
		PrintInt(bitmap_size(bitmap_ptr));
	} else if (SUBCMD("set")) {
		IF_NULL_EXIT(arg1 && arg2);
		bitmap_set(bitmap_ptr, ToInt(arg1), ToBool(arg2));
	} else if (SUBCMD("mark")) {
		IF_NULL_EXIT(arg1);
		bitmap_mark(bitmap_ptr, ToInt(arg1));
	} else if (SUBCMD("reset")) {
		IF_NULL_EXIT(arg1);
		bitmap_reset(bitmap_ptr, ToInt(arg1));
	} else if (SUBCMD("flip")) {
		IF_NULL_EXIT(arg1);
		bitmap_flip(bitmap_ptr, ToInt(arg1));
	} else if (SUBCMD("test")) {
		IF_NULL_EXIT(arg1);
		PrintBool(bitmap_test(bitmap_ptr, ToInt(arg1)));
	} else if (SUBCMD("set_all")) {
		IF_NULL_EXIT(arg1);
		bitmap_set_all(bitmap_ptr, ToBool(arg1));
	} else if (SUBCMD("set_multiple")) {
		IF_NULL_EXIT(arg1 && arg2 && arg3);
		bitmap_set_multiple(bitmap_ptr, ToInt(arg1), ToInt(arg2), ToBool(arg3));
	} else if (SUBCMD("count")) {
		IF_NULL_EXIT(arg1 && arg2 && arg3);
		PrintSizeT(bitmap_count(bitmap_ptr, ToInt(arg1), ToInt(arg2), ToBool(arg3)));
	} else if (SUBCMD("contains")) {
		IF_NULL_EXIT(arg1 && arg2 && arg3);
		PrintBool(bitmap_contains(bitmap_ptr, ToInt(arg1), ToInt(arg2), ToBool(arg3)));
	} else if (SUBCMD("any")) {
		IF_NULL_EXIT(arg1 && arg2);
		PrintBool(bitmap_any(bitmap_ptr, ToInt(arg1), ToInt(arg2)));
	} else if (SUBCMD("none")) {
		IF_NULL_EXIT(arg1 && arg2);
		PrintBool(bitmap_none(bitmap_ptr, ToInt(arg1), ToInt(arg2)));
	} else if (SUBCMD("all")) {
		IF_NULL_EXIT(arg1 && arg2);
		PrintBool(bitmap_all(bitmap_ptr, ToInt(arg1), ToInt(arg2)));
	} else if (SUBCMD("scan")) {
		IF_NULL_EXIT(arg1 && arg2 && arg3);
		PrintSizeT(bitmap_scan(bitmap_ptr, ToInt(arg1), ToInt(arg2), ToBool(arg3)));
	} else if (SUBCMD("scan_and_flip")) {
		IF_NULL_EXIT(arg1 && arg2 && arg3);
		PrintSizeT(bitmap_scan_and_flip(bitmap_ptr, ToInt(arg1), ToInt(arg2), ToBool(arg3)));
	} else if (SUBCMD("dump")) {
		bitmap_dump(bitmap_ptr);
	} else if (SUBCMD("expand")) {
		IF_NULL_EXIT(arg1);
		bitmap_expand(bitmap_ptr, ToInt(arg1));
	}
}

struct list * FindList(char *name) {
	int i=0;
	IF_NULL_EXIT(name);
	for (i=0; i<list_idx+1; i++) {
		if (CMP(name, my_list[i].name))
			return &(my_list[i].os_list);
	}
	return NULL;
}

struct hash * FindHash(char *name) {
	int i=0;
	IF_NULL_EXIT(name);
	for (i=0; i<hash_idx+1; i++) {
		if (CMP(name, my_hash[i].name))
			return &(my_hash[i].os_hash);
	}
	return NULL;
}

struct bitmap * FindBitmap(char *name) {
	int i=0;
	IF_NULL_EXIT(name);
	for (i=0; i<bitmap_idx+1; i++) {
		if (CMP(name, my_bitmap[i].name))
			return (my_bitmap[i].os_bitmap);
	}
	return NULL;
}

void DumpList(struct list *target) {
	IF_NULL_EXIT(target);
	IterateList(target, PrintListItem);
	printf("\n");
}

void DumpHash(struct hash *target) {
	IF_NULL_EXIT(target);
	struct hash_iterator i;
	hash_first(&i, target);
	while (hash_next(&i)) {
		printf("%d ", GET_HASH_DATA(hash_cur(&i)));
	}
	printf("\n");
}

void DumpBitmap(struct bitmap *target) {
	IF_NULL_EXIT(target);
	int  i=0;
	for (i=0; i < bitmap_size(target); i++) {
		printf("%d", bitmap_test(target, i)?1:0);
	}
	printf("\n");
}

void IterateList(struct list *target, list_iterate_func *func) {
	struct list_elem *e;
	for(e = list_begin(target); e != list_end(target); e = list_next(e)){
		func(e);
	}
}

void PrintListItem(struct list_elem *e) {
	printf("%d ", GET_LIST_DATA(e));
}

void FreeListItem(struct list_elem *e) {
	free(GET_LIST_ITEM(e));
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

struct hash_elem * CreateHashElem(int data) {
	struct hash_item *new_item = (struct hash_item*)malloc(sizeof(struct hash_item));
	new_item->data = data;
	return &(new_item->elem);
}

unsigned hhf (const struct hash_elem *e, void *aux) {
	return hash_int(GET_HASH_DATA(e));
}

bool hlf (const struct hash_elem *a, const struct hash_elem *b, void *aux) {
	if (GET_HASH_DATA(a) < GET_HASH_DATA(b))
		return true;
	return false;
}

void haf (struct hash_elem *e, void *aux) {
}

void haf_square (struct hash_elem *e, void *aux) {
	int *data = &(GET_HASH_DATA(e));
	*data = (*data) * (*data);
}

void haf_triple (struct hash_elem *e, void *aux) {
	int *data = &(GET_HASH_DATA(e));
	*data = (*data) * (*data) * (*data);
}
void haf_free_item (struct hash_elem *e, void *aux) {
	free(GET_HASH_ITEM(e));
}

void PrintInt(int d) {
	printf("%d\n", d);
}
void PrintBool(bool bl) {
	if (bl)
		printf("true\n");
	else
		printf("false\n");
}

void PrintSizeT(size_t st) {
	if (st == SIZE_MAX)
		printf("4294967295\n");
	else
		printf("%zu\n", st);
}

int ToInt(char *str) {
	int num;
	sscanf(str, "%d", &num);
	return num;
}

bool ToBool(char *str) {
	if (CMP(str, "true"))
		return true;
	return false;
}
