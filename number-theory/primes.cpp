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

void checkPrimes(int n, vector<int> ans) {
	Primes P = Primes(n);
	(void)P;
	assert (ans.size() == P.primesn);
	for (size_t i = 0; i < ans.size(); ++i) {
		assert (ans[i] == P.primes[i]);
	}

	assert (P.isPrime(ans.back()));
	assert (P.isPrime(ans.back() + 1) == false);
}

void checkLeastPrime(int n, vector<int> ans) {
	Primes P = Primes(n);
	(void)P;

	for (size_t i = 2; i < ans.size(); ++i) {
		assert (ans[i] == P.primes[P.leastPrime[i]]);
	}
}

int main() {
	checkPrimes(20, {2, 3, 5, 7, 11, 13, 17, 19});
	checkLeastPrime(20,
			{-1, -1, 2, 3, 2, 5, 2, 7, 2, 3,
			 2, 11, 2, 13, 2, 3, 2, 17, 2, 19, 2});
	return 0;
}
