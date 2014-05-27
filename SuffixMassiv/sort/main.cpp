#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
char a[100000];
int cnt[100000],p[100000],col[100000],pn[100000],coln[100000];

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	         
	gets(a);
	
	int n = strlen(a);
	a[n++] = 'a'-1;
	
	for (int i = 0; i < n; ++i) {
	        a[i] -= 'a';
	        a[i]++;

		cnt[a[i]]++;
	}


	for (int i = 1; i < 27; ++i)
		cnt[i] += cnt[i-1];

	for (int i = 0; i < n; ++i)
		p[--cnt[a[i]]] = i;

	int cls = 0;
	for (int i = 0; i < n; ++i) {
		if (i > 0 && a[p[i-1]] != a[p[i]]) cls++;
		col[p[i]] = cls;
	}

	for (int h = 1; h < n; h<<=1) {

       		memset(cnt,0,sizeof(cnt));

		for (int i = 0; i < n; ++i) {
			pn[i] = p[i] - h;
			if (pn[i] < 0) pn[i] += n;
			cnt[col[pn[i]]]++;
		}
		
		for (int i = 1; i <= cls; ++i)
			cnt[i] += cnt[i-1];

		for (int i = n-1; i >= 0; --i)
			p[--cnt[col[pn[i]]]] = pn[i];
		
		cls = 0;
		for (int i = 0; i < n; ++i) 
		{
			if (i > 0 && (col[p[i]] != col[p[i-1]] || col[(p[i]+h)%n] != col[(p[i-1]+h)%n])) cls++;
			coln[p[i]] = cls;
		}	

		memcpy(col,coln,sizeof(col));

	}


	for (int i = 1; i < n; ++i)
		printf("%d ",p[i]+1);

	return 0;
}
