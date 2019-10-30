#include<stdio.h>

int fib(int i);

void main()
{
	int i=0;
	for(i = 0; i < 200; i++)
	{
		printf("%d\n",fib(i));
	}
}

int fib(int i)
{
	if(i==0)
	{
		return 0;
	}
	if(i==1)
	{
		return 1;
	}
	return fib(i-1)+fib(i-2);
}
