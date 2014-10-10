#include <iostream>
#include <cmath>
using namespace std;
const double eps = 1e-9;

struct Point {
	
	double x,y;

	Point() {
		x = y = 0;
	}

	Point(double _x,double _y) {
		x = _x; y= _y;
	}
	
	void read() {
		scanf("%lf%lf", &x, &y);
	}

	Point operator - (Point a) {
		return Point(x - a.x, y - a.y);
	}
	
	Point operator + (Point a) {
		return Point(x + a.x, y + a.y);
	}

	double operator * (Point a) {
		return x * a.y - y * a.x;
	}

	double scal(Point a) {
		return x * a.x + y * a.y;
	}

	double dist() {
		return sqrt(x * x + y * y);
	}
	
	double dist(Point p) {
		return sqrt((p.x-x) * (p.x-x)+ (p.y-y) * (p.y-y));
	}

	void makeLen(double l)
	{
		double dist = sqrt(x*x+y*y);
		x*=l/dist;
		y*=l/dist;
	}

};

struct Line {
	double a,b,c;
	
	Line()
	{
		a=b=c=0;
	}
	
	Line(double _a, double _b, double _c) {
		a = _a; b = _b; c = _c;
	}

	Line(Point p1, Point p2) {
		a = p2.y - p1.y;
		b = p1.x - p2.x;
		c = -(a * p1.x + b * p1.y);
	}

	Point Intersec(Line l) {
		Point p = Point((b*l.c-l.b*c)/(a*l.b-l.a*b) , 
				-(a*l.c-l.a*c)/(a*l.b-l.a*b));
		return p;
	}

	double dist(Point p) {
		return abs(a*p.x+b*p.y+c)/sqrt(a*a+b*b);
	}                                      
};

Point half(Point p, Point q) {
	return Point((p.x + q.x) / 2, (p.y + q.y) / 2);
}
Line getCenterLine(Point p1,Point p2)
{
	Line l = Line(p1, p2);
	Point norm = Point(l.a, l.b);
	Point p = Point((p1.x+p2.x)/2,(p1.y+p2.y)/2);
	return Line(norm + p, p);
}

void getCircle(Point p1, Point p2, Point p3, Point &o, double &r) {
	Line l1 = getCenterLine(p1,p2);
	Line l2 = getCenterLine(p3,p2);
	o = l1.Intersec(l2);
	r = o.dist(p1);
}

int n;
Point p[1000];

void min_disk2(int n, Point a, Point b, Point &circ, double &R) {
	circ = half(a, b);
	R = circ.dist(a);
	for (int i = 0; i < n; ++i) 
		if (R + eps < circ.dist(p[i]))
			getCircle(p[i], a, b, circ, R);
}


void min_disk1(int n, Point a, Point &circ, double &R) {
	circ = half(a, p[0]);
	R = circ.dist(p[0]);
	for (int i = 1; i < n; ++i)
		if (R + eps < circ.dist(p[i])) 
			min_disk2(i, a, p[i], circ, R);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		p[i].read();
	}
	random_shuffle(p, p + n);

	Point circ = half(p[0], p[1]);
	double R = circ.dist(p[0]);

	for (int i = 2; i < n; ++i) 
		if (R + eps < circ.dist(p[i]))
			min_disk1(i, p[i], circ, R);
	printf("%.2lf\n", R * 2);
}
