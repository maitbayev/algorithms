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
#define mp make_pair
#define pb push_back
#define pii pair<int, int>
#define vi vector<int>
#define all(v) (v).begin(), (v).end()
#define forit(it,v) for (typeof(v.begin()) it = v.begin(); it != v.end(); ++it)
#define f0(a) memset(a, 0, sizeof(a))
#define ll long long
struct Point { 
	int x, y;
	Point() {
		x = y = 0;
	}
	Point(int _x, int _y) {
		x = _x; y = _y;
	}
	bool operator < (Point a) const{
		return (x < a.x || (x == a.x && y < a.y));
	}
	Point operator - (Point a) {
		return Point(x - a.x, y - a.y);
	}
	ll scal(Point a) {
		return x * a.x + y * a.y;
	}
	ll operator * (Point a) {
		return 1ll * x * a.y - 1ll * y * a.x;
	}
	ll sdist() {
		return x * x + y * y;
	}
	ll sdist(Point a) {
		a.x -= x;
		a.y -= y;
		return a.sdist();
	}
	void read() {
		scanf("%d%d", &x, &y);
	}
};

int n;
vector<Point> a[2];
Point origin;

ll area(Point o, Point p, Point q) {
	return (p - o) * (q - o);
}
void convex_hull(vector<Point> &a) {
	if (a.size() <= 2) return;
	sort(all(a));
	Point p1 = a[0], p2 = a.back();
	vector<Point> up, down;
	up.pb(p1); down.pb(p1);
	for (int i = 1; i < n; ++i) {
		if (i == n - 1 || area(p1, a[i], p2) < 0) {
			while (up.size() >= 2 && area(up[(int)up.size() - 2],
						up[(int)up.size() - 1], a[i]) >= 0) 
				up.pop_back();
			up.pb(a[i]);
		}
	
		if (i == n - 1 || area(p1, a[i], p2) > 0) {
			
			while (down.size() >= 2 && area(down[(int)down.size() - 2],
						down[(int)down.size() - 1], a[i]) <= 0) 
				down.pop_back();
			down.pb(a[i]);
		}
	}
	a.clear();
	for (int i = 0; i < (int)down.size(); ++i)
		a.pb(down[i]);
	for (int i = (int)up.size() - 2; i > 0; --i)
		a.pb(up[i]);
}

bool cmp_ang(Point a, Point b) {
	ll A = area(origin, a, b);
	if (A > 0) return true;
	if (A < 0) return false;
	return a.sdist(origin) < b.sdist(origin);
}

bool inside_tr(Point a, Point b, Point c, Point p) {
	ll A = abs(area(a, b, c));
	A -= abs(area(a, b, p));
	A -= abs(area(a, c, p));
	A -= abs(area(b, c, p));
	return A == 0;
}

bool inSegment(Point a, Point b, Point p) {
	if (area(a, b, p) != 0) return false;
	if ((p - a).scal(b - a) < 0) return false;
	if ((p - b).scal(a - b) < 0) return false;
	return true;
}
int doit(vector<Point> a, vector<Point> b) {
	convex_hull(a);
	origin = a[0];
	sort(all(b), cmp_ang);
	int inside = 0, j = 0;
	for (int i = 1; i + 1 < (int)a.size(); ++i) {
		while (j < b.size() && cmp_ang(b[j], a[i]))
			++j;

		while (j < b.size() && cmp_ang(b[j], a[i + 1])) {
			inside += inside_tr(origin, a[i], a[i + 1], b[j]);
			++j;
		}
				
	}
	while (j < b.size()) {
		inside += 
			inSegment(a[(int)a.size() - 1], a[(int)a.size() - 2], b[j++]);
	}
	return inside;

}
int main() {
	freopen("curling.in", "r", stdin);
	freopen("curling.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < 2; ++i) {
		a[i].resize(n);
		for (int j = 0; j < n; ++j) 
			a[i][j].read();
	}
	cout << doit(a[0], a[1]) << " " << doit(a[1], a[0]) << endl;

	return 0;
}

