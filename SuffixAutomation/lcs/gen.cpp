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
	int n = rand()%100+1, m = rand()%100+1;

	for (int i = 0; i < n; ++i)
		putchar(rand()%4+'a');
	putchar('\n');
	for (int i = 0; i < m; ++i)
		putchar(rand()%4+'a');

	return 0;
}
