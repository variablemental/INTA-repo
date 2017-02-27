#include<iostream>
#include<cstdio>
using namespace std;
#define INF 0x3F3F3F

int max(int a,int b){
	return a>b?a:b;
}

int ROD(int *price,int n){
	if(n==0)
		return 0;
	int q=INF*-1;
	for(int i=1;i<=n;i++)
		q=max(q,price[i]+ROD(price,n-i));
	return q;
}

int MEMORIZED_CUT_ROD_AUX(int *price,int n,int *r){
	if(r[n]>=0)
		return r[n];
	int q;
	if(n==0)
		q=0;
	else
		q=INF*-1;
	for(int i=1;i<=n;i++)
		q=max(q,price[i]+MEMORIZED_CUT_ROD_AUX(price,n-i,r));
	r[n]=q;
	return q;	
}

int MEMORIZED_CUT_ROD(int *price,int n){
	int *r=new int[n+1];
	for(int i=0;i<=n;i++)
		r[i]=INF*-1;
	int s=MEMORIZED_CUT_ROD_AUX(price,n,r);
	if(s!=price[n]){
	for(int i=1;i<=n/2;i++)										//输出解决方案
		if(r[i]+r[n-i]==s){
			printf("%d+",MEMORIZED_CUT_ROD(price,i));
			printf("%d ",MEMORIZED_CUT_ROD(price,n-i)) ;
		}
	}
	return s;
	
}

int BOTTOM_CUT_ROD(int *price,int n){
	int *r=new int[n];
	r[0]=0;
	for(int i=1;i<=n;i++){
		int q=INF*-1;
		for(int j=1;j<=i;j++)
			q=max(q,price[j]+r[i-j]);
		r[i]=q;
	}
	return r[n];
}



int main(){
	int price[11]={0,1,5,8,9,10,17,17,20,24,30};
	printf("function ROD:%d\n",ROD(price,7));
	printf("function ROD_MEMORIZED: %d\n",MEMORIZED_CUT_ROD(price,7));
	printf("function BOTTOM_CUT_ROD: %d\n",BOTTOM_CUT_ROD(price,7));
	return 0;
}
