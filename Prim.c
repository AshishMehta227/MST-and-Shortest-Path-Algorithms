#include<stdio.h>
#include<stdlib.h>
struct node
{
	int value, dist, x;
	struct node *ptr;
};
void display(struct node nodelist[], int N)
{
	int i;
	printf("nodes in the graph are:- \n");
	for(i=0;i<N;i++)
		printf("%d --- %d\n", i+1, nodelist[i].value);
}
void show(struct node nodelist[], int N)
{
	struct node *temp;
	for(int i=0;i<N;i++)
	{
		temp=nodelist[i].ptr;
		printf("\n%d %d %d ---> ", nodelist[i].value, nodelist[i].dist, nodelist[i].x);
		while(temp!=NULL)
		{
			printf(" %d %d %d\t", temp->value, temp->dist, temp->x);
			temp=temp->ptr;
		}
	}
}
int getnodeindex(int v, struct node nodelist[], int N)
{
	for(int i=0;i<N;i++)
    	{
        	if(v==nodelist[i].value)
			return i;
	}
}
void initialize(struct node nodelist[], int N)
{
	for(int i=0;i<N;i++)
	{
		nodelist[i].value=i+1;
		nodelist[i].dist=RAND_MAX;
		nodelist[i].x=-1;
		nodelist[i].ptr=NULL;
	}
}
void insertnode(struct node *head, struct node nodelist[], int v, int N)
{
	int i=0, d;
	struct node *newnode1, *newnode2, *temp=head;
	newnode1=(struct node *)malloc(sizeof(struct node));	
	newnode2=(struct node *)malloc(sizeof(struct node));
	if(newnode1==NULL || newnode2==NULL)
	{
		printf("MEMORY ALLOCATION FAILED\n");
		exit(-1);
	}
	newnode1->value=v;
	newnode1->x=-1;
	printf("Enter Distance from %d:- ", head->value);
	scanf("%d", &newnode1->dist);
	newnode1->ptr=head->ptr;
	head->ptr=newnode1;
	newnode2->value=head->value;
	newnode2->x=-1;
	newnode2->dist=newnode1->dist;
	i=getnodeindex(v, nodelist, N);
	temp=&nodelist[i];
	newnode2->ptr=temp->ptr;
	temp->ptr=newnode2;
	return ;
}
int ispresent(struct node nodelist[], int val, int N)
{
	int i;
	for(i=0;i<N;i++)
	{
		if(val==nodelist[i].value)
			return 1;
	}
	return 0;
}
int exists(struct node *temp, int v)
{
	while(temp!=NULL)
	{
	        if(v==temp->value)
			return 1;
	        else
			temp=temp->ptr;
	}
	return 0;
}

void createlink(struct node nodelist[], int N)
{
	int i, v;
	printf("\n");
	for(i=0;i<N;i++)
	{	
		while(1)
		{
			printf("Enter link for node %d(-1 to end):- ", nodelist[i].value);	
			scanf("%d", &v);
			if(v==-1)
				break;
			if(!ispresent(nodelist, v, N))
			{
				printf("Cant find node %d\n", v);
				continue;
			}
			if(exists(nodelist[i].ptr, v))
            		{
			        printf("Link already exists from %d to %d\n", nodelist[i].value, v);
		                printf("PLease enter another node\n");
		                continue;
            		}
			insertnode(&nodelist[i], nodelist, v, N);
		}
		printf("\n");
	}
}
struct node *check(struct node *head, int v)
{
	struct node *temp=head;
	while(temp!=NULL)
	{
		if(v==temp->value)
			return temp;
		temp=temp->ptr;
	}
	return NULL;
}
struct node *insert(struct node *h, struct node *head)
{
	struct node *newnode, *temp=head;
	newnode=(struct node *)malloc(sizeof(struct node));
	if(newnode==NULL)
	{
		printf("MEMORY ALLOCATION FAILED\n");
		exit(-1);
	}
	newnode->value=h->value;
	newnode->x=h->x;
	newnode->dist=h->dist;
	if(head==NULL || newnode->dist<head->dist)
	{
		newnode->ptr=head;
		head=newnode;
		return head;	
	}
	while(temp->ptr!=NULL && newnode->dist>=(temp->ptr)->dist)
		temp=temp->ptr;
	newnode->ptr=temp->ptr;
	temp->ptr=newnode;
	return head;
}
struct node *arrange(struct node *head, struct node *temp, struct node *temp1)
{
	struct node *t=head;
	if(temp1==head)
	{
		if(temp->dist<(head->ptr)->dist)
		{
			head->dist=temp->dist;
			return head;
		}
		head=head->ptr;
		temp1->dist=temp->dist;
		while(t->ptr!=NULL && temp1->dist>=(t->ptr)->dist)
			t=t->ptr;
		temp->ptr=t->ptr;
		t->ptr=temp1;
		return head;	
	}
	while(t->ptr!=temp1)
		t=t->ptr;
	temp1->dist=temp->dist;
	t->ptr=temp1->ptr;
	t=head;
	while(t->ptr!=NULL && temp1->dist>=(t->ptr)->dist)
		t=t->ptr;
	temp1->ptr=t->ptr;
	t->ptr=temp1;
	return head;	
}
void Prim(struct node nodelist[], struct node *head, int N)
{
	int i, val, index, traversed[N];
	struct node *temp, *temp1;
	for(i=0;i<N;i++)
		traversed[i]=0;
	printf("\nEnter the starting point:- ");
	scanf("%d", &val);
	index=getnodeindex(val, nodelist, N);	
	nodelist[index].dist=0;
	nodelist[index].x=-1;
	head=insert(&nodelist[index], head);
	while(head!=NULL)
	{
		index=getnodeindex(head->value, nodelist, N);
		traversed[index]=1;
		temp=nodelist[index].ptr;
		head=head->ptr;
		i=index;
		while(temp!=NULL)
		{
			index=getnodeindex(temp->value, nodelist, N);
			if(traversed[index]==0)
			{
				if(temp->dist<nodelist[index].dist)
				{
					nodelist[index].dist=temp->dist;
					nodelist[index].x=nodelist[i].value;
					temp1=check(head, temp->value);
					if(temp1!=NULL)
					{
						if(temp->dist<temp1->dist)
							head=arrange(head, temp, temp1);
					}
					else
						head=insert(temp, head);
				}
			}
			temp=temp->ptr;
		}
					
	}
}
void main()
{
	int N, cost=0;
	struct node *nodelist, *head=NULL;
	printf("Enter the number of nodes:- ");
	scanf("%d", &N);
	nodelist=(struct node *)malloc(sizeof(struct node)*N);
	printf("\n");
	if(nodelist==NULL)
	{
		printf("MEMORY ALLOCATION FAILED\n");
		exit(-1);
	}
	initialize(nodelist, N);
	display(nodelist, N);
	createlink(nodelist, N);
	printf("\n");
	show(nodelist, N);
	Prim(nodelist, head, N);
	printf("\nMST is:- \n");
	for(int i=0;i<N;i++)
	{
		printf("%d\t%d\t%d\n", i+1, nodelist[i].x, nodelist[i].dist);
		cost+=nodelist[i].dist;
	}
	printf("\nTotal Cost:- %d\n", cost);
}

