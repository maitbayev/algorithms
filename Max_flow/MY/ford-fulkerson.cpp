#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int n,s,t,m,c[99][99],R[99],Z[99][99],C[99],p[99],q[10000],f[99][99],ans;
bool u[99];

void BuildGraph()
{
	s=0; t=n+m+1;
	int i,j;
	for (i=1;i<=n;i++)
	c[0][i]=R[i];


	for (i=1;i<=n;i++)
	for (j=1;j<=m;j++)
	if (Z[i][j]==-1) 
		c[i][j+n]=(1<<29);

        for (j=1;j<=m;j++)
        c[j+n][t]=C[j];
		
}
                 
int min(int a,int b)
{
    return (a>b)?b:a;
}

bool Bfs()
{
	memset(u,0,sizeof(u));
        int r=0,w=1;
	u[s] = true;
	p[s] = -1;
	q[w] = s;
	int cur,i;
	while (r!=w)
	{
		cur=q[++r];
		for (i=s;i<=t;i++)
		if (c[cur][i]-f[cur][i]>0 && !u[i]) {
			p[i]=cur;
			u[i]=true;
			q[++w]=i;
		}

	}
	return u[t];
}

void MaxFlow()
{

	while (Bfs()){
		int k=t;
    	    	int mn=(1<<30);
		while (k!=s){
			mn=min(mn,c[p[k]][k]-f[p[k]][k]);
			k=p[k];
		}
		k=t;
		while (k!=s){
			f[p[k]][k]+=mn;
			f[k][p[k]]-=mn;
			k=p[k];
		}
		ans+=mn;
	}
	printf("%d",ans);
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&m);
	int i,j;
	for (i=1;i<=n;i++) scanf("%d",&R[i]);
	for (i=1;i<=m;i++) scanf("%d",&C[i]);
	for (i=1;i<=n;i++)
	for (j=1;j<=m;j++) {
		scanf("%d",&Z[i][j]);
		if (Z[i][j]!= -1) {
			R[i]-=Z[i][j];
			C[j]-=Z[i][j];
			if (R[i]<0) {
				puts("-1");
				return 0;
			}
			if (C[i]<0) {
				puts("-1");
				return 0;
			}
			ans+=Z[i][j];
		} 
		
	}
	BuildGraph();
	MaxFlow();
	return 0;
}
