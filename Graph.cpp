#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

#define N 100
#define INF 0x3F3F3F

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

typedef struct Edge{
	int begin;
	int end;
	int weight;
	Edge(){};
	Edge(int begin,int end,int weight){
		this->begin=begin;
		this->end=end;
		this->weight=weight;
	}
}Edge;

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

Edge edgeSet[N];
void loadEdge(Graph *g){
	int n=0;
	for(int i=0;i<g->vexnum;i++){
		ArcNode *q=g->vertix[i].firstArc;
		while(q){
			Edge *newEdge=new Edge(i,q->adjvex,q->weight);
			edgeSet[n]=*newEdge;
			n++;	
			q=q->next;
		}
	}
}

void sort(Edge *arr){
	int length=sizeof(arr)/sizeof(arr[0]);
	for(int i=1;i<length;i++){
		int j;
		Edge reg=arr[i];
		for(j=0;j<i;j++){
			if(arr[j].weight>arr[i].weight)
				break;
		}
		for(int k=i;k>j;k--){
			arr[k]=arr[k-1];
		}
		arr[j]=reg;
	}
}

bool contain(int *arr,int v){
	int length=sizeof(arr)/sizeof(arr);
	for(int i=0;i<length;i++){
		if(arr[i]==v)
			return true;
	}
	return false;
}

void Kruskal(Graph *g){
	loadEdge(g);
	Edge *ex=edgeSet;
	int length=sizeof(ex)/sizeof(ex[0]);
	sort(ex);
	int visited[g->vexnum];
	int n=0;
	int vex=0;
	while(n<=g->vexnum){
		if(!(contain(visited,ex[vex].begin)&&contain(visited,ex[vex].end))){
				visited[n]=ex[vex].begin;
				visited[n+1]=ex[vex].end;
				n+=2;
				vex++;
				printf("%d->%d\n",ex[vex].begin,ex[vex].end);
		}
	}
}

void printMat(int** mat,int row,int length){
	cout<<length<<" "<<row<<endl;
	for(int i=0;i<row;i++){
		for(int j=0;j<length;j++){
			if(mat[i][j]==INF)
				cout<<"INF	";
			else
				cout<<mat[i][j]<<"	";
			}
		cout<<endl;
	}

}

int **getMatrix(Graph *g){
	const int vexnum=g->vexnum;
	const int arcnum=g->arcnum;
	int **mat=new int*[vexnum];
	for(int i=0;i<g->vexnum;i++){
		mat[i]=new int[arcnum];
		for(int j=0;j<g->vexnum;j++)
			mat[i][j]=INF;
	}
	for(int i=0;i<g->vexnum;i++){
		ArcNode *q=g->vertix[i].firstArc;
		while(q){
			mat[i][q->adjvex]=q->weight;
			q=q->next;
		}
	}
	return mat;
}

int **getMatrix_non(Graph *g){
	const int vexnum=g->vexnum;
	const int arcnum=g->arcnum;
	int **mat=new int*[vexnum];
	for(int i=0;i<vexnum;i++){
		mat[i]=new int[vexnum];
		for(int j=0;j<vexnum;j++)
			mat[i][j]=INF;
	}
	for(int i=0;i<g->vexnum;i++){
		ArcNode *q=g->vertix[i].firstArc;
		while(q){
			if(q->weight<INF){
				mat[i][q->adjvex]=q->weight;
				mat[q->adjvex][i]=q->weight;
			}
			q=q->next;
		}
	}
	printMat(mat,vexnum,vexnum);
	return mat;
}

void Prime(Graph *g){
	int **mat=getMatrix(g);
	bool visited[g->vexnum];
	int dist[g->vexnum];
	int sum=0;
	memset(visited,false,sizeof(visited));
	
	visited[0]=true;
	for(int i=0;i<g->vexnum;i++)
		dist[i]=mat[0][i];
		
	for(int i=0;i<g->vexnum;i++){
		int min=INF;
		int index=0;
		for(int j=0;j<g->vexnum;j++)
			if(!visited[j]&&min>dist[j]){
				min=dist[j];
				index=j;
			}
		visited[index]=true;
		sum+=min;
		
		for(int j=0;j<g->vexnum;j++){
			if(!visited[j]&&dist[j]>mat[index][j])
				dist[j]=mat[index][j];
		}
		
		for(int j=0;j<g->vexnum;j++){
			if(mat[j][index]==min){
				printf("%c",g->vertix[j].data);
			}
			printf("->%c ",g->vertix[index].data);
		}
		cout<<sum;	
	}
}

void printRoad(int *prev,int i){
	if(prev[i]==INF){
		printf("%d->",i);
		return ;
	}
	printRoad(prev,prev[i]);
	printf("%d->",prev[i]);
}

bool validate(int *visited){
	int length=sizeof(visited)/sizeof(visited[0]);
	for(int i=0;i<length;i++)
		if(!visited[i])
			return false;
	return true;
}

void dijkstra(Graph *g){
	int visited[g->vexnum];
	int dist[g->vexnum];
	int prev[g->vexnum];
	int **mat=getMatrix_non(g);
	memset(visited,false,sizeof(visited));
	for(int i=0;i<g->vexnum;i++){
		dist[i]=mat[0][i];
		if(mat[0][i]!=INF)
			prev[i]=0;
		else
			prev[i]=INF;
	}
	visited[0]=true;
	cout<<"0->";
	int min=INF;
	int select=0;
	for(int k=1;k<g->vexnum;k++){
		int min=INF;
		int flag=select;
		for(int i=0;i<g->vexnum;i++)
			if(!visited[i]&&min>dist[i]){
				min=dist[i];
				select=i;
			}
		if(flag==select)
			break;
		visited[select]=true;
		cout<<select<<"->";
		for(int i=0;i<g->vexnum;i++){
			if(!visited[i]&&dist[select]+mat[select][i]<dist[i]){
				dist[i]=dist[select]+mat[select][i];
				prev[i]=select;
			}
		}
	}
	cout<<"endpoint"<<endl;
}



int main(){
	Graph g=createGraph();
	cout<<"finished"<<endl;
	ArcNode *p=g.vertix[2].firstArc;
	while(p!=NULL){
		cout<<p->adjvex<<endl;
		p=p->next;
	}
	printf("BFS:\n");
	BFS(g);
	cout<<endl;
	printf("DFS:\n");
	DFS(g);
	printf("Algorithm Kruskal:\n");
	Kruskal(&g);
	cout<<"Algorithm Prime:"<<endl;
	Prime(&g);
	cout<<endl;
	cout<<"Algorithm Dijkstra:"<<endl;
	dijkstra(&g);
	return 0;
}











