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
struct Edge {
	int from, to, f, c;
	Edge(){}
	Edge(int _from, int _to, int _c) {
		from = _from; to = _to; c = _c; f = 0;
	}
};

Edge E[100000];
vi g[1000];
int dist[1000], q[1000], it[10000];
int En, n, S, T, m, B, D;

void addEdge(int u, int v, int c){
	E[En++] = Edge(u, v, c);
	g[u].pb(En - 1);
	E[En++] = Edge(v, u, 0);
	g[v].pb(En - 1);
}
       
bool Bfs() {
	for (int i = 0; i < 2 * n + 2; ++i) 
		dist[i] = -1;


	int head = 0, tail = 0;
	dist[S] = 0;
	q[tail++] = S;
	while (head != tail) {
		int v = q[head++];
	
		forit(it, g[v]) {
			Edge &e = E[*it];
			if (e.c - e.f <= 0 || dist[e.to] != -1) continue;
			dist[e.to] = dist[e.from] + 1;
			q[tail++] = e.to;
		}
	}
	return dist[T] != -1;
	
}

int Dfs(int v, int flow) {
	if (!flow) return 0;
	if (v == T) return flow;

	for (int &i = it[v]; i < g[v].size(); ++i) {
		Edge &e = E[g[v][i]];
	
		if (e.c - e.f <= 0 || dist[e.from] + 1 != dist[e.to]) continue;
		int push = Dfs(e.to, min(flow, e.c - e.f));
		if (push) {
			E[g[v][i]].f += push;
			E[g[v][i] ^ 1].f -= push;
			return push;
		}

	}
	return 0;
}


int maxFlow() {
	int flow = 0;
	while (Bfs()) {
		memset(it, 0, sizeof(it[0]) * (2 * n + 2));
		for(;;) {
			int push = Dfs(S, (int)1e9);
			if (!push) break;
			flow += push;
		}
	}
	return flow;
}
void Solve() {

	scanf("%d", &n);

	for (int i = 0; i < 2 * n + 2; ++i) 
		g[i].clear();

	En = 0;

	for (int i = 0; i < n; ++i) {
		int c;
		scanf("%d", &c);
		addEdge(i * 2, i * 2 + 1, c);
	}	

	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c); --u; --v;
		addEdge(u * 2 + 1, v * 2, c);
	}
	scanf("%d%d", &B, &D);
	S = 2 * n; T = 2 * n + 1;
	for (int i = 0; i < B; ++i) {
		int v;
		scanf("%d", &v); --v;
		addEdge(S, v * 2, 2010);
	}
	for (int i = 0; i < D; ++i) {
		int v;
		scanf("%d", &v); --v;
		addEdge(v * 2 + 1, T, 2010);
	}
	printf("%d\n", maxFlow());
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
