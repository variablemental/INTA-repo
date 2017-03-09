#include<iostream>
#include<cstdio>
using namespace std;
#define N 8

int board[N][N];
int count=0;

void init_Board(){
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			board[i][j]=0;
}

void print_board(){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout<<board[i][j]<" ";
		}
		cout<<endl;
	}
	cout<<"==============================="<<endl;
}

bool validate(int i,int j){
	for(int k=0;k<N;k++){
		if(k!=i&&board[k][j]==1)
			return false;
	}
	for(int si=0;si<N;si++){
		for(int sj=0;sj<N;sj++){
			if(board[si][sj]==1&&((si-i==sj-j)||(si-i)==-(sj-j)))
				return false;
		}
	}
	return true;	
}

void Eight_Queen(int n){
	if(n==N){
		print_board();
		count++;
		return ;
	}
	for(int i=0;i<N;i++){
		if(validate(n,i)){
			board[n][i]=1;
			Eight_Queen(n+1);
		}
		board[n][i]=0;
	}
}

int main(){
	init_Board();
	Eight_Queen(0);
	cout<<"solution counts:"<<count<<endl;
}





