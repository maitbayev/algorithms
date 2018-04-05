#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int maxn = 200000000;
int n, leastPrime[maxn], prime[maxn], primecnt;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
	int n;
	cin >> n;
	for (int i = 2; i <= n; ++i) {
		if (!leastPrime[i]) {
			prime[++primecnt] = i;
			leastPrime[i] = primecnt;		
		}

		for (int j = 1; j <= leastPrime[i]; ++j) {
			int x = prime[j];
			if (x * i > n)
				break;
			leastPrime[x * i] = j;
		}
	}
        
        int ans = 0;
        for (int i = 2; i <= n; ++i)
        	if (prime[leastPrime[i]] == i)
        		ans++;
	cout << ans << endl;
	return 0;
}