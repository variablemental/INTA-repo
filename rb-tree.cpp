#include<iostream>
#define MAXS(a,b) a>b?a:b
#define BLACK 1
#define RED   0
using namespace std;


typedef struct Node
{
	int data;
	Node *left;
	Node *right;
	Node *parent;
	int color;
	Node(int data=0,Node *left=NULL,Node *right=NULL,Node *parent=NULL){
		this->data=data;
		this->left=left;
		this->right=right;	
		this->parent=parent;
	}
}Node;

class Tree
{
private:
	Node *root;
	int height;
	int calHeight(Node *node);
protected:
	void setRoot(Node *node){root=node;};
	void transplant(Node *u,Node *v);	
public:
	Tree(Node *root=NULL):root(root){}
	Node *findMin(Node *node);
	Node* Insert(Node *parent,int data);
	void Delete(Node *node);
	Node* getRoot(){return root;}
	int getHeight();
	void TranverseInorder(Node *node);		
	Node* Query(Node *node,int data);
};

Node* Tree::Insert(Node *parent,int data)
{
	if(data>parent->data){
		if(parent->right!=NULL)
			return Insert(parent->right,data);
		else{
			Node *newNode=new Node(data,NULL,NULL,parent);
			parent->right=newNode;
			return newNode;
		}			
	}
	else {
		if(parent->left!=NULL)
			return Insert(parent->left,data);
		else{
			Node *newNode=new Node(data,NULL,NULL,parent);
			parent->left=newNode;
			return newNode;
		}	
	}	
}

//中序遍历二叉树
void Tree::TranverseInorder(Node *node)
{
	if(node!=NULL){
		TranverseInorder(node->left);
		cout<<node->data<<endl;
		TranverseInorder(node->right);
	}
}

//寻找node的后继节点
Node* Tree::findMin(Node *node)
{
	if(node->left!=NULL)
		return findMin(node->left);
	return node;
}


//	让以v为根节点的子树代替以u为根节点的子树，拼接到u的双亲节点上

void Tree::transplant(Node *u,Node *v)
{
	if(u->parent==NULL)
		root=v;
	else if(u==u->parent->left)
		u->parent->left=v;
	else
		u->parent->right=v;
	if(v!=NULL)
		v->parent=u->parent;
}

/*
分为四种情况：
	1.node无左孩子，则将node的右孩子代替node，无论node右孩子是否为NULL
	2.node无右孩子，则将node的左孩子代替node，无论node左孩子是否为NULL
	3.node有左右孩子 1)node最小后继是node右孩子，直接让node右孩子代替node拼接
					 2)node最小后继不是右孩子，则将该最小节点y为node右孩子，原来		的						右孩子为y的右孩子，y的右孩子为node的左孩子
	
	
*/

void Tree::Delete(Node *node)
{
	if(node->left==NULL)
		transplant(node,node->right);
	else if(node->right==NULL)
		transplant(node,node->left);
	else{
		Node *y=findMin(node->right);
		if(y->parent!=node){
			transplant(y,y->right);
			y->right=node->right;
			y->right->parent=y;
		}
		transplant(node,y);
		y->left=node->left;
		y->left->parent=y;
	}
}

Node* Tree::Query(Node *node,int data)
{
	if(node->data==data)
		return node;
	else if(node->data>data)
		return Query(node->left,data);
	else
		return Query(node->right,data);
	
}

int Tree::calHeight(Node *node)
{
	if(node==NULL)
		return 1;
	return MAXS(calHeight(node->left),calHeight(node->right))+1;
}

int Tree::getHeight()
{
	return calHeight(root);
}

class rb_tree:public Tree
{
private:
	Node *nil;
protected:
	void right_rotate(Node *node);
	void left_rotate(Node *node);
	void setRoot(Node *node){Tree::setRoot(node);getRoot()->parent=nil;}
public:
	rb_tree(Node *root):Tree(root){
		nil=new Node(0,NULL,NULL,NULL);
		nil->color=BLACK;
		root->color=BLACK;
		root->parent=nil;
		root->left=nil;
		root->right=nil;
	}
	void Insert(int data);
	void TranverseInorder(Node *node);
		
	

};

void rb_tree::right_rotate(Node *node)
{
	if(node==nil)
		return;
	Node *y=node->left;
	node->left=y->right;
	if(y->right!=nil)
		y->right->parent=node;
	y->parent=node->parent;
	if(node->parent==nil)
		setRoot(y);
	else if(node==node->parent->left)
		node->parent->left=y;
	else
		node->parent->right=y;
	y->right=node;
	node->parent=y;
}

void rb_tree::left_rotate(Node *node)
{
	if(node==nil)
		return;
	Node *y=node->right;
	node->right=y->left;
	if(y->left!=nil)
		y->left->parent=node;
	y->parent=node->parent;
	if(node->parent==nil)
		setRoot(y);
	else if(node==node->parent->left)
		node->parent->left=y;
	else 
		node->parent->right=y;
	y->left=node;
	node->parent=y;
}

void rb_tree::Insert(int data)
{
	Node *z=new Node(data,NULL,NULL,NULL);
	Node *x=getRoot();
	Node *y=nil;
	while(x!=nil){
		y=x;
		if(z->data<x->data)
			x=x->left;
		else
			x=x->right;
	}
	z->parent=y;
	if(y==nil)
		setRoot(z);
	else if(y->data>z->data)
		y->left=z;
	else y->right=z;
	z->left=nil;
	z->right=nil;
	z->color=RED;
	
	while(z->parent->color==RED){
		if(z->parent==z->parent->parent->left){
			Node *uncle=z->parent->parent->right;
			if(uncle->color==RED){
				z->parent->color=BLACK;
				uncle->color=BLACK;
				z->parent->parent->color=RED;
				z=z->parent->parent;
			}
			else if(z==z->parent->right){
				z=z->parent;
				left_rotate(z);
			}
			else{
				z->parent->color=BLACK;
				z->parent->parent->color=RED;
				right_rotate(z->parent->parent);
			}
		}
		else{
			Node *uncle=z->parent->left;
			if(uncle->color==RED){
				z->parent->color=BLACK;
				uncle->color=BLACK;
				z->parent->parent->color=RED;
			}
			else if(z==z->parent->left){
				z=z->parent;
				right_rotate(z);
			}
			else
			{
				z->parent->color=BLACK;
				z->parent->parent->color=RED;
				left_rotate(z->parent->parent);
			}
		}
	}
}

void rb_tree::TranverseInorder(Node *node)
{
	if(node!=nil){
		TranverseInorder(node->left);
		cout<<node->data<<endl;
		TranverseInorder(node->right);
	}
}

int main()
{
	int arr[6]={7,5,2,5,7,8};
	Node *root=new Node(6,NULL,NULL,NULL);
	Tree *t=new Tree(root);
//	for(int i=0;i<sizeof(arr)/sizeof(typeof(arr[0]));i++){
//		t->Insert(t->getRoot(),arr[i]);
//	}
//	t->TranverseInorder(t->getRoot());
//	t->Delete(t->Query(t->getRoot(),7));
//	cout<<endl;
//	t->TranverseInorder(t->getRoot());
//	cout<<t->getHeight()<<endl;
	Node *rb_root=new Node(10,NULL,NULL,NULL);
	rb_tree *t2=new rb_tree(rb_root);
		for(int i=0;i<sizeof(arr)/sizeof(typeof(arr[0]));i++){
		t2->Insert(arr[i]);
	}
	t2->TranverseInorder(t2->getRoot());
	return 0;
}



