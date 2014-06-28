#include <cstdio>
#include <vector>
using namespace std;
const int infinity = (1<<30);
int path[551],n,m,q[25010],c[551][551],f[552][551],s,t;
bool u[551];


bool Dfs(int v,int flow)
{
	u[v]=true;
	if (v==t) return flow;
	int i,cur;
        for (i=s;i<=t;i++)
	if (!u[i] && c[v][i] - f[v][i] > 0) {
		cur = Dfs(i, min(c[v][i] - f[v][i],flow));	
		if (cur>0) {
			f[v][i]+=cur;
			f[i][v]-=cur;
			return cur;
		}
	}
	return 0;
}
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	scanf("%d %d",&n,&m);
	int i,x;
	for (i=1;i<=n;i++) {
	        scanf("%d",&x);
		while (x) {
			x+=n;
			c[i][x]=1;
			scanf("%d",&x);
		}
	}
	s=0;
	t=n+m+1;

	for (i=1;i<=n;i++) c[s][i]=1;
	for (i=n+1;i<=n+m;i++) c[i][t]=1;

	int cur,min,cnt;

	for (cnt=0,cur=1;Dfs(s,infinity);memset(u,0,sizeof(u)),cnt++);

	printf("%d\n",cnt);
	int j;
	for (i=1;i<=n;i++)
	for (j=n+1;j<t;j++)
	if (f[i][j]==1) printf("%d %d\n",i,j-n);
}
