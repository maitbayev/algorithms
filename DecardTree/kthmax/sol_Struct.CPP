#include <cstdio>
#include <ctime>
#include <cstdlib>
struct Node {
	Node *l,*r;
	int c,x,y;
	Node()
	{
		l=r=NULL;
		c=x=0;
	}
} *root;

int n;

int count(Node * root)
{
	if (!root) return 0;
	return root->c;
}

void Norm(Node * &root)
{
	if (root)
	root->c=count(root->l)+count(root->r)+1;
}

void Split(Node * root,int x,Node * &l,Node * &r)
{
	if (!root) {
		l=r=NULL;
		return;
	}	
	if (x>root->x) {
		Split(root->r,x,root->r,r); l=root;
		Norm(l);
	}   else
	{
		Split(root->l,x,l,root->l); r=root;
		Norm(r);
	}
}

void insert(Node * &root,int x,int y)
{
	if (!root||y>root->y) {
		Node *tmp=new Node();
		Split(root,x,tmp->l,tmp->r);
		root=tmp;
		root->x=x;
		root->y=y;
//		Norm(root);
	}  else
	if (x>root->x) insert(root->r,x,y); else
	if (x<root->x) insert(root->l,x,y);
	Norm(root);

}

Node *Merge(Node *l,Node *r)
{
	if (!l) return r; 
	if (!r) return l;
	if (l->y>r->y) {
		l->r=Merge(l->r,r);
		Norm(l);
		return l;
	} else
	{
		r->l=Merge(l,r->l);
		Norm(r);
		return r;
	}
}

void Delete(Node * &root,int x)
{
	if (!root) return;
	if (root->x>x) Delete(root->l,x); else
	if (root->x<x) Delete(root->r,x); else
	{
		Node *tmp=root;
		root=Merge(root->l,root->r);
		Norm(root);
		delete tmp;
	}
	Norm(root);
}

void FindKTH(Node * root,int x)
{
	if (count(root->r)+1==x) {
		printf("%d\n",root->x);
		return;
	} else
	if (count(root->r)>=x) FindKTH(root->r,x); else
	FindKTH(root->l,x-count(root->r)-1);
}

int Rand2()
{
	return (rand()<<16)|rand();

}
int main()
{
	freopen("input.txt","r",stdin);	
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	
//	srand(time(NULL));
	int i,code,x;
	for (i=0;i<n;i++){
		scanf("%d %d",&code,&x);
		if (code==1) insert(root,x,Rand2()); else
		if (code==0) FindKTH(root,x); else
		Delete(root,x);
	}
}
