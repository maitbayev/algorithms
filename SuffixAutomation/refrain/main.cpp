#include <iostream>
#include <cassert>        	
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back

struct state {
	int next[26];
	int len,suff,endpos,from;
} st[500000];

int sz,last,len,cnt[500000],m,p[500000],psz,sta[500000];
char s[500000];

vector<int> g[500000],aa;



void SA_add(char ch,int pos)
{
       	int p = last;
	int nv = sz++;
	st[nv].len = st[last].len+1;
	st[nv].endpos = pos;
	st[nv].from = last;

	memset(st[nv].next,-1,sizeof(st[nv].next));

	for (;p != -1 && st[p].next[ch] == -1; p = st[p].suff)
		st[p].next[ch] = nv;

	if (p == -1) st[nv].suff = 0; else
	{
		int q = st[p].next[ch];
		if (st[q].len == st[p].len+1) st[nv].suff = q; else
		{
			int clone = sz++;
			memcpy(st[clone].next,st[q].next,sizeof(st[clone].next));
			st[clone].from = p;
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

int Dfs(int v) {
	int stsz = 0;

	sta[stsz++] = v;

	while (stsz > 0) {
		int v = sta[--stsz];
		p[psz++] = v;
		for (int i = 0; i < g[v].size(); ++i)
			sta[stsz++] = g[v][i];
	}
	for (int i = psz-1; i >= 0; --i) {
		int v = p[i];
		cnt[v] = 0;
		if (st[v].endpos != -1) cnt[v] = 1;
		for (int i = 0; i < g[v].size(); ++i)	
			cnt[v] += cnt[g[v][i]];
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	sz = 1;
	
	last = 0;
	
	st[0].len = 0;
	st[0].suff = -1;
	
	memset(st[0].next,-1,sizeof(st[0].next));

	scanf("%d%d\n",&len,&m);
	for (int i = 0; i < len; ++i)
	{
		int x;
		scanf("%d",&x);
		SA_add(x-1,i);
	}
	
	for (int i = 1; i < sz; ++i)
		g[st[i].suff].pb(i);

	memset(cnt,-1,sizeof(cnt));
	Dfs(0);

	long long ans = 0;
	int cur = 0;
	for (int i = 0; i < sz; ++i) 
	if (st[i].len*1ll*cnt[i] > ans) {
		ans = st[i].len*1ll*cnt[i];
		cur = i;
	}

	printf("%I64d\n%d\n",ans,st[cur].len);
	psz = 0;
	while (cur != 0) {
		int t = st[cur].from;

		for (int i = 0; i < m; ++i)
			if (st[t].next[i] == cur) {
				p[psz++] = i+1;
				break;
			}
		cur = t;
	}

	for (int i = psz-1; i >= 0; --i)
		printf("%d ",p[i]);

}
