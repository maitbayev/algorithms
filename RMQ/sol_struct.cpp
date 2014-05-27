#include <iostream>
using namespace std;
const int maxn = 30000;

struct Tree {
	int Max,add;
	Tree()
	{
		Max=add=0;
	}
};

int n,m,k;

struct RMQ {
	
	Tree T[2*maxn+10];
	
	void Push(int v)
	{
		T[v].Max+=T[v].add;
		T[2*v].add+=T[v].add,T[2*v+1].add+=T[v].add;
		T[v].add=0;
	}

	int FindMax(int v,int l,int r,int sl,int sr)
	{
		if (l>r) return 0;
		if (sl==l && sr==r) return T[v].Max+T[v].add;
		Push(v);
		return max(FindMax(v*2,l,min(r,(sl+sr)/2),sl,(sl+sr)/2) , FindMax(v*2+1,max(l,(sl+sr)/2+1),r,(sl+sr)/2+1,sr));
	}

	void Update(int v,int l,int r,int sl,int sr)
	{       	
		if (l>r) return;
		if (sl==l && sr== r) {
			T[v].add++;
			return;
		}	

		Push(v);
		Update(v*2,l,min(r,(sl+sr)/2),sl,(sl+sr)/2);
		Update(v*2+1,max(l,(sl+sr)/2+1),r,(sl+sr)/2+1,sr);
		T[v].Max = max(T[v*2].Max+T[v*2].add,T[v*2+1].Max+T[v*2+1].add);
	}
	
	void Update(int l,int r) {
		Update(1,l,r,1,n);
	}
	
	int FindMax(int l,int r)
	{
		return FindMax(1,l,r,1,n);
	}


} T;



int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	scanf("%d%d%d",&n,&k,&m);

	for (int i=0;i<m;i++) {
		int l,r;
		scanf("%d%d",&l,&r);
		l++;
		if (T.FindMax(l,r) >= k) puts("0"); else
		{
			puts("1");
			T.Update(l,r);
		} 

	}
	return 0; 	
}
