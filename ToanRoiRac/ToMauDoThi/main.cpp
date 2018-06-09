#include<stdio.h>
#include<stdlib.h>

// Lay du lieu tu file
int ** InputFile(int *N, int *M)
{
	int **A;
	FILE* fi = fopen("dothi.txt", "r");
	fscanf(fi, "%d", N);
	fscanf(fi, "%d", M);
	A = (int**)malloc(2 * sizeof(int));
	for (int i=0; i<=1; i++)
		A[i] = (int*)malloc((*M)*sizeof(int));
	for (int j = 0; j<*M; j++)
		for (int i = 0; i <= 1; i++)
		{
			fscanf(fi, "%d", &A[i][j]);
		}
	fclose(fi);
	return A;
}
// Tinh bac cac dinh
int* Deg(int ** A,int m,int n)
{
	int* deg = (int*)calloc(n+1,sizeof(int));
	if(m==0) return deg;
	for (int j=0;j<m;j++)
	{
		deg[A[0][j]] ++;
		deg[A[1][j]] ++;
	}
	return deg;
}
// Tim bac Max
int degMax(int *deg,int N)
{
	int max=0;
	for(int i=1;i<=N;i++)
	{
		if(deg[i]>max) max=deg[i];
	}
	return max;
}
// Tim dinh co bac Max -1
int Find(int *deg,int N)
{
	int max=0,find=0;
	for(int i=1;i<=N;i++)
	{
		if(deg[i]>max) max=deg[i];
	}
	if(max==0) return find;
	for(int i=1;i<=N;i++)
	{
		if(deg[i]==max-1)
		{
			find=i;
			break;
		}
	}
	return find;
}

