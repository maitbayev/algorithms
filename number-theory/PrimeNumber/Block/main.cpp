#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

#define f first
#define s second
#define mp make_pair
#define pb push_back
const int blockS = 30000;
int npr[1000000], prime[1000000], primecnt, n;

int main() {
	freopen("input.txt", "r", stdin);	
	freopen("output.txt", "w", stdout);
	cin >> n;
	int nsqrt = (int)sqrt(n + 1.0) + 1;
	for (int i = 2; i <= nsqrt; ++i)
		if (!npr[i]) {
			for (int j = i + i; j <= nsqrt; j += i)
				npr[j] = true;
			prime[primecnt++] = i;
		}

	int ans = 0;
	
	for (int k = 0, maxK = n / blockS; k <= maxK; ++k) {
		int start = k * blockS;
		for (int i = 0; i < blockS; ++i)
			npr[i] = false;

		for (int i = 0; i < primecnt; ++i) { 
			for (int j = max((start + prime[i] - 1) / prime[i], 2) * prime[i] - start; j < blockS; j += prime[i])
				npr[j] = true;
		}

		if (k == 0)
			npr[0] = npr[1] = true;
		for (int i = 0; start + i <= n && i < blockS; ++i)
			if (!npr[i])
				ans++;
	}
	cout << ans << endl;
	return 0;
}
