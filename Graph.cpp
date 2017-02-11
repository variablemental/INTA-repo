#include<iostream>
#include<cstdio>
using namespace std;

#define N 100

typedef struct ArcNode{
	int adjvex;
	int weight;
	ArcNode* next;
	ArcNode(int vex,int weight,ArcNode* next){
		this->adjvex=vex;
		this->weight=weight;
		this->next=next;
	}
}ArcNode;

typedef struct Vex{
	char data;
	ArcNode* firstArc;
	
	Vex(){firstArc=NULL;}
	Vex(char data,ArcNode* firstArc){
		this->data=data;
		this->firstArc=firstArc;
	}	
}Vex,AdjList[N];

typedef struct Graph{
	AdjList vertix;
	int vexnum,arcnum;
}Graph;

int LocateVex(Graph &G,char &ch){
	int i;
	for(i=0;i<G.vexnum;i++)
		if(G.vertix[i].data==ch)
			return i;
	if(i>=G.vexnum)
		return -1;
	return 0;
}

Graph createGraph(){
	freopen("Graph.txt","r",stdin);
	Graph g;
	scanf("%d",&g.vexnum);
	for(int i=0;i<g.vexnum;i++){
		scanf("%c",&g.vertix[i].data);
		cout<<g.vertix[i].data<<endl;
		g.vertix[i].firstArc=NULL;
	}
	g.arcnum=0;
	char u,v;
	while(scanf("%c %c",&u,&v)==2){
		int x=LocateVex(g,u);
		int y=LocateVex(g,v);
		int weight=0;
		scanf("%d",&weight);
		if(g.vertix[x].firstArc==NULL){
			g.vertix[x].firstArc=new ArcNode(y,weight,NULL);	
		}else{
			ArcNode *trace=g.vertix[x].firstArc;
			ArcNode *newNode=new ArcNode(y,weight,NULL);
			while(trace->next!=NULL)
				trace=trace->next;
			trace->next=newNode;
		}
		g.arcnum++;
	}
	return g;
}

int main(){
	Graph g=createGraph();
	cout<<"finished"<<endl;
	ArcNode *p=g.vertix[2].firstArc;
	while(p!=NULL){
		cout<<p->adjvex<<endl;
		p=p->next;
	}
	return 0;
}











