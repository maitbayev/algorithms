#include "range_query_tree.hpp"
#include <iostream>
using namespace std;

int main() {
	int n = 4;
	int a[] = {1, 2, 1, 4};
	auto max_query = RangeQueryTree::Max(a, n);
	cout << max_query->calc(1, 3) << endl;
	auto sum_query = RangeQueryTree::Sum(a, n);
	cout << sum_query->calc(1, 3) << endl;

}
