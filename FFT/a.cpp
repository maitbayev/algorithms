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
#include <complex>
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

typedef complex<double> base;

const int maxn = (int)1e6;
const int maxm = (1<<16);
int a[maxn];
int cnt[maxm], cnta[maxm], cntb[maxm];
ll cntc[maxm];
int n;
int rev[maxn];
base fa[maxm], fb[maxm];
base wlen_pw[maxm];

void fft (base a[],  bool invert) {
	int n = maxm;
	for (int i=0; i<n; ++i)
		if (i < rev[i])
			swap (a[i], a[rev[i]]);
 
	for (int len=2; len<=n; len<<=1) {
		double ang = 2*M_PI/len * (invert?-1:+1);
		int len2 = len>>1;
 
		base wlen (cos(ang), sin(ang));
		wlen_pw[0] = base (1, 0);
		for (int i=1; i<len2; ++i)
			wlen_pw[i] = wlen_pw[i-1] * wlen;

		for (int i=0; i<n; i+=len) {
			base t,
				 *pu = a+i,
				 *pv = a+i+len2, 
				 *pu_end = a+i+len2,
				 *pw = wlen_pw;
			for (; pu!=pu_end; ++pu, ++pv, ++pw) {
				t = *pv * *pw;
				*pv = *pu - t;
				*pu += t;
			}
		}
	}

	if (invert)
		for (int i=0; i<n; ++i)
			a[i] /= n;
}

void calc_rev (int n, int log_n) {
	for (int i=0; i<n; ++i) {
		rev[i] = 0;
		for (int j=0; j<log_n; ++j)
			if (i & (1<<j))
				rev[i] |= 1<<(log_n-1-j);
	}
}
void multiply()
{
	for (int i = 0; i < maxm; ++i) {
		fa[i] = cnta[i]; fb[i] = cntb[i];
	}
	fft(fa, false);
	fft(fb, false);
	    
	for (int i = 0; i < maxm; ++i)
		fa[i] *= fb[i];
	fft(fa, true);
	for (int i = 0; i < maxm; ++i) 
		cntc[i] = (ll)(fa[i].real() + 0.5);
}

int main() {
	calc_rev(maxm, 16);
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	int size = 5000;
	int blocks = (n - 1) / size;

	for (int i = 0; i < n; ++i) 
		cntb[a[i]]++;

	ll ans = 0;

	for (int bl = 0; bl <= blocks; ++bl) {
		int le = bl * size, ri = min(n, (bl + 1) * size);
		for (int i = le; i < ri; ++i)
			cntb[a[i]]--;


		multiply();
		for (int i = le; i < ri; ++i)  {
			if (2 * a[i] < maxm)
				ans += cntc[2 * a[i]];
		}

		for (int i = le; i < ri; ++i) {
			for (int j = i + 1; j < ri; ++j) {
				int d = a[j] - a[i];
				if (a[i] - d >= 0 && a[i] - d < maxm) {
					ans += cnta[a[i] - d];
					ans += cnt[a[i] - d];
				}
				if (a[j] + d >= 0 && a[j] + d < maxm) ans += cntb[a[j] + d];

			}
			cnt[a[i]]++;
		}

		for (int i = le; i < ri; ++i)
			cnt[a[i]] = 0;

		for (int i = le; i < ri; ++i)
			cnta[a[i]]++;
	}
	cout << ans << endl;
	return 0;
}
