#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define pb push_back
const long double eps = 1e-8;

int comp(long double x, long double y) {
	if (fabs(x - y) <= eps) return 0;
	if (x - y > eps) return 1;
	return -1;
}

struct Point {
	long double x,y;
	Point()
	{
		x = y = 0;
	}

	Point(double xx,double yy)
	{
		x = xx; y = yy;
	}

	void read()
	{
		double xx, yy;
		scanf("%lf%lf",&xx,&yy);
		x = xx; y = yy;
	}

	bool operator < (Point a) const {
		if (comp(x, a.x) < 0) return true;
		if (comp(x, a.x) > 0) return false;
		if (comp(y, a.y) < 0) return true;
		if (comp(y, a.y) > 0) return false;
		return false;
	}

	bool operator == (Point a) const {
		return (comp(x, a.x) == 0 && comp(y, a.y) == 0);
	}

	Point operator - (Point a)
	{
		Point res = Point(x - a.x,y - a.y);
		return res;
	}
	Point operator + (Point a) {
		return Point(x + a.x, y + a.y);
	}
	long double operator * (Point a)
	{
		return x*a.y-y*a.x;
	}

	long double scal(Point a)
	{
		return x*a.x+y*a.y;
	}
	
	long double dist(Point a)
	{
		return sqrt((a.x-x)*(a.x-x) + (a.y-y)*(a.y-y));
	}
	
	long double dist()
	{
		return sqrt(x*x+y*y);
	}
	void makeLen(double len) {
		double di = dist();
		x /= di; y /= di;
		x *= len; y *= len;
	}
};

vector<Point> intersect(Point o1, long double r1, Point o2, long double r2) {
	vector<Point> ret;
	long double dist = o1.dist(o2);
	if (comp(dist, r1 + r2) > 0 || comp(fabs(r2 - r1),  dist) > 0) 
		return ret;
	long double x = (r1 * r1 - r2 * r2 + dist * dist)/(2 * dist);
	
	Point ve = o2 - o1;
	ve.makeLen(x);
	ve = ve + o1;

	Point norm = Point(o1.y-o2.y,o2.x-o1.x);
	norm.makeLen(sqrt(r1 * r1 - x * x));
	ret.pb(ve + norm);
	if (norm == Point(0, 0)) 
		return ret;
	ret.pb(ve - norm);
	return ret;
}

int main(){
	Point a, b;
	double r1, r2;
	a.read(); scanf("%lf", &r1);
	b.read(); scanf("%lf", &r2);
	if (a == b && comp(r1, r2) == 0) {
		puts("3");
		return 0;
	}
	vector<Point> points = intersect(a, r1, b, r2);
	cout << points.size() << endl;
	for (int i = 0; i < points.size(); ++i)
		printf("%.6lf %.6lf\n", (double)points[i].x, (double)points[i].y);
	return 0;
}
