#include <iostream>
using namespace std;

int main()
{
	freopen("input.txt","w",stdout);
	srand(time(NULL));
	int n = rand()%2000+1;
	cout<<n<<endl;
	for (int i=1;i<=n;i++) cout<<rand()<< " ";
	int m=rand()%1000+1;

	cout<<endl<<m<<endl;
	for (int i=1;i<=m;i++) {
		int l = rand()%n+1;
		int r = rand()%n+1;
		if (l>r) swap(l,r);
		cout<<l<< " "<<r<<endl;
	}
	                      
}