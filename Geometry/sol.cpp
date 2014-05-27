#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	double x1, y1, x2, y2, ang;

	scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
	double vect = x1 * y2 - y1 * x2;
	double scal = x1 * x2 + y1 * y2;

	ang = atan2(vect,scal);


	printf("%.5f",abs(ang));

	return 0;
}
