#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int main()
{

	
	freopen("input.txt","w",stdout);
	srand(time(0));
	int n = rand()%100+1;

	cout<<n<<endl;
	for (int i = 0; i < n; ++i)
		putchar(rand()%4+'a');
	putchar('\n');
	int l = rand()%n,r = rand()%n;
	if (l > r) swap(l,r);
	cout<<l<<" "<<r<<endl;
}
