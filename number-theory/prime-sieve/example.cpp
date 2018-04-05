#include "prime_sieve.hpp"
#include <iostream>
using namespace std;

int main() {
	PrimeSieve sieve = PrimeSieve(20);
	// should print "2 3 5 7 11 13 17 19"
	for (int p: sieve.getPrimes()) {
		cout << p << " ";
	}
}
