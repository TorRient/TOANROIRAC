#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void pruferCode(int n,int **a)
{
	int x=1,min=1,i,nut,stop=0;
	int *phantu;
	phantu=(int*)calloc(n+1,sizeof(int));
	for (int j=0;j<n;j++)
	{
		phantu[a[0][j]] ++;
		phantu[a[1][j]] ++;
	}
	while(phantu[min]!=1) min++;
	x=min;
	while(phantu[x]==1 && stop < n-1)
	{
		for(i=0;i<n;i++)
		{
			if(a[1][i]==x && phantu[a[0][i]]!=0)
			{
				stop++;
				printf("%d ",a[0][i]);
				nut=a[0][i];
				phantu[x]--;
				phantu[a[0][i]]--;
				break;
			}
			else
				if(a[0][i]==x && phantu[a[1][i]]!=0)
				{
					stop++;
					printf("%d ",a[1][i]);
					nut=a[1][i];
					phantu[x]--;
					phantu[a[1][i]]--;
					break;
				}
		}
		if(phantu[nut]==1 && min>nut && nut !=0) x=nut;
		else
		{
			while(phantu[min]!=1) min++;
			x=min;
		}
	}
	free(phantu);
}
int main()
{
	int n;
    clock_t start, end;
    double time_use;
    start = clock();
	FILE *fo=fopen("TREEOUT.txt","r");
	fscanf(fo,"%d",&n);
	int **a;
	a=(int**)malloc(2*sizeof(int));
	for(int i=0;i<2;i++)
	{
		a[i]=(int*)malloc(n*sizeof(int));
	}
	for(int i=0;i<n;i++)
	{
		fscanf(fo,"%d %d",&a[0][i],&a[1][i]);
	}
	fclose(fo);
	pruferCode(n,a);
	end = clock();
	time_use = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\n\n\n\nPruferCode take %f seconds", time_use);
	free(a);
	return 0;
}
