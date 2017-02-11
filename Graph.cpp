#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
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

void BFS(Graph &g){	
	queue<int> Q;
	bool visited[g.vexnum];
	memset(visited,0,g.vexnum);
	ArcNode *q=g.vertix[0].firstArc;
	if(q==NULL)
		for(int i=0;i<g.arcnum;i++){
			if(g.vertix[i].firstArc!=NULL){
				q=g.vertix[i].firstArc;
				break;
			}
		}
	while(q!=NULL){
		Q.push(q->adjvex);
		q=q->next;
	}
	printf("%c",g.vertix[0].data);
	visited[0]=true;
	while(!Q.empty()){
		visited[Q.front()]=true;
		char temp=g.vertix[Q.front()].data;
		q=g.vertix[Q.front()].firstArc;
		while(q!=NULL){
			if(!visited[q->adjvex])
				Q.push(q->adjvex);
			q=q->next;
		}
		Q.pop();
		printf("->%c",temp);
	}
}


void DFS_visit(Graph &g,int adj,bool *visited){
	printf("%c->",g.vertix[adj].data);
	ArcNode *q=g.vertix[adj].firstArc;
	visited[adj]=true;
	while(q!=NULL){
		if(!visited[q->adjvex])
			DFS_visit(g,q->adjvex,visited);
		q=q->next;
	}
	return ;
}

void DFS(Graph &g){
	bool visited[g.vexnum];
	memset(visited,0,g.vexnum);
	for(int i=0;i<g.vexnum;i++){
		if(!visited[i]){
			DFS_visit(g,i,visited);
		}
	}
}

int main(){
	Graph g=createGraph();
	cout<<"finished"<<endl;
	ArcNode *p=g.vertix[2].firstArc;
	while(p!=NULL){
		cout<<p->adjvex<<endl;
		p=p->next;
	}
	BFS(g);
	cout<<endl;
	DFS(g);
	return 0;
}











