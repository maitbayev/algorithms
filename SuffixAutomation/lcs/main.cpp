#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
struct state {
	int next[26];
	int len,suff;
} st[100000];
int sz,last;
char s[10000],t[10000];

void SA_add(char ch)
{
	int nv = sz++;
	st[nv].len = st[last].len+1;
	memset(st[nv].next,-1,sizeof(st[nv].next));
	int p = last;
	for (;p != -1 && st[p].next[ch] == -1; p = st[p].suff)
		st[p].next[ch] = nv;
	if (p == -1) st[nv].suff = 0; else
	{
		int q = st[p].next[ch];
		if (st[q].len == st[p].len+1) st[nv].suff = q; else
		{
			int clone = sz++;
			memcpy(st[clone].next,st[q].next,sizeof(st[clone].next));
			st[clone].len = st[p].len+1;
			st[clone].suff = st[q].suff;
			for (;p != -1 && st[p].next[ch] == q; p = st[p].suff)
				st[p].next[ch] = clone;
			st[q].suff = st[nv].suff = clone;
		}
	}
	last = nv;
}


int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	last = 0;
	sz = 1;
	memset(st[0].next,-1,sizeof(st[0].next));
	st[0].len = 0;
	st[0].suff = -1;


	gets(s);
	for (int i = 0; s[i] != 0; ++i)
		SA_add(s[i]-'a');

	gets(t);

	int len = 0, p = 0,ans = 0,pos = 0;
	
	for (int i = 0; t[i] != 0; ++i) {
		if (st[p].next[t[i]-'a'] != -1) {
			++len;
			p = st[p].next[t[i]-'a'];
		} else
		{
			for (;p != -1 && st[p].next[t[i]-'a'] == -1; p = st[p].suff);
			if (p == -1) p = 0,len = 0; else
			{
			       	len = st[p].len+1;
				p = st[p].next[t[i]-'a'];
			}
		}

		if (ans < len) {
			ans = len;
			pos = i-len+1;
		}
	}

	for (int i = 0; i < ans; ++i)
		putchar(t[i+pos]);
	return 0;
}
