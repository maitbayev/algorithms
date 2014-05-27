#include<iostream>
#include<vector>
using namespace std;
#define mp make_pair
#define f first
#define s second

string s;
int n, a[200][200], val[200], b[200][200], col[200], l[200], cc, nn;

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

	cin>>nn;
	
	for (int i = 0; i < nn; i++) {
		int u,v;
		cin>>v>>u;
		v +=v; u += u;

		a[v^1][u] = true;
		a[u^1][v] = true;

		b[u][v^1] = true;
		b[v][u^1] = true;

		L.push_back( mp(u, v));
		n = max(n,max(u+1,v+1));
	}

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
	
	for (int i = 0; i <= n/2; i++)
	cout<<val[i]<< " ";

	for (int i = 0; i < L.size(); i++) {
		int u = L[i].f, v = L[i].s;

		int x = val[u/2] , y = val[v/2];
		if (u&1) x=!x;
		if (v&1) y=!y;

		if (!(x || y)) { cerr<<"WA"; assert(false); }

	}

	return 0;
}
