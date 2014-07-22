#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define pb push_back
#define vi vector<int>
const int maxn = (int)1e6;
struct Tree {
	Tree *L, *R, *P;
	int y, v;
	int size;
	bool rev;
	Tree()
	{
		P = L = R = 0;
		y = rev = 0;
		size = 0;
	}
} *root;

Tree *wh[maxn];
int p[maxn], pn;

int Count(Tree *root)
{
	if (!root) return 0;
	return root -> size;
}

void Norm(Tree *&root)
{
	if (!root) return;
	root -> size = Count(root -> L) + Count(root -> R) + 1;
}

void Push(Tree *&root)
{
	if (!root) return;
	if (!root->rev) return;

	root -> rev = false;

	swap(root -> L, root -> R);

	if (root -> L) root -> L ->rev ^= true;
	if (root -> R) root -> R ->rev ^= true;
}

void Split(Tree *v, int x, Tree *&l, Tree *&r)
{
	if (!v) {
		l = r = 0; 
		return;
	}

	Push(v);

	if (Count(v -> L) + 1 <= x) {
		Split(v -> R, x - Count(v -> L) - 1, v->R, r);
		if (v -> R) v -> R -> P = v;
		v -> P = NULL;
		l = v;
		Norm(l);
	} else
	{
		Split(v -> L, x, l, v -> L);
		if (v -> L) v -> L -> P = v;
		v -> P = NULL;
		r = v;
		Norm(r);
	}        
}


Tree * Merge(Tree *l,Tree *r)
{
	if (!l) return r;
	if (!r) return l;

	Push(l); Push(r);

	if (l->y > r->y) {
		l -> R = Merge(l -> R, r);
		if (l -> R) l -> R -> P = l;
		l -> P = NULL;
		Norm(l);
		return l;
	} else
	{
		r -> L = Merge(l, r -> L);
		if (r -> L) r -> L -> P = r;
		r -> P = NULL;
		Norm(r);
		return r;
	}
}

void Reverse(int l,int r)
{
	Tree *t1, *t2, *t3;
	Split(root,l-1 , t1, t2);	
	Split(t2, r - l + 1, t2, t3);

	if (t2) t2 -> rev ^= true;
	root = Merge(Merge(t1, t2), t3);
}

int getPos(int p) {

	Tree *v = wh[p];
	vi seq;
	while (v -> P) {
		Tree *p = v -> P;
		seq.pb(p -> R == v);
		v = p;
	}
	
	v = root;
	reverse(seq.begin(), seq.end());
	int pos = 0;
	for (int i = 0; i < seq.size(); ++i) {
		int to = seq[i];
		if (v -> rev) {
			to = 1 - to;
			Push(v);
		}
		if (to == 1) {
			pos += Count(v -> L) + 1;
			v = v -> R;
		} else {
			v = v -> L;
		}
	}
	Push(v);
	pos += Count(v -> L) + 1;
	return pos;
	
}
int main()
{
	int n,m;
	scanf("%d %d",&n, &m);
	for (int i = 1; i <= n; i++) {
		Tree *t = new Tree();
		t -> v = i;
		t -> y = (rand()<<16)|rand();
		t -> size = 1;
		wh[i] = t;
		root = Merge(root, t);
	
	}

	for (int i = 0;i < m; i++) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int l, r;
			scanf("%d%d", &l, &r);
			Reverse(l, r);
		} else if (type == 2) {
			int v;
			scanf("%d", &v);
			printf("element %d is at position %d\n", v, getPos(v));
		} else if (type == 3) {
			int p;
			scanf("%d", &p);
			Tree *t1, *t2, *t3;
			Split(root, p, t2, t3);
			Split(t2, p - 1, t1, t2);
			printf("element at position %d is %d\n", p, t2 -> v);
			root = Merge(Merge(t1, t2), t3);
		}
	}

}
