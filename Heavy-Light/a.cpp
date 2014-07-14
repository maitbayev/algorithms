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
const int maxn = (int)2e5;
const int logn = 20;
int pos[maxn];

struct Tree {
    int sum;
    int push;
    Tree() {
        sum = push = 0;
    }
};
struct IntervalTree {
    vi A;
    vector<Tree> T;
    int N;

    IntervalTree() {
        A.clear(); 
    }
    void init() {
        N = (int)A.size();
        for (int i = 0; i < N; ++i)
            pos[A[i]] = i;       

        T.resize(4 * N);
        //DELETE ME:
        for (int i = 0; i < T.size(); ++i)
            T[i] = Tree();
    }
    
    void Push(int v, int sl, int sr) {
        T[v].sum += (sr - sl + 1) * T[v].push;
        if (sl != sr) {
            T[v + v].push += T[v].push;
            T[v + v + 1].push += T[v].push;
        }
        T[v].push = 0;
    }

    void update(int v, int sl, int sr, int l, int r) {
        Push(v, sl, sr);
        if (min(sr, r) < max(sl, l)) return;
        if (l <= sl && sr <= r) {
            T[v].push++;
            Push(v, sl, sr);
            return;
        }
        int mid = (sl + sr) / 2;
        update(v + v, sl, mid, l, r);
        update(v + v + 1, mid + 1, sr, l, r);
        T[v].sum = T[v + v].sum + T[v + v + 1].sum;
    }
    
    int findSum(int v, int sl, int sr, int l, int r) {
        Push(v, sl, sr);
        if (min(sr, r) < max(sl, l)) return 0;
        if (l <= sl && sr <= r) 
            return T[v].sum;
        int mid = (sl + sr) / 2;
        return findSum(v + v, sl, mid, l, r)
             + findSum(v + v + 1, mid + 1, sr, l, r);
    }

    void inc(int l, int r) {
        update(1, 0, N - 1, l, r);
    }

    int sum(int l, int r) {
        return findSum(1, 0, N - 1, l, r);
    }
} T[maxn];

int wh[maxn], Tn;
int n, m;
vi g[maxn];
int par[maxn], size[maxn], u;
int up[maxn][logn + 1];
int tin[maxn], tout[maxn], timer;


void Dfs(int v, int p) {

    size[v] = 1;
    tin[v] = ++timer;
    up[v][0] = p; 

    for (int l = 1; l <= logn; ++l)
        if (up[v][l - 1] != -1)
            up[v][l] = up[up[v][l - 1]][l - 1];

    int av = -1;
    forit(it, g[v]) {
        int to = *it;
        if (to == p) continue;
        Dfs(to, v);
        
        if (av == -1 || size[to] > size[av])
            av = to;

        size[v] += size[to];
    }

    if (av != -1 && (size[v] + 1) / 2 <= size[av]) { 
        T[wh[av]].A.pb(v);
        wh[v] = wh[av];
    } else {
        Tn++;
        T[Tn - 1].A.pb(v);
        wh[v] = Tn - 1;
    }

    tout[v] = ++timer;

}

bool upper(int u, int v) {
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}

int LCA(int u, int v) {
    if (upper(u, v)) return u;
    if (upper(v, u)) return v;
    for (int k = logn; k >= 0; --k)
        if (up[u][k] != -1 && !upper(up[u][k], v))
            u = up[u][k];
    return up[u][0];
}

int query(int v, int par, char c) {

    int ans = 0;

    while (v != par) {
        int le = pos[v];
        
        if (wh[v] == wh[par]) {
            int ri = pos[par] - 1;
            if (c == 'P')
                T[wh[v]].inc(le, ri);
            else
                ans += T[wh[v]].sum(le, ri);
            break;
        }
        int ri = T[wh[v]].N - 1;
        if (c == 'P')
            T[wh[v]].inc(le, ri);
        else
            ans += T[wh[v]].sum(le, ri);
        v = up[T[wh[v]].A.back()][0];
    }
    return ans;
}


int main() {
	scanf("%d%d", &n, &m);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v); --u; --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    memset(up, -1, sizeof(up));
    Dfs(0, -1);

    for (int i = 0; i < Tn; ++i) 
        T[i].init();

    for (int it = 0; it < m; ++it) {
        char c;
        int u, v;
        scanf("\n%c %d %d", &c, &u, &v); --u; --v;

        int lc = LCA(u, v);

        int ans = query(u, lc, c);
        ans += query(v, lc, c);
        if (c == 'Q')
            printf("%d\n", ans);
    }
    return 0;
}

