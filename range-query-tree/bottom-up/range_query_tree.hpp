#include <functional>
#include <algorithm>
using namespace std;

struct RangeQueryTree {
	int n;
	int *t;
	function<int(int, int)> binOp;

	RangeQueryTree(int *a, int n, function<int(int,int)> op): 
		n(n), binOp(op)  {
		t = new int[n + n];
		for (int i = 0; i < n; ++i)
			t[i + n] = a[i];
		for (int i = n - 1; i >= 0; --i)
			t[i] = binOp(t[i + i], t[i + i + 1]);
	}

	int calc(int l, int r) const {
		l += n; r += n;
		int res;
		bool is_res_set = false;

		auto update = [&res, &is_res_set, this](int value) {
			if (!is_res_set) {
				res = value;
				is_res_set = true;
			}	else {
				res = binOp(res, value);
			}
		};

		while (l <= r) {
			if (l & 1) update(t[l]);
			if (!(r & 1)) update(t[r]);
			l = (l + 1) / 2;
			r = (r - 1) / 2;
		}
		return res;
	}

	static RangeQueryTree* Min(int *a, int n) {	
		return new RangeQueryTree(a, n, [](int a, int b) { return min(a, b); });
	}

	static RangeQueryTree* Max(int *a, int n) {
		return new RangeQueryTree(a, n, [](int a, int b) { return max(a, b); });
	}

	static RangeQueryTree* Sum(int *a, int n) {
		return new RangeQueryTree(a, n, [](int a, int b) { return a + b; } );
	}
};

