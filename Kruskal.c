#include<stdio.h>
void InsertionSort(int c[][3])
{
	int i=1, j, a, b, key;
	printf("\n");
	while(c[i][0]!=0)
	{
		a=c[i][0];
		b=c[i][1];
		key=c[i][2];
		for(j=i-1;j>=0;j--)
		{
			if(c[j][2]>key)
			{
		                c[j+1][2]=c[j][2];
		                c[j][2]=key;
				c[j+1][1]=c[j][1];
				c[j][1]=b;
				c[j+1][0]=c[j][0];
				c[j][0]=a;
		        }
			else
				break;
		}
		i++;
	}
}
int check(int track[], int i)
{
	if(track[i]==-1) 
		return i;
	return check(track, track[i]);
}
void Kruskal(int order[][3], int track[], int N)
{
	int i=0, j=0, x, y;
	while(order[i][0]!=0)
	{
		j=0;
		x=order[i][0]-1;
		y=order[i][1]-1;
		if(check(track, x)==check(track, y))
			order[i][2]=0;
		else
			track[check(track, x)]=y;
		i++;			
	}
}
void main()
{
	int i, j, k=0, N, count=0, sum=0;
	printf("Enter the number of vertices:- ");
	scanf("%d", &N);
	for(i=N-1;i>0;i--)
		count+=i;
	int graph[N][N], order[count][3], track[N];
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
			graph[i][j]=0;
		track[i]=-1;
	}
	for(i=0;i<count;i++)
		order[i][0]=0;
	for(i=0;i<N;i++)
	{
		while(1)
		{
			printf("Enter link for vertex %d(-1 to end):- ", i+1);
			scanf("%d", &j);
			if(j==-1)
				break;
			if(i+1==j)
			{
				printf("Self Loop Not Allowed\n");
				continue;
			}
			if(graph[j-1][i]!=0)
			{
				printf("Edge Already Exists\n");
				continue;
			}
			printf("Enter distance from %d:- ", i+1);
			scanf("%d", &graph[i][j-1]);
			graph[j-1][i]=graph[i][j-1];
			order[k][0]=i+1;
			order[k][1]=j;
			order[k][2]=graph[j-1][i];
			k++;
		}
		printf("\n");
	}
	InsertionSort(order);
	Kruskal(order, track, N);
	printf("MST is:- \n");
	i=0;
	while(order[i][0]!=0)
	{
		if(order[i][2]!=0)
		{
			printf("%d\t%d\t%d\n", order[i][0], order[i][1], order[i][2]);
			sum+=order[i][2];
		}
		i++;
	}
	printf("\nTotal cost is %d\n", sum);
}
