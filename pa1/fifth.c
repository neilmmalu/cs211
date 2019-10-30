#include "fifth.h"

int main(int argc , char *argv[])
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
	
	int row = 0, col = 0;
	if(fscanf(fp, "%d %d\n", &row, &col) == 2)
	{
		int **a = (int **)malloc(row * sizeof(int));
		int **b = (int **)malloc(row * sizeof(int));
		
		int i, j;
		for(i = 0; i < row; i++)
		{
			a[i] = (int *)malloc(col * sizeof(int));
			b[i] = (int *)malloc(col * sizeof(int));
		}
		
		
		for(i = 0; i < row; i++)
		{
			for(j = 0; j < col; j++)
			{
				fscanf(fp, "%d", &a[i][j]);
			}
			fscanf(fp, "\n");
		}

		int sum = 0;
		
		for(i = 0; i < row; i++)
		{
			for(j = 0; j < col; j++)
			{
				fscanf(fp, "%d", &sum);
				sum = sum + a[i][j];
				a[i][j] = sum;
			}
			fscanf(fp, "\n");
		}

		for(i = 0; i < row; i++)
		{
			for(j = 0; j < col; j++)
			{
				printf("%d\t", a[i][j]);
			}
			printf("\n");
		}
		return 0;
	}
	else
	{
		return 0;
	}
}
