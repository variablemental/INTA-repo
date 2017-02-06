#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

#define N 100
#define INF 0x3F3F3F3F


int M;
int dis[N];
bool visited[N];
int road[N][N];

int prime()
{
	int sum=0;
	for(int i=1;i<=M;i++){
		dis[i]=INF;
		visited[i]=false;
	}
	dis[1]=0;
	for(int i=1;i<=M;i++){
		int min=INF,temp;
		for(int j=1;j<=M;j++){
			if(!visited[j]&&min>dis[j]){
				min=dis[j];
				temp=j;
			}
		}
		visited[temp]=true;
		for(int i=1;i<=M;i++){
			if(!visited[i]&&road[temp][i]<dis[i])
				dis[i]=road[temp][i];
		}

}
	for(int i=1;i<=M;i++)
	sum+=dis[i];
	return sum;

}




int main()
{
	memset(road,0x3F,sizeof(road));
	while(scanf("%d",&M)==1){
		for(int i=1;i<=M;i++)
			for(int j=1;j<=M;j++)
				scanf("%d",&road[i][j]);
		int Q;
		scanf("%d",&Q);
		while(Q--){
			int u,v;
			scanf("%d %d",&u,&v);
			road[u][v]=0;
			road[v][u]=0;
		}
		printf("%d",prime());
	}
	return 0;
}

