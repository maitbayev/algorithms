#include <iostream>             		
#include <cstdio>
#include <cstring>
using namespace std;
struct state {
	int next[26]; 
	int suff,len; 
} st[200020];
char s[100002];
int last,sz;


void SA_add(int ch)
{
	int p = last;
	int nv = sz++;
	st[nv].len = st[last].len+1;
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

			st[clone].suff = st[q].suff;
			st[clone].len = st[p].len+1;
			
			for (;p != -1 && st[p].next[ch] == q; p = st[p].suff)
				st[p].next[ch] = clone;

			st[nv].suff = st[q].suff = clone;
		}

	}
	last = nv;
}


int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	memset(st[0].next,-1,sizeof(st[0].next));
	st[0].suff = -1;
	st[0].len = 0;
	last = 0;
	sz = 1;
	
	char ch;
	while(scanf("%c %s\n",&ch,&s) == 2) {
		int len = strlen(s);
		if (ch == '?') {
			int cur = 0;
			bool ok = true;
			for (int i = 0; i < len; ++i) {
				cur = st[cur].next[tolower(s[i])-'a'];
				if (cur == -1) {
					ok = false;
					break;
				}
			}	
			puts(ok ? "YES" : "NO");
		} else
		{
			for (int i = 0; i < len; ++i)
				SA_add(tolower(s[i])-'a');
		}
	}
	for (int i = 0; i < sz; ++i) {
		cout<<"state "<<i<<endl;
		for (int j = 0; j < 26; ++j)
			if (st[i].next[j] != -1)  cout<<char(j+'a')<< " "<<st[i].next[j]<<endl;
	}

	return 0;
}
                  