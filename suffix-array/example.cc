#include <string>
#include <iostream>

#include "suffix_tree.hpp"

int main() {
  string s = "aaba";
  vector<int> p = suffixArray(s);
  assert(p.size() == 4);
  assert(p[0] == 3);
  assert(p[1] == 0);
  assert(p[2] == 1);
  assert(p[3] == 2);
  return 0;
}
