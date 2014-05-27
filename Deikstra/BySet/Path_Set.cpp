#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <utility>
using namespace std;
#define pii pair<int,int> 
set<pii> S;
vector<pii> a[10001];

const int inf = (1<<30);
int n,m,s,f,d[20001],l,r,w,min,pos;


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
	S.insert(pii(0,s));

	while (pos!=f){

		pos=(*S.begin()).second;
                S.erase(*S.begin());
		int sz=a[pos].size();
		for (i=0;i<sz;i++) {
			int v2 = a[pos][i].first, w=a[pos][i].second;
			if (d[v2]>d[pos]+w) {
				if (d[v2]!=inf) S.erase(S.find(pii(d[v2],v2)));
				d[v2]=d[pos]+w;
				S.insert(pii(d[v2],v2));
			}
		}
	}
	printf("%d",d[f]);
	fclose(stdin);
	fclose(stdout);
}
