#include <iostream>
using namespace std;
struct Tree {
	Tree *l,*r;
	int y,sz,v;
	bool rev;
	Tree()
	{
		l=r=0;
		y=sz=rev=0;
	}
} *root;

int Count(Tree *root)
{
	if (!root) return 0;
	return root->sz;
}

void Norm(Tree *&root)
{
	if (!root) return;
	root->sz = Count(root->l) + Count(root->r) + 1;
}


void Push(Tree *&root)
{
	if (!root) return;
	if (!root->rev) return;

	root->rev=false;

	swap(root->l,root->r);

	if (root->l) root->l->rev ^= true;
	if (root->r) root->r->rev ^= true;

}

void Split(Tree *root,int x,Tree *&l,Tree *&r)
{
	if (!root) {l=r=0; return;}

	Push(root);

	if (Count(root->l)+1 <= x) {
		Split(root->r,x-Count(root->l)-1,root->r,r);
		l=root;
		Norm(l);
	} else
	{
		Split(root->l,x,l,root->l);
		r=root;
		Norm(r);
	}        
}


Tree * Merge(Tree *&l,Tree *&r)
{
	if (!l) return r;
	if (!r) return l;

	Push(l); Push(r);
	if (l->y > r->y) {
		l->r = Merge(l->r,r);
		Norm(l);
		return l;
	} else
	{
		r->l = Merge(l,r->l);
		Norm(r);
		return r;
	}
}

void Insert(Tree *&root,int x,int y,int v)
{
	Tree *L,*R;
	
	Split(root,x-1,L,R);

	Tree *tmp= new Tree();
	tmp -> y = y; tmp->v = v; tmp->rev=false;
        Norm(tmp);

	L = Merge(L,tmp);
	root= Merge(L,R);

}

void Reverse(Tree *&root,int l,int r)
{
	Tree *L,*R , *Rl,*Rr;
	Split(root,l-1 , L,R);	
	Split(R,r-l+1,Rl,Rr);

	Rl->rev^= true;

	R = Merge(Rl,Rr);
	root= Merge(L,R);

}

int Rand2()
{
	return (rand()<<16)|rand();
}

void print(Tree *&root)
{
	if (!root) return;

	Push(root);

	print(root->l);
	printf("%d ",root->v);
	print(root->r);

}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		int x;
		scanf("%d",&x);
		Insert(root,i,Rand2(),x);
	}	

	scanf("%d",&m);
	for (int i=0;i<m;i++) {
		int l,r;
		scanf("%d%d",&l,&r);
		Reverse(root,l,r);
	}
	print(root);

}
