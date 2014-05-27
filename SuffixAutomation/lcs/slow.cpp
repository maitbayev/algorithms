#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
string s,anss,t;
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output2.txt","w",stdout);
	cin>>t>>s;
	
	int ans = -1,rr;

	for (int l = 0; l < s.size(); ++l)
	for (int r = l; r < s.size(); ++r)
	{
		int len = r-l+1;
		string ss = s.substr(l,len);


		bool ok = false;
		for (int i = 0; i < t.size() && !ok; ++i)
			if (ss == t.substr(i,len)) ok = true;

		if (ok && (len > ans || (len == ans && rr > r))) {
			rr = r;
			ans = len;
			anss = ss;
		}
		
	}

	cout<<anss;

	return 0;
}
