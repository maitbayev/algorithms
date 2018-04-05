#include <vector>
using namespace std;

struct PrimeSieve {
	int *isPrime;
	int n;

	PrimeSieve(int n): n(n) {
		isPrime = new int[n / 32 + 1];
		for (int i = 0; i <= n / 32; ++i) isPrime[i] = ~0;
		unset(0); 
		unset(1);
		for (int i = 4; i <= n; i += 2) unset(i);
		
		for (int i = 3; i * i <= n; ++i) if (bit(i)) {
			for (int j = i * i; j <= n; j += 2 * i)
				unset(j);
		}
	}

	inline void unset(int i) {
		isPrime[i >> 5] &= ~(1 << (i & 31));
	}

	inline bool bit(int i) {
		return (isPrime[i >> 5] >> (i & 31)) & 1;
	}

	vector<int> getPrimes() {
		vector<int> primes;
		for (int i = 2; i <= n; ++i) if (bit(i)) {
			primes.push_back(i);
		}
		return primes;
	}

	vector<int> getPrimes(int count) {
		vector<int> primes;
		primes.reserve(count);
		for (int i = 2; i <= n && (int)primes.size() < count; ++i) if (bit(i)) {
			primes.push_back(i);
		}
		assert(primes.size() == count);
		return primes;
	}
};
