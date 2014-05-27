#include <iostream>
using namespace std;

struct Tree {
	Tree *l,*r;
	int y,sz,Max,add,v;		
	
	Tree()
	{
		l=r=0;
		y=sz=v=Max=add=0;
	}

}*root;

void Push(Tree *&root)
{
	if (!root) return;
	root->Max+=root->add;

	root->v+=root->add;
	if (root->l) root->l->add+=root->add;
	if (root->r) root->r->add+=root->add;
	root->add=0;
}

int Count(Tree *root)
{
	if (!root) return 0;
	return root->sz;
}

int MaxValue(Tree *&root)
{
	if (!root) return 0;
	Push(root);
	return root->Max;
}

void Norm(Tree *&root)
{
	if (!root) return;
	root->sz = Count(root->l) + Count(root->r)+1;

	root->Max = max(max(MaxValue(root->l) ,MaxValue(root->r)),root->v);
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

Tree *Merge(Tree *l,Tree *r)
{
	if (!l) return  r;
	if (!r) return l;
	Push(r);Push(l);
	if (l->y > r->y) {
		l->r =Merge(l->r,r);
		Norm(l);
		return l;
	} else
	{
		r->l =Merge(l,r->l);
		Norm(r);
		return r;
	}
}

void insert(Tree *&root,int x,int y)
{
	Tree *L,*R;
	Split(root,x-1,L,R);
	
	Tree *tmp=new Tree();
	
	tmp->y=y;

	Norm(tmp);

	L = Merge(L,tmp);
	root=Merge(L,R);
}

void Display(Tree *root)
{
	if (!root) return;
	Display(root->l);
	printf("%d ",root->v);
	Display(root->r);
}


int FindMax(Tree *&root,int l,int r)
{
	Tree *L,*R,*Rl,*Rr;
	Split(root,l-1,L,R);
	Split(R,r-l+1,Rl,Rr);
	Push(Rl);
	int ans=0;
	if (Rl) ans= Rl->Max;

	R=Merge(Rl,Rr);
	root=Merge(L,R);

	return ans;
}

void Update(Tree *&root,int l,int r)
{
	Tree *L,*R,*Rl,*Rr;

	Split(root,l-1,L,R);
	Split(R,r-l+1,Rl,Rr);

	if (Rl) Rl->add++;

	R=Merge(Rl,Rr);
	root=Merge(L,R);

}

int Rand2()
{
	return (rand()<<16)|rand();
}

int main()

{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,k,m;
	scanf("%d%d%d",&n,&k,&m);
	
	for (int i=1;i<=n;i++) insert(root,i,Rand2());
	
	for (int i=0;i<m;i++) {
		int l,r;
		scanf("%d%d",&l,&r);
		l++;

		if (FindMax(root,l,r) >= k) puts("0"); else
		{
			puts("1");
			Update(root,l,r);
		} 
	}
	
	return 0; 	
}
