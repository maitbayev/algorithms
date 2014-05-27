#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;

struct state {
	int next[2];
	int end,suff;
} st[500000];
int sz,n,u[500000],to[500000][2],q[500000];
string s;

void Dfs(int v)
{
	u[v] = 1;

	for (int i = 0; i < 2; ++i)
	if (!st[to[v][i]].end) {
		if (u[to[v][i]] == 1) {
			puts("TAK");
			exit(0);
		} 
		if (!u[to[v][i]])
			Dfs(to[v][i]);	

	}
	u[v] = 2;
}
        
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	memset(st[0].next,-1,sizeof(st[0].next));
	st[0].suff = -1;
	st[0].end = 0;

	sz = 1;

	cin>>n;
	for (int i = 0; i < n; ++i) {
		cin>>s;
		

		int cur = 0;


		for (int j = 0; j < s.size(); ++j) {
			if (st[cur].next[s[j]-'0'] == -1) {
				memset(st[sz].next,-1,sizeof(st[sz].next));
				st[sz].end = false;
				st[cur].next[s[j]-'0'] = sz++;
			}
                        cur = st[cur].next[s[j]-'0'];
		}
		st[cur].end = true;
	}
	
	int head = 0, tail = 0;

	q[tail++] = 0;

	while (head != tail) {
		int cur = q[head++];

		for (int i = 0; i < 2; ++i)
			if (st[cur].next[i] != -1) to[cur][i] = st[cur].next[i]; else 
			if (cur > 0) to[cur][i] = to[st[cur].suff][i]; else
			to[cur][i] = cur;

		for (int i = 0; i < 2; ++i)
		if (st[cur].next[i] != -1) {
			int v = st[cur].next[i];
			q[tail++] = v;

			int p = st[cur].suff;
			for (;p != -1 && st[p].next[i] == -1; p = st[p].suff);

			if (p == -1) st[v].suff = 0; else
			st[v].suff = st[p].next[i];

			st[v].end |= st[st[v].suff].end;
		} 
	}

	Dfs(0);
	puts("NIE");
	return 0;


}
        	                           