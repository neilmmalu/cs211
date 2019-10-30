#include "second.h"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("error\n");
		return 0;
	}	

	int a = atoi(argv[1]);
	
	if(a == 1)
	{
		printf("no\n");
		return 0;
	}

	if(a == 2)
	{
		printf("yes\n");
		return 0;
	}

	int i = 2;
	for(i = 2; i <= a; i++)
	{
	 	if(a == i)
		{
			printf("yes\n");
			return 0;
		}
		if(a % i == 0)
		{
			printf("no\n");
			return 0;
		}
	}
	return 0;
}
