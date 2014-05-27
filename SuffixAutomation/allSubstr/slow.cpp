#include <iostream>             	
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define pb push_back
char s[10000];
int l,r,len;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output2.txt","w",stdout);

	scanf("%d\n",&len);
	for (int i = 0; i < len; ++i)
	{
		s[i] = getchar();
	}

	int l,r;
	scanf("%d %d",&l,&r);

	for (int i = 0; i+r-l < len; ++i) {
		bool ok = true;
		for (int j = 0; j <= r-l; ++j)
			if (s[j+l] != s[i+j]) ok = false;
		if (ok) cout<<i<<" ";
	}

}
