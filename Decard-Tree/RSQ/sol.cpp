#include <iostream>
using namespace std;
struct Tree {
	Tree *l,*r;
	int y,add,v,sum,sz;
	Tree()
	{
		l=r=0;
		y=add=v=sum=sz=0;
	}
}*root;



void Push(Tree *&root)
{
	if (!root) return;
	root->sum += root->sz*root->add;
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
int SumValue(Tree *root)
{
	if (!root) return 0;
	Push(root);
	return root->sum;
}

void Norm(Tree *&root)
{
	if (!root) return;
	root->sz = Count(root->l) + Count(root->r)+1;
	root->sum = SumValue(root->l) + SumValue(root->r) + root->v;
}

void Split(Tree *root,int x,Tree *&l,Tree *&r)
{
	if (!root) {l=r=0; return;}
	Push(root);
	if (Count(root->l)+1<=x) {
		Split(root->r,x-Count(root->l)-1,root->r,r);
		l=root;
		Norm(l);
	}else
	{
		Split(root->l,x,l,root->l);
		r=root;
		Norm(r);
	}
}

Tree *Merge(Tree *l,Tree *r)
{
	if (!l) return r;
	if (!r) return l;
	Push(l);Push(r);
	if (l->y > r->y) {
		l->r = Merge(l->r,r);
		Norm(l);
		return l;
	}else
	{
		r->l = Merge(l,r->l);
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
	root = Merge(L,R);

}

void Display(Tree *root)
{
	if (!root) return;
	Display(root->l);
	printf("%d\n",root->v);
	Display(root->r);
}

void Update(Tree *&root,int l,int r,int s)
{
	Tree *L,*R,*Rl,*Rr;
	Split(root,l-1,L,R);
	Split(R,r-l+1,Rl,Rr);

	if (Rl) Rl->add+=s;
	
	R=Merge(Rl,Rr);
	root=Merge(L,R);

}


int FindSum(Tree *&root,int l,int r)
{
	Tree *L,*R,*Rl,*Rr;
	Split(root,l-1,L,R);
	Split(R,r-l+1,Rl,Rr);
	int ans=0;
	Push(Rl);
	if (Rl) ans=Rl->sum;
	
	R = Merge(Rl,Rr);
	root=Merge(L,R);

	return ans;

}

int Rand2()
{
	return (rand()<<16)|rand();
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	
	n++;

	for (int i=1;i<=n;i++) insert(root,i,Rand2());

	for (int i=1;i<=m;i++) {
		int code;
		scanf("%d",&code);
		if (code==1) {
			int l,r,s;
			scanf("%d%d%d",&l,&r,&s);
			l++;
			Update(root,l,r,s);

		} else
		{
			int l,r;
			scanf("%d%d",&l,&r);
			l++;
			printf("%d\n",FindSum(root,l,r));
			
		}

	}
	return 0;
}
