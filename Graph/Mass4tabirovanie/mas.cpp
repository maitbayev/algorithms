#include <iostream>
#include <cstring>	
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
struct Edge {
	int from,to,c,f;
	Edge(){
		from = to = c = f = 0;
	}
	Edge(int ffrom,int tto,int cc)
	{
		from = ffrom;
		to = tto;
		c = cc;
	}
} E[10000];
int n,Esz,m,u[10000];
vector<int> a[10000];                                     



int Dfs(int v,int Min)
{
	if (v == n) return Min;

	u[v] = true;
	for (int i = 0; i < a[v].size(); i++) {
		Edge e = E[a[v][i]];
		int to = e.to;
		if (v == to) to = e.from;
		if (u[to]) continue;

		if (e.c - e.f > 0){
			int push = Dfs(to,min(Min,e.c-e.f));
			if (push > 0) {
				E[a[v][i]].f += push;
				E[a[v][i]^1].f -= push;
				return push;
			}
		} 
		 
	}
	return 0;
}

int main()
{                	                        
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i = 0; i < m; i++) {
		int u,v,c;
		scanf ("%d%d%d",&u,&v,&c);
		E[Esz++] = Edge(u,v,c);
		a[u].push_back(Esz-1);
		E[Esz++] = Edge(v,u,0);
		a[v].push_back(Esz-1);
	}

	int push,ans = 0;
	while (true){
		memset(u,0,sizeof(u));
		int push = Dfs(1,(1<<30));
		if (!push) break;
		ans+=push;
	}

	cout<<ans<<endl;




	return 0;
}