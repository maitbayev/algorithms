#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <ctime> 
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

#define f first
#define s second
#define pb push_back
#define vi vector<int>
#define all(v) (v).begin(), (v).end()
#define sz(v) (int)(v).size()
#define f0(a) memset(a, 0, sizeof(a))
#define ll long long
#define pii pair<int, int>
#define mp make_pair
#define forn(i, a, b) for (int i = (a); i < (b); ++i)

struct Primes {
	int *leastPrime;
	int *primes;
	int primesn;

	Primes(int n) {
		leastPrime = new int[n + 1];
		primes = new int[n + 1];
		primesn = 0;
		for (int i = 2; i <= n; ++i) leastPrime[i] = -1;

		for (int i = 2; i <= n; ++i) {
			if (leastPrime[i] == -1) {
				primes[primesn++] = i;
				leastPrime[i] = primesn - 1;
			}
			for (int j = 0; j <= leastPrime[i]; ++j) {
				long long x = 1ll * primes[j] * i;
				if (x > n) break;
				leastPrime[x] = j;
			}
		}
	}

	vector<pair<int, int>> factorize(int n) {
		vector<pair<int, int>> res;
		while (n > 1) {
			int p = primes[leastPrime[n]];
			if (res.empty() || res.back().first != p) 
				res.push_back({p, 1});
			else 
				res.back().second++;
			n /= p;
		}
		return res;
	}

	bool isPrime(int n) {
		return n >= 2 && n == primes[leastPrime[n]];
	}
};

int main() {
	Primes P = Primes(10);
	assert (P.primesn == 4);
	assert (P.primes[0] == 2);
	assert (P.primes[1] == 3);
	assert (P.primes[1] == 5);
	assert (P.primes[1] == 7);
	return 0;
}
