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
#define mp make_pair
#define pb push_back
#define pii pair<int, int>
#define vi vector<int>
#define all(v) (v).begin(), (v).end()
#define forit(it,v) for (__typeof(v.begin()) it = v.begin(); it != v.end(); ++it)
#define f0(a) memset(a, 0, sizeof(a))
#define ll long long
#define REP(i,n) for(int i=0;i<n;++i)
typedef complex<double> base;
const int mod = 100003;
const int maxn = (int)3e4;
int n;
int a[maxn];
int pa[maxn], pb[maxn], pc[maxn];

#define REP(i,n) for(int i=0;i<n;++i)

typedef int LL;
void mul(LL a[], int an, LL b[], int bn, LL c[], int &cn) {
  if (an < bn) { swap(an, bn); swap(a, b); }

  if (bn == 0) { cn = 0; return; }
  if (bn == 1) { cn = an; REP(i, cn) c[i] = (1ll * a[i] * b[0]) % mod; return; }
  cn = an + bn - 1;
  memset(c, 0, sizeof(c[0])*cn);

  int m = (an+1)/2, n = min(m, bn), tn1, tn2, tn3;

  LL *al = a, *ah = a+m, *bl = b, *bh = b+m;

  LL tmp1[2*m], tmp2[2*m], tmp3[2*m];

  REP(i, m) {
	  tmp1[i] = al[i] + (i < an-m ? ah[i] : 0);
	  tmp1[i] %= mod;
  }
  REP(i, n) {
	  tmp2[i] = bl[i] + (i < bn-n ? bh[i] : 0);
	  tmp2[i] %= mod;
  }
  mul(tmp1, m, tmp2, n, tmp3, tn3);     // = (al + ah)(bl + bh)
  mul(al, m, bl, n, tmp1, tn1);         // = al bl
  mul(ah, an-m, bh, bn-n, tmp2, tn2);   // = ah bh

  REP(i, tn1) { 
	  c[i] += tmp1[i]; c[i] %= mod;
	  c[i+m] -= tmp1[i];  
	  c[i+m] %= mod;
	  if (c[i+m] < 0) c[i+m] += mod;
  
  }
  REP(i, tn2) { 
	  c[i+2*m] += tmp2[i]; 
	  c[i+2*m] %= mod;
	  c[i+m] -= tmp2[i]; 
	  c[i+m] %= mod;
	  if (c[i+m] < 0) c[i+m] += mod;
  }
  REP(i, tn3) {
	  c[i+m] += tmp3[i];
	  c[i+m] %= mod;
  }
}

vi multiply(vi le, vi ri) {
	vi ret;
	for (int i = 0; i < le.size(); ++i)
		pa[i] = le[i];
	for (int i = 0; i < ri.size(); ++i)
		pb[i] = ri[i];
	int cn;
	mul(pa, le.size(), pb, ri.size(), pc, cn);
	for (int i = 0; i < cn; ++i)
		ret.pb(pc[i]);
	return ret;
}

vi doit(int l, int r) {
	if (l == r) {
		vi ret;
		ret.pb(1);
		ret.pb(a[l]);
		return ret;
	}
	int mid = (l + r) / 2;
	return multiply(doit(l, mid), doit(mid + 1, r));	
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	vi F = doit(0, n - 1);
	int qn;
	scanf("%d", &qn);
	for (int it = 0; it < qn; ++it) {
		int k;
		scanf("%d", &k);
		if (k < F.size())
			printf("%d\n", F[k]);
		else
			printf("%d\n", 0);
	}
	return 0;
}

