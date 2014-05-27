#include <iostream>
using namespace std;
int n,a[10000],m;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output2.txt","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);

	scanf("%d",&m);

	for (int j=0;j<m;j++) {
		int l,r;
		scanf("%d %d",&l,&r);
		
		while (l<=r) {
			swap(a[l],a[r]);
			l++;r--;
		}

	}

	for (int i=1;i<=n;i++) printf("%d ",a[i]);

        
	return 0;
}