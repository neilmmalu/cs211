#include "fourth.h"

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

	int hashtable[1000];
	int i;
	for(i = 0; i < 1000; i++)
	{
		hashtable[i] = NULL;
	}
	
	int n;
	char c;

	while(fscanf(fp, "%c %d\n", &c, &n) == 2)
	{
		if(c == 'i')
		{
			add(hashtable, n);
		}
		else if(c == 's')
		{
			if(search(hashtable, n) == 1)
			{
				printf("present\n");
			}
			else
			{
				printf("absent\n");
			}
		}
		else
		{
			printf("error\n");
		}
	}
	return 0;
}

void add(int arr[], int n)
{
	if(n < 0)
	{
		n = -n;
	}
	int index = n % 1000;
	if(search(arr, n) == 1)
	{
		printf("duplicate\n");
		return;
	}
	if(arr[index] == NULL)
	{
		arr[index] = n;
		printf("inserted\n");
		return;
	}
	else
	{
		while(arr[index]!= NULL)
		{
			index++;
			if(index == 1000)
			{
				index = 0;
			}	
		}
		arr[index] = n;
	}
}

int search(int arr[], int n)
{
	if(n < 0)
	{
		n = -n;
	}
	int index = n % 1000;
	int flag = 0;
	int temp = index;
	if(arr[index] == NULL)
	{
		return 0;
	}
	if(arr[index] == n)
	{
		return 1;
	}
	while(arr[index] != n)
	{
		index++;

		if(flag == 1 && index >= temp)
		{
			return 0;
		}
		if(index == 1000)
		{
			index = 0;
			flag = 1;
		}
	}
	return 1;
}
