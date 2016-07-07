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

const int maxn = (int)1e6;
const int mod = 786433;
const int root = 5;
const int root_1 = 471860;
const int root_pw = 1<<18;


int modPow(int a, int n) {
	int res = 1;
	while (n > 0) {
		if (n & 1) res = 1ll * res * a % mod;
		a = 1ll * a * a % mod;
		n >>= 1;
	}
	return res;
}
void fft (vector<int> & a, bool invert) {
	int n = (int) a.size();
 
	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}
 
	for (int len=2; len<=n; len<<=1) {
		int wlen = invert ? root_1 : root;
		for (int i=len; i<root_pw; i<<=1)
			wlen = int (wlen * 1ll * wlen % mod);
		for (int i=0; i<n; i+=len) {
			int w = 1;
			for (int j=0; j<len/2; ++j) {
				int u = a[i+j],  v = int (a[i+j+len/2] * 1ll * w % mod);
				a[i+j] = u+v < mod ? u+v : u+v-mod;
				a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
				w = int (w * 1ll * wlen % mod);
			}
		}
	}
	if (invert) {
		int nrev = modPow(n, mod - 2);
		for (int i=0; i<n; ++i)
			a[i] = int (a[i] * 1ll * nrev % mod);
	}
}

vi multiply (vi & a, vi & b) {
	vector<int> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max(a.size(), b.size())) n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);
	fft (fa, false),  fft (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] = 1ll * fa[i] * fb[i] % mod;
	fft (fa, true);
	while (sz(fa) > 1 && fa.back() == 0)
		fa.pop_back();
	return fa;
}

void read(vi &v) {
	int n;
	scanf("%d", &n); n++;
	v.resize(n);
	for (int i = 0; i < n; ++i) scanf("%d", &v[i]);
}
void solve() {
	vi a, b;
	read(a); read(b);
	vi res = multiply(a, b);
	for (int i = 0; i < sz(res); ++i) 
		printf("%d ", res[i]);
	puts("");
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int t = 0; t < tests; ++t)
		solve();
}
