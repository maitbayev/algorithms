#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <complex>
#include <vector>

using namespace std;

typedef complex<double> base;

const int maxn = (1<<16);
vector<base> a, b;

int rev(int x,int n) {
	int res = 0;
	for (int i = n-1; i >= 0; --i) {
		res = (res<<1) + (x&1);
		x >>= 1;	
	}
	return res;

}

void fft(vector<base> &a, bool invert) {
	int n = (int)a.size();

	for (int i = 0; i < n; ++i)
		if (i < rev(i, 16))
			swap(a[i], a[rev(i,16)]);

	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2.0 * M_PI / len * (invert ? -1 : 1);
		base w(cos(ang), sin(ang));

		for (int i = 0; i < n; i += len) {
			base wn(1);
		
			for (int j = 0; j < len/2; ++j) {
				base u = a[i + j], v = wn * a[i + j + len/2];
				a[i + j] = u + v;
				a[i + j + len/2] = u - v;
				wn *= w;	
			}	
		} 	
	} 
	if (invert)
		for (int i = 0; i < n; ++i)
			a[i] /= n;
}

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	a.resize(maxn);
	b.resize(maxn);
	
	int n, m; 

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		a[x] = a[x] + base(1);		
	}
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int x;
		scanf("%d", &x);
		b[x] = b[x] + base(1);
	}

	fft(a, false);
	
	fft(b, false);
		
	for (int i = 0; i < maxn; ++i)
		a[i] *= b[i];
	
	fft(a, true);

	for (int i = 0; i < maxn; ++i) {
		long long x = (long long)(a[i].real() + 0.5);
		if (x > 0) printf("%d - %I64d\n", i, x);
	}
	return 0;	
}