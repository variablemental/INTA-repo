#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 20
#define M N*2-1

//存储树节点，
//[1...n]是需要编码的字符节点，[n+1...m]是新增的字符节点的父节点
typedef struct HtNode
{
	int parent;
	int weight;
	int lchild;
	int rchild;
}HtNode;

//存储源字符信息，和最后编码的结果
typedef struct HcNode{
	char data;
	int weight;
	char code[N];

}HcNode;

//读入数据
void init(HcNode hc[],int *n){
	freopen("huffmantree.txt","r",stdin);
	scanf("%d",n);
	for(int i=1;i<=*n;i++){
		char rd;
		scanf("%c",&rd);
		if(rd=='\n')
			scanf("%c",&hc[i].data);
		else
			hc[i].data=rd;
		scanf("%d",&hc[i].weight);
		cout<<hc[i].data<<" "<<hc[i].weight<<endl;
	}
	
}

//在树的数组中获取权值最小的两个节点
/**
	param 
	int *s1,*s2 负责取得这两个节点的地址
    int k       目前数组存放节点的数量
**/
//获取的时候需要注意s1和s2的初始化，需要最初赋值为没有双亲的第一个节点
void Select(HtNode ht[],int k,int *s1,int *s2){
	int i;
	for(i=1;i<=k&&ht[i].parent!=0;i++);
	*s1=i;
	for(i=1;i<=k;i++)
		if(ht[i].parent==0&&ht[i].weight<ht[*s1].weight)
			*s1=i;
	for(i=1;i<=k;i++)
		if(ht[i].parent==0&&i!=*s1)
			break;
	*s2=i;
	for(int i=1;i<=k;i++)
		if(ht[i].parent==0 && i!=*s1 && ht[i].weight<=ht[*s2].weight)
			*s2=i;
}

//获得Huffman编码
void getHuffmanCode(HtNode ht[],HcNode hc[],int n){
	int *s1,*s2;
	int m=2*n-1;
	char code[N];
	for(int i=1;i<=m;i++){									//初始化HtNode数组
		if(i<=n)
			ht[i].weight=hc[i].weight;
		ht[i].parent=ht[i].lchild=ht[i].rchild=0;
	}
	for(int i=n+1;i<=m;i++){								//编织节点
		Select(ht,i-1,s1,s2);
		ht[*s1].parent=i;
		ht[*s2].parent=i;
		ht[i].lchild=*s1;
		ht[i].rchild=*s2;
		ht[i].weight=ht[*s1].weight+ht[*s2].weight;
	}
	
	code[n-1]='\0';											//最大编码长度为字符的个数		
	
	for(int i=1;i<=n;i++){									//从尾部开始添加0-1串
		int start=n-1;
		for(int j=i;ht[j].parent;j=ht[j].parent){
			if(ht[ht[j].parent].lchild==j)
				code[start--]='0';
			else
				code[start--]='1';
		}
		strcpy(hc[i].code,&code[start]);					//从start开始截取到hc[i].code字符串
	}
}


int main(){
	int n;
	HtNode ht[M+1];
	HcNode hc[N+1];
	
	init(hc,&n);
	getHuffmanCode(ht,hc,n);
	
	for(int i=1;i<=n;i++)
		cout<<hc[i].data<<":"<<hc[i].code<<endl;
	return 0;
}
