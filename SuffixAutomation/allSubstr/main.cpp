#include <iostream>             	
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back

struct state {
	int next[26];
	int len,suff,endpos;
} st[10000];

int sz,last,len;
char s[10000];

vector<int> g[1000],aa;



void SA_add(char ch,int pos)
{
       	int p = last;
	int nv = sz++;
	st[nv].len = st[last].len+1;
	st[nv].endpos = pos;
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

void Dfs(int v,int len) {
	
//	cerr<<v<<endl;

	if (st[v].endpos != -1) aa.pb(st[v].endpos-len+1);

	for (int i = 0; i < g[v].size(); ++i)
		Dfs(g[v][i],len);
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

	scanf("%d\n",&len);
	for (int i = 0; i < len; ++i)
	{
		s[i] = getchar();
		SA_add(s[i]-'a',i);
	}
	
	for (int i = 0; i < sz; ++i)
		g[st[i].suff].pb(i);

	int l,r;
	scanf("%d %d",&l,&r);

	int cur = 0;
	
	for (int i = l; i <= r; ++i)
		cur = st[cur].next[s[i]-'a'];
	Dfs(cur,r-l+1);

	sort(aa.begin(),aa.end());
	for (int i = 0; i < aa.size(); ++i)
		cout<<aa[i]<< " ";

}
