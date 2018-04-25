
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const long double PI = 3.14159265358979323846264;


int main()
{
	long double x1, x2, x3, y1, y2, y3;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

	//get the circumcircle
	long double a11 = 2 * (x1 - x2);
	long double a12 = 2 * (y1 - y2);
	long double a21 = 2 * (x2 - x3);
	long double a22 = 2 * (y2 - y3);
	long double b1 = x1*x1 + y1*y1 - x2*x2 - y2*y2;
	long double b2 = x2*x2 + y2*y2 - x3*x3 - y3*y3;
	long double x0 = (b1*a22 - b2*a12) / (a11*a22 - a21*a12);
	long double y0 = (b2*a11 - b1*a21) / (a11*a22 - a21*a12);
	long double r = sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1));
	long double d12 = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	long double d23 = sqrt((x2 - x3)*(x2 - x3) + (y2 - y3)*(y2 - y3));
	long double d31 = sqrt((x3 - x1)*(x3 - x1) + (y3 - y1)*(y3 - y1));
	long double ang12 = 2 * asin(d12 / 2.0000 / r);
	long double ang23 = 2 * asin(d23 / 2.0000 / r);
	long double ang31 = 2 * asin(d31 / 2.0000 / r);

	//calculate the Greatest Common Divisor(GCD) of the three central angles
	vector<long double> ang;
	ang.push_back(ang12); ang.push_back(ang23); ang.push_back(ang31);
	sort(ang.begin(), ang.end());
	long double ang_1st = ang[0], ang_2nd = ang[1];
	while (ang_1st > 0.00001)
	{

		long double temp = ang_1st;
		ang_1st = fmod(ang_2nd, ang_1st);
		ang_2nd = temp;
	}
	long double ang0 = ang_2nd;

	//get the smallest n-polygon
	long double n, m;
	bool found = false;
	for (auto i = 3; i <= 100; ++i)
	{
		long double baseang = 2 * PI / i;
		for (auto j = 1; j <= i; ++j)
		{
			if (abs(j*baseang - ang0) < 0.0001)
			{
				n = i; m = j;
				found = true; break;
			}
		}
		if (found)
			break;
	}
	/*cout << fixed << setprecision(16) << x0 << " " << y0 << " " << r << endl;
	cout << fixed << setprecision(16) << 180 * ang12 / PI << " " << 180 * ang23 / PI << " " << 180 * ang31 / PI << endl;
	cout << fixed << setprecision(16) << 180 * ang0 / PI << " " << n << " " << " " << m << m * 360 / n << endl;*/
	cout << fixed << setprecision(12) << n*0.5*r*r*sin(2 * PI / n) << endl;
	return 0;
}


