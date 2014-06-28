#include <iostream>
using namespace std;

struct Tree {
	Tree *l,*r;
	int y,sz,sum,add,v;		
	
	Tree()
	{
		l=r=0;
		y=sz=v=sum=add=0;
	}

};

class DecardTree {
 	Tree *root;
	void Push(Tree *&root)
	{
		if (!root) return;
		root->sum+=root->add*root->sz;

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

	int sumValue(Tree *&root)
	{
		if (!root) return 0;
		Push(root);
		return root->sum;
	}

	void Norm(Tree *&root)
	{
		if (!root) return;
		root->sz = Count(root->l) + Count(root->r)+1;
		root->sum = sumValue(root->l) +sumValue(root->r)+root->v;
	}

	int Rand2()
	{
		return (rand()<<16)+rand();
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

	void Display(Tree *root)
	{
		if (!root) return;
		Display(root->l);
		printf("%d ",root->v);
		Display(root->r);
	}
        void insert(int x,int y)
	{
		Tree *L,*R;
		Split(root,x-1,L,R);
	
		Tree *tmp=new Tree();
	
		tmp->y=y;

		Norm(tmp);

		L = Merge(L,tmp);
		root=Merge(L,R);
	}

	public:
	
	void Display()
	{
		Display(root);
	}
        
	void insert(int x)
	{
		insert(x,Rand2());
	}
	
        int FindSum(int l,int r)
	{
		Tree *L,*R,*Rl,*Rr;
		Split(root,l-1,L,R);
		Split(R,r-l+1,Rl,Rr);
		Push(Rl);
		int ans=0;
		if (Rl) ans= Rl->sum;
		
		R=Merge(Rl,Rr);
		root=Merge(L,R);

		return ans;
	}

	void Update(int l,int r,int s)
	{
		Tree *L,*R,*Rl,*Rr;

		Split(root,l-1,L,R);
		Split(R,r-l+1,Rl,Rr);

		if (Rl) Rl->add+=s;
	
		R=Merge(Rl,Rr);
		root=Merge(L,R);

	}

} T;


int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	
	n++;

	for (int i=1;i<=n;i++) T.insert(i);

	for (int i=1;i<=m;i++) {
		int code;
		scanf("%d",&code);
		if (code==1) {
			int l,r,s;
			scanf("%d%d%d",&l,&r,&s);
			l++;
			T.Update(l,r,s);

		} else
		{
			int l,r;
			scanf("%d%d",&l,&r);
			l++;
			printf("%d\n",T.FindSum(l,r));
			
		}

	}
	return 0;
}
