#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <complex>
#include <vector>

using namespace std;

typedef complex<double> base;

#define pb push_back

vector<int> a, b, c;
char s[10000];
int rev(int x,int n) {
	int res = 0;
	for (int i = 0; i < n; ++i) {
		res = res * 2 + x % 2;
		x /= 2;
	}
	return res;
}

void fft(vector<base> &a, bool invert) {
	int n = a.size();

	int lgn = 0;
	while ((1<<lgn) < n)
		++lgn;

	for (int i = 0; i < n; ++i) {
		int rev1 = rev(i, lgn);
		if (rev1 < i)
			swap(a[rev1], a[i]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * M_PI / len * (invert ? -1 : 1);
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

                       
void multiply(vector<int> &a, vector<int> &b, vector<int> &c)
{
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while (n <= max(a.size(), b.size()))
		n <<= 1;
	n <<= 1;

	fa.resize(n);
	fb.resize(n);

	fft(fa, false);
	fft(fb, false);
	    
	for (int i = 0; i < n; ++i)
		fa[i] *= fb[i];
	fft(fa, true);
	c.resize(n);
	for (int i = 0; i < n; ++i) 
		c[i] = int(fa[i].real() + 0.5);
	
	int carry = 0;

	for (int i = 0; i < n; ++i) {
		carry += c[i];
		c[i] = carry % 10;
		carry /= 10;
	}

}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	gets(s);
	int len = strlen(s);

	for (int i = len - 1; i >= 0; --i)
		a.pb(s[i] - '0');
	
	gets(s);

	len = strlen(s);

	for (int i = len - 1; i >= 0; --i)
		b.pb(s[i] - '0');
	
	multiply(a, b, c);
	while (*c.rbegin() == 0)
		c.pop_back();
	for (int i = (int)c.size() - 1; i >= 0; --i)
		printf("%d", c[i]);
	return 0;
}