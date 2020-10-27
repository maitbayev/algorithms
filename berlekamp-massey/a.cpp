#include <iostream>
#include <vector>
using namespace std;

const int mod = 998244353;

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int modPow(int a, int n) {
  int res = 1;
  while (n > 0) {
    if (n & 1) res = mul(res, a);
    a = mul(a, a);
    n >>= 1;
  }
  return res;
}

void dec(int &x, int delta) {
  x -= delta;
  if (x < 0) x += mod;
}

void inc(int &x, int delta) {
  x += delta;
  if (x >= mod) x -= mod;
}

int sub(int a, int b) {
  a -= b;
  if (a < 0) a += mod;
  return a;
}

vector<int> berlekampMassey(const vector<int> &a) {
  vector<int> c = {1};
  vector<int> b = {1};
  int db = 1; 
  int shift = 0;
  for (int i = 0; i < a.size(); ++i) {
    ++shift;
    int d = 0; 
    for (int j = 0; j < c.size(); ++j) {
      inc(d, mul(c[j], a[i - j]));
    }
    if (d == 0) continue;

    vector<int> cprev = c;
    int coef = mul(d, modPow(db, mod - 2));
    c.resize(max(c.size(), b.size() + shift));
    for (int j = 0; j < b.size(); ++j) {
      dec(c[j + shift], mul(coef, b[j]));
    }
    if (cprev.size() < c.size()) { 
      b = cprev; 
      db = d;
      shift = 0;
    }
  }
  c.erase(c.begin());
  for (int &a : c) {
    if (a > 0) a = mod - a;
  }
  return c;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<int> c = berlekampMassey(a);
  cout << c.size() << endl;
  for (int a : c) cout << a << " ";
}
