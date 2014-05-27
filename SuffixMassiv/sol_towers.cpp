#include <iostream>
using namespace std;

int n, a[100000],p[100000];
#define ULL long long
const ULL base = 107;
ULL hash[200000] , Pow[200000];



bool Equal(int i1,int i2,int len)
{
  	ULL h1 = hash[i1+len-1];
  	if (i1) h1-=hash[i1-1];
  	ULL h2 = hash[i2+len-1];
  	if (i2) h2-=hash[i2-1];
	 
	if (i1<i2) return (h1*Pow[i2-i1] == h2); 
	return (h1 == h2*Pow[i1-i2]);

}

bool op(int ii,int jj)
{
	int l=0,r=n+1;
	while (l<r-1) {
		int m = (l+r)/2;
		if (Equal(ii,jj,m)) l=m; else
		r=m;
	}
	return (a[l+ii] < a[l+jj]);
}

int main()
{
	freopen("towers.in","r",stdin);
	freopen("towers.out","w",stdout);

	while (true) {
		scanf("%d",&n);
		if (!n) break;

		for (int i=0;i<n;i++) scanf("%d",&a[i]) , p[i] = i , a[i]++,a[n+i]=a[i]; 

		Pow[0]=1;
		for (int i=1;i<2*n;i++) Pow[i] = Pow[i-1]*base;	

		
		hash[0] = a[0];
		for (int i=1;i<2*n;i++) hash[i] = hash[i-1] + Pow[i] * a[i];

		sort(p,p+n,op);


		ULL cnt = 0;
		for (int i=1;i<n;i++) {
			int l =0, r=n+1;
			while(l<r-1) {
				int m= (l+r)/2;
				if (Equal(p[i],p[i-1],m)) l=m; else 
				r=m;
			} 
			cnt+=l;
		}
		printf("%I64d\n",cnt);
	}

}
