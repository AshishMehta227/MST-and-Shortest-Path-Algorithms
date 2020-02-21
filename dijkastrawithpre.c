#include<stdio.h>
int main()
{
int n,k,ans,delmin_point,ptr=0,d_flag=0;
printf("enter number of nodes");
scanf("%d",&n);
int temp=n*n;
int a[n][3],adj[n][3];
	for(int i=0;i<n;i++)
	{
	   a[i][0]=i;
	   a[i][1]=100;
	   a[i][2]=100;
	}
for(int i=0;i<n;i++)
	{
	printf("%d\t%d\n",a[i][0],a[i][1]);
	}
while(1){
	printf("Do you want to insert data\t 1=>insert other value for no operation\n");
	scanf("%d",&ans);
	if(ans==1){
		printf("enter source and destination and path value between this two\n");
		//scanf("%d\n %d\n %d\n ",&adj[ptr][0],&adj[ptr][1],&adj[ptr][2]);
		scanf("%d",&adj[ptr][0]);
		scanf("%d",&adj[ptr][1]);
		scanf("%d",&adj[ptr][2]);		
		ptr++;	
	}else{
		break;	
	}
}
printf("enter delmin point\n");
scanf("%d",&delmin_point);
for(k=0;k<n;k++)
{
	if(a[k][0]==delmin_point){
		d_flag=1;	
		break;
	}
}
if(d_flag==1)
{
a[k][1]=0;
}
else
{
printf("invalid delmin point\n");
}
int co[ptr][3],p1=0,ko=0;
for(int i1=0;i1<ptr;i1++){
	if(delmin_point==adj[i1][0]){
	co[p1][0]=adj[i1][0];
	co[p1][1]=adj[i1][1];
	co[p1][2]=adj[i1][2];
	p1++;
	}
}
for(int i2=0;i2<ptr;i2++){
	if(delmin_point!=adj[i2][0]){
	co[p1][0]=adj[i2][0];
	co[p1][1]=adj[i2][1];
	co[p1][2]=adj[i2][2];
	p1++;
	}
}
for(int c=0;c<p1;c++){
	adj[ko][0]=co[c][0];
	adj[ko][1]=co[c][1];
	adj[ko][2]=co[c][2];
	ko++;
}
for(int c1=0;c1<ptr;c1++){
	printf("%d\t%d\t%d\n",adj[c1][0],adj[c1][1],adj[c1][2]);
}
for(int i=0;i<ptr;i++){
	int so,ans,find=adj[i][0]; 
	for(int j=0;j<n;j++){
	if(find==a[j][0]){
	so=a[j][1];
	break;
	}
	}
	ans=adj[i][2]+so;
	for(int j1=0;j1<n;j1++){
	if(adj[i][1]==a[j1][0]){
	if(a[j1][1]>ans){	
	a[j1][1]=ans;
	a[j1][2]=adj[i][0];
	break;
	}
	}		
	}
	
}
for(int k=0;k<n;k++){
printf("\nsource=%d\t shortest path=%d\t predeseccor=%d\n",a[k][0],a[k][1],a[k][2]);
}
return 0;
}
