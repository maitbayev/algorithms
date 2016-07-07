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

inline int inv(int a) {
	return modPow(a, mod - 2);
}

void normalize(vi &a) {
	while (sz(a) > 1 && a.back() == 0) a.pop_back();
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
	normalize(fa);
	return fa;
}

vi subtract(vi a, vi b) {
	vi res(max(sz(a), sz(b)));
	for (int i = 0; i < sz(res); ++i) {
		if (i < sz(a)) res[i] = a[i]; else res[i] = 0;
		if (i < sz(b)) res[i] -= b[i];
		if (res[i] < 0) res[i] += mod;
	}
	normalize(res);
	return res;
}


vi add(vi a, vi b) {
	vi res(max(sz(a), sz(b)));
	for (int i = 0; i < sz(res); ++i) {
		if (i < sz(a)) res[i] = a[i]; else res[i] = 0;
		if (i < sz(b)) res[i] += b[i];
		if (res[i] >= mod) res[i] -= mod;
	}
	normalize(res);
	return res;
}

vi inverse(vi a, int n) {
	if (sz(a) > n) a.resize(n);

	if (n == 1) return vi(1, inv(a[0]));
	int t = (n + 1) / 2;
	vi a0 = inverse(a, t);
	vi val = multiply(a, a0);
	val[0]--; if (val[0] < 0) val[0] += mod;
	val = multiply(val, a0);
	val = subtract(a0, val);
	if (sz(val) > n) val.resize(n);
	return val;
}

pair<vi, vi> divide(vi &a, vi &b) {
	int m = sz(a), n = sz(b);
	vi ar(a);
	vi br(b);
	reverse(all(ar));
	reverse(all(br));
	vi bri = inverse(br, m - n + 1);
	vi dr = multiply(ar, bri);
	if (sz(dr) > m - n - 1) dr.resize(m - n + 1);
	vi d(dr);
	reverse(all(d));
	vi r = subtract(a, multiply(d, b));
	normalize(d); normalize(r);
	return mp(d, r);
}

pair<vi, vi> divide_slow(vi a, vi b) {
	vi r(a);
	vi q(sz(a), 0);

	while (sz(r) >= sz(b)) {
		int t = 1ll * r.back() * inv(b.back()) % mod;
		int shift = sz(r) - sz(b);
		q[shift] += t;
		for (int i = 0; i < sz(b); ++i) {
			r[i + shift] -= 1ll * t * b[i] % mod;
			if (r[i + shift] < 0) r[i + shift] += mod;
		}
		normalize(r);
		if (sz(r) == 1 && r[0] == 0) break;
	}
	normalize(q);
	normalize(r);
	return mp(q, r);
}

void read(vi &v) {
	int n;
	scanf("%d", &n); n++;
	v.resize(n);
	for (int i = 0; i < n; ++i) scanf("%d", &v[i]);
}

void write(vi v) {
	for (int i: v) cout << i << " ";
	cout << endl;
}
void solve() {
	vi a, b;
	read(a);
	read(b);
	assert(divide(a, b) == divide_slow(a, b));
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int t = 0; t < tests; ++t)
		solve();
}
