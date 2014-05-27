#include<iostream>
#include<vector>
using namespace std;
#define mp make_pair
#define f first
#define s second

string s;
int n, a[200][200], val[200], b[200][200], col[200], l[200], cc;

vector< pair<int,int> > L;

void Dfs(int v)
{
	col[v] = true;
	for (int i = 0; i <= n; i++)
	if (a[v][i] && !col[i]) Dfs(i);

	l[++l[0]] = v;
}

void Sfd(int v)
{
	col[v] = cc;
	for (int i = 0; i<= n; i++)
	if (b[v][i] && !col[i]) Sfd(i);
}

int main()
{
	freopen("input.txt","r",stdin);	
	freopen("output.txt","w",stdout);
	getline(cin,s);


	for (int i = 0; i < s.length(); i++) {
		int add = 0, v = 0;
		while (i < s.length() && s[i] != '~' && !isdigit(s[i])) ++i;
		if (s[i] == '~') add = 1 , i+=2;
		while (i < s.length() && isdigit(s[i])) v = v * 10 + s[i] - 48, ++i; 		
		v--; v = v * 2 + add;

		int u = 0; add = 0;
		while (i < s.length() && s[i] != '~' && !isdigit(s[i])) ++i;
		if (s[i] == '~') add = 1 , i+=2;
		while (i < s.length() && isdigit(s[i])) u = u * 10 + s[i] - 48, ++i; 		
		u--; u = u * 2 + add;		
		
		a[v^1][u] = true;
		a[u^1][v] = true;

		b[u][v^1] = true;
		b[v][u^1] = true;

		L.push_back( mp(u, v));
		n = max(n,max(u,v));

	}


	n = (n/2)*2+1;



	for (int i = 0; i <= n; i++)
	if (!col[i]) Dfs(i);

	for (int i = 0; i <= n; i++) col[i] = 0;
	
	for (int i = l[0]; i > 0; i--)
	if (!col[l[i]]) {
		cc++;
		Sfd(l[i]);
	}


	for (int i = 0; i <= n; i++)
	if (col[i] == col[i^1]) { puts("NO"); return 0; }

	puts("YES");

	for (int i = 0; i <= n; i++)	
	if (col[i] > col[i^1]) val[i / 2] = !(i&1);

	for (int i = 0; i < L.size(); i++) {
		int u = L[i].f, v = L[i].s;

		int x = val[u/2] , y = val[v/2];
		if (u&1) x=!x;
		if (v&1) y=!y;

		if (!(x || y)) { cerr<<"WA"; assert(false); }

	}

	return 0;
}
