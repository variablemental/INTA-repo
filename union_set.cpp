#include<iostream>
#include<cstdio>
#include<cstring>
#define n 105
using namespace std;

int union_set[n];

void initial(int num){
	for(int i=1;i<=num;i++)
		union_set[i]=i;
}

int find(int x){
	return union_set[x]==x?x:find(union_set[x]);
}

void connect(int A,int B){
	int x=find(A);
	int y=find(B);
	if(x!=y)
		union_set[y]=x;
}



int main()
{
	int T;
	scanf("%d",&T);
	memset(union_set,0,sizeof(union_set));
	while(T--){
		int N,M;
		scanf("%d %d",&N,&M);
		initial(N);
		while(M--){
			int A,B;
			scanf("%d %d",&A,&B);
			connect(A,B);
		}
		int ans=0;
		for(int i=1;i<=N;i++)
			if(union_set[i]==i)
				ans++;
		cout<<ans<<endl;		
	}
	return 0;
}
