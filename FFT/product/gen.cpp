#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>

using namespace std;

void next() {
	int n = rand()%1000+1;
	for (int i = 0; i < n; ++i) {
		if (i == 0)
			cout<<rand()%9+1;
		else
			cout<< rand()%10;
	}
	cout << endl;
}
int main() {
	srand(time(0));
	freopen("input.txt", "w", stdout);
	next(); next();
	return 0;
}