//kiem tra tinh lien thông
int checkConnext(int **a,int m,int n)
{

	if(m==0) return 0;
	int *check=(int*)calloc(n+1,sizeof(int));

	check[a[0][0]]=1;
	int dem=1;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(check[a[0][j]]==1 && check[a[1][j]]==0)
			{
				check[a[1][j]]=1;
				dem++;
			}
			if(check[a[0][j]]==0 && check[a[1][j]]==1)
			{
				check[a[0][j]]=1;
				dem++;
			}
		}
		if(dem==n) return 1;
	}
	free(check);
	return 0;
}
//kiem tra tinh chinh quy
int checkRegular(int *deg,int n)
{
	for(int i=1;i<n;i++)
	{
		if(deg[i]!=deg[i+1])
			return 0;
	}
	return 1;
}
// Sap xep cho truong hop lien thong và khong chinh quy
int* sortGraph1(int **b,int finddeg,int n,int m)
{
	int* Sort =(int*)malloc(n*sizeof(int));

	Sort[0]=finddeg;
	int pri=1,up =0;

	for(int i=0;;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(Sort[up]==b[0][j])
			{
				Sort[pri]=b[1][j];
				pri++;
			}
			if(Sort[up]==b[1][j])
			{
				Sort[pri]=b[0][j];
				pri++;
			}
		}

		for(int j=0;j<m;j++)
		{
			for(int k=0;k<=pri;k++)
			{
				if(b[0][j]==Sort[k])
				{
					for(int k=0;k<=pri;k++)
					{
						if(b[1][j]==Sort[k])
						{
							b[0][j]=b[1][j]=0;
						}
					}
				}
			}
		}
		if(pri==n)
		{
			return Sort;
		}
		up++;
	}
}
// Sap xep cho truong hop con lai
int *sortGraph2(int *deg,int degmax,int n)
{
	int tmp=degmax,pri=0;
	int* Sort = (int*)malloc(n*sizeof(int));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(deg[j]==tmp)
			{
				Sort[pri]=j;
				pri++;
				deg[j]=-1;
			}
		}
		if(tmp!=0)
			tmp--;
	}
	return Sort;
}
// To mau do thi
int* coloringGraph(int **a,int *sort,int n,int m,int degmax)
{
	int *color = (int*)calloc(n+1,sizeof(int));
	int *tmpcolor = (int*)calloc(degmax+1,sizeof(int));
	color[sort[0]]=1;
	int pri=1;
	do
	{
		int d=0;
		sort[pri];
		for(int i=1;i<=n;i++)
		{
			if(color[i]!=0)
			{
				for(int j=0;j<m;j++)
				{
					if((a[0][j]==i && a[1][j]==sort[pri])||(a[0][j]==sort[pri] && a[1][j]==i))
					{
						tmpcolor[d]=color[i];
						d++;
					}
				}
			}
		}
		int x=1;
		int i;
		do
		{
			i=0;
			color[sort[pri]]=x;
			for(int j=0;j<d;j++)
			{
				if(x!=tmpcolor[j])
				{
					i++;
				}
				else
				{
					x++;
					break;
				}
			}
		} while(i!=d);
		pri++;
	} while(pri!=n);
	free(tmpcolor);
	return color;
}
// Xuat file
void Output(int *color,int **a,int n,int m)
{
	FILE* fo= fopen("dothitomau.dot","w");
	fprintf(fo,"graph dothi\n {");
	for(int i=1;i<=n;i++)
	{
		fprintf(fo,"\n\t%d",i);
		switch(color[i])
		{
		case 1:
		{
			fprintf(fo,"[fillcolor=red, style=filled];");
			break;
		}
		case 2:
		{
			fprintf(fo,"[fillcolor=green, style=filled];");
			break;
		}
		case 3:
		{
			fprintf(fo,"[fillcolor=blue, style=filled];");
			break;
		}
		case 4:
		{
			fprintf(fo,"[fillcolor=yellow, style=filled];");
			break;
		}
		case 5:
		{
			fprintf(fo,"[fillcolor=gray, style=filled];");
			break;
		}
		case 6:
		{
			fprintf(fo,"[fillcolor=orangered, style=filled];");
			break;
		}
		case 7:
		{
			fprintf(fo,"[fillcolor=brown, style=filled];");
			break;
		}
		case 8:
		{
			fprintf(fo,"[fillcolor=pink, style=filled];");
			break;
		}
		case 9:
		{
			fprintf(fo,"[fillcolor=skyblue, style=filled];");
			break;
		}
		case 10:
		{
			fprintf(fo,"[fillcolor=greenyellow, style=filled];");
			break;
		}
		case 11:
		{
			fprintf(fo,"[fillcolor=khaki3, style=filled];");
			break;
		}
		case 12:
		{
			fprintf(fo,"[fillcolor=purple4, style=filled];");
			break;
		}
		case 13:
		{
			fprintf(fo,"[fillcolor=olivedrab, style=filled];");
			break;
		}
		case 14:
		{
			fprintf(fo,"[fillcolor=darkgreen, style=filled];");
			break;
		}
		case 15:
		{
			fprintf(fo,"[fillcolor=orange2, style=filled];");
			break;
		}
		case 16:
		{
			fprintf(fo,"[fillcolor=indianred1, style=filled];");
			break;
		}
		case 17:
		{
			fprintf(fo,"[fillcolor=springgreen, style=filled];");
			break;
		}
		case 18:
		{
			fprintf(fo,"[fillcolor=palegreen4, style=filled];");
			break;
		}
		case 19:
		{
			fprintf(fo,"[fillcolor=cyan4, style=filled];");
			break;
		}
		case 20:
		{
			fprintf(fo,"[fillcolor=violet, style=filled];");
			break;
		}
		}
	}
	for(int i=0;i<m;i++)
	{
		fprintf(fo,"\n\t%d--%d",a[0][i],a[1][i]);
	}
	fprintf(fo,"\n}");
	fclose(fo);
}
int main()
{
	int n, m,**a,**b,*deg,*color,degmax,*sort,finddeg;
	a= InputFile(&n, &m);
	if(n==0)
	{
		Output(color,a,n,m);
		return 0;
	}
	b= InputFile(&n, &m);
	//Bac cac dinh
	deg=Deg(a,m,n);
	// Bac max
	degmax=degMax(deg,n);
	// Bac max -1
	finddeg=Find(deg,n);
	// To mau voi truong hop lien thong

	if(checkConnext(a,m,n))
	{
		if(!checkRegular(deg,n)) // khong chinh quy
		{
			// sap xep
			sort=sortGraph1(b,finddeg,n,m);
			// To mau do thi
			color=coloringGraph(a,sort,n,m,degmax);
			// Xuat file
			Output(color,a,n,m);
		}
		else   // chinh quy
		{
			// sap xep
			finddeg=1;
			sort=sortGraph1(b,finddeg,n,m);
			// To mau do thi
			color=coloringGraph(a,sort,n,m,degmax);
			// Xuat file
			Output(color,a,n,m);
		}
	}
	// To mau voi cac truong hop con lai
	else
	{
		// sap xep
		sort=sortGraph2(deg,degmax,n);
		// To mau do thi
		color=coloringGraph(a,sort,n,m,degmax);
		// Xuat file
		Output(color,a,n,m);
	}
	free(a);
	free(b);
	free(deg);
	free(color);
	free(sort);
	return 0;
}
