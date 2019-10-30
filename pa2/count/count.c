#include "count.h"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("error\n");
		return 0;
	}

	FILE *fp = fopen(argv[1], "r");

	if(!fp)
	{
		printf("error\n");
		return 0;
	}
	
	int i;
	for(i = 0; i < 1000; i++)
	{
		hashtable[i] = malloc(sizeof(struct node));
		hashtable[i]->data = NULL;
		hashtable[i]->next = NULL;
	}
	
	long address;
	char *line = malloc(80*sizeof(char));

	while(fscanf(fp, "0x%lx\n", &address) == 1)
	{
		if(checkDuplicate(address) == 1)
		{
			continue;
		}	
		else
		{	
			addToTable(address);
		}
	}		 	
	
	printf("%d\n", count);
	return 0;
}



int checkDuplicate(long address)
{
	int i = 0;
	int temp = address%1000;
	if(hashtable[temp] == NULL)
	{
		return 0;
	}
	struct node *ptr = hashtable[temp];
	while(ptr != NULL)
	{
		if(ptr->data == address)
		{
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}



void addToTable(long address)
{
	int temp = address%1000;
	struct node *new = malloc(sizeof(struct node));
	new->data = address;
	new->next = hashtable[temp];
	hashtable[temp] = new;
	count++;
}
