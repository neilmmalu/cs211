#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

struct node {
	long data;
	struct node *next;	
}node;

int count = 0;

struct node *hashtable[1000];

int checkDuplicate(long address);

void addToTable(long address);
