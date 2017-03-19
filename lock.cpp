#include<iostream>
#include<cstdio>
using namespace std;

int map[10][10];
int record[10][10];
int count=0,edge_num,depth_aim,visited[10];

void init(){
	record[1][3]=record[3][1]=record[1][7]=record[7][1]=1;
	record[3][9]=record[9][3]=record[3][7]=record[7][3]=1;
	record[4][6]=record[6][4]=1;
	record[1][9]=record[9][1]=1;
	record[7][9]=record[9][7]=1;
	record[2][8]=record[8][2]=1;
	for(int i=0;i<10;i++){
		for(int j=0;j<=10;j++)
			map[i][j]=0;
		visited[i]=0;
	}
}

void dfs(int num,int depth,int edge){
	if(depth==depth_aim&&edge==edge_num){
		count++;
		return ;
	}
	
	for(int i=0;i<=9;i++){
		if(record[num][i]&&!visited[(num+i)/2])
			continue;
		if(!visited[i]){
			visited[i]=1;
			if(map[num][i])
				dfs(i,depth+1,edge+1);
			else
				dfs(i,depth,edge);
			visited[i]=0;
		}
	}
}


int main(){
int t,n;
cin>>t;
int row,col;

init();
while(t--){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>row>>col;
		map[row][col]=map[row][col]=1;
	}
	edge_num=n;
	for(depth_aim=(n+1>4?n+1:4);depth_aim<10;depth_aim++){
		for(int i=1;i<=9;i++){
			visited[i]=1;
			dfs(i,1,0);
			visited[i]=0;
		}
	}
	cout<<count<<endl;
}	
}
