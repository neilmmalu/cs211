#include "third.h"

int main(int argc, char * argv[])
{
	char c;
	int n;
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

	struct node *head = malloc(sizeof(struct node));
	head = NULL;
	while(fscanf(fp,"%c %d\n", &c, &n) == 2)
	{
		if(c == 'i')
		{	
			head = addNode(head, n);
		}
		else if(c == 'd')
		{
			head = deleteNode(head, n);
		}	
		else
		{
			return 0;
		}
	}
	
	fclose(fp);
	if(head->next == NULL && head->data == 0)
	{
		return 0;
	}
	head = head->next;
	printList(head);
	free(head);
	return 0;
	
}

void printList(struct node *head)
{
	for(head = head; head != NULL; head = head->next)
	{
		printf("%d ", head->data);
		
		if(head->next != NULL)
		{
			printf("\t");
		}
	}
	printf("\n");
}

struct node * addNode(struct node * head, int n)
{
	if(head == NULL)
	{
		head->data = n;
		head->next = NULL;
		return head;
	}

	struct node *ptr = head;
	if(head->data == n)
	{
		return head;
	}
	if(head->data > n)
	{
		struct node *new = malloc(sizeof(struct node));
		new->data = n;
		new->next = head;
		head = new;
		return head;
	}

	while(ptr->next != NULL)
	{	
		if(ptr->next->data == n)
		{
			return head;
		}
		if(ptr->next->data > n)
		{
			struct node *new = malloc(sizeof(struct node));
			new->data = n;
			new->next = ptr->next;
			ptr->next = new;
			return head;
		}
		ptr = ptr->next;
	}
	struct node *new = malloc(sizeof(struct node));
	ptr->next = new;
	new->data = n;
	new->next = NULL; 
	/*
	struct node *new = malloc(sizeof(struct node));
	new->data = n;
	new->next = NULL;
	ptr->next = new;
	*/
	return head;
} 

struct node * deleteNode(struct node *head, int n)
{
	if(head == NULL)
	{
		return head;
	}

	if(head->next == NULL && head->data == 0)
	{
		return head;
	}

	if(head->next == NULL && head->data == n)
	{
		head->data = 0;
		return head;
	}
	if(head->data == n)
	{
		return head->next;
	}

	struct node *ptr = head;
	while(ptr->next != NULL)
	{
		if(ptr->next->data == n)
		{
			ptr->next = ptr->next->next;
			return head;
		}
		ptr = ptr->next;
	}
	return head;
}
