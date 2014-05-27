#include <iostream>                                                                    
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;

struct Edge { 
	int from,to,f,c,add,id;
	Edge()
	{
		from = to = f = id = add = c = 0;
	}
	
	Edge(int ffrom,int tto,int ff,int cc,int addd,int idd)
	{
		from = ffrom; to = tto;
		id = idd;
                f = ff; c = cc;
                add = addd;
	}
	
}e[10000];
int esz,n,m,d[10000],q[10000],it[1000],ans[1000],L[1000],R[1000],mn[1000],mx[1000],in[1000],out[1000];
vector<int> a[204];

void AddEdge(int u,int v,int c,int add,int id)
{
	e[esz++] = Edge(u,v,0,c,add,id);
	a[u].push_back(esz-1);
	e[esz++] = Edge(v,u,0,0,0,0);
	a[v].push_back(esz-1);
}

bool Bfs(int s,int t)
{
	for (int i = s; i <= t; i++) d[i] = -1;
	
	int r = 0, w = 0;
	d[s] = 0;
	q[++w] = s;
	while (r!=w) {
		int v = q[++r];
		for (int i = 0; i < a[v].size(); i++) {
			int to = e[a[v][i]].to;
			if (d[to] == -1 && e[a[v][i]].c - e[a[v][i]].f > 0) {
				d[to] = d[v] +1;
				q[++w] = to;
			}
		}
	}
	return d[t]!=-1;
}

int Dfs(int v,int flow)
{
	if (v == n+1) return flow;
	if (!flow) return 0;

	for (;it[v] < a[v].size(); ++it[v]) {
		
		int id = a[v][it[v]];
		int to = e[id].to;
		if (d[to] != d[v]+1) continue;
		if (e[id].c - e[id].f <= 0) continue;
		int tmp = Dfs(to,min(flow,e[id].c-e[id].f));

		if (tmp > 0) {
			e[id].f+=tmp;
			e[id^1].f-=tmp;
			return tmp;
		}
	}
	return 0;
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i = 1; i <= m; i++) {
		int u,v,l,r;
		scanf("%d%d%d%d",&u,&v,&l,&r);
		AddEdge(u,v,r-l,l,i);
		AddEdge(u,n+1,l,-1,0);
		AddEdge(0,v,l,-1,0);
		L[i] = u; R[i] = v;
		mn[i] = l; mx[i] = r;
	}
	
	while (Bfs(0,n+1)) 
	{
		memset(it,0,sizeof(it));
		while (Dfs(0,(1<<30)));
	}

	for (int i = 0; i < esz; i++) {
		ans[e[i].id] += e[i].f+e[i].add;  
	}
        
        for (int i = 1; i <= m; i++) {
        	in[R[i]] += ans[i];
        	out[L[i]] += ans[i];
        	if (!(mn[i] <= ans[i] && ans[i] <= mx[i])) {
        		puts("NO");
        		return 0;
        	}
        }

        for (int i = 1; i <= n; i++)
        if (in[i] != out[i]) {
        	puts("NO");
        	return 0;
        }
        puts("YES");
        for (int i = 1; i <= m; i++) cout<<ans[i]<< endl;
	return 0;
}
