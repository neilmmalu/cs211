#include<stdio.h>

int fib(int i);

int main(){
	int i;
	unsigned long long x[200];
	x[0] = 0;
	x[1] = 1;
	for(i = 2; i < 200; i++)
	{
		x[i] = x[i-1]+x[i-2];
		printf("%lli\n", x[i]);
	}
}

int fib(int i){
	if(i == 0)
	{
		return 0;
	}
	if(i == 1)
	{
		return 1;
	}
	return fib(i - 1) + fib(i - 2);
}
