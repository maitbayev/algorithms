#include <iostream>
using namespace std;

void GenBig(int len)
{
	int n = rand()%len+1;
	if (rand()&1) putchar('-');
	putchar(rand()%9+'1');
	for (int i = 0; i < n; i++) putchar(rand()%10+'0');
	putchar('\n');

}
int main()
{
	freopen("input.txt","w",stdout);
	srand(time(0));
	GenBig(100);
	GenBig(8);
	return 0;
}
