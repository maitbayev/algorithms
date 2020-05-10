#include <string>
#include <vector>
using namespace std;

vector<int> suffixArray(const string &s) {
  const int alphabet = 256;
  const int n = s.size();

  vector<int> p(n), c(n), cnt(max(alphabet, n));
  vector<int> pn(n), cn(n);

  for (char c : s) ++cnt[c];
  for (int i = 1; i < alphabet; ++i) cnt[i] += cnt[i - 1];
  for (int i = 0; i < n; ++i) p[--cnt[s[i]]] = i;

  c[p[0]] = 0;
  int classes = 1;
  for (int i = 1; i < n; ++i) {
    if (s[p[i]] != s[p[i - 1]]) ++classes;
    c[p[i]] = classes - 1;
  }

  for (int len = 1; len < n; len *= 2) {
    for (int i = 0; i < n; ++i) {
      pn[i] = p[i] - len;
      if (pn[i] < 0) pn[i] += n;
    }
    fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < n; ++i) ++cnt[c[pn[i]]];
    for (int i = 1; i < classes; ++i) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];

    cn[p[0]] = 0;
    classes = 1;
    for (int i = 1; i < n; ++i) {
      int m1 = (p[i] + len) % n, m2 = (p[i - 1] + len) % n;
      if (c[p[i]] != c[p[i - 1]] || c[m1] != c[m2]) ++classes;
      cn[p[i]] = classes - 1;
    }
    copy(cn.begin(), cn.end(), c.begin());
  }

  return p;
}
