#include <iostream>
#include <fstream> 
#include <sstream> 
#include <array>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <ctime>
#include <iomanip>
using namespace std;

array<long double, 2> cal(long double x1, long double y1, long double x2, long double y2)
{
	long double k = (y2 - y1) / (x2 - x1);
	long double p = x2 - x1 + k*(y1 + y2);
	long double a = k*k + 1;
	long double b = -(2 * y1 + k*p);
	long double c = y1*y1 + p*p / 4 - 4;
	long double y_root = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
	long double x_root = (x1 + x2) / 2 + k*(y1 + y2) / 2 - k*y_root;
	array<long double, 2> root;
	root[0] = x_root;
	root[1] = y_root;
	return root;
}
int main()
{
	int num;
	while (true)
	{
		cin >> num;
		if (num == 0)
			break;
		deque<long double> x;
		x.resize(num);
		for (auto i = 0; i < num; ++i)
			cin >> x[i];
		sort(x.begin(), x.end());
		deque<long double> y;
		y.resize(num);
		for (auto &i : y)
			i = 1.0;
		for (auto i = num; i > 1; --i)
		{
			for (auto j = 0; j < i - 1; ++j)
			{
				array<long double, 2> rslt = cal(x[0], y[0], x[1], y[1]);
				x.push_back(rslt[0]); x.pop_front();
				y.push_back(rslt[1]); y.pop_front();
			}
			x.pop_front(); y.pop_front();
		}
		cout << fixed << showpoint << setprecision(4) << x[0] << " " << y[0] << endl;
	}
	return 0;
}

