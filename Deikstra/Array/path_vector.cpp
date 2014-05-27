#include <cstdio>
#include <vector>
using namespace std;
#define pii pair<int,int>
vector<pii>a[10001];
int n,m,s,f,d[10001],l,r,w,min,pos;
const int inf=(1<<30);
bool used[10001];


int main()
{
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);	
		scanf("%d %d",&n,&m);
		int i;
		for (i=1;i<=m;i++){
			scanf("%d %d %d",&l,&r,&w);
			a[l].push_back(pii(r,w));
			a[r].push_back(pii(l,w));
		}
	scanf("%d %d",&s,&f);
	for (i=1;i<=n;i++)d[i]=inf;
	d[s]=0;
//	used[s]=1;
	while (!used[f]){
		int min=inf;
		for (i=1;i<=n;i++)
		if (!used[i]&&min>d[i]){min=d[i];pos=i;}
		if (min==inf)break;
		used[pos]=true;
	        int sz=a[pos].size();
	        for (i=0;i<sz;i++) {
	        	int v=a[pos][i].first,w=a[pos][i].second;
			if (d[v]>d[pos]+w) d[v]=d[pos]+w;
		}
	}
	printf("%d",d[f]);
	fclose(stdin);
	fclose(stdout);
}
