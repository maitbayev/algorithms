#include <iostream>
#include <algorithm>
using namespace std;

#define mp make_pair
#define f first
#define s second

int p[100],r[100],n,m;
pair<int,pair<int,int> > a[1000];


int findSet(int v)
{
	if (p[v] != v) p[v] = findSet(p[v]);
	return p[v];
}

void joinSet(int u,int v)
{
	u = findSet(u);
	v = findSet(v);
	if (u == v) return;
	if (r[u] > r[v]) p[v] = u; else
	{
		p[u] = v;
		if (r[u] == r[v]) p[v]++;
	}
}


int main()
{
	cin>>n;
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++)
	{
		int x;
		cin>>x;
		if (x == 0) joinSet(i,j);
		a[m++] = mp(x,mp(i,j));
	}

	sort(a,a+m);

	int ans= 0;
	for (int i = 0; i < m; ++i) 
		if (findSet(a[i].s.f) != findSet(a[i].s.s)) ans+=a[i].f,joinSet(a[i].s.f,a[i].s.s);
	cout<<ans<<endl;
	return 0;
}