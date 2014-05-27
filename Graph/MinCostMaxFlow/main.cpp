#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <set>
#include <ctime>
#include <cassert>
#include <queue>

using namespace std;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define forit(it,con) for (typeof(con.begin()) it = con.begin(); it != con.end(); ++it)
#define f0(a) memset(a, 0, sizeof(a))
#define all(v) v.begin(), v.end()
#define pii pair<int,int>
#define vi vector<int>
#define ll long long
#ifdef WIN32
	#define I64 "%I64d"
#else 
	#define I64 "%lld"
#endif
const int inf = (int)1e8;
const int di[4] = {0, 0,  1, -1};
const int dj[4] = {1, -1, 0,  0};

struct Edge { 
	int from, to, f, c, cost;
	Edge(){}
	Edge(int _from, int _to, int _c, int _cost) {
		from = _from; to = _to; c = _c; cost = _cost;
		f = 0;
	}
};
Edge E[10000];
vi g[1000];
int a[1000], b[1000], phi[1000], dist[1000], used[1000], fr[1000];
int dis[100][100];
char s[100][100];
pii q[10000];
int En, N, n;

inline void addEdge(int u, int v, int c, int cost) {
	E[En++] = Edge(u, v, c, cost);
	g[u].pb(En - 1);
	E[En++] = Edge(v, u, 0, -cost);
	g[v].pb(En - 1);
}

bool Dijikstra() {

	for (int i = 0; i < N; ++i) {
		dist[i] = inf;
		used[i] = false;
	}

	dist[0] = 0;

	for (;;) {
		int v = -1;
		for (int i = 0; i < N; ++i) 
			if (!used[i] && (v == -1 || dist[v] > dist[i]))	
				v = i;
		if (v == -1 || dist[v] == inf) break;
		used[v] = true;
		forit (it, g[v]) {
			Edge &e = E[*it];
			if (e.c - e.f > 0 && dist[e.to] > dist[e.from] + e.cost + phi[e.from] - phi[e.to]) {
				dist[e.to] = dist[e.from] + e.cost + phi[e.from] - phi[e.to];
				fr[e.to] = *it;
			}
		}
	}  
	for (int i = 0; i < N; ++i)
		phi[i] += dist[i];
	return dist[N - 1] < inf;
}

inline int minCostMaxFlow() {

	for (int i = 0; i < N; ++i)
		phi[i] = inf;

	phi[0] = 0;
	for (int it = 0; it < N + 10; ++it) {
		for (int i = 0; i < En; ++i) if (E[i].c > 0) {
			int u = E[i].from, v = E[i].to;
			phi[v] = min(phi[v], phi[u] + E[i].cost);
		}
	}

	while (Dijikstra()) {
		int t = N - 1;	
		while (t != 0) {
			E[fr[t]].f++;
			E[fr[t] ^ 1].f--;
			t = E[fr[t]].from;
		}
	}

	int ans = 0;
	for (int i = 0; i < En; ++i) 
		if (E[i].f > 0)
			ans += E[i].f * E[i].cost;
	return ans;
}

void Solve() {
	
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &b[i]);
	N = n + n + 2;
	for (int i = 0; i < N; ++i) 
		g[i].clear();
	En = 0;

	for (int i = 1; i <= n; ++i) {
		addEdge(0, i, 1, 0);
		addEdge(i + n, N - 1, 1, 0);
		for (int j = 1; j <= n; ++j) {
			int cost = 0;
			if (a[i] > b[j]) cost = -2;
			if (a[i] == b[j]) cost = -1;
			addEdge(i, j + n, 1, cost);
		}
	}
	
	printf("%d\n", -minCostMaxFlow());	
}

int main() {
	#ifdef LOCAL
		freopen("in","r",stdin);
		freopen("out","w",stdout);
	#endif
	int tests; 
	scanf("%d", &tests);
	for (int test = 1; test <= tests; ++test) {
		printf("Case %d: ", test);
		Solve();
	}
	return 0;
}

