#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
using namespace std;
#define pii pair<int,int> 

priority_queue<pii,vector<pii>,greater<pii> > Heap;
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
	Heap.push(pii(0,s));

	int v2,w,sz;
	while (pos!=f){
		pos=Heap.top().second;
		w = Heap.top().first;
		Heap.pop();

		if (w == d[pos]) {
			sz=a[pos].size();
			for (i=0;i<sz;i++) {
				v2 = a[pos][i].first; w=a[pos][i].second;
				if (d[v2]>d[pos]+w) {
					d[v2]=d[pos]+w;
					Heap.push(pii(d[v2],v2));
				}
        		}       	
		}
	}
	printf("%d",d[f]);
	fclose(stdin);
	fclose(stdout);
}
