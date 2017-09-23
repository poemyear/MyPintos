#include "main.h"

int main (void) {
	char cmd[255]={0, };
	char *ptr;
	int i;
	bool isQuit=false;

	while(!isQuit){
		get_string(cmd);
		switch (get_command(cmd)) {
			case QUIT:
				isQuit=true;
			break;
			case CREATE:
			printf("create\n");
			break;
			case DELETE:
			printf("delete\n");
			break;
			case DUMPDATA:
			printf("dumpadata\n");
			break;
			case LIST:
			printf("list\n");
			break;
			case HASH:
			printf("hash\n");
			break;
			case BITMAP:
			printf("bitmap\n");
			break;
			default:
			break;
		}
	}
	return 0;
}

void get_string(char *str)
{	
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

int get_command(char *cmd) 
{
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
