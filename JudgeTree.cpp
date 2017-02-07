#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

#define N 10050

bool visited[N];
int pre[N];

int find(int x){	
	return pre[x]==x?x:find(pre[x]);
}

bool join(int x,int y){
	int nx=find(x);
	int ny=find(y);
	if(y!=ny||nx==ny)	return false;
	pre[ny]=nx;
	return true;	
}




int main()
{
	freopen("input.txt","r",stdin);
	int T,a,b;
	while(scanf("%d %d",&a,&b)==2){
		if(a<0||b<0)
			break;
		for(int i=1;i<=10000;i++)
			pre[i]=i;
		memset(visited,0,sizeof(visited));
		bool flag=true;
		while(a!=0){
			visited[a]=true;
			visited[b]=true;
			if(flag&&!join(a,b)) flag=false;
			scanf("%d %d",&a,&b);
		}
		int ans=0;
		for(int i=1;i<=10000;i++)
			if(visited[i]&&pre[i]==i)	ans++;
		if(ans>1)	flag=false;
		cout<<"第"<<T+1<<"棵"<<(flag?"是":"不是")<<"树"<<endl;
		T++;
	}


	return 0;
}
