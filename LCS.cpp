#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int **C,**b;

//b--1 ^
//b--2 <
//b--3 <^

void LCS(char *X,char *Y){
const int m=strlen(X);
const int n=strlen(Y);
C=new int*[n+1];
b=new int*[n+1];
for(int i=0;i<n+1;i++){
	C[i]=new int[m+1];
	b[i]=new int[m+1];
	for(int j=0;j<m+1;j++){
		C[i][j]=0;
		b[i][j]=0;
	}
}
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		if(Y[i]==X[j]){
			C[i][j]=C[i-1][j-1]+1;
			b[i][j]=3;
		}
		else if(C[i-1][j]>=C[i][j-1]){
			C[i][j]=C[i-1][j];
			b[i][j]=1;
		}
		else{
			C[i][j]=C[i][j-1];
			b[i][j]=2;
		}
	}
}
}

void print_LCS(char* Y,int i,int j){
	if(i==0||j==0)
		return;
	if(b[i][j]==3){
		print_LCS(Y,i-1,j-1);
		cout<<Y[i]<<" ";
	}
	else if(b[i][j]==1)
		print_LCS(Y,i-1,j);
	else
		print_LCS(Y,i,j-1);
	cout<<endl;
}


int main()
{
	char X[7]="BDCABA";
	char Y[8]="ABCBDAB";
	//cout<<strlen(x)<<" "<<sizeof(X)<<endl;
	//cout<<Y[0]<<endl;
	LCS(X,Y);
	print_LCS(Y,strlen(X),strlen(Y));

}
