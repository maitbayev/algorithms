#include <iostream>
#include <cassert>        	
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back
const int maxn = (int)1e6;
struct state {
	int next[26];
	int len, suff, endpos;
    state() {
        memset(next, -1, sizeof(next));
        suff = -1;
        len = endpos = 0;
    }
} st[maxn];

int sz = 1, last;
int cnt[maxn];
char s[maxn];

vector<int> g[maxn];



void SA_add(char ch,int pos)
{   int p = last;
	int nv = sz++;
	st[nv].len = st[last].len + 1;
	st[nv].endpos = pos;

	for (;p != -1 && st[p].next[ch] == -1; p = st[p].suff)
		st[p].next[ch] = nv;

	if (p == -1) st[nv].suff = 0; else
	{
		int q = st[p].next[ch];
		if (st[q].len == st[p].len+1) st[nv].suff = q; else
		{
			int clone = sz++;
			memcpy(st[clone].next,st[q].next,sizeof(st[clone].next));
			st[clone].endpos = -1;
			st[clone].len = st[p].len+1;
			st[clone].suff = st[q].suff;
			
			for (;p != -1 && st[p].next[ch] == q; p = st[p].suff)
				st[p].next[ch] = clone;
			
			st[q].suff = st[nv].suff = clone;
		}
	}
	last = nv;
}

void Dfs(int v) {
    if (cnt[v] != -1) return;
    cnt[v] = 0;
    if (st[v].endpos != -1) cnt[v] = 1;

	for (int i = 0; i < g[v].size(); ++i) {
        Dfs(g[v][i]);
		cnt[v] += cnt[g[v][i]];
    }	
}

int main()
{   
    scanf("%s", s);
	for (int i = 0; s[i]; ++i)
	    SA_add(s[i] - 'a',i);
	

	for (int i = 1; i < sz; ++i)
		g[st[i].suff].pb(i);

	memset(cnt, -1, sizeof(cnt));
	Dfs(0);

	long long ans = 0;
	for (int i = 0; i < sz; ++i) {
        Dfs(i);
	    ans = max(ans, 1ll * st[i].len * cnt[i]);
    }
	cout << ans << endl;
    return 0;
}
