#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Node {
	int l,r;
	int c,x,y;
	Node()
	{
		l=r=c=x=y=0;
	}
};
vector< Node > root;
int n,rt;

void Norm(int v)
{
    if (v)
	root[v].c=root[root[v].l].c+root[root[v].r].c+1;
}

void Split(int v,int x,int &l,int &r)
{
	if (!v) {
		l=r=0;
		return;
	}	

	if (x>root[v].x) {
		Split(root[v].r,x,root[v].r,r); l=v;
		Norm(l);                          
	}   else
	{
		Split(root[v].l,x,l,root[v].l); r=v;
		Norm(r);
	}
}


void insert(int &v,int x,int y)
{
	if (!v || y>root[v].y) {
	        Node tmp=Node();
                Split(v,x,tmp.l,tmp.r);
                tmp.x=x;
                tmp.y=y;
        	root.push_back(tmp);
		v=root.size()-1;
	} else
	if (x>root[v].x) insert(root[v].r,x,y); else   
	if (x<root[v].x) insert(root[v].l,x,y);
	Norm(v);
}



int random()
{
	return (unsigned(rand())<<15+unsigned(rand()));
}

int Merge(int &l,int &r)
{
	if (!l || !r) return l+r; 
	if (root[l].y>root[r].y) {
		root[l].r=Merge(root[l].r,r);
		Norm(l);
		return l;
	} else
	{
		root[r].l=Merge(l,root[r].l);
		Norm(r);
		return r;
	}
}

void Delete(int &v,int x)
{
	if (!v) return;
	if (root[v].x>x) Delete(root[v].l,x); else
	if (root[v].x<x) Delete(root[v].r,x); else
	v=Merge(root[v].l,root[v].r);
	Norm(v);
}

void FindKTH(int v,int x)
{
	if (root[root[v].r].c+1==x) {
		printf("%d\n",root[v].x);
		return;
	} else
	if (root[root[v].r].c>=x) FindKTH(root[v].r,x); else
	FindKTH(root[v].l,x-root[root[v].r].c-1);
}

int main()
{
	freopen("input.txt","r",stdin);	
	freopen("output.txt","w",stdout);
	scanf("%d",&n);
	srand(time(NULL));
	root.reserve(n);
	int i,code,x,y;
	root.push_back(Node());
	for (i=0;i<n;i++){
		scanf("%d %d",&code,&x);
		if (code==1){  insert(rt,x,random());/* prn();*/}else
		if (code==0)  FindKTH(rt,x); else
		Delete(rt,x);
	}
	return  0;
}
