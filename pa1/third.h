#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node * next;
} node;

struct node * addNode(struct node *new, int n);
struct node * deleteNode(struct node *head, int n);
void printList(struct node *head);
