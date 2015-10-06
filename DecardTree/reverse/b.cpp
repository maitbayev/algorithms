#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <ctime> 
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

#define f first
#define s second
#define pb push_back
#define vi vector<int>
#define all(v) (v).begin(), (v).end()
#define sz(v) (int)(v).size()
#define f0(a) memset(a, 0, sizeof(a))
#define ll long long
#define pii pair<int, int>
#define mp make_pair


struct Tree {
	Tree *le, *ri;
	int y, value, size; 
	bool rev;
	Tree(int _value) {
		le = ri = 0;
		value = _value;
		y = rand();
		size = 1;
		rev = 0;
	}
	void push() {
		if (!rev) return;
		swap(le, ri);
		if (le) le->rev ^= 1;
		if (ri) ri->rev ^= 1;
		rev = 0;
	}

	void norm() {
		size = 1;
		if (le) size += le -> size;
		if (ri) size += ri -> size;
	}
} *root;

Tree * Merge(Tree *le, Tree *ri) {

	if (!le) return ri;
	if (!ri) return le;

	le -> push(); ri -> push();
	if (le -> y > ri -> y) {
		le -> ri = Merge(le -> ri, ri);
		le -> norm();
		return le;
	} else {
		ri -> le = Merge(le, ri -> le);
		ri -> norm();
		return ri;
	}
}


void Split(Tree *v, int x, Tree *&le, Tree *&ri) {

	if (!v) {
		le = ri = 0;
		return;
	}

	v -> push();
	int index = 1;
	if (v -> le) index += v -> le -> size;
	if (index < x) {
		Split(v -> ri, x - index, v -> ri, ri);
		le = v; 
	} else {
		Split(v -> le, x, le, v -> le);
		ri = v;
	}

	v -> norm();
}

void Display(Tree *v) {
	if (!v) return;
	v -> push();
	Display(v->le);
	printf("%d ", v->value);
	Display(v->ri);
}
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) 
		root = Merge(root, new Tree(i));

	for (int i = 0; i < m; ++i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		Tree *t1, *t2, *t3;
		Split(root, a + 1, t1, t2);
		Split(t2, b + 1, t2, t3);
		t2 -> rev ^= 1;

		root = Merge(t1, t3);
		Split(root, c + 1, t1, t3);
		root = Merge(t2, t3);
		root = Merge(t1, root);
	}
	Display(root);
	return 0;
}
