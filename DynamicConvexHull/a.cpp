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
const int maxn = (int)1e6;
const ll inf = (int)1e18;
struct Line {
	ll m, b;
	double x;
	Line(ll _x) {
		x = _x;
		m = b = inf;
	}
	Line(ll _m, ll _b) {
		m = _m; b = _b; x = -inf;
	}
	bool operator < (const Line & other) const {	
		if (other.m == inf || m == inf) {
			return x < other.x;
		}
		return m > other.m;
	}
	ll getAt(ll x) const {
		return m * x + b;
	}
};

double intersect(Line x, Line y) {
	assert(x.m != y.m);
	return (y.b - x.b + 0.0) / (x.m - y.m + 0.0);
}

struct ConvexHull {
	multiset<Line> hull;

	bool bad(const set<Line>::iterator &y) {
		set<Line>::iterator x, z;

		if (y != hull.begin()) {
			x = prev(y);
			if (x->m == y->m) return (y->b >= x->b);
		}

		z = next(y);
		if (z != hull.end() && z->m == y->m) {
			return (y->b >= z->b);
		}

		if (y == hull.begin() || z == hull.end()) 
			return false;
		return intersect(*x, *y) >= intersect(*x, *z);
	}

	void updateLeft(set<Line>::iterator it) {
		if (it == hull.begin()) {
			return;
		}
		double x = intersect(*it, *prev(it));
		Line l(*it);
		l.x = x;
		hull.erase(it);
		hull.insert(l);
	}

	void insert_line(ll m, ll b) {
		auto it = hull.insert(Line(m, b));
		if (bad(it)) {hull.erase(it); return; }

		while (next(it) != hull.end() && bad(next(it)))
			hull.erase(next(it));
		while (it != hull.begin() && bad(prev(it))) 
			hull.erase(prev(it));

		updateLeft(it);

		if (it != hull.begin())
			updateLeft(prev(it));
		if (next(it) != hull.end()) 
			updateLeft(next(it));
	} 

	ll getBest(double x) {
		if (hull.empty()) return inf;
		auto it = hull.lower_bound(Line(x));
		return prev(it)->getAt(x);
	}
};

ConvexHull T[maxn*2+1];

int n;
int p[maxn];
int a[maxn];
int A[maxn], An;
int h[maxn];
ll dp[maxn];

void update(int v, ll m, ll b) {
	v += n;
	while (v > 0) {
		T[v].insert_line(m, b);
		v /= 2;
	}
}

ll findMin(int l, int r, ll x) {
	l += n; r += n;
	ll res = inf;
	while (l <= r) {
		if (l & 1) res = min(res, T[l].getBest(x));
		if (!(r & 1)) res = min(res, T[r].getBest(x));
		l = (l + 1) / 2;
		r = (r - 1) / 2;
	} 
	return res;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &p[i]); --p[i];
	}
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < n; ++i)
		scanf("%d", &h[i]);

	dp[0] = a[0];
	update(p[0], -2ll*h[0], dp[0] + 1ll*h[0]*h[0]);
	for (int i = 1; i < n; ++i) {
		dp[i] = findMin(0, p[i] - 1, h[i]);
		if (dp[i] < inf) {
			dp[i] += 1ll*h[i]*h[i] + a[i];
			update(p[i], -2*h[i], dp[i] + 1ll*h[i]*h[i]);
		}
	}
	cout << dp[n - 1] << endl;
	return 0;
}